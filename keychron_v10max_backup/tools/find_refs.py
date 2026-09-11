#!/usr/bin/env python3
"""Code anchors for a QMK flash dump: keymap accessors, encoder map, DIP switch, keychron tables,
tap-dance actions, leader sequences, process_record_user. Capstone only (no Ghidra).

Run from the fork worktree root (so the QMK keycode spec can be loaded for names):
  cd /Users/dexter/code/qmk-keychron
  uv run --with capstone --with hjson --with jsonschema --with milc python3 \
      keychron_v10max_backup/tools/find_refs.py keychron_v10max_backup/dump_a.bin \
      --symbols keychron_v10max_backup/dump_symbols.json --json keychron_v10max_backup/code_anchors.json

Everything printed is derived from the dump bytes; addresses are flash addresses (file offset =
addr - 0x08000000). Function boundaries are heuristic: starts are BL targets, matched symbols and
plausible Thumb function pointers; a function extends to the next start.
"""
import argparse, bisect, json, os, re, struct, sys
from collections import Counter, defaultdict

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS
from capstone.arm import ARM_OP_IMM, ARM_OP_REG, ARM_OP_MEM, ARM_REG_PC, ARM_REG_SP

FLASH = 0x08000000
RAM = 0x20000000

# ----------------------------------------------------------------------------- keycode names
KEYCHRON_KB = {0x7E00: 'KC_LOPTN', 0x7E01: 'KC_ROPTN', 0x7E02: 'KC_LCMMD', 0x7E03: 'KC_RCMMD', 0x7E04: 'KC_MCTRL',
               0x7E05: 'KC_LNPAD', 0x7E06: 'KC_TASK', 0x7E07: 'KC_FILE', 0x7E08: 'KC_SNAP', 0x7E09: 'KC_CTANA',
               0x7E0A: 'KC_SIRI', 0x7E0B: 'BT_HST1', 0x7E0C: 'BT_HST2', 0x7E0D: 'BT_HST3', 0x7E0E: 'P2P4G', 0x7E0F: 'BAT_LVL'}
FALLBACK_BASIC = {0: 'KC_NO', 1: 'KC_TRNS', 0x04: 'KC_A', 0x05: 'KC_B', 0x06: 'KC_C', 0x07: 'KC_D', 0x08: 'KC_E', 0x09: 'KC_F',
                  0x0A: 'KC_G', 0x0B: 'KC_H', 0x0C: 'KC_I', 0x0D: 'KC_J', 0x0E: 'KC_K', 0x0F: 'KC_L', 0x10: 'KC_M', 0x11: 'KC_N',
                  0x12: 'KC_O', 0x13: 'KC_P', 0x14: 'KC_Q', 0x15: 'KC_R', 0x16: 'KC_S', 0x17: 'KC_T', 0x18: 'KC_U', 0x19: 'KC_V',
                  0x1A: 'KC_W', 0x1B: 'KC_X', 0x1C: 'KC_Y', 0x1D: 'KC_Z', 0x28: 'KC_ENTER', 0x29: 'KC_ESCAPE', 0x2A: 'KC_BACKSPACE',
                  0x2B: 'KC_TAB', 0x2C: 'KC_SPACE', 0x34: 'KC_QUOTE', 0x37: 'KC_DOT', 0x38: 'KC_SLASH', 0x39: 'KC_CAPS_LOCK',
                  0x4C: 'KC_DELETE', 0x4F: 'KC_RIGHT', 0x50: 'KC_LEFT', 0x51: 'KC_DOWN', 0x52: 'KC_UP',
                  0xA9: 'KC_AUDIO_VOL_UP', 0xAA: 'KC_AUDIO_VOL_DOWN', 0xE0: 'KC_LEFT_CTRL', 0xE1: 'KC_LEFT_SHIFT',
                  0xE2: 'KC_LEFT_ALT', 0xE3: 'KC_LEFT_GUI', 0xE4: 'KC_RIGHT_CTRL', 0xE5: 'KC_RIGHT_SHIFT', 0xE6: 'KC_RIGHT_ALT',
                  0xE7: 'KC_RIGHT_GUI', 0x7827: 'RGB_VAI', 0x7828: 'RGB_VAD', 0x7820: 'RGB_TOG', 0x7C58: 'QK_LEADER'}
SPEC = None


def load_qmk_spec(qmk_root):
    global SPEC
    try:
        sys.path.insert(0, os.path.join(qmk_root, 'lib', 'python'))
        cwd = os.getcwd()
        os.chdir(qmk_root)
        from qmk.keycodes import load_spec
        s = load_spec('0.0.3')
        os.chdir(cwd)
        SPEC = {int(k, 16): v['key'] for k, v in s['keycodes'].items()}
    except Exception as e:  # pragma: no cover
        print('# keycode spec not loaded (%s); using fallback names' % e)
        SPEC = None


def kc_name(kc):
    tbl = SPEC if SPEC else FALLBACK_BASIC
    if kc in tbl:
        return tbl[kc]
    if kc in KEYCHRON_KB:
        return KEYCHRON_KB[kc]
    if 0x0100 <= kc <= 0x1FFF:
        m = (kc >> 8) & 0x1F
        base = tbl.get(kc & 0xFF, '0x%02X' % (kc & 0xFF))
        names = [n for bit, n in ((1, 'LCTL'), (2, 'LSFT'), (4, 'LALT'), (8, 'LGUI')) if m & bit]
        if m & 0x10:
            names = ['R' + n[1:] for n in names]
        for n in names:
            base = '%s(%s)' % (n, base)
        return base
    for lo, nm in ((0x5200, 'TO'), (0x5220, 'MO'), (0x5240, 'DF'), (0x5260, 'TG'), (0x5280, 'OSL'), (0x52A0, 'OSM'), (0x52C0, 'TT')):
        if lo <= kc < lo + 0x20:
            if nm == 'OSM':
                mods = [n for bit, n in ((1, 'MOD_LCTL'), (2, 'MOD_LSFT'), (4, 'MOD_LALT'), (8, 'MOD_LGUI')) if kc & bit]
                if kc & 0x10:
                    mods = [n.replace('MOD_L', 'MOD_R') for n in mods]
                return 'OSM(%s)' % '|'.join(mods)
            return '%s(%d)' % (nm, kc & 0x1F)
    if 0x5700 <= kc <= 0x57FF:
        return 'TD(%d)' % (kc & 0xFF)
    if 0x7700 <= kc <= 0x777F:
        return 'MC_%d' % (kc & 0x7F)
    if 0x7E40 <= kc <= 0x7E7F:
        return 'QK_USER_%d' % (kc - 0x7E40)
    return '0x%04X' % kc


# ----------------------------------------------------------------------------- image + disassembler
class Image:
    def __init__(self, path, code_start, rodata_end):
        self.d = open(path, 'rb').read()
        self.code_start = code_start
        self.rodata_end = rodata_end

    def u32(self, off):
        return struct.unpack_from('<I', self.d, off)[0]

    def u16(self, off):
        return struct.unpack_from('<H', self.d, off)[0]

    def word(self, addr):
        return self.u32(addr - FLASH)

    def find_words(self, pred, lo, hi):
        return [FLASH + o for o in range(lo & ~3, hi - 3, 4) if pred(self.u32(o))]


class Analyzer:
    def __init__(self, img, syms, text_end, verbose=False):
        self.img = img
        self.d = img.d
        self.text_end = text_end
        self.names = dict(syms)           # addr -> name
        self.ram_names = {}
        self.verbose = verbose
        self.md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        self.md.detail = True
        self.md.skipdata = True
        self.insns = []
        self.bl_sites = defaultdict(list)   # target -> [site addr]
        self.bw_sites = defaultdict(list)   # b.w (tail call) target -> [site]
        self.ldr_lit = {}                   # site addr -> pool addr
        self.movwt = {}                     # site addr (movt) -> value
        self.sweep()
        self.build_functions()

    # -- linear sweep ----------------------------------------------------------------------------
    def sweep(self):
        base = FLASH + self.img.code_start
        code = self.d[self.img.code_start:self.text_end]
        pending = {}
        for ins in self.md.disasm(code, base):
            self.insns.append(ins)
            if ins.id == 0:
                continue
            m = ins.mnemonic
            ops = ins.operands
            if m in ('bl', 'blx') and ops and ops[0].type == ARM_OP_IMM:
                self.bl_sites[ops[0].imm & ~1].append(ins.address)
            elif m == 'b.w' and ops and ops[0].type == ARM_OP_IMM:
                self.bw_sites[ops[0].imm & ~1].append(ins.address)
            elif m in ('ldr', 'ldr.w') and len(ops) == 2 and ops[1].type == ARM_OP_MEM and ops[1].mem.base == ARM_REG_PC:
                self.ldr_lit[ins.address] = ((ins.address + 4) & ~3) + ops[1].mem.disp
            elif m in ('movw', 'movt') and len(ops) == 2 and ops[1].type == ARM_OP_IMM:
                r = ops[0].reg
                if m == 'movw':
                    pending[r] = (ops[1].imm, ins.address)
                elif r in pending:
                    lo, a = pending.pop(r)
                    self.movwt[ins.address] = (ops[1].imm << 16) | lo

    def ends_before(self, off):
        """True if a function plausibly ends right before file offset `off`."""
        if off < self.img.code_start + 4:
            return False
        prev = self.img.u16(off - 2)
        if prev == 0x4770 or prev == 0xBF00 or (prev & 0xFF00) == 0xBD00 or (prev & 0xF800) == 0xE000:
            return True
        p2 = self.img.u16(off - 4)
        if (p2 & 0xF800) == 0xF000 and (prev & 0xD000) == 0x9000:      # b.w
            return True
        if (p2 & 0xFFD0) == 0xE8BD and (prev & 0x8000):                 # ldmia.w sp!, {..pc}
            return True
        w = self.img.u32(off - 4)
        if (FLASH <= w < FLASH + 0x40000) or (RAM <= w < RAM + 0x20000):  # literal pool word
            return True
        if prev == 0x0000:                                              # alignment padding
            return self.ends_before(off - 2)
        return False

    def plausible_start(self, addr):
        off = addr - FLASH
        if off < self.img.code_start + 2 or off >= self.text_end:
            return False
        return self.ends_before(off)

    def build_functions(self):
        starts = set(self.bl_sites.keys())
        starts |= {t for t in self.bw_sites if self.plausible_start(t)}
        starts |= {a for a in self.names if FLASH + self.img.code_start <= a < FLASH + self.text_end}
        # function pointers anywhere in the image (vector table, literal pools, rodata, .data init image)
        lo, hi = FLASH + self.img.code_start, FLASH + self.text_end
        for o in range(0, self.img.rodata_end - 3, 4):
            w = self.img.u32(o)
            if (w & 1) and lo < w < hi and self.plausible_start(w & ~1):
                starts.add(w & ~1)
        for o in range(self.img.rodata_end, len(self.d) - 3, 4):
            w = self.img.u32(o)
            if (w & 1) and lo < w < hi and self.plausible_start(w & ~1):
                starts.add(w & ~1)
        starts = {s for s in starts if lo <= s < hi}
        starts.add(lo)
        self.starts = sorted(starts)

    def func_of(self, addr):
        addr &= ~1
        i = bisect.bisect_right(self.starts, addr) - 1
        s = self.starts[i]
        e = self.starts[i + 1] if i + 1 < len(self.starts) else FLASH + self.text_end
        return s, e

    # -- naming --------------------------------------------------------------------------------
    def name(self, addr):
        a = addr & ~1
        return self.names.get(a, 'sub_%08x' % a)

    def set_name(self, addr, nm):
        a = addr & ~1
        if a in self.names and self.names[a] != nm:
            nm = '%s|%s' % (self.names[a], nm)
        self.names[a] = nm

    def ram_name(self, a):
        return self.ram_names.get(a, 'ram_%08x' % a)

    def describe_word(self, w):
        if FLASH + self.img.code_start <= (w & ~1) < FLASH + self.text_end and (w & 1):
            return '&%s' % self.name(w)
        if FLASH <= w < FLASH + len(self.d):
            return 'flash %s' % self.rodata_name(w)
        if RAM <= w < RAM + 0x20000:
            return self.ram_name(w)
        if 0x40000000 <= w < 0x60000000:
            return 'periph'
        return ''

    def rodata_name(self, w):
        return self.names.get(w, 'rodata_%08x' % w)

    # -- xrefs ---------------------------------------------------------------------------------
    def xrefs(self, addr):
        a = addr & ~1
        res = []
        if a == 0:
            return res
        for s in self.bl_sites.get(a, []):
            res.append(('bl', s, self.func_of(s)[0]))
        for s in self.bw_sites.get(a, []):
            res.append(('b.w', s, self.func_of(s)[0]))
        for o in range(0, len(self.d) - 3, 4):
            w = self.img.u32(o)
            if (w & ~1) == a and (w & 1):
                res.append(('ptr', FLASH + o, None))
        return res

    def literal_refs(self, value, lo=None, hi=None):
        lo = self.img.code_start if lo is None else lo
        hi = self.img.rodata_end if hi is None else hi
        out = [FLASH + o for o in range(lo & ~3, hi - 3, 4) if self.img.u32(o) == value]
        out += [FLASH + o for o in range(lo | 2, hi - 3, 4) if self.img.u32(o) == value]
        return sorted(out)

    def literal_refs_range(self, lo_v, hi_v):
        return [(FLASH + o, self.img.u32(o)) for o in range(self.img.code_start & ~3, self.img.rodata_end - 3, 4)
                if lo_v <= self.img.u32(o) < hi_v]

    def movwt_refs(self, lo_v, hi_v):
        return [(a, v) for a, v in self.movwt.items() if lo_v <= v < hi_v]

    # -- disassembly printer ---------------------------------------------------------------------
    def disasm(self, start, end=None, title=None):
        start &= ~1
        s, e = self.func_of(start)
        if end is None:
            end = e
        start = s if start == s else start
        pool = set()
        # pass 1: collect literal pool words inside range
        for ins in self.md.disasm(self.d[start - FLASH:end - FLASH], start):
            if ins.id and ins.mnemonic in ('ldr', 'ldr.w', 'ldrd') and len(ins.operands) >= 2:
                op = ins.operands[-1]
                if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC:
                    t = ((ins.address + 4) & ~3) + op.mem.disp
                    pool.add(t)
                    if ins.mnemonic == 'ldrd':
                        pool.add(t + 4)
        lines = []
        hdr = '---- %s @ %08x..%08x (%d bytes)%s' % (self.name(start), start, end, end - start, (' : ' + title) if title else '')
        lines.append(hdr)
        a = start
        pending = {}
        while a < end:
            if a in pool and a + 4 <= end:
                w = self.img.word(a)
                lines.append('  %08x:  .word 0x%08x    ; %s' % (a, w, self.describe_word(w)))
                a += 4
                continue
            insl = list(self.md.disasm(self.d[a - FLASH:min(a + 4, end) - FLASH], a, count=1))
            if not insl:
                a += 2
                continue
            ins = insl[0]
            note = ''
            m = ins.mnemonic
            ops = ins.operands
            if ins.id:
                if m in ('bl', 'blx', 'b.w', 'b', 'bx') and ops and ops[0].type == ARM_OP_IMM:
                    t = ops[0].imm
                    if not (start <= t < end):
                        note = '<%s>' % self.name(t)
                elif m.startswith('b') and ops and ops[0].type == ARM_OP_IMM and not (start <= ops[0].imm < end) and m not in ('bic', 'bfi', 'bfc', 'bics'):
                    note = '<%s>' % self.name(ops[0].imm)
                elif m in ('ldr', 'ldr.w') and len(ops) == 2 and ops[1].type == ARM_OP_MEM and ops[1].mem.base == ARM_REG_PC:
                    t = ((ins.address + 4) & ~3) + ops[1].mem.disp
                    if t + 4 <= len(self.d) + FLASH:
                        w = self.img.word(t)
                        note = '= 0x%08x %s' % (w, self.describe_word(w))
                elif m == 'movw' and len(ops) == 2 and ops[1].type == ARM_OP_IMM:
                    pending[ops[0].reg] = ops[1].imm
                    v = ops[1].imm
                    if 0x0100 <= v <= 0x7FFF or v in FALLBACK_BASIC:
                        note = '; kc %s' % kc_name(v)
                elif m == 'movt' and len(ops) == 2 and ops[1].type == ARM_OP_IMM and ops[0].reg in pending:
                    v = (ops[1].imm << 16) | pending.pop(ops[0].reg)
                    note = '= 0x%08x %s' % (v, self.describe_word(v))
                elif m in ('movs', 'mov', 'mov.w', 'cmp', 'cmp.w') and len(ops) == 2 and ops[1].type == ARM_OP_IMM:
                    v = ops[1].imm
                    if 4 <= v <= 0xE7 or 0x0100 <= v <= 0x7FFF:
                        note = '; %s' % kc_name(v)
            lines.append(('  %08x:  %-8s %-28s %s' % (ins.address, ins.mnemonic, ins.op_str, note)).rstrip())
            a += ins.size
        return lines

    def print_func(self, addr, title=None, end=None):
        for l in self.disasm(addr, end=end, title=title):
            print(l)

    def imm_ops(self, start, end=None, mnems=('cmp', 'cmp.w')):
        s, e = self.func_of(start)
        end = end or e
        out = []
        for ins in self.md.disasm(self.d[start - FLASH:end - FLASH], start):
            if ins.id and ins.mnemonic in mnems and len(ins.operands) == 2 and ins.operands[1].type == ARM_OP_IMM:
                out.append((ins.address, ins.reg_name(ins.operands[0].reg), ins.operands[1].imm))
        return out

    def func_insns(self, start, end=None):
        start &= ~1
        s, e = self.func_of(start)
        end = end or e
        raw = [i for i in self.md.disasm(self.d[start - FLASH:end - FLASH], start) if i.id]
        pool = set()
        for i in raw:
            if i.mnemonic in ('ldr', 'ldr.w', 'ldrd') and len(i.operands) >= 2:
                op = i.operands[-1]
                if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC:
                    t = ((i.address + 4) & ~3) + op.mem.disp
                    pool.update((t, t + 2))
                    if i.mnemonic == 'ldrd':
                        pool.update((t + 4, t + 6))
        return [i for i in raw if i.address not in pool and bytes(i.bytes) != b'\x00\x00']

    def bl_targets_in(self, start, end=None):
        return [(i.address, i.operands[0].imm & ~1) for i in self.func_insns(start, end)
                if i.mnemonic in ('bl', 'b.w') and i.operands and i.operands[0].type == ARM_OP_IMM
                and not (self.func_of(start)[0] <= i.operands[0].imm < (end or self.func_of(start)[1]))]

    def pool_words(self, start, end=None):
        out = []
        for i in self.func_insns(start, end):
            if i.mnemonic in ('ldr', 'ldr.w') and len(i.operands) == 2 and i.operands[1].type == ARM_OP_MEM and i.operands[1].mem.base == ARM_REG_PC:
                t = ((i.address + 4) & ~3) + i.operands[1].mem.disp
                out.append((i.address, t, self.img.word(t)))
        return out


# ----------------------------------------------------------------------------- helpers
def parse_crt0(img):
    """Return dict with __textdata_base__, __data_base__, __data_end__, __bss_base__, __bss_end__, main."""
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    md.detail = True
    res = {}
    insns = list(md.disasm(img.d[0x8000:0x80e0], FLASH + 0x8000))
    lits = []
    for i, ins in enumerate(insns):
        if ins.mnemonic == 'ldr' and ins.operands[1].type == ARM_OP_MEM and ins.operands[1].mem.base == ARM_REG_PC:
            t = ((ins.address + 4) & ~3) + ins.operands[1].mem.disp
            lits.append((ins.address, ins.reg_name(ins.operands[0].reg), img.word(t)))
        if ins.mnemonic == 'bl' and i > 0 and insns[i - 1].mnemonic == 'b' and False:
            pass
    # dloop: consecutive ldr r1 / ldr r2 / ldr r3 followed by a cmp r2,r3 ; bloop: ldr r1 / ldr r2 after movs r0,#0
    for k in range(len(lits) - 2):
        (a1, r1, v1), (a2, r2, v2), (a3, r3, v3) = lits[k], lits[k + 1], lits[k + 2]
        if (r1, r2, r3) == ('r1', 'r2', 'r3') and FLASH <= v1 < FLASH + 0x40000 and RAM <= v2 <= v3 < RAM + 0x20000:
            res['__textdata_base__'], res['__data_base__'], res['__data_end__'] = v1, v2, v3
            res['dloop_ldr_addrs'] = (a1, a2, a3)
            if k + 4 < len(lits) and lits[k + 3][1] == 'r1' and lits[k + 4][1] == 'r2':
                res['__bss_base__'], res['__bss_end__'] = lits[k + 3][2], lits[k + 4][2]
            break
    for ins in insns:
        if ins.mnemonic == 'msr' and 'msp' in ins.op_str.lower():
            pass
    # main: the bl right after the init-array loop (blx r1 ; b.n ; bl main)
    for i, ins in enumerate(insns):
        if ins.mnemonic == 'bl' and i >= 2 and insns[i - 1].mnemonic == 'b' and insns[i - 2].mnemonic == 'blx':
            res['main'] = ins.operands[0].imm
    return res


def hexs(b):
    return ' '.join('%02x' % x for x in b)


# ----------------------------------------------------------------------------- analyses
def analysis_keymap(an, KM, layer_bytes, facts):
    print('\n' + '=' * 100 + '\n[1] KEYMAP TABLE REFERENCES  (keymaps[] expected @ 0x%08x)' % KM)
    hits = an.literal_refs_range(KM, KM + 6 * layer_bytes)
    mw = an.movwt_refs(KM, KM + 6 * layer_bytes)
    print('literal-pool words pointing into [0x%08x,0x%08x): %s' % (KM, KM + 6 * layer_bytes, ['0x%08x=0x%08x' % h for h in hits] or 'none'))
    print('movw/movt sequences composing such a value: %s' % (['0x%08x=0x%08x' % h for h in mw] or 'none'))
    facts['keymap_literal_refs'] = ['0x%08x' % a for a, v in hits]
    seen = set()
    for a, v in hits + mw:
        s, e = an.func_of(a)
        if s in seen:
            continue
        seen.add(s)
        cmps = an.imm_ops(s)
        movs = an.imm_ops(s, mnems=('movs', 'mov', 'mov.w'))
        muls = [i for i in an.func_insns(s) if i.mnemonic in ('muls', 'mul', 'mla', 'lsls', 'lsl.w', 'add.w')]
        print('\nenclosing function of literal 0x%08x: %s [0x%08x..0x%08x)' % (a, an.name(s), s, e))
        print('  cmp immediates : %s' % ', '.join('%s#%d@%08x' % (r, v_, ad) for ad, r, v_ in cmps))
        print('  mov immediates : %s' % ', '.join('%s#%d@%08x' % (r, v_, ad) for ad, r, v_ in movs))
        print('  multiplies     : %s' % ', '.join('%s %s@%08x' % (i.mnemonic, i.op_str, i.address) for i in muls))
        by_reg = {}
        for ad, r, v_ in cmps:
            by_reg.setdefault(r, v_)
        if {'r0', 'r1', 'r2'} <= set(by_reg):
            L, R, C = by_reg['r0'] + 1, by_reg['r1'] + 1, by_reg['r2'] + 1
            mulc = [v_ for ad, r, v_ in movs if v_ in (R * C, C, R * C * 2)]
            print('  => bounds: layer < %d, row < %d, col < %d ; row stride const %s (expect %d = rows*cols) ; col const %s (expect %d)' %
                  (L, R, C, [m for m in mulc if m != C], R * C, [m for m in mulc if m == C], C))
            if 216 // 2 == R * C or layer_bytes == R * C * 2:
                print('  => layer_bytes = %d*%d*2 = %d  matches keymaps[] stride %d' % (R, C, R * C * 2, layer_bytes))
            an.set_name(s, 'keycode_at_keymap_location_raw')
            facts['keycode_at_keymap_location_raw'] = {'addr': '0x%08x' % s, 'layers': L, 'rows': R, 'cols': C,
                                                       'literal_at': '0x%08x' % a, 'literal_value': '0x%08x' % v}
            # weak wrapper: b.w to this function
            for site in an.bw_sites.get(s, []):
                ws, we = an.func_of(site)
                if ws == site:
                    an.set_name(ws, 'keycode_at_keymap_location')
                    facts['keycode_at_keymap_location'] = '0x%08x' % ws
            # callers
            print('  xrefs of raw: %s' % ', '.join('%s@%08x in %s' % (k, sa, an.name(f) if f else '-') for k, sa, f in an.xrefs(s)))
            wrap = next((k for k, v2 in an.names.items() if v2 == 'keycode_at_keymap_location'), None)
            if wrap:
                print('  xrefs of wrapper keycode_at_keymap_location @0x%08x: %s' % (wrap, ', '.join('%s@%08x in %s' % (k, sa, an.name(f) if f else '-') for k, sa, f in an.xrefs(wrap))))
        an.print_func(s)
    # any 'movs r0,#6 ; bx lr'
    lc = [m.start() + FLASH for m in re.finditer(b'\x06\x20\x70\x47', an.d[an.img.code_start:an.text_end])]
    lc = [x + an.img.code_start for x in lc]
    print('\n"movs r0,#6 ; bx lr" (keymap_layer_count_raw shape) occurrences: %s' % ['0x%08x' % x for x in lc])
    for x in lc:
        s, e = an.func_of(x)
        xr = an.xrefs(x)
        print('  0x%08x: function %s [%08x..%08x) xrefs=%s' % (x, an.name(s), s, e, ['%s@%08x(%s)' % (k, sa, an.name(f) if f else '-') for k, sa, f in xr]))
    facts['movs_r0_6_bx_lr'] = ['0x%08x' % x for x in lc]


def analysis_encoder(an, KM, facts):
    print('\n' + '=' * 100 + '\n[2] ENCODER')
    # (a) keycode_at_encodermap_location_raw shape: cmp r0,#N ; bhi ; cbnz r1 ; eor.w r2,r2,#1 ; ldr r3,[pc] ; add.w ; ldrh.w
    found = None
    for m in re.finditer(rb'[\x00-\x1f]\x28[\x00-\xff]\xd8\x39\xb9\x82\xf0\x01\x02', an.d[an.img.code_start:an.text_end]):
        a = FLASH + an.img.code_start + m.start()
        s, e = an.func_of(a)
        layers = an.d[an.img.code_start + m.start()] + 1
        pw = an.pool_words(s)
        tbl = pw[0][2] if pw else None
        print('keycode_at_encodermap_location_raw shape at 0x%08x (function %s): cmp r0,#%d -> %d layers; cbnz r1 -> 1 encoder; eor clockwise^1; table literal = %s' %
              (a, an.name(s), layers - 1, layers, '0x%08x' % tbl if tbl else '?'))
        an.set_name(s, 'keycode_at_encodermap_location_raw')
        an.print_func(s)
        for site in an.bw_sites.get(s, []):
            ws, we = an.func_of(site)
            if ws == site:
                an.set_name(ws, 'keycode_at_encodermap_location')
                print('  weak wrapper keycode_at_encodermap_location = 0x%08x ; its xrefs: %s' % (ws, ['%s@%08x in %s' % (k, sa, an.name(f) if f else '-') for k, sa, f in an.xrefs(ws)]))
        if tbl:
            found = (s, layers, tbl)
            an.names[tbl] = 'encoder_map'
            rows = []
            for L in range(layers):
                cw, ccw = an.img.u16(tbl - FLASH + L * 4), an.img.u16(tbl - FLASH + L * 4 + 2)
                rows.append({'layer': L, 'cw': '0x%04x' % cw, 'ccw': '0x%04x' % ccw, 'cw_name': kc_name(cw), 'ccw_name': kc_name(ccw)})
                print('  encoder_map[%d] @0x%08x = {0x%04x, 0x%04x}  -> index[0]=clockwise %-22s index[1]=counter-clockwise %-22s  == ENCODER_CCW_CW(%s, %s)' %
                      (L, tbl + L * 4, cw, ccw, kc_name(cw), kc_name(ccw), kc_name(ccw), kc_name(cw)))
            print('  table spans 0x%08x..0x%08x (%d bytes); keymaps[] begins at 0x%08x -> %s' %
                  (tbl, tbl + layers * 4, layers * 4, KM, 'contiguous, encoder_map immediately precedes keymaps[]' if tbl + layers * 4 == KM else 'gap %d' % (KM - tbl - layers * 4)))
            facts['encoder_map'] = {'addr': '0x%08x' % tbl, 'layers': layers, 'entries': rows, 'accessor': '0x%08x' % s}
    if not found:
        print('no keycode_at_encodermap_location_raw shape found')
    # (b) brute-force rodata scan for 6x2 u16 tables of plausible paired keycodes
    print('\nrodata scan for 6-layer x {cw,ccw} u16 tables (pairs differ by 1 or both zero, >=3 non-zero pairs):')
    def plausible(k):
        return k == 0 or 4 <= k <= 0xE7 or 0x7820 <= k <= 0x7830 or 0x00A5 <= k <= 0x00DF
    cands = []
    for o in range(an.text_end & ~1, an.img.rodata_end - 24, 2):
        vals = struct.unpack_from('<12H', an.d, o)
        pairs = list(zip(vals[0::2], vals[1::2]))
        if all(plausible(a) and plausible(b) for a, b in pairs) and sum(1 for a, b in pairs if a or b) >= 3 and all((a == b == 0) or abs(a - b) == 1 for a, b in pairs):
            cands.append(o)
    for o in cands:
        vals = struct.unpack_from('<12H', an.d, o)
        print('  0x%08x: %s' % (FLASH + o, ' '.join('{%s,%s}' % (kc_name(a), kc_name(b)) for a, b in zip(vals[0::2], vals[1::2]))))
    facts['encoder_table_candidates'] = ['0x%08x' % (FLASH + o) for o in cands]
    # (c) encoder event path: functions using both 0xFD and 0xFC (KEYLOC_ENCODER_CW/CCW) immediates
    print('\nfunctions using both #0xFD and #0xFC immediates (KEYLOC_ENCODER_CW/CCW, i.e. encoder event path):')
    for s, e in zip(an.starts, an.starts[1:] + [FLASH + an.text_end]):
        imms = {v for ad, r, v in an.imm_ops(s, mnems=('cmp', 'movs', 'mov', 'mov.w', 'cmp.w'))}
        if 0xFD in imms and 0xFC in imms:
            print('  %s @0x%08x  bl/b.w targets: %s' % (an.name(s), s, ', '.join(an.name(t) for _, t in an.bl_targets_in(s))))
            facts.setdefault('encoder_event_path_funcs', []).append({'addr': '0x%08x' % s, 'name': an.name(s)})
            if an.name(s).startswith('sub_') or 'keymap_key_to_keycode' in an.name(s):
                an.print_func(s)
    # (d) weak encoder_update_user default shape 'movs r0,#1; bx lr' called from encoder_update_kb: only report names if known
    for nm in ('encoder_update_kb', 'encoder_update_user', 'encoder_read', 'encoder_inerrupt_read', 'encoder_exec_mapping'):
        for a, n in an.names.items():
            if n == nm:
                print('\n%s @0x%08x:' % (nm, a))
                an.print_func(a)


def analysis_dip(an, facts):
    print('\n' + '=' * 100 + '\n[3] DIP SWITCH')
    # signature: mvn.w r1, r1, lsr #8 ; and.w r6, r1, #1  (bit 8 of GPIOA IDR = pin A8, inverted)
    sig = b'\x6f\xea\x11\x21\x01\xf0\x01\x06'
    hits = [FLASH + an.img.code_start + m.start() for m in re.finditer(re.escape(sig), an.d[an.img.code_start:an.text_end])]
    if not hits:
        # generic: any function reading a GPIO IDR (+0x10) then lsr #8
        print('signature not found; falling back to GPIOA literal + lsr #8 scan')
        for a in an.literal_refs(0x40020000):
            s, e = an.func_of(a)
            txt = '\n'.join(an.disasm(s))
            if 'lsr #8' in txt and '#0x10]' in txt:
                hits.append(s)
    for h in hits:
        s, e = an.func_of(h)
        an.set_name(s, 'dip_switch_read')
        print('dip_switch_read candidate: %s @0x%08x (signature at 0x%08x: GPIOA->IDR bit 8 = pin A8, active-low)' % (an.name(s), s, h))
        an.print_func(s)
        pw = an.pool_words(s)
        rams = [w for _, _, w in pw if RAM <= w < RAM + 0x20000]
        print('  RAM vars: %s (dip_switch_state / last_dip_switch_state)' % ['0x%08x' % w for w in rams])
        facts['dip_switch_read'] = {'addr': '0x%08x' % s, 'ram': ['0x%08x' % w for w in rams]}
        for site, t in an.bl_targets_in(s):
            callees = an.bl_targets_in(t)
            cn = [an.name(c) for _, c in callees]
            if 'default_layer_set' in cn and an.name(t).startswith('sub_'):
                an.set_name(t, 'dip_switch_update_kb')
                for _, c in callees:
                    if an.name(c).startswith('sub_'):
                        an.set_name(c, 'dip_switch_update_user')
                facts['dip_switch_update_kb'] = '0x%08x' % t
            elif len(callees) == 1 and an.name(t).startswith('sub_'):
                an.set_name(t, 'dip_switch_update_mask_kb')
                an.set_name(callees[0][1], 'dip_switch_update_mask_user')
            print('\n  callee %s @0x%08x (called from 0x%08x):' % (an.name(t), t, site))
            an.print_func(t)
            # look for default_layer_set / layer moves inside and one level deeper
            for site2, t2 in an.bl_targets_in(t):
                if an.name(t2).startswith('sub_'):
                    print('\n    callee %s @0x%08x (called from 0x%08x):' % (an.name(t2), t2, site2))
                    an.print_func(t2)
        # extract the default_layer_set argument mapping
        for site, t in an.bl_targets_in(s):
            insns = an.func_insns(t)
            for i, ins in enumerate(insns):
                if ins.mnemonic in ('bl', 'b.w') and ins.operands[0].type == ARM_OP_IMM and an.name(ins.operands[0].imm).startswith('default_layer_set'):
                    ctx = insns[max(0, i - 4):i]
                    print('\n  default_layer_set call at 0x%08x in %s; preceding: %s' % (ins.address, an.name(t), ' | '.join('%s %s' % (c.mnemonic, c.op_str) for c in ctx)))
                    facts.setdefault('dip_default_layer_set_sites', []).append({'site': '0x%08x' % ins.address, 'in': an.name(t), 'preceding': ['%s %s' % (c.mnemonic, c.op_str) for c in ctx]})
    if not hits:
        print('no dip_switch_read found')


def analysis_tables(an, KM, layer_bytes, facts):
    print('\n' + '=' * 100 + '\n[4] TABLES AFTER keymaps[] AND KEYCHRON TABLES')
    after = KM + 6 * layer_bytes
    expect = [(0xA8, 'KC_AUDIO_MUTE', 0xE2), (0xA9, 'KC_AUDIO_VOL_UP', 0xE9), (0xAA, 'KC_AUDIO_VOL_DOWN', 0xEA), (0xAB, 'KC_MEDIA_NEXT_TRACK', 0xB5),
              (0xAC, 'KC_MEDIA_PREV_TRACK', 0xB6), (0xAD, 'KC_MEDIA_STOP', 0xB7), (0xAE, 'KC_MEDIA_PLAY_PAUSE', 0xCD), (0xAF, 'KC_MEDIA_SELECT', 0x183),
              (0xB0, 'KC_MEDIA_EJECT', 0xCC), (0xB1, 'KC_MAIL', 0x18A), (0xB2, 'KC_CALCULATOR', 0x192), (0xB3, 'KC_MY_COMPUTER', 0x194),
              (0xB4, 'KC_WWW_SEARCH', 0x221), (0xB5, 'KC_WWW_HOME', 0x223), (0xB6, 'KC_WWW_BACK', 0x224), (0xB7, 'KC_WWW_FORWARD', 0x225),
              (0xB8, 'KC_WWW_STOP', 0x226), (0xB9, 'KC_WWW_REFRESH', 0x227), (0xBA, 'KC_WWW_FAVORITES', 0x22A), (0xBB, 'KC_MEDIA_FAST_FORWARD', 0xB3),
              (0xBC, 'KC_MEDIA_REWIND', 0xB4), (0xBD, 'KC_BRIGHTNESS_UP', 0x6F), (0xBE, 'KC_BRIGHTNESS_DOWN', 0x70), (0xBF, 'KC_CONTROL_PANEL', 0x19F),
              (0xC0, 'KC_ASSISTANT', 0x1CB), (0xC1, 'KC_MISSION_CONTROL', 0x29F), (0xC2, 'KC_LAUNCHPAD', 0x2A0)]
    n = len(expect)
    for copy in range(2):
        base = after + copy * n * 2
        vals = struct.unpack_from('<%dH' % n, an.d, base - FLASH)
        ok = all(v == e[2] for v, e in zip(vals, expect))
        print('u16[%d] at 0x%08x..0x%08x: %s' % (n, base, base + n * 2, 'IDENTICAL to KEYCODE2CONSUMER(KC_AUDIO_MUTE..KC_LAUNCHPAD) HID consumer usages' if ok else 'mismatch: %s' % [hex(v) for v in vals]))
        if ok:
            an.names[base] = 'KEYCODE2CONSUMER_lut%d' % copy
            refs = an.literal_refs(base)
            for r in refs:
                s, e = an.func_of(r)
                callees = {an.name(t) for _, t in an.bl_targets_in(s)}
                if 'host_consumer_send' in callees and 'send_keyboard_report' in callees and an.name(s).startswith('sub_'):
                    an.set_name(s, 'register_code')      # quantum/action.c:942 host_consumer_send(KEYCODE2CONSUMER(code))
                elif an.name(s).startswith('sub_') and e - s > 0x100:
                    an.set_name(s, 'action_for_keycode') # quantum/keymap_common.c:71 ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(keycode))
                print('  literal 0x%08x referenced from pool word 0x%08x in %s @0x%08x (callees: %s)' % (base, r, an.name(s), s, ', '.join(sorted(callees))))
            facts.setdefault('consumer_lut', []).append({'addr': '0x%08x' % base, 'refs': ['0x%08x in %s' % (r, an.name(an.func_of(r)[0])) for r in refs]})
    for e_ in expect[:3]:
        pass
    print('  first 3 entries: ' + ', '.join('%s(0x%02X)->0x%03X' % (nm, kc, u) for kc, nm, u in expect[:3]) + ' ...')
    nxt = after + 2 * n * 2
    words = [an.img.word(nxt + 4 * i) for i in range(6)]
    print('following words at 0x%08x: %s  (ChibiOS ioline_t: 0x40020000=GPIOA 0x40020400=GPIOB 0x40020800=GPIOC | pad) -> matrix pin arrays' %
          (nxt, ' '.join('0x%08x' % w for w in words)))
    # Keychron tables
    mk = an.d.find(b'\xe2\xe6\xe3\xe7', an.text_end)
    kcl = an.d.find(bytes.fromhex('02e32b0002e3080003e1e32102e30600'), an.text_end)
    print('\nmac_keycode[4] = {KC_LOPT 0xE2, KC_ROPT 0xE6, KC_LCMD 0xE3, KC_RCMD 0xE7}: %s' % ('0x%08x' % (FLASH + mk) if mk > 0 else 'not found'))
    print('key_comb_list[4] = {2,{LWIN,TAB}},{2,{LWIN,E}},{3,{LSFT,LCMD,4}},{2,{LWIN,C}}: %s' % ('0x%08x' % (FLASH + kcl) if kcl > 0 else 'not found'))
    if kcl > 0:
        print('  bytes: %s' % hexs(an.d[kcl:kcl + 16]))
    for nm, off in (('mac_keycode', mk), ('key_comb_list', kcl)):
        if off > 0:
            an.names[FLASH + off] = nm
            refs = an.literal_refs(FLASH + off)
            for r in refs:
                s, e = an.func_of(r)
                print('  %s referenced from pool 0x%08x in %s @0x%08x' % (nm, r, an.name(s), s))
                if nm == 'key_comb_list' and an.name(s).startswith('sub_'):
                    an.set_name(s, 'process_record_keychron_common?')
            facts[nm] = {'addr': '0x%08x' % (FLASH + off), 'refs': ['0x%08x' % r for r in refs]}


def analysis_tapdance(an, crt, facts):
    print('\n' + '=' * 100 + '\n[5] TAP DANCE (.data init image scan)')
    tb, db, de = crt['__textdata_base__'], crt['__data_base__'], crt['__data_end__']
    size = de - db
    print('.data init image: flash 0x%08x..0x%08x (%d bytes) -> RAM 0x%08x..0x%08x ; bss 0x%08x..0x%08x' %
          (tb, tb + size, size, db, de, crt.get('__bss_base__', 0), crt.get('__bss_end__', 0)))
    img = an.d[tb - FLASH: tb - FLASH + size]
    lo, hi = FLASH + an.img.code_start, FLASH + an.text_end
    def is_fn(w):
        return w == 0 or ((w & 1) and lo < w < hi)
    def is_ud(w):
        return w == 0 or (hi <= w < FLASH + an.img.rodata_end and w % 2 == 0) or (RAM <= w < RAM + 0x20000 and w % 2 == 0) or (tb <= w < tb + size)
    cands = []
    for o in range(0, size - 28 + 1, 4):
        st = img[o:o + 8]
        if st != b'\x00' * 8:
            continue
        fns = struct.unpack_from('<4I', img, o + 8)
        ud = struct.unpack_from('<I', img, o + 24)[0]
        if all(is_fn(f) for f in fns) and any(fns) and is_ud(ud):
            cands.append((o, fns, ud))
    print('candidates (state==0, fn pointers odd in text or NULL, user_data NULL/rodata/RAM):')
    for o, fns, ud in cands:
        ram = db + o
        refs = an.literal_refs(ram)
        print('  file 0x%06x flash 0x%08x -> RAM 0x%08x : fn={on_each_tap=%s, on_dance_finished=%s, on_reset=%s, on_each_release=%s} user_data=0x%08x ; code literal refs to RAM addr: %s' %
              (tb - FLASH + o, tb + o, ram, *['%s' % (an.name(f) if f else 'NULL') for f in fns], ud,
               ['0x%08x in %s' % (r, an.name(an.func_of(r)[0])) for r in refs]))
    # the real tap_dance_actions[] is the candidate whose RAM address is loaded by code (process_tap_dance.c)
    real = [(o, fns, ud) for o, fns, ud in cands if an.literal_refs(db + o)]
    for o, fns, ud in real:
        ram = db + o
        an.ram_names[ram] = 'tap_dance_actions'
        print('\ntap_dance_actions[] = RAM 0x%08x (init image flash 0x%08x). Entry 0: %s' % (ram, tb + o, hexs(img[o:o + 28])))
        facts['tap_dance_actions'] = {'ram': '0x%08x' % ram, 'init_image': '0x%08x' % (tb + o),
                                      'fn': {'on_each_tap': '0x%08x' % fns[0], 'on_dance_finished': '0x%08x' % fns[1], 'on_reset': '0x%08x' % fns[2], 'on_each_release': '0x%08x' % fns[3]},
                                      'user_data': '0x%08x' % ud}
        # is there a second entry? check next 28 bytes for another plausible struct
        o2 = o + 28
        if o2 + 28 <= size:
            st2 = img[o2:o2 + 8]
            fns2 = struct.unpack_from('<4I', img, o2 + 8)
            print('  next 28 bytes (would be entry 1): %s -> %s' % (hexs(img[o2:o2 + 28]), 'plausible entry' if st2 == b'\x00' * 8 and all(is_fn(f) for f in fns2) and any(fns2) else 'NOT a tap dance entry => exactly 1 entry'))
        for r in an.literal_refs(ram):
            s, e = an.func_of(r)
            print('\n  referencing function %s @0x%08x (process_tap_dance.c; look for *28 stride: movs #28 / lsl #2 + lsl #3 ...):' % (an.name(s), s))
            an.print_func(s)
        labels = ['on_each_tap', 'on_dance_finished', 'on_reset', 'on_each_release']
        for lab, f in zip(labels, fns):
            if f:
                an.set_name(f, 'td0_%s' % lab)
        for lab, f in zip(labels, fns):
            if f:
                for site, t in an.bl_targets_in(f):
                    if an.name(t).startswith('sub_'):
                        ins_ = an.func_insns(t)
                        txt_ = ' '.join('%s %s' % (i.mnemonic, i.op_str) for i in ins_)
                        if '[r0, #2]' in txt_ and '[r0, #5]' in txt_:
                            an.set_name(t, 'td0_cur_dance')        # reads state->count and state->{pressed,interrupted}
                        else:
                            an.set_name(t, 'td0_helper_%08x' % t)
        for lab, f in zip(labels, fns):
            if not f:
                continue
            print('\n  callback %s = 0x%08x:' % (lab, f))
            an.print_func(f)
            for site, t in an.bl_targets_in(f):
                if an.name(t).startswith('sub_') or an.name(t).startswith('td0_'):
                    s2, e2 = an.func_of(t)
                    if e2 - s2 <= 0x80:
                        print('\n    helper %s @0x%08x (called from 0x%08x):' % (an.name(t), t, site))
                        an.print_func(t)
                        for site3, t3 in an.bl_targets_in(t):
                            if an.name(t3).startswith('sub_'):
                                s3, e3 = an.func_of(t3)
                                if e3 - s3 <= 0x40:
                                    print('\n      helper %s @0x%08x (called from 0x%08x):' % (an.name(t3), t3, site3))
                                    an.print_func(t3)


def decode_action_block(an, insns, i0, i1, reg_names, follow=False):
    """Summarise register/unregister/tap calls between instruction indices. With follow=True an
    unconditional in-function 'b' is followed (shared tails) until a return / already-visited insn."""
    out = []
    regs = {}
    seq = list(range(i0, min(i1, len(insns))))
    if follow:
        by_addr = {x.address: k for k, x in enumerate(insns)}
        seq = []
        k = i0
        seen = set()
        while k < len(insns) and k not in seen and len(seq) < 200:
            seen.add(k)
            seq.append(k)
            x = insns[k]
            if x.mnemonic == 'b' and x.operands and x.operands[0].type == ARM_OP_IMM and x.operands[0].imm in by_addr:
                k = by_addr[x.operands[0].imm]
                continue
            if x.mnemonic in ('pop', 'pop.w', 'bx', 'b.w') or (x.mnemonic == 'ldr' and 'pc' in x.op_str.split(',')[0]):
                break
            k += 1
    for ins in (insns[k] for k in seq):
        if ins.mnemonic in ('movs', 'mov', 'mov.w', 'movw') and len(ins.operands) == 2 and ins.operands[1].type == ARM_OP_IMM:
            regs[ins.reg_name(ins.operands[0].reg)] = ins.operands[1].imm
        elif ins.mnemonic in ('mov', 'movs') and len(ins.operands) == 2 and ins.operands[1].type == ARM_OP_REG:
            regs[ins.reg_name(ins.operands[0].reg)] = regs.get(ins.reg_name(ins.operands[1].reg), '?')
        elif ins.mnemonic in ('bl', 'b.w') and ins.operands and ins.operands[0].type == ARM_OP_IMM:
            nm = an.name(ins.operands[0].imm)
            if nm in ('register_code', 'unregister_code', 'tap_code', 'tap_code16', 'register_code16', 'unregister_code16', 'tap_code_delay'):
                out.append('%s(%s)' % (nm, kc_name(regs.get('r0', -1))))
            elif nm.startswith('send_string'):
                out.append('%s(0x%08x)' % (nm, regs.get('r0', 0)))
            elif nm.startswith('rgb_matrix_set_color'):
                out.append('%s(%s)' % (nm, ','.join(str(regs.get(r, '?')) for r in ('r0', 'r1', 'r2', 'r3')[: (3 if 'all' in nm else 4)])))
            else:
                out.append('%s(r0=%s)' % (nm, regs.get('r0', '?')))
    return out


def analysis_leader(an, facts):
    print('\n' + '=' * 100 + '\n[6] LEADER KEY')
    # process_leader: the function containing movw #0x7C58
    pl = [a for a, v in an.movwt.items()]  # not used; movw alone:
    sites = []
    for ins in an.insns:
        if ins.id and ins.mnemonic == 'movw' and len(ins.operands) == 2 and ins.operands[1].type == ARM_OP_IMM and ins.operands[1].imm == 0x7C58:
            sites.append(ins.address)
    print('movw #0x7C58 (QK_LEADER) sites: %s' % ['0x%08x in %s' % (s_, an.name(an.func_of(s_)[0])) for s_ in sites])
    if not sites:
        print('no leader code found')
        return
    pl_s, pl_e = an.func_of(sites[0])
    an.set_name(pl_s, 'process_leader')
    an.print_func(pl_s)
    # classify callees of process_leader
    leader_end = leader_start = None
    for site, t in an.bl_targets_in(pl_s):
        ins = an.func_insns(t)
        txt = ' ; '.join('%s %s' % (i.mnemonic, i.op_str) for i in ins)
        # leader_end: strb #0 to `leading`, then call/tail-call leader_end_user
        strb0 = any(i.mnemonic == 'strb' for i in ins) and any(i.mnemonic == 'movs' and i.operands[1].type == ARM_OP_IMM and i.operands[1].imm == 0 for i in ins)
        calls = [c for _, c in an.bl_targets_in(t)]
        if strb0 and len(ins) <= 8 and len(calls) == 1 and not any(i.mnemonic in ('cbz', 'cbnz') for i in ins):
            leader_end = t
            an.set_name(t, 'leader_end')
            an.set_name(calls[0], 'leader_end_user')
        elif any(i.mnemonic == 'strb' for i in ins) and len(calls) >= 3:
            leader_start = t
            an.set_name(t, 'leader_start')
    print('\nprocess_leader callees:')
    for site, t in an.bl_targets_in(pl_s):
        print('  0x%08x -> %s @0x%08x' % (site, an.name(t), t))
    for site, t in an.bl_targets_in(pl_s):
        an.print_func(t)
    if leader_start:
        callees = an.bl_targets_in(leader_start)
        if callees:
            an.set_name(callees[0][1], 'leader_start_user')       # first call, before leading = true
            facts['leader_start_user'] = '0x%08x' % callees[0][1]
            if len(callees) > 1 and an.name(callees[1][1]).startswith('sub_'):
                an.set_name(callees[1][1], 'timer_read')            # leader_time = timer_read()
        for site, t in callees:
            print('\n  leader_start callee %s @0x%08x:' % (an.name(t), t))
            an.print_func(t)
    # leader_sequence_is and the N-key wrappers, leader_sequence_timed_out (LEADER_TIMEOUT)
    for a, nm in list(an.names.items()):
        if nm == 'leader_end_user':
            leu = a
    # find leader_sequence_is: function whose pool word is RAM and that does 5 ldrh compares incl [sp,#12]
    lsi = None
    for s, e in zip(an.starts, an.starts[1:]):
        ins = an.func_insns(s, e)
        if sum(1 for i in ins if i.mnemonic in ('ldrh', 'ldrh.w')) >= 5 and any('sp, #0xc]' in i.op_str for i in ins) and e - s <= 0x40:
            lsi = s
            an.set_name(s, 'leader_sequence_is')
            pw = an.pool_words(s)
            if pw:
                an.ram_names[pw[0][2]] = 'leader_sequence[5]'
                facts['leader_sequence_ram'] = '0x%08x' % pw[0][2]
            print('\nleader_sequence_is @0x%08x (leader_sequence[] = %s):' % (s, ['0x%08x' % w for _, _, w in pw]))
            an.print_func(s)
            break
    seqfn = {}
    if lsi:
        for kind, site, f in an.xrefs(lsi):
            if kind != 'bl':
                continue
            s, e = an.func_of(site)
            ins = an.func_insns(s, e)
            zeroed = {i.reg_name(i.operands[0].reg) for i in ins if i.mnemonic in ('mov', 'movs') and ((i.operands[1].type == ARM_OP_IMM and i.operands[1].imm == 0) or (i.operands[1].type == ARM_OP_REG and i.reg_name(i.operands[1].reg) == 'r3'))}
            zeroed |= {i.reg_name(i.operands[0].reg) for i in ins if i.mnemonic in ('mov', 'movs') and i.operands[1].type == ARM_OP_REG and 'r3' in zeroed}
            n = 5 - len({r for r in zeroed if r in ('r1', 'r2', 'r3')}) - (1 if any(i.mnemonic == 'str' and 'sp' in i.op_str for i in ins) else 0)
            nm = {1: 'leader_sequence_one_key', 2: 'leader_sequence_two_keys', 3: 'leader_sequence_three_keys', 4: 'leader_sequence_four_keys', 5: 'leader_sequence_five_keys'}.get(n, 'leader_sequence_%d_keys' % n)
            an.set_name(s, nm)
            seqfn[s] = n
            print('  %s @0x%08x (zeroes %s)' % (nm, s, sorted(zeroed)))
            an.print_func(s)
    # LEADER_TIMEOUT: function calling timer_elapsed and comparing with immediate, referenced from leader_task
    for s, e in zip(an.starts, an.starts[1:]):
        ins = an.func_insns(s, e)
        if e - s <= 0x30 and any(i.mnemonic == 'bl' and an.name(i.operands[0].imm) == 'timer_elapsed' for i in ins):
            cm = [i for i in ins if i.mnemonic in ('cmp', 'cmp.w') and i.operands[1].type == ARM_OP_IMM]
            mw = [i for i in ins if i.mnemonic == 'movw' and i.operands[1].type == ARM_OP_IMM]
            ldrh = [i for i in ins if i.mnemonic == 'ldrh']
            if ldrh and (cm or mw) and any(i.mnemonic in ('ite', 'it') for i in ins):
                val = cm[0].operands[1].imm if cm else mw[0].operands[1].imm
                pw = an.pool_words(s)
                print('\nleader_sequence_timed_out candidate %s @0x%08x: timer_elapsed(leader_time@%s) > %d  => LEADER_TIMEOUT = %d ms' %
                      (an.name(s), s, ['0x%08x' % w for _, _, w in pw], val, val))
                an.set_name(s, 'leader_sequence_timed_out?')
                if pw:
                    an.ram_names[pw[0][2]] = 'leader_time'
                facts['leader_timeout_ms'] = val
                an.print_func(s)
    # decode leader_end_user
    if 'leu' in locals():
        print('\nleader_end_user @0x%08x:' % leu)
        an.print_func(leu)
        ins = an.func_insns(leu)
        print('\nDecoded leader sequences (condition -> actions):')
        regs = {}
        seqs = []
        i = 0
        while i < len(ins):
            x = ins[i]
            if x.mnemonic in ('movs', 'mov', 'mov.w', 'movw') and len(x.operands) == 2 and x.operands[1].type == ARM_OP_IMM:
                regs[x.reg_name(x.operands[0].reg)] = x.operands[1].imm
            elif x.mnemonic in ('mov',) and len(x.operands) == 2 and x.operands[1].type == ARM_OP_REG:
                regs[x.reg_name(x.operands[0].reg)] = regs.get(x.reg_name(x.operands[1].reg), '?')
            if x.mnemonic == 'bl' and x.operands[0].type == ARM_OP_IMM and (x.operands[0].imm & ~1) in seqfn:
                n = seqfn[x.operands[0].imm & ~1]
                keys = [regs.get('r%d' % k, '?') for k in range(n)]
                # next instruction should be cbz r0, skip
                skip = None
                if i + 1 < len(ins) and ins[i + 1].mnemonic in ('cbz', 'beq') :
                    skip = ins[i + 1].operands[-1].imm
                j = i + 2
                while j < len(ins) and (skip is None or ins[j].address < skip):
                    j += 1
                acts = decode_action_block(an, ins, i + 2, j, None)
                seqs.append({'keys': ['0x%04x' % k if isinstance(k, int) else k for k in keys], 'names': [kc_name(k) if isinstance(k, int) else k for k in keys], 'actions': acts, 'site': '0x%08x' % x.address})
                print('  LEAD, %-30s -> %s' % (', '.join(kc_name(k) if isinstance(k, int) else str(k) for k in keys), ' ; '.join(acts)))
                i = j
                continue
            i += 1
        # prologue actions (before the first sequence test)
        first = min((k for k, x in enumerate(ins) if x.mnemonic == 'bl' and x.operands[0].type == ARM_OP_IMM and (x.operands[0].imm & ~1) in seqfn), default=len(ins))
        print('  prologue (unconditional, before first test): %s' % ' ; '.join(decode_action_block(an, ins, 0, first, None)))
        facts['leader_sequences'] = seqs
        facts['leader_end_user'] = '0x%08x' % leu


def analysis_process_record_user(an, facts):
    print('\n' + '=' * 100 + '\n[7] process_record_user / custom keycodes / oneshot hooks')
    pru = next((a for a, n in an.names.items() if n == 'process_record_user'), None)
    if pru is None:
        # fallback: function containing movw #0x7E40
        for ins in an.insns:
            if ins.id and ins.mnemonic == 'movw' and ins.operands[1].type == ARM_OP_IMM and ins.operands[1].imm == 0x7E40:
                pru = an.func_of(ins.address)[0]
                an.set_name(pru, 'process_record_user?')
    if pru is None:
        print('process_record_user not located')
        return
    print('process_record_user @0x%08x, xrefs: %s' % (pru, ['%s@%08x in %s' % (k, s, an.name(f) if f else '-') for k, s, f in an.xrefs(pru)]))
    an.print_func(pru)
    facts['process_record_user'] = '0x%08x' % pru
    # custom keycode blocks: movw rX,#imm ; cmp rY,rX ; bne -> the block until the branch target
    ins = an.func_insns(pru)
    for i, x in enumerate(ins):
        if x.mnemonic == 'movw' and x.operands[1].type == ARM_OP_IMM and 0x7E40 <= x.operands[1].imm <= 0x7E7F and i + 2 < len(ins) and ins[i + 1].mnemonic == 'cmp' and ins[i + 2].mnemonic == 'bne':
            kc = x.operands[1].imm
            end = ins[i + 2].operands[0].imm
            j = i + 3
            acts = []
            while j < len(ins) and ins[j].address < end and ins[j].mnemonic not in ('b', 'pop', 'bx'):
                j += 1
            acts = decode_action_block(an, ins, i + 3, len(ins), None, follow=True)
            print('  %s (0x%04x) pressed -> %s' % (kc_name(kc), kc, ' ; '.join(acts)))
            facts.setdefault('custom_keycodes', []).append({'keycode': '0x%04x' % kc, 'name': kc_name(kc), 'actions': acts, 'site': '0x%08x' % x.address})
    # helpers called from process_record_user that are unnamed & small
    for site, t in an.bl_targets_in(pru):
        if an.name(t).startswith('sub_'):
            s2, e2 = an.func_of(t)
            if e2 - s2 <= 0x90:
                print('\n  helper %s @0x%08x (called from 0x%08x):' % (an.name(t), t, site))
                an.print_func(t)
                for site3, t3 in an.bl_targets_in(t):
                    if an.name(t3).startswith('sub_') and an.func_of(t3)[1] - an.func_of(t3)[0] <= 0x40:
                        print('\n    helper %s @0x%08x (called from 0x%08x):' % (an.name(t3), t3, site3))
                        an.print_func(t3)
    kbh = next((a for a, n in an.names.items() if n == 'oneshot_layer_changed_kb'), None)
    if kbh:
        for _, t in an.bl_targets_in(kbh):
            if an.name(t).startswith('sub_'):
                an.set_name(t, 'oneshot_layer_changed_user')
                facts['oneshot_layer_changed_user'] = '0x%08x' % t
                print('\noneshot_layer_changed_user (sole callee of matched oneshot_layer_changed_kb @0x%08x) = 0x%08x:' % (kbh, t))
                an.print_func(t)
    # oneshot_layer_changed_user / layer_state_set_user candidates: functions called from set_oneshot_layer/clear_oneshot_layer_state chain
    for nm in ('clear_oneshot_layer_state', 'reset_oneshot_layer', 'set_oneshot_layer'):
        a = next((k for k, v in an.names.items() if v == nm), None)
        if a is None:
            continue
        print('\n%s @0x%08x callees: %s' % (nm, a, ', '.join('%s@%08x' % (an.name(t), t) for _, t in an.bl_targets_in(a))))
        for _, t in an.bl_targets_in(a):
            if an.name(t).startswith('sub_'):
                print('  callee %s:' % an.name(t))
                an.print_func(t)
                for _, t2 in an.bl_targets_in(t):
                    if an.name(t2).startswith('sub_'):
                        print('    callee %s:' % an.name(t2))
                        an.print_func(t2)


def analysis_action_layer(an, facts):
    """Name the action_layer.c primitives from their call structure, anchored on the byte-matched
    layer_on / default_layer_set: layer_on tail-calls layer_state_set; default_layer_set tail-calls
    default_layer_state_set; *_state_set stores r0 (u16) to the state variable after calling the kb hook."""
    print('\n' + '=' * 100 + '\n[0] ACTION_LAYER PRIMITIVES (identified from call structure anchored on matched layer_on/default_layer_set)')
    lo = next((a for a, n in an.names.items() if n == 'layer_on'), None)
    dls = next((a for a, n in an.names.items() if n == 'default_layer_set'), None)
    def tail_target(f):
        for _, t in an.bl_targets_in(f):
            return t
        return None
    def name_state_set(f, nm, var_nm):
        an.set_name(f, nm)
        ins = an.func_insns(f)
        pw = an.pool_words(f)
        for i in ins:
            if i.mnemonic == 'strh' and pw:
                an.ram_names[pw[0][2]] = var_nm
                facts.setdefault('action_layer', {})[var_nm] = '0x%08x' % pw[0][2]
        kb = tail_target(f)
        if kb:
            an.set_name(kb, nm + '_kb')
            usr = tail_target(kb)
            if usr:
                an.set_name(usr, nm + '_user')
        facts.setdefault('action_layer', {})[nm] = '0x%08x' % f
    if dls:
        dss = tail_target(dls)
        if dss:
            name_state_set(dss, 'default_layer_state_set', 'default_layer_state')
    lss = None
    if lo:
        lss = tail_target(lo)
        if lss:
            name_state_set(lss, 'layer_state_set', 'layer_state')
    if lss:
        # every small function tail-calling layer_state_set / default_layer_state_set: classify by body
        dss = tail_target(dls) if dls else None
        for s, e in zip(an.starts, an.starts[1:]):
            if e - s > 0x30 or s in (lo, dls):
                continue
            ins = an.func_insns(s, e)
            bw = [k for k, i in enumerate(ins) if i.mnemonic == 'b.w']
            if not bw:
                continue
            tgt = ins[bw[0]].operands[0].imm & ~1
            if tgt not in (lss, dss):
                continue
            body = ins[:bw[0]]
            txt = ' ; '.join('%s %s' % (i.mnemonic, i.op_str) for i in body)
            pre = 'layer' if tgt == lss else 'default_layer'
            nm = None
            if len(body) == 1 and body[0].mnemonic == 'movs' and body[0].operands[1].type == ARM_OP_IMM and body[0].operands[1].imm == 0:
                nm = 'layer_clear'
            elif 'lsl.w' in txt and 'uxth' in txt and 'ldrh' not in txt:
                nm = 'layer_move'
            elif 'orrs' in txt and 'lsl' in txt:
                nm = 'layer_on'
            elif 'bic' in txt:
                nm = 'layer_off'
            elif 'eors' in txt and 'lsl' in txt:
                nm = 'layer_invert'
            elif 'orrs' in txt:
                nm = pre + '_or'
            elif 'ands' in txt:
                nm = pre + '_and'
            elif 'eors' in txt:
                nm = pre + '_xor'
            if nm and s not in an.names:
                an.set_name(s, nm)
            if nm:
                facts.setdefault('action_layer', {})[nm] = '0x%08x' % s
        # layer_state_is: reads layer_state, clz shape, between layer_state_set and layer_move
        for s, e in zip(an.starts, an.starts[1:]):
            if lss < s < lss + 0x60:
                txt = ' ; '.join('%s %s' % (i.mnemonic, i.op_str) for i in an.func_insns(s, e))
                if 'clz' in txt and 'asr.w' in txt and s not in an.names:
                    an.set_name(s, 'layer_state_is')
                    facts.setdefault('action_layer', {})['layer_state_is'] = '0x%08x' % s
    lo_w = (dls or lss or 0) - 0x30
    hi_w = (lo or lss or 0) + 0x80
    for s, e in zip(an.starts, an.starts[1:]):
        if lo_w <= s <= hi_w:
            txt = ' ; '.join('%s %s' % (i.mnemonic, i.op_str) for i in an.func_insns(s, e))
            print('  0x%08x..0x%08x %-28s %s' % (s, e, an.name(s), txt[:110]))


def analysis_tu_map(an, lo, hi, facts):
    """List every function in [lo,hi) (the keymap.c / v10_max.c translation units) with callers and callees."""
    print('\n' + '=' * 100 + '\n[8] TRANSLATION-UNIT MAP 0x%08x..0x%08x (custom keymap.c / v10_max.c region)' % (lo, hi))
    # keyboard_post_init_kb: GPIOA literal + mov.w r1,#0x400 (A10) + mov.w r1,#0x200 (A9) + strh #0x1000 (B12 BSRR) then tail-call user hook
    for s, e in zip(an.starts, an.starts[1:]):
        if not (lo <= s < hi):
            continue
        ins = an.func_insns(s, e)
        imms = [i.operands[1].imm for i in ins if i.mnemonic in ('mov.w', 'movs') and len(i.operands) == 2 and i.operands[1].type == ARM_OP_IMM]
        pw = [w for _, _, w in an.pool_words(s, e)]
        if 0x400 in imms and 0x200 in imms and 0x1000 in imms and 0x40020000 in pw and an.name(s).startswith('sub_'):
            an.set_name(s, 'keyboard_post_init_kb')
            bws = [i for i in ins if i.mnemonic == 'b.w']
            if bws:
                an.set_name(bws[-1].operands[0].imm & ~1, 'keyboard_post_init_user')
                facts['keyboard_post_init_user'] = '0x%08x' % (bws[-1].operands[0].imm & ~1)
    rows = []
    for s, e in zip(an.starts, an.starts[1:]):
        if not (lo <= s < hi):
            continue
        callers = sorted({an.name(f) if f else 'ptr@%08x' % sa for k, sa, f in an.xrefs(s)})
        callees = [an.name(t) for _, t in an.bl_targets_in(s, e)]
        rows.append({'addr': '0x%08x' % s, 'size': e - s, 'name': an.name(s), 'callers': callers, 'callees': callees})
        print('  %08x %4d %-34s callers=%s\n%s callees=%s' % (s, e - s, an.name(s), ', '.join(callers) or '-', ' ' * 54, ', '.join(callees) or '-'))
    facts['tu_map'] = rows
    for nm in ('keyboard_post_init_kb', 'keyboard_post_init_user'):
        a = next((k for k, v in an.names.items() if v == nm), None)
        if a:
            an.print_func(a)


# ----------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dump')
    ap.add_argument('--symbols', help='dump_symbols.json from match_ref_funcs.py')
    ap.add_argument('--keymaps', type=lambda x: int(x, 0), default=0x080169B8)
    ap.add_argument('--layer-bytes', type=int, default=216)
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=0x8000)
    ap.add_argument('--text-end', type=lambda x: int(x, 0), default=None, help='file offset where .text ends (auto: last matched symbol end, rounded)')
    ap.add_argument('--rodata-end', type=lambda x: int(x, 0), default=None, help='file offset of .data init image (auto from crt0)')
    ap.add_argument('--qmk-root', default='/Users/dexter/code/qmk-keychron')
    ap.add_argument('--json', help='write facts JSON here')
    ap.add_argument('--func', type=lambda x: int(x, 0), action='append', help='also disassemble the function containing this address')
    ap.add_argument('--tu-lo', type=lambda x: int(x, 0), default=0x0800CCF0, help='start of the custom TU region for the [8] map')
    ap.add_argument('--tu-hi', type=lambda x: int(x, 0), default=0x0800D2CC, help='end of the custom TU region for the [8] map')
    args = ap.parse_args()

    load_qmk_spec(args.qmk_root)
    img0 = Image(args.dump, args.code_start, 0x1774C)
    crt = parse_crt0(img0)
    rodata_end = args.rodata_end or (crt['__textdata_base__'] - FLASH)
    img = Image(args.dump, args.code_start, rodata_end)
    syms = {}
    symsize = {}
    if args.symbols:
        j = json.load(open(args.symbols))
        for n, r in j['symbols'].items():
            a = int(r['dump_addr'], 16)
            syms[a] = n if a not in syms else syms[a] + '|' + n
            symsize[a] = r.get('size', 0)
    text_end = args.text_end
    if text_end is None:
        last = max(((a - FLASH) + symsize.get(a, 0) for a in syms), default=0x16000)
        text_end = (last + 0x1F) & ~0xF
    print('# dump %s: code 0x%x.., text_end 0x%x (auto), rodata_end/.data image 0x%x' % (args.dump, args.code_start, text_end, rodata_end))
    print('# crt0 literals: __textdata_base__=0x%08x __data_base__=0x%08x __data_end__=0x%08x __bss_base__=0x%08x __bss_end__=0x%08x main=0x%08x (ldr sites %s)' %
          (crt['__textdata_base__'], crt['__data_base__'], crt['__data_end__'], crt.get('__bss_base__', 0), crt.get('__bss_end__', 0), crt.get('main', 0),
           ['0x%08x' % a for a in crt.get('dloop_ldr_addrs', ())]))
    an = Analyzer(img, syms, text_end)
    print('# linear sweep: %d insns, %d distinct BL targets, %d function starts' % (len(an.insns), len(an.bl_sites), len(an.starts)))
    facts = {'crt0': {k: ('0x%08x' % v if isinstance(v, int) else v) for k, v in crt.items()}, 'text_end': '0x%x' % text_end, 'rodata_end': '0x%x' % rodata_end}

    analysis_action_layer(an, facts)
    analysis_keymap(an, args.keymaps, args.layer_bytes, facts)
    analysis_encoder(an, args.keymaps, facts)
    analysis_dip(an, facts)
    analysis_tables(an, args.keymaps, args.layer_bytes, facts)
    analysis_tapdance(an, crt, facts)
    analysis_leader(an, facts)
    analysis_process_record_user(an, facts)
    analysis_tu_map(an, args.tu_lo, args.tu_hi, facts)
    for f in args.func or []:
        print('\n' + '=' * 100 + '\n[extra] function containing 0x%08x' % f)
        s, e = an.func_of(f)
        print('xrefs: %s' % ['%s@%08x in %s' % (k, s_, an.name(fn) if fn else '-') for k, s_, fn in an.xrefs(s)])
        an.print_func(s)
    facts['names_assigned'] = {('0x%08x' % a): n for a, n in an.names.items() if a not in syms}
    facts['ram_names'] = {('0x%08x' % a): n for a, n in an.ram_names.items()}
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(facts, f, indent=1, sort_keys=True)
        print('\n# facts written to %s' % args.json)


if __name__ == '__main__':
    main()
