#!/usr/bin/env python3
"""refsyms.py  <ref.elf> [-o OUTDIR]  ->  OUTDIR/refsyms_<name>.json

Extract every STT_FUNC symbol (size>0) and every sized STT_OBJECT from a QMK
reference ELF (Thumb-2, Cortex-M4) and build masked signatures for matching
against a raw flash dump built from (nearly) the same sources.

Normalisation (capstone, CS_ARCH_ARM, CS_MODE_THUMB|CS_MODE_MCLASS, detail on):
  * BL / BLX immediates are masked (keep opcode bits: hw1&0xF800, hw2&0xD000).
  * B / B.W / B<cond> / CBZ / CBNZ whose target leaves [func_start, func_end)
    have their immediates masked; intra-function branches are kept verbatim.
  * MOVW / MOVT immediates are masked (Rd kept).
  * Literal-pool words (found via PC-relative LDR/LDRD/VLDR, iterated to a
    fixed point) are treated as data; a word whose value lies in
    0x08000000-0x08040000 (flash) or 0x20000000-0x20010000 (RAM) is masked;
    other constants (peripheral bases 0x4000_0000+, small immediates) are kept.
  * TBB/TBH jump tables directly following the instruction are kept as data.
  * A coarser "skeleton" token list is produced for fuzzy matching:
    mnemonic (".w" stripped) + operand kinds (r/sp/pc/lr, #imm if <256 else I,
    [base,idx,#disp], L for local branch targets, X for external branches,
    bl for calls, DW/DWp for literal words, TBL for jump tables).

Run with:  uv run --with capstone --with pyelftools python3 refsyms.py ref.elf
"""
import argparse
import json
import os
import sys

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS
from capstone.arm import (ARM_OP_REG, ARM_OP_IMM, ARM_OP_MEM, ARM_OP_FP,
                          ARM_OP_CIMM, ARM_OP_PIMM, ARM_OP_SYSREG, ARM_REG_PC,
                          ARM_INS_B, ARM_INS_BL, ARM_INS_BLX, ARM_INS_CBZ,
                          ARM_INS_CBNZ, ARM_INS_PUSH, ARM_INS_POP, ARM_INS_STM,
                          ARM_INS_LDM, ARM_INS_STMDB, ARM_INS_LDMDB, ARM_INS_VPUSH,
                          ARM_INS_VPOP)
from elftools.elf.elffile import ELFFile

FLASH_LO, FLASH_HI = 0x08000000, 0x08040000
RAM_LO, RAM_HI = 0x20000000, 0x20010000
REGLIST_INS = {ARM_INS_PUSH, ARM_INS_POP, ARM_INS_STM, ARM_INS_LDM, ARM_INS_STMDB,
               ARM_INS_LDMDB, ARM_INS_VPUSH, ARM_INS_VPOP}


def in_ptr_range(v):
    return (FLASH_LO <= v < FLASH_HI) or (RAM_LO <= v < RAM_HI)


_md = None


def get_md():
    global _md
    if _md is None:
        _md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        _md.detail = True
    return _md


def _le16(b, i):
    return b[i] | (b[i + 1] << 8)


def _le32(b, i):
    return b[i] | (b[i + 1] << 8) | (b[i + 2] << 16) | (b[i + 3] << 24)


def _branch_target(ins):
    for op in ins.operands:
        if op.type == ARM_OP_IMM:
            return op.imm
    return None


def _mask_for_insn(ins, raw, start, end):
    """Return (mask_bytes, kind, target). mask byte 0xFF = compare, 0 = ignore."""
    size = len(raw)
    hw1 = _le16(raw, 0)
    hw2 = _le16(raw, 2) if size == 4 else None
    m1, m2 = 0xFFFF, 0xFFFF
    kind = 'ins'
    target = None
    if size == 4 and (hw1 & 0xF800) == 0xF000 and hw2 is not None and (hw2 & 0xD000) == 0xD000:
        # BL (T1)
        m1, m2 = 0xF800, 0xD000
        kind = 'call'
        target = _branch_target(ins)
    elif size == 4 and (hw1 & 0xFBF0) in (0xF240, 0xF2C0) and hw2 is not None and (hw2 & 0x8000) == 0:
        # MOVW (0xF240) / MOVT (0xF2C0): mask i, imm4, imm3, imm8; keep Rd
        m1, m2 = 0xFBF0, 0x8F00
        kind = 'movw' if (hw1 & 0xFBF0) == 0xF240 else 'movt'
    elif ins.id == ARM_INS_B:
        target = _branch_target(ins)
        if target is not None and not (start <= target < end):
            kind = 'bout'
            if size == 2:
                if (hw1 & 0xF000) == 0xD000:      # T1 conditional
                    m1 = 0xFF00
                elif (hw1 & 0xF800) == 0xE000:    # T2 unconditional
                    m1 = 0xF800
            else:
                if hw2 is not None and (hw2 & 0x1000):  # T4 unconditional
                    m1, m2 = 0xF800, 0xD000
                else:                                  # T3 conditional
                    m1, m2 = 0xFBC0, 0xD000
        else:
            kind = 'bin'
    elif ins.id in (ARM_INS_CBZ, ARM_INS_CBNZ):
        target = _branch_target(ins)
        if target is not None and not (start <= target < end):
            kind = 'bout'
            m1 = 0xFD07
        else:
            kind = 'bin'
    elif ins.id == ARM_INS_BLX and size == 4:
        m1, m2 = 0xF800, 0xD000
        kind = 'call'
        target = _branch_target(ins)
    mask = bytearray([m1 & 0xFF, (m1 >> 8) & 0xFF])
    if size == 4:
        mask += bytes([m2 & 0xFF, (m2 >> 8) & 0xFF])
    return bytes(mask), kind, target


def _token(ins, kind):
    mn = ins.mnemonic
    if mn.endswith('.w'):
        mn = mn[:-2]
    if kind == 'call':
        return 'bl'
    if kind == 'bout':
        return mn + ' X'
    if ins.id in REGLIST_INS:
        nregs = sum(1 for op in ins.operands if op.type == ARM_OP_REG)
        return '%s{%d}' % (mn, nregs)
    parts = []
    is_branch = ins.id in (ARM_INS_B, ARM_INS_CBZ, ARM_INS_CBNZ)
    for op in ins.operands:
        t = op.type
        if t == ARM_OP_REG:
            r = ins.reg_name(op.reg)
            parts.append(r if r in ('sp', 'pc', 'lr') else 'r')
        elif t == ARM_OP_IMM:
            v = op.imm
            if is_branch:
                parts.append('L')
            elif kind in ('movw', 'movt'):
                parts.append('I')
            elif 0 <= v < 256:
                parts.append('#%d' % v)
            else:
                parts.append('I')
        elif t == ARM_OP_MEM:
            base = ins.reg_name(op.mem.base) if op.mem.base else ''
            if base not in ('sp', 'pc'):
                base = 'r'
            idx = ',r' if op.mem.index else ''
            d = op.mem.disp
            dd = (',#%d' % d) if -256 < d < 256 else ',I'
            parts.append('[%s%s%s]' % (base, idx, dd))
        elif t == ARM_OP_FP:
            parts.append('F')
        elif t in (ARM_OP_CIMM, ARM_OP_PIMM):
            parts.append('C')
        elif t == ARM_OP_SYSREG:
            parts.append('S')
        else:
            parts.append('?')
    return mn + ' ' + ','.join(parts) if parts else mn


def normalize(code, addr, start=None, end=None):
    """Normalise one function body.

    code: bytes of the function, addr: its VMA (even), [start,end): function
    extent used to classify branches (defaults to the code extent).
    Returns dict: masked (bytes, = code & mask), mask (bytes, per-bit: 1 =
    compare bit, 0 = ignore), items (list of (off, size, token)), calls (off, target),
    bouts (off, target), lits (off, value, masked?), tables (off, len).
    """
    n = len(code)
    if start is None:
        start = addr
    if end is None:
        end = addr + n
    md = get_md()
    lit_offs = set()      # offsets (relative) of 4-byte literal words
    tables = {}           # off -> len
    for _ in range(6):
        new_lits = set()
        new_tables = {}
        data_offs = sorted(set(lit_offs) | set(tables))
        pos = 0
        while pos + 1 < n:
            if pos in lit_offs:
                pos += 4
                continue
            if pos in tables:
                pos += tables[pos]
                continue
            stop = n
            for d in data_offs:
                if d > pos:
                    stop = min(stop, d)
                    break
            got = False
            for ins in md.disasm(bytes(code[pos:stop]), addr + pos):
                got = True
                for op in ins.operands:
                    if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC and op.mem.index == 0:
                        disp = op.mem.disp
                        if getattr(op, 'subtracted', False) and disp > 0:
                            disp = -disp
                        tgt = ((ins.address + 4) & ~3) + disp
                        off = tgt - addr
                        width = 4
                        mn = ins.mnemonic
                        if mn.startswith('ldrd') or mn.startswith('strd'):
                            width = 8
                        elif mn.startswith('vldr') and ins.op_str.startswith('d'):
                            width = 8
                        if mn.startswith(('ldr', 'vldr')) and 0 <= off and off + width <= n:
                            for k in range(0, width, 4):
                                new_lits.add(off + k)
                if ins.mnemonic in ('tbb', 'tbh'):
                    base = ins.address + 4
                    boff = base - addr
                    esz = 1 if ins.mnemonic == 'tbb' else 2
                    i = 0
                    min_tgt = end
                    while boff + i * esz + esz <= n and base + i * esz < min_tgt:
                        e = code[boff + i * esz] if esz == 1 else _le16(code, boff + i * esz)
                        t = base + 2 * e
                        if t <= base:
                            break
                        min_tgt = min(min_tgt, t)
                        i += 1
                    tl = i * esz
                    if tl & 1:
                        tl += 1
                    if tl > 0:
                        new_tables[boff] = tl
                pos = ins.address + ins.size - addr
            if not got or pos < stop:
                # undecodable halfword: skip 2 bytes as data
                pos += 2
        changed = False
        if not new_lits <= lit_offs:
            lit_offs |= new_lits
            changed = True
        for k, v in new_tables.items():
            if tables.get(k) != v:
                tables[k] = v
                changed = True
        if not changed:
            break

    # second: emit masked bytes, mask, tokens
    masked = bytearray(code)
    mask = bytearray(b'\xff' * n)
    items = []
    calls = []
    bouts = []
    lits = []
    data_offs = sorted(set(lit_offs) | set(tables))
    pos = 0
    while pos + 1 < n:
        if pos in lit_offs:
            if pos + 4 <= n:
                v = _le32(code, pos)
                if in_ptr_range(v):
                    masked[pos:pos + 4] = b'\0\0\0\0'
                    mask[pos:pos + 4] = b'\0\0\0\0'
                    items.append((pos, 4, 'DWp'))
                    lits.append((pos, v, 1))
                else:
                    items.append((pos, 4, 'DW'))
                    lits.append((pos, v, 0))
                pos += 4
            else:
                items.append((pos, n - pos, 'DW'))
                pos = n
            continue
        if pos in tables:
            tl = tables[pos]
            items.append((pos, tl, 'TBL'))
            pos += tl
            continue
        stop = n
        for d in data_offs:
            if d > pos:
                stop = min(stop, d)
                break
        got = False
        for ins in md.disasm(bytes(code[pos:stop]), addr + pos):
            got = True
            off = ins.address - addr
            raw = code[off:off + ins.size]
            m, kind, target = _mask_for_insn(ins, raw, start, end)
            for k in range(ins.size):
                masked[off + k] &= m[k]
                mask[off + k] = m[k]
            if kind == 'call' and target is not None:
                calls.append((off, target))
            elif kind == 'bout' and target is not None:
                bouts.append((off, target))
            items.append((off, ins.size, _token(ins, kind)))
            pos = off + ins.size
        if not got or pos < stop:
            items.append((pos, 2, 'BAD'))
            pos += 2
    if pos < n:
        items.append((pos, n - pos, 'PAD'))
    return {
        'masked': bytes(masked), 'mask': bytes(mask), 'items': items,
        'calls': calls, 'bouts': bouts, 'lits': lits,
        'tables': sorted(tables.items()),
    }


def mask_pointers_in_data(code, addr):
    """For rodata/data objects: mask 4-byte aligned words that look like pointers."""
    masked = bytearray(code)
    mask = bytearray(b'\xff' * len(code))
    first = (-addr) & 3
    for off in range(first, len(code) - 3, 4):
        v = _le32(code, off)
        if in_ptr_range(v):
            masked[off:off + 4] = b'\0\0\0\0'
            mask[off:off + 4] = b'\0\0\0\0'
    return bytes(masked), bytes(mask)


def load_elf(path):
    f = open(path, 'rb')
    elf = ELFFile(f)
    secs = []
    for s in elf.iter_sections():
        if s['sh_flags'] & 0x2 and s['sh_type'] != 'SHT_NOBITS' and s['sh_size'] > 0:
            secs.append({'name': s.name, 'addr': s['sh_addr'], 'size': s['sh_size'],
                         'offset': s['sh_offset'], 'exec': bool(s['sh_flags'] & 0x4),
                         'write': bool(s['sh_flags'] & 0x1)})
    f.seek(0)
    blob = f.read()
    symtab = elf.get_section_by_name('.symtab')
    syms = []
    for sym in symtab.iter_symbols():
        st = sym['st_info']['type']
        name = sym.name
        if not name or name.startswith('$'):
            continue
        syms.append({'name': name, 'value': sym['st_value'], 'size': sym['st_size'],
                     'type': st, 'bind': sym['st_info']['bind'], 'shndx': sym['st_shndx']})
    return elf, blob, secs, syms


def sec_for(secs, addr):
    for s in secs:
        if s['addr'] <= addr < s['addr'] + s['size']:
            return s
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('elf')
    ap.add_argument('-o', '--outdir', default=None)
    ap.add_argument('--name', default=None)
    args = ap.parse_args()
    name = args.name or os.path.splitext(os.path.basename(args.elf))[0]
    outdir = args.outdir or os.path.dirname(os.path.abspath(args.elf))
    elf, blob, secs, syms = load_elf(args.elf)

    link = {}
    for s in syms:
        if s['name'] in ('__textdata_base__', '__data_base__', '__data_end__', '__bss_base__',
                         '__bss_end__', '__init_array_base__', '__init_array_end__',
                         '__main_thread_stack_base__', '__main_thread_stack_end__',
                         '__process_stack_base__', '__process_stack_end__', '__ram0_init_text__',
                         '__flash0_base__', '__flash0_end__', '__textdata_end__'):
            link[s['name']] = s['value']
    textdata_base = link.get('__textdata_base__')
    data_base = link.get('__data_base__')

    # names at address (functions get Thumb bit cleared)
    names_at = {}
    prio = {}
    for s in syms:
        if s['type'] in ('STT_FUNC', 'STT_OBJECT', 'STT_NOTYPE') and s['shndx'] != 'SHN_UNDEF':
            a = s['value'] & ~1 if s['type'] == 'STT_FUNC' else s['value']
            nm = s['name']
            # rank: real functions/objects first, then globals, then plain names; linker
            # symbols (__x_base__/__x_end__) and local labels (.foo) last
            r = (0 if s['type'] in ('STT_FUNC', 'STT_OBJECT') else 2,
                 0 if s['bind'] == 'STB_GLOBAL' else (1 if s['bind'] == 'STB_WEAK' else 2),
                 1 if (nm.startswith('__') and (nm.endswith('_base__') or nm.endswith('_end__'))) else 0,
                 1 if nm.startswith('.') else 0,
                 1 if nm.startswith('Vector') else 0,
                 nm)
            names_at.setdefault(a, set()).add(nm)
            if nm not in prio or r < prio[nm]:
                prio[nm] = r
    for a in names_at:
        names_at[a] = sorted(names_at[a], key=lambda n: prio[n])

    funcs = []
    seen = set()
    for s in syms:
        if s['type'] != 'STT_FUNC' or s['size'] <= 0:
            continue
        addr = s['value'] & ~1
        size = s['size']
        sec = sec_for(secs, addr)
        if sec is None or not sec['exec']:
            continue
        key = (addr, size, s['name'])
        if key in seen:
            continue
        seen.add(key)
        off = sec['offset'] + (addr - sec['addr'])
        code = blob[off:off + size]
        if len(code) != size:
            continue
        nz = normalize(code, addr, addr, addr + size)
        calls = []
        for (o, t) in nz['calls']:
            calls.append([o, t, names_at.get(t & ~1, [None])[0]])
        bouts = []
        for (o, t) in nz['bouts']:
            bouts.append([o, t, names_at.get(t & ~1, [None])[0]])
        lits = []
        for (o, v, m) in nz['lits']:
            nm = []
            if m:
                nm = list(names_at.get(v & ~1, [])) if (v & 1) else list(names_at.get(v, []))
                if not nm and (v & 1) == 0:
                    nm = list(names_at.get(v & ~1, []))
            lits.append([o, v, m, nm])
        funcs.append({
            'name': s['name'], 'addr': addr, 'size': size, 'bind': s['bind'],
            'section': sec['name'],
            'bytes': code.hex(), 'masked': nz['masked'].hex(), 'mask': nz['mask'].hex(),
            'skel': ';'.join(t for (_, _, t) in nz['items']),
            'skel_offs': [[o, sz] for (o, sz, _) in nz['items']],
            'calls': calls, 'bouts': bouts, 'lits': lits,
            'tables': nz['tables'],
        })
    # size-0 code symbols (assembly routines: _crt0_entry, __port_switch, newlib
    # memchr/strlen..., weak Vector aliases): infer size = distance to the next
    # code symbol, capped, and mark them inferred.
    covered = []
    for f in funcs:
        covered.append((f['addr'], f['addr'] + f['size']))
    covered.sort()

    def is_covered(a):
        for (lo, hi) in covered:
            if lo <= a < hi:
                return True
        return False
    code_addrs = set()
    cands = {}
    for s in syms:
        if s['type'] not in ('STT_FUNC', 'STT_NOTYPE') or s['shndx'] == 'SHN_UNDEF':
            continue
        a = s['value'] & ~1
        sec = sec_for(secs, a)
        if sec is None or not sec['exec']:
            continue
        nm = s['name']
        if nm.startswith('__') and (nm.endswith('_base__') or nm.endswith('_end__')):
            continue
        code_addrs.add(a)
        if s['size'] == 0 and not is_covered(a):
            cands.setdefault(a, []).append((s['bind'] == 'STB_WEAK', nm.startswith('Vector'), nm))
    for f in funcs:
        code_addrs.add(f['addr'])
    code_sorted = sorted(code_addrs)
    for a, names in sorted(cands.items()):
        sec = sec_for(secs, a)
        nxt = None
        for b in code_sorted:
            if b > a:
                nxt = b
                break
        end = min(nxt if nxt else sec['addr'] + sec['size'], sec['addr'] + sec['size'], a + 2048)
        size = end - a
        if size <= 0:
            continue
        names.sort()
        rep = names[0][2]
        off = sec['offset'] + (a - sec['addr'])
        code = blob[off:off + size]
        nz = normalize(code, a, a, a + size)
        calls = [[o, t, names_at.get(t & ~1, [None])[0]] for (o, t) in nz['calls']]
        bouts = [[o, t, names_at.get(t & ~1, [None])[0]] for (o, t) in nz['bouts']]
        lits = []
        for (o, v, m) in nz['lits']:
            nm = []
            if m:
                nm = list(names_at.get(v & ~1, [])) if (v & 1) else list(names_at.get(v, []))
            lits.append([o, v, m, nm])
        funcs.append({
            'name': rep, 'addr': a, 'size': size, 'bind': 'inferred', 'section': sec['name'],
            'aliases': [n[2] for n in names[1:]], 'inferred': True,
            'bytes': code.hex(), 'masked': nz['masked'].hex(), 'mask': nz['mask'].hex(),
            'skel': ';'.join(t for (_, _, t) in nz['items']),
            'skel_offs': [[o, sz] for (o, sz, _) in nz['items']],
            'calls': calls, 'bouts': bouts, 'lits': lits, 'tables': nz['tables'],
        })
    funcs.sort(key=lambda f: (f['addr'], -f['size'], f['name']))

    objs = []
    seen = set()
    for s in syms:
        if s['type'] != 'STT_OBJECT' or s['size'] <= 0:
            continue
        addr = s['value']
        size = s['size']
        sec = sec_for(secs, addr)
        if sec is None:
            continue
        key = (addr, size, s['name'])
        if key in seen:
            continue
        seen.add(key)
        flash_addr = addr
        if sec['write'] and textdata_base is not None and data_base is not None and sec['name'] == '.data':
            flash_addr = textdata_base + (addr - data_base)
        off = sec['offset'] + (addr - sec['addr'])
        data = blob[off:off + size]
        if len(data) != size:
            continue
        masked, mask = mask_pointers_in_data(data, addr)
        objs.append({'name': s['name'], 'addr': addr, 'flash_addr': flash_addr, 'size': size,
                     'section': sec['name'], 'bind': s['bind'], 'bytes': data.hex(),
                     'masked': masked.hex(), 'mask': mask.hex()})
    objs.sort(key=lambda o: (o['flash_addr'], -o['size'], o['name']))

    # vector table (function pointers) for call-site anchoring
    vec = None
    vsec = next((s for s in secs if s['name'] == '.vectors'), None)
    if vsec:
        vb = blob[vsec['offset']:vsec['offset'] + vsec['size']]
        vec = []
        for i in range(0, len(vb) - 3, 4):
            v = _le32(vb, i)
            vec.append([i, v, names_at.get(v & ~1, [None])[0] if v else None])

    out = {
        'elf': os.path.abspath(args.elf), 'name': name, 'sections': secs, 'link': link,
        'names_at': {('0x%08x' % a): n for a, n in names_at.items()},
        'functions': funcs, 'objects': objs, 'vectors': vec,
    }
    outpath = os.path.join(outdir, 'refsyms_%s.json' % name)
    with open(outpath, 'w') as f:
        json.dump(out, f)
    tot = sum(f['size'] for f in funcs)
    ninf = sum(1 for f in funcs if f.get('inferred'))
    print('%s: %d functions (%d bytes; %d with inferred size), %d objects -> %s' % (name, len(funcs), tot, ninf, len(objs), outpath))


if __name__ == '__main__':
    main()
