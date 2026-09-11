#!/usr/bin/env python3
"""Recover function names in a stripped flash dump by matching reference-build functions.

Usage:
  uv run --with capstone --with pyelftools python3 match_ref_funcs.py \
      --ref-elf refs/ref1011_default.elf --ref-bin refs/ref1011_default.bin \
      --dump dump_a.bin --out dump_symbols.json

Method (pure byte matching, no Ghidra):
  * every STT_FUNC symbol with size >= MIN_SIZE in the reference ELF is disassembled with
    capstone (Thumb-2, Cortex-M);
  * a byte mask is built: BL / BLX / B.W immediates are masked (they encode absolute code
    distance which differs between builds), literal-pool words reached by 'ldr rX,[pc,#imm]'
    are masked, and any 4-byte aligned word whose value looks like a flash / SRAM address is
    masked. Short branches, cbz/cbnz, immediates and register choices are kept;
  * the masked pattern is searched (regex with '.' wildcards) in the dump's code region;
  * matches are then cross-checked: for each BL inside a matched function whose reference
    target is itself a matched function, the dump-side BL target must equal that function's
    dump address. The fraction of consistent calls is reported and used to break ties.

Output: JSON {name: {dump_addr, ref_addr, size, candidates, calls_checked, calls_ok}} plus a
text listing sorted by dump address. Only functions with exactly one surviving candidate are
written. Everything is an inference (byte-shape identity), confidence grows with size and
with calls_ok/calls_checked.
"""
import argparse, json, re, struct, sys

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS
from capstone.arm import ARM_OP_IMM, ARM_OP_MEM, ARM_REG_PC
from elftools.elf.elffile import ELFFile

FLASH_BASE = 0x08000000
MIN_SIZE = 8            # bytes; smaller functions are hopelessly ambiguous
MIN_FIXED = 10          # minimum unmasked bytes for a pattern to count


def looks_like_address(w):
    return (0x08000000 <= w < 0x08040000) or (0x20000000 <= w < 0x20010000)


def build_pattern(code, base, md):
    """Return bytearray mask (1 = fixed, 0 = wildcard) and list of (offset, ref_target) for BLs."""
    n = len(code)
    mask = bytearray([1]) * n
    bl_sites = []
    pool = set()
    off = 0
    # Linear disassembly; capstone stops at undecodable data, then we step 2 bytes and retry.
    while off < n:
        insns = list(md.disasm(code[off:], base + off))
        if not insns:
            off += 2
            continue
        for ins in insns:
            o = ins.address - base
            if ins.mnemonic in ('bl', 'blx') and ins.size == 4 and ins.operands and ins.operands[0].type == ARM_OP_IMM:
                # T1 BL encoding: hw1 = 11110 S imm10, hw2 = 11 J1 1 J2 imm11 -> mask everything but the fixed bits
                mask[o:o + 4] = b'\x00\x00\x00\x00'
                bl_sites.append((o, ins.operands[0].imm))
            elif ins.mnemonic.startswith('b') and ins.size == 4 and ins.mnemonic not in ('bic', 'bics', 'bfi', 'bfc', 'bkpt') and ins.operands and ins.operands[0].type == ARM_OP_IMM:
                # b.w / bcond.w : long branches, may leave the function (tail calls)
                mask[o:o + 4] = b'\x00\x00\x00\x00'
            elif ins.mnemonic in ('ldr', 'ldr.w', 'ldrd', 'vldr') and ins.operands:
                for op in ins.operands:
                    if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC:
                        tgt = ((ins.address + 4) & ~3) + op.mem.disp
                        pool.add(tgt - base)
                        if ins.mnemonic == 'ldrd':
                            pool.add(tgt - base + 4)
        off = insns[-1].address + insns[-1].size - base
    for p in pool:
        if 0 <= p and p + 4 <= n:
            mask[p:p + 4] = b'\x00\x00\x00\x00'
    # any aligned word that looks like an address (catch pool words we failed to see)
    for p in range(((base + 3) & ~3) - base, n - 3, 4):
        w = struct.unpack_from('<I', code, p)[0]
        if looks_like_address(w):
            mask[p:p + 4] = b'\x00\x00\x00\x00'
    return mask, bl_sites


def pattern_regex(code, mask):
    parts = []
    run = bytearray()
    for b, m in zip(code, mask):
        if m:
            run.append(b)
        else:
            if run:
                parts.append(re.escape(bytes(run)))
                run = bytearray()
            parts.append(b'.')
    if run:
        parts.append(re.escape(bytes(run)))
    return re.compile(b''.join(parts), re.DOTALL)


def decode_bl_target(dump, off, addr):
    """Decode the BL/B.W immediate at dump offset `off` located at flash address `addr`."""
    hw1, hw2 = struct.unpack_from('<HH', dump, off)
    if (hw1 & 0xF800) != 0xF000:
        return None
    S = (hw1 >> 10) & 1
    imm10 = hw1 & 0x3FF
    J1 = (hw2 >> 13) & 1
    J2 = (hw2 >> 11) & 1
    imm11 = hw2 & 0x7FF
    if (hw2 & 0xD000) == 0xD000 or (hw2 & 0xD000) == 0x9000:  # BL or B.W (T4)
        I1 = 1 - (S ^ J1)
        I2 = 1 - (S ^ J2)
        imm = (S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1)
        if imm & (1 << 24):
            imm -= 1 << 25
        return addr + 4 + imm
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--ref-elf', required=True)
    ap.add_argument('--ref-bin', required=True)
    ap.add_argument('--dump', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=0x8000)
    ap.add_argument('--code-end', type=lambda x: int(x, 0), default=0x1774C)
    args = ap.parse_args()

    dump = open(args.dump, 'rb').read()
    refbin = open(args.ref_bin, 'rb').read()
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    md.detail = True

    funcs = {}
    with open(args.ref_elf, 'rb') as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name('.symtab')
        for sym in symtab.iter_symbols():
            if sym['st_info']['type'] != 'STT_FUNC' or sym['st_size'] < MIN_SIZE:
                continue
            addr = sym['st_value'] & ~1
            size = sym['st_size']
            off = addr - FLASH_BASE
            if off < 0 or off + size > len(refbin):
                continue
            name = sym.name
            if name in funcs and funcs[name][0] != addr:
                name = '%s@%08x' % (name, addr)
            funcs[name] = (addr, size)

    region = dump[args.code_start:args.code_end]
    results = {}
    ambiguous = {}
    for name, (addr, size) in funcs.items():
        code = refbin[addr - FLASH_BASE: addr - FLASH_BASE + size]
        mask, bls = build_pattern(code, addr, md)
        if sum(mask) < MIN_FIXED:
            continue
        rx = pattern_regex(code, mask)
        cands = [m.start() + args.code_start for m in rx.finditer(region, overlapped=False)] if False else []
        pos = 0
        while True:
            m = rx.search(region, pos)
            if not m:
                break
            cands.append(m.start() + args.code_start)
            pos = m.start() + 2
        if not cands:
            continue
        results[name] = {'ref_addr': addr, 'size': size, 'fixed_bytes': sum(mask), 'candidates': cands, 'bls': bls}

    ref_by_addr = {a: n for n, (a, s) in funcs.items()}

    # Cross-check calls; iterate twice so that late-resolved names help early ones.
    final = {}
    for _ in range(3):
        final = {}
        for name, r in results.items():
            scored = []
            for c in r['candidates']:
                checked = ok = 0
                for (o, ref_tgt) in r['bls']:
                    tname = ref_by_addr.get(ref_tgt & ~1)
                    if tname is None or tname not in results:
                        continue
                    tr = results[tname]
                    dump_tgts = [x for x in tr['candidates']]
                    if len(dump_tgts) != 1 and tname not in final:
                        continue
                    want = final[tname]['dump_addr'] if tname in final else dump_tgts[0]
                    got = decode_bl_target(dump, c + o, FLASH_BASE + c + o)
                    checked += 1
                    if got is not None and (got & ~1) == want:
                        ok += 1
                scored.append((ok - (checked - ok) * 2, ok, checked, c))
            scored.sort(reverse=True)
            best = scored[0]
            if len(scored) > 1 and scored[1][0] == best[0] and best[2] == 0:
                ambiguous[name] = [hex(FLASH_BASE + c) for c in r['candidates']]
                continue
            if best[2] and best[1] * 2 < best[2]:
                ambiguous[name] = ['%s(ok %d/%d)' % (hex(FLASH_BASE + s[3]), s[1], s[2]) for s in scored]
                continue
            final[name] = {'dump_addr': FLASH_BASE + best[3], 'ref_addr': FLASH_BASE + (r['ref_addr'] - FLASH_BASE),
                           'size': r['size'], 'fixed_bytes': r['fixed_bytes'],
                           'candidates': len(r['candidates']), 'calls_checked': best[2], 'calls_ok': best[1]}

    # Call-graph propagation: a byte-matched function's BL sites sit at the same offsets in both
    # builds, so the dump-side target of each site is the function the reference calls there.
    # Names obtained this way are flagged 'propagated' (body not byte-verified). Iterate to a fixpoint.
    all_ref_funcs = {n: (a, s) for n, (a, s) in funcs.items()}
    # also include tiny reference functions (size < MIN_SIZE) as propagation targets
    with open(args.ref_elf, 'rb') as f:
        elf = ELFFile(f)
        for sym in elf.get_section_by_name('.symtab').iter_symbols():
            if sym['st_info']['type'] == 'STT_FUNC' and sym['st_size'] and sym.name not in all_ref_funcs:
                all_ref_funcs[sym.name] = (sym['st_value'] & ~1, sym['st_size'])
    ref_name_by_addr = {a: n for n, (a, s) in all_ref_funcs.items()}
    changed = True
    while changed:
        changed = False
        votes = {}
        for name, r in list(final.items()):
            if r.get('propagated'):
                continue
            rr = results[name]
            c = r['dump_addr'] - FLASH_BASE
            for (o, ref_tgt) in rr['bls']:
                tname = ref_name_by_addr.get(ref_tgt & ~1)
                if tname is None or tname in final:
                    continue
                got = decode_bl_target(dump, c + o, FLASH_BASE + c + o)
                if got is None or not (args.code_start <= (got & ~1) - FLASH_BASE < args.code_end):
                    continue
                votes.setdefault(tname, {}).setdefault(got & ~1, []).append(name)
        for tname, v in votes.items():
            if len(v) != 1:
                ambiguous[tname] = ['propagated-conflict ' + ','.join('%s<-%s' % (hex(a), ','.join(fr)) for a, fr in v.items())]
                continue
            (daddr, callers), = v.items()
            final[tname] = {'dump_addr': daddr, 'ref_addr': all_ref_funcs[tname][0], 'size': all_ref_funcs[tname][1],
                            'fixed_bytes': 0, 'candidates': 0, 'calls_checked': 0, 'calls_ok': 0,
                            'propagated': True, 'named_by': sorted(set(callers))}
            changed = True

    # Detect two names landing on the same dump address (aliases / identical bodies): keep both but flag.
    by_dump = {}
    for n, r in final.items():
        by_dump.setdefault(r['dump_addr'], []).append(n)
    for a, names in by_dump.items():
        if len(names) > 1:
            for n in names:
                final[n]['aliases'] = [x for x in names if x != n]

    out = {'meta': {'ref_elf': args.ref_elf, 'dump': args.dump, 'matched': len(final), 'ref_funcs': len(funcs)},
           'symbols': {n: {k: (hex(v) if k in ('dump_addr', 'ref_addr') else v) for k, v in r.items()} for n, r in final.items()},
           'ambiguous': ambiguous}
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=1, sort_keys=True)
    txt = args.out.rsplit('.', 1)[0] + '.txt'
    with open(txt, 'w') as f:
        f.write('# dump_addr size ref_addr calls_ok/checked cands name\n')
        for n, r in sorted(final.items(), key=lambda kv: kv[1]['dump_addr']):
            f.write('%08x %5d %08x %2d/%-2d %2d %s %s%s\n' % (r['dump_addr'], r['size'], r['ref_addr'], r['calls_ok'],
                                                          r['calls_checked'], r['candidates'],
                                                          'P' if r.get('propagated') else 'M', n,
                                                          (' (alias: %s)' % ','.join(r['aliases'])) if 'aliases' in r else ''))
    print('ref functions: %d, matched uniquely: %d, ambiguous: %d -> %s, %s' % (len(funcs), len(final), len(ambiguous), args.out, txt))


if __name__ == '__main__':
    main()
