#!/usr/bin/env python3
"""fw_funcs.py -- capstone-based function-boundary detection and per-function
feature extraction for a flat Thumb-2 (Cortex-M4) firmware image.

Run with:  uv run --with capstone python3 fw_funcs.py <image.bin> [--base 0x08000000]
           [--code-start 0x8000] [--code-end 0x...] [--image-end 0x...] [--json out.json]

Algorithm (see functions_linkorder.md for the write-up):
  1. iterative linear sweep with capstone; pc-relative literal loads (ldr/ldrd/vldr/adr)
     and tbb/tbh jump tables mark data bytes; the sweep restarts after each data range,
     iterated to convergence so mis-decoded pool words never corrupt the following code.
  2. hard entry points = vector table entries + BL targets + odd pointer words found
     anywhere in the image (rodata / .data-init / literal pools) that land on a decoded
     instruction start.
  3. function boundaries: a hard entry always starts a function; otherwise a function
     ends at an unconditional terminal (pop{..pc}, bx lr, b/b.w, ldr pc, udf, bl noreturn)
     that has no pending forward branch target from inside the function; trailing pool
     words / padding attach to the function that owns them.
  4. features: size, BL fan-out, push prologue, peripheral constants (pool words and
     movw/movt pairs), referenced rodata content tokens and strings, RAM refs.
"""
import sys, struct, json, argparse
import capstone as cs
from capstone.arm import (ARM_OP_IMM, ARM_OP_MEM, ARM_OP_REG, ARM_REG_PC, ARM_REG_LR, ARM_REG_SP,
                          ARM_CC_AL, ARM_CC_INVALID, ARM_INS_B, ARM_INS_BL, ARM_INS_BLX, ARM_INS_BX,
                          ARM_INS_POP, ARM_INS_LDM, ARM_INS_LDR, ARM_INS_UDF, ARM_INS_PUSH, ARM_INS_STMDB,
                          ARM_INS_TBB, ARM_INS_TBH, ARM_INS_ADR, ARM_INS_MOVW, ARM_INS_MOVT, ARM_INS_MOV,
                          ARM_INS_CBZ, ARM_INS_CBNZ, ARM_INS_SUB, ARM_INS_LDRD, ARM_INS_VLDR, ARM_INS_IT,
                          ARM_INS_NOP, ARM_INS_SVC, ARM_INS_STR, ARM_INS_CMP, ARM_INS_STRD, ARM_INS_LDRB,
                          ARM_INS_LDRH, ARM_INS_LDRSB, ARM_INS_LDRSH, ARM_INS_STRB, ARM_INS_STRH)

PERIPH_RANGES = [(0x40000000, 0x60000000), (0xE0000000, 0xE0100000)]


def in_periph(v):
    return any(lo <= v < hi for lo, hi in PERIPH_RANGES)


class Insn:
    __slots__ = ('addr', 'size', 'id', 'mn', 'ops', 'cc', 'target', 'pool', 'pool_size', 'writes_pc',
                 'is_bl', 'is_uncond_b', 'is_cond_b', 'push_like', 'imm', 'tb', 'bytes')

    def __repr__(self):
        return f"{self.addr:08x} {self.mn} {self.ops}"


class Analyzer:
    def __init__(self, data, base=0x08000000, code_start=0x8000, code_end=None, image_end=None):
        self.data = data
        self.base = base
        self.code_start = base + code_start
        self.image_end = base + (image_end if image_end is not None else len(data))
        self.code_end = base + code_end if code_end is not None else self.image_end
        self.md = cs.Cs(cs.CS_ARCH_ARM, cs.CS_MODE_THUMB | cs.CS_MODE_MCLASS)
        self.md.detail = True
        self.insns = {}        # addr -> Insn
        self.data_ranges = {}  # start -> (end, kind)
        self.entries = {}      # addr -> set(kinds)
        self.funcs = []        # list of dicts

    # ---------------------------------------------------------------- helpers
    def u32(self, a):
        o = a - self.base
        return struct.unpack_from('<I', self.data, o)[0]

    def u16(self, a):
        o = a - self.base
        return struct.unpack_from('<H', self.data, o)[0]

    def in_code(self, a):
        return self.code_start <= a < self.code_end

    def in_image(self, a):
        return self.base <= a < self.image_end

    def is_data(self, a):
        # data ranges are few thousand; use sorted list for speed
        import bisect
        keys = self._dkeys
        i = bisect.bisect_right(keys, a) - 1
        if i >= 0:
            s = keys[i]
            e, _ = self.data_ranges[s]
            if s <= a < e:
                return True
        return False

    def _data_kind(self, a):
        import bisect
        i = bisect.bisect_right(self._dkeys, a) - 1
        if i >= 0:
            s = self._dkeys[i]; e, k = self.data_ranges[s]
            if s <= a < e:
                return k
        return None

    def table_targets(self, n):
        """Intra-function targets of a tbb/tbh/adr-jump-table instruction."""
        out = []
        if n.tb:
            tbl = n.addr + n.size
            if tbl in self.data_ranges:
                e, k = self.data_ranges[tbl]
                width = 1 if k == 'tbb' else 2
                for ea in range(tbl, e, width):
                    v = self.data[ea - self.base] if width == 1 else self.u16(ea)
                    out.append(tbl + 2 * v)
        elif n.id == ARM_INS_ADR and n.pool is not None and n.pool in self.data_ranges and self.data_ranges[n.pool][1] == 'jtab':
            e, _ = self.data_ranges[n.pool]
            for ea in range(n.pool, e, 4):
                out.append(self.u32(ea) & ~1)
        return out

    def _rebuild_dkeys(self):
        self._dkeys = sorted(self.data_ranges)

    # ------------------------------------------------------------- decoding
    def decode_insn(self, i):
        n = Insn()
        n.addr = i.address; n.size = i.size; n.id = i.id; n.mn = i.mnemonic; n.ops = i.op_str
        n.bytes = bytes(i.bytes)
        n.cc = i.cc
        n.target = None; n.pool = None; n.pool_size = 0; n.writes_pc = False
        n.is_bl = False; n.is_uncond_b = False; n.is_cond_b = False; n.push_like = False; n.imm = None; n.tb = None
        cond = i.cc not in (ARM_CC_AL, ARM_CC_INVALID)
        if i.id in (ARM_INS_BL, ARM_INS_BLX):
            for op in i.operands:
                if op.type == ARM_OP_IMM:
                    n.target = op.imm & ~1
            n.is_bl = True
        elif i.id in (ARM_INS_B, ARM_INS_CBZ, ARM_INS_CBNZ):
            for op in i.operands:
                if op.type == ARM_OP_IMM:
                    n.target = op.imm & ~1
            if i.id == ARM_INS_B and not cond:
                n.is_uncond_b = True
            else:
                n.is_cond_b = True
        elif i.id in (ARM_INS_POP, ARM_INS_LDM):
            try:
                _, w = i.regs_access()
                if ARM_REG_PC in w:
                    n.writes_pc = True
            except Exception:
                if 'pc' in i.op_str:
                    n.writes_pc = True
        elif i.id == ARM_INS_BX:
            n.writes_pc = True
        elif i.id in (ARM_INS_LDR, ARM_INS_MOV):
            ops = i.operands
            if ops and ops[0].type == ARM_OP_REG and ops[0].reg == ARM_REG_PC:
                n.writes_pc = True
        if i.id in (ARM_INS_PUSH,) or (i.id == ARM_INS_STMDB and i.op_str.startswith('sp!')):
            n.push_like = True
        if i.id == ARM_INS_SUB and i.op_str.startswith('sp,'):
            n.push_like = True
        # pc-relative literal loads
        if i.id in (ARM_INS_LDR, ARM_INS_LDRD, ARM_INS_VLDR, ARM_INS_LDRB, ARM_INS_LDRH, ARM_INS_LDRSB, ARM_INS_LDRSH):
            for op in i.operands:
                if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC and op.mem.index == 0:
                    pc = (i.address + 4) & ~3
                    n.pool = pc + op.mem.disp
                    n.pool_size = 8 if i.id in (ARM_INS_LDRD,) or (i.id == ARM_INS_VLDR and 'd' in i.op_str.split(',')[0]) else 4
                    if i.id in (ARM_INS_LDRB, ARM_INS_LDRSB):
                        n.pool_size = 1
                    elif i.id in (ARM_INS_LDRH, ARM_INS_LDRSH):
                        n.pool_size = 2
        if i.id == ARM_INS_ADR:
            for op in i.operands:
                if op.type == ARM_OP_IMM:
                    pc = (i.address + 4) & ~3
                    n.pool = pc + op.imm
                    n.pool_size = 0  # unknown size table (adr); only used as a reference
        if i.id in (ARM_INS_TBB, ARM_INS_TBH):
            n.tb = 'tbb' if i.id == ARM_INS_TBB else 'tbh'
        if i.id in (ARM_INS_MOVW, ARM_INS_MOVT, ARM_INS_MOV, ARM_INS_CMP):
            for op in i.operands:
                if op.type == ARM_OP_IMM:
                    n.imm = op.imm
        return n

    def sweep_segment(self, start, end):
        """Linear decode of [start,end) skipping already-known data ranges."""
        a = start
        while a < end:
            if self.is_data(a):
                import bisect
                i = bisect.bisect_right(self._dkeys, a) - 1
                a = self.data_ranges[self._dkeys[i]][0]
                a = (a + 1) & ~1
                continue
            # next data start
            import bisect
            j = bisect.bisect_right(self._dkeys, a)
            seg_end = self._dkeys[j] if j < len(self._dkeys) else end
            seg_end = min(seg_end, end)
            off = a - self.base
            chunk = self.data[off:seg_end - self.base]
            got = False
            for i in self.md.disasm(chunk, a):
                got = True
                n = self.decode_insn(i)
                self.insns[n.addr] = n
                a = n.addr + n.size
            if not got:
                # undecodable halfword: mark as data-ish and step
                self.insns[a] = self.mk_bad(a)
                a += 2
            elif a < seg_end:
                # decoder stopped early (invalid); record bad and skip 2
                self.insns[a] = self.mk_bad(a)
                a += 2

    def mk_bad(self, a):
        n = Insn()
        n.addr = a; n.size = 2; n.id = -1; n.mn = '<bad>'; n.ops = f"0x{self.u16(a):04x}"; n.cc = ARM_CC_AL
        n.bytes = self.data[a - self.base:a - self.base + 2]
        n.target = None; n.pool = None; n.pool_size = 0; n.writes_pc = False
        n.is_bl = False; n.is_uncond_b = False; n.is_cond_b = False; n.push_like = False; n.imm = None; n.tb = None
        return n

    def collect_data_ranges(self):
        """From current instruction set, derive literal pool words and jump tables."""
        new = 0
        for n in list(self.insns.values()):
            if n.pool is not None and n.pool_size:
                s = n.pool; e = n.pool + n.pool_size
                if self.in_code(s) and s not in self.data_ranges:
                    self.data_ranges[s] = (e, 'pool')
                    new += 1
                elif self.in_code(s) and self.data_ranges[s][0] < e:
                    self.data_ranges[s] = (e, 'pool')
            if n.tb:
                tbl = n.addr + n.size
                width = 1 if n.tb == 'tbb' else 2
                mn = None; k = 0
                while True:
                    ea = tbl + k * width
                    if ea + width > self.code_end or (mn is not None and ea >= mn) or k >= 256:
                        break
                    v = self.data[ea - self.base] if width == 1 else self.u16(ea)
                    t = tbl + 2 * v
                    if t <= ea:        # pad byte / impossible target -> table ended
                        break
                    mn = t if mn is None else min(mn, t)
                    k += 1
                if mn is not None and mn > tbl:
                    e = mn
                    if tbl not in self.data_ranges or self.data_ranges[tbl][0] < e:
                        self.data_ranges[tbl] = (e, n.tb)
                        new += 1
            if n.id == ARM_INS_ADR and n.pool is not None and self.in_code(n.pool):
                # word jump table: consecutive odd in-code pointers close to the table
                tbl = n.pool; k = 0
                while tbl + 4 * k + 4 <= self.code_end and k < 256:
                    v = self.u32(tbl + 4 * k)
                    if not (v & 1) or not self.in_code(v - 1) or abs((v - 1) - tbl) > 0x1000:
                        break
                    k += 1
                if k >= 2:
                    e = tbl + 4 * k
                    if tbl not in self.data_ranges or self.data_ranges[tbl][0] < e:
                        self.data_ranges[tbl] = (e, 'jtab')
                        new += 1
        self._rebuild_dkeys()
        return new

    def analyze(self, max_iter=12):
        """Fixpoint: data ranges are derived from the instructions decoded with the
        previous data ranges; iterate until the derived set stops changing."""
        self.data_ranges = {}
        self._rebuild_dkeys()
        prev = None
        for it in range(max_iter):
            self.insns = {}
            self.sweep_segment(self.code_start, self.code_end)
            old_ranges = self.data_ranges
            self.data_ranges = {}
            self._rebuild_dkeys()
            self.collect_data_ranges()
            cur = frozenset((s, e, k) for s, (e, k) in self.data_ranges.items())
            if prev is not None and cur == prev:
                break
            if prev is not None and it >= max_iter - 2:
                # oscillation guard: keep only ranges present in both of the last two sets
                keep = cur & prev
                self.data_ranges = {s: (e, k) for s, e, k in keep}
                self._rebuild_dkeys()
            prev = cur
        self.insns = {}
        self.sweep_segment(self.code_start, self.code_end)
        self.iterations = it + 1
        self.find_entries()
        self.split_functions()
        self.features()
        return self

    def dump_range(self, lo, hi):
        starts = {f['start'] for f in self.funcs}
        a = lo
        while a < hi:
            if self.is_data(a):
                k = self._data_kind(a)
                print(f"  {a:08x}  [{k}] .word 0x{self.u32(a):08x}")
                a += 4 if k != 'tbb' and k != 'tbh' else 2
                continue
            n = self.insns.get(a)
            if n is None:
                a += 2; continue
            flags = []
            if a in starts: flags.append('FUNC')
            if a in self.entries: flags.append('entry:' + ','.join(sorted(self.entries[a])))
            tt = self.table_targets(n)
            if tt: flags.append('tbl->' + ','.join(f"{t:x}" for t in tt[:6]))
            print(f"  {a:08x}  {n.bytes.hex():10s} {n.mn:8s} {n.ops:32s} {' '.join(flags)}")
            a += n.size

    # -------------------------------------------------------------- entries
    def find_entries(self):
        E = {}
        def add(a, kind):
            if a in self.insns and not self.is_data(a):
                E.setdefault(a, set()).add(kind)
        # vector table
        for off in range(4, 0x1e0, 4):
            v = self.u32(self.base + off)
            if v & 1 and self.in_code(v - 1):
                add(v - 1, 'vector')
        # BL targets
        for n in self.insns.values():
            if n.is_bl and n.target is not None and self.in_code(n.target):
                add(n.target, 'bl')
        # pointer words anywhere in the image (rodata, .data init, pools)
        for a in range(self.code_start, self.image_end - 3, 4):
            v = self.u32(a)
            if v & 1 and self.in_code(v - 1):
                # reject words that sit inside decoded code unless they are in a data range
                inside_code_insn = (a in self.insns) or ((a - 2) in self.insns and self.insns[a - 2].size == 4)
                if self.in_code(a) and inside_code_insn and not self.is_data(a):
                    continue
                if self.in_code(a) and self._data_kind(a) in ('jtab', 'tbb', 'tbh'):
                    continue
                add(v - 1, 'ptr')
        self.entries = E

    # ------------------------------------------------------- function split
    def split_functions(self):
        import bisect
        addrs = sorted(self.insns)
        ekeys = sorted(self.entries)
        # noreturn detection: BL targets whose next instruction is a hard entry or a push
        callsites = {}
        for a in addrs:
            n = self.insns[a]
            if n.is_bl and n.target in self.entries:
                nxt = a + n.size
                while nxt in self.insns and self.insns[nxt].mn == 'nop':
                    nxt += self.insns[nxt].size
                nn = self.insns.get(nxt)
                after_entry = (nxt in self.entries) or (nn is not None and nn.push_like) or self.is_data(nxt)
                c = callsites.setdefault(n.target, [0, 0])
                c[0] += 1
                c[1] += 1 if after_entry else 0
        self.noreturn = {t for t, (tot, ent) in callsites.items() if tot >= 2 and ent / tot >= 0.75}
        # walk
        funcs = []
        cur = None
        pending = -1
        after_term = False
        for a in addrs:
            n = self.insns[a]
            hard = a in self.entries
            if cur is None:
                cur = a; pending = -1; after_term = False
            elif hard or (after_term and not self._is_padding(n)):
                # close current function at a
                funcs.append((cur, a))
                cur = a; pending = -1; after_term = False
            elif after_term:
                # padding after a terminal: attach to previous function
                continue
            # branch bookkeeping: forward targets are intra-function unless a hard entry lies between
            tgts = []
            if n.target is not None and not n.is_bl and self.in_code(n.target):
                tgts.append(n.target)
            tgts.extend(self.table_targets(n))
            for t in tgts:
                if t > a and t not in self.entries and (t - a) < 0x1000:
                    j = bisect.bisect_right(ekeys, a)
                    if j < len(ekeys) and ekeys[j] <= t:
                        continue   # crosses a hard entry: tail call
                    pending = max(pending, t)
            term = False
            if n.cc in (ARM_CC_AL, ARM_CC_INVALID):
                if n.writes_pc or n.is_uncond_b or n.id == ARM_INS_UDF:
                    term = True
                if n.is_bl and n.target in self.noreturn:
                    term = True
            if term and pending <= a:
                after_term = True
        if cur is not None:
            funcs.append((cur, self.code_end))
        # trim: function end = start of next function; keep data ranges attached
        self.func_ranges = funcs

    def _is_padding(self, n):
        if n.mn == 'nop':
            return True
        if n.id == -1:
            return True
        if n.bytes == b'\x00\x00':
            return True
        return False

    # -------------------------------------------------------------- features
    def features(self):
        out = []
        for (s, e) in self.func_ranges:
            f = dict(start=s, end=e, size=e - s)
            kinds = self.entries.get(s, set())
            f['entry'] = ','.join(sorted(kinds))
            bl = []; consts = set(); rams = set(); rodata_refs = []; strings = []; imms = []
            n_insn = 0; last_movw = {}
            first = self.insns.get(s)
            f['push'] = bool(first and first.push_like)
            a = s
            term_seen = False
            while a < e:
                n = self.insns.get(a)
                if n is None:
                    a += 2; continue
                n_insn += 1
                if n.is_bl and n.target is not None:
                    bl.append(n.target)
                if n.pool is not None and n.pool_size == 4 and self.in_image(n.pool):
                    v = self.u32(n.pool)
                    self._classify_const(v, consts, rams, rodata_refs, strings)
                if n.id == ARM_INS_MOVW and n.imm is not None:
                    reg = n.ops.split(',')[0]
                    last_movw[reg] = n.imm
                elif n.id == ARM_INS_MOVT and n.imm is not None:
                    reg = n.ops.split(',')[0]
                    if reg in last_movw:
                        v = (n.imm << 16) | (last_movw[reg] & 0xffff)
                        self._classify_const(v, consts, rams, rodata_refs, strings)
                        imms.append(v)
                if n.id in (ARM_INS_CMP, ARM_INS_MOVW, ARM_INS_MOV) and n.imm is not None and n.imm > 0xff:
                    imms.append(n.imm)
                a += n.size
            f['n_insn'] = n_insn
            f['bl'] = bl
            f['n_bl'] = len(bl)
            f['consts'] = sorted(consts)
            f['n_ram'] = len(rams)
            f['rodata'] = rodata_refs
            f['strings'] = strings
            f['imms'] = sorted(set(imms))
            out.append(f)
        self.funcs = out

    def _classify_const(self, v, consts, rams, rodata_refs, strings):
        if in_periph(v):
            consts.add(v)
        elif 0x20000000 <= v < 0x20010000:
            rams.add(v)
        elif self.in_image(v) and v >= self.code_end:
            # rodata content token: 16 bytes at target
            o = v - self.base
            blob = self.data[o:o + 16]
            txt = self._as_string(o)
            if txt is not None:
                strings.append(txt)
            else:
                rodata_refs.append(blob.hex())

    def _as_string(self, o):
        b = self.data[o:o + 64]
        s = bytearray()
        for c in b:
            if c == 0:
                break
            if 32 <= c < 127 or c in (9, 10, 13):
                s.append(c)
            else:
                return None
        if len(s) >= 3:
            return s.decode()
        return None

    # ------------------------------------------------------------------ io
    def to_json(self):
        return dict(base=self.base, code_start=self.code_start, code_end=self.code_end, image_end=self.image_end,
                    funcs=self.funcs, entries={f"{a:#x}": sorted(k) for a, k in self.entries.items()},
                    noreturn=sorted(f"{a:#x}" for a in self.noreturn),
                    data_ranges={f"{s:#x}": [e, k] for s, (e, k) in self.data_ranges.items()})


def find_code_end(an):
    """Estimate .text end: end of the last function that is a hard entry (BL/ptr/vector target)."""
    last = None
    for (s, e) in an.func_ranges:
        if s in an.entries:
            last = (s, e)
    return last


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('image')
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=0x8000)
    ap.add_argument('--code-end', type=lambda x: int(x, 0), default=None)
    ap.add_argument('--image-end', type=lambda x: int(x, 0), default=None)
    ap.add_argument('--json', default=None)
    ap.add_argument('--dump-range', default=None, help='lo:hi hex addresses to print')
    args = ap.parse_args()
    data = open(args.image, 'rb').read()
    an = Analyzer(data, args.base, args.code_start, args.code_end, args.image_end).analyze()
    print(f"iterations: {an.iterations}  instructions: {len(an.insns)}  data ranges: {len(an.data_ranges)}  entries: {len(an.entries)}  functions: {len(an.funcs)}  noreturn: {[hex(x) for x in sorted(an.noreturn)]}")
    if args.json:
        json.dump(an.to_json(), open(args.json, 'w'), indent=1)
    if args.dump_range:
        lo, hi = [int(x, 16) for x in args.dump_range.split(':')]
        an.dump_range(lo, hi)
        return
    for f in an.funcs[:20]:
        print(f"{f['start']:08x} {f['size']:5d} entry={f['entry']:10s} push={f['push']} bl={f['n_bl']} consts={[hex(c) for c in f['consts']]} strings={f['strings'][:2]}")


if __name__ == '__main__':
    main()
