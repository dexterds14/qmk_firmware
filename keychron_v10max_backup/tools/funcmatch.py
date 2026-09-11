#!/usr/bin/env python3
"""funcmatch.py <dump.bin> <refsyms.json>... [--base 0x08000000] [--code-start 0x8000]
               [--code-end 0x17F04] [--out-dir DIR] [--fuzzy 0.85] [--anchored 0.5]

Masked function-signature matcher for a raw Cortex-M4 flash dump against one or
more reference ELFs pre-processed by refsyms.py.

Pipeline
  1. exact   : for every reference function pick an 8-byte (fallback 4-byte)
               fully-unmasked anchor window, look it up in a halfword-aligned
               window index of the dump code region, verify the whole masked body
               ((dump & mask) == masked).  Ranges are assigned largest-first,
               one dump byte belongs to one function.  Several names with an
               identical body (weak defaults) -> 'exact-ambiguous' until a caller
               anchors the name.
  2. votes   : from every unambiguous match decode the dump's BL / B.W tail-call /
               literal function pointers at the offsets where the reference calls
               a named symbol -> "dump address T should be symbol S" votes.  Votes
               resolve ambiguous bodies and label hooks even when their body is
               custom (unmatched).  Vector-table slots vote too.
  3. data    : rodata / .data-init objects (pointer words masked) matched exactly.
  4. fuzzy   : leftover reference functions vs function-start candidates inside
               unmatched gaps (gap starts, BL targets, literal function pointers)
               by skeleton-token similarity (difflib ratio >= --fuzzy, size within
               10%).  Vote-anchored candidates are also scored ('fuzzy-anchored',
               threshold --anchored, reported separately, never counted as stock).
  5. report  : functions_matched.csv, unmatched_regions.csv, coverage.txt,
               hooks.csv, matches.json.

Run with: uv run --with capstone --with pyelftools python3 funcmatch.py ...
"""
import argparse
import csv
import difflib
import json
import os
import sys
from array import array
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import refsyms as RS  # noqa: E402

DEFAULT_HOOKS = [
    'process_record_user', 'process_record_kb', 'process_record_keychron', 'process_record_keychron_common',
    'process_record_quantum', 'housekeeping_task_user', 'housekeeping_task_kb', 'matrix_scan_user', 'matrix_scan_kb',
    'keyboard_post_init_user', 'keyboard_post_init_kb', 'keyboard_pre_init_user', 'keyboard_pre_init_kb',
    'layer_state_set_user', 'layer_state_set_kb', 'default_layer_state_set_user', 'default_layer_state_set_kb',
    'rgb_matrix_indicators_user', 'rgb_matrix_indicators_kb', 'rgb_matrix_indicators_advanced_user',
    'rgb_matrix_indicators_advanced_kb', 'dip_switch_update_kb', 'dip_switch_update_user',
    'dip_switch_update_mask_kb', 'dip_switch_update_mask_user', 'encoder_update_user', 'encoder_update_kb',
    'keycode_at_encodermap_location_raw', 'keycode_at_keymap_location_raw', 'leader_start_user', 'leader_end_user',
    'raw_hid_receive', 'raw_hid_receive_kb', 'eeconfig_init_user', 'eeconfig_init_kb', 'get_tapping_term',
    'process_tap_dance', 'tap_dance_task', 'preprocess_tap_dance', 'process_leader', 'leader_task',
    'shutdown_user', 'shutdown_kb', 'suspend_power_down_user', 'suspend_power_down_kb', 'suspend_wakeup_init_user',
    'suspend_wakeup_init_kb', 'led_update_user', 'led_update_kb', 'via_custom_value_command_kb',
    'process_record_via', 'get_hold_on_other_key_press', 'get_permissive_hold', 'get_retro_tapping',
    'pre_process_record_user', 'pre_process_record_kb', 'post_process_record_user', 'post_process_record_kb',
    'battery_low_user', 'wireless_pre_task', 'wireless_post_task', 'keyboard_init', 'keyboard_task', 'main',
]


class RefFn(object):
    __slots__ = ('name', 'elf', 'addr', 'size', 'raw', 'masked', 'mask', 'maskint', 'maskedint',
                 'skel', 'skel_offs', 'calls', 'bouts', 'lits', 'anchor', 'bind', 'key', 'inferred')

    def __init__(self, d, elf):
        self.name = d['name']
        self.elf = elf
        self.addr = d['addr']
        self.size = d['size']
        self.raw = bytes.fromhex(d['bytes'])
        self.masked = bytes.fromhex(d['masked'])
        self.mask = bytes.fromhex(d['mask'])
        self.maskint = int.from_bytes(self.mask, 'little')
        self.maskedint = int.from_bytes(self.masked, 'little')
        self.skel = d['skel'].split(';') if d['skel'] else []
        self.skel_offs = d['skel_offs']
        self.calls = d['calls']
        self.bouts = d['bouts']
        self.lits = d['lits']
        self.bind = d.get('bind')
        self.inferred = bool(d.get('inferred'))
        self.anchor = find_anchor(self.mask, self.raw)
        self.key = (self.name, self.masked, self.mask)


class RefObj(object):
    __slots__ = ('name', 'elf', 'addr', 'flash_addr', 'size', 'raw', 'masked', 'mask', 'maskint', 'maskedint',
                 'anchor', 'section')

    def __init__(self, d, elf):
        self.name = d['name']
        self.elf = elf
        self.addr = d['addr']
        self.flash_addr = d['flash_addr']
        self.size = d['size']
        self.section = d['section']
        self.raw = bytes.fromhex(d['bytes'])
        self.masked = bytes.fromhex(d['masked'])
        self.mask = bytes.fromhex(d['mask'])
        self.maskint = int.from_bytes(self.mask, 'little')
        self.maskedint = int.from_bytes(self.masked, 'little')
        self.anchor = find_anchor(self.mask, self.raw, min_distinct=3)


def find_anchor(mask, raw, min_distinct=2):
    """Longest run of fully-unmasked bytes; return (offset, window bytes) with an
    even offset and 8 (or 4) bytes; prefer the window with most distinct bytes."""
    n = len(mask)
    runs = []
    i = 0
    while i < n:
        if mask[i] == 0xFF:
            j = i
            while j < n and mask[j] == 0xFF:
                j += 1
            runs.append((i, j))
            i = j
        else:
            i += 1
    runs.sort(key=lambda r: -(r[1] - r[0]))
    for wlen in (8, 4):
        for (a, b) in runs:
            if b - a < wlen:
                break
            best = None
            for o in range(a + (a & 1), b - wlen + 1, 2):
                w = raw[o:o + wlen]
                nd = len(set(w))
                if nd < min_distinct:
                    continue
                if best is None or nd > best[0]:
                    best = (nd, o, w)
            if best:
                return (best[1], best[2])
    return None


def load_refs(paths):
    fns, objs, elfs = [], [], []
    for p in paths:
        d = json.load(open(p))
        elf = d['name']
        elfs.append({'name': elf, 'link': d['link'], 'vectors': d['vectors'], 'names_at': d['names_at'],
                     'sections': d['sections']})
        for f in d['functions']:
            fns.append(RefFn(f, elf))
        for o in d['objects']:
            objs.append(RefObj(o, elf))
    return fns, objs, elfs


def build_index(dump, cs, ce):
    idx8 = defaultdict(list)
    idx4 = defaultdict(list)
    idx2 = defaultdict(list)
    for o in range(cs, ce - 1, 2):
        idx2[dump[o:o + 2]].append(o)
        if o + 4 <= ce:
            idx4[dump[o:o + 4]].append(o)
        if o + 8 <= ce:
            idx8[dump[o:o + 8]].append(o)
    return idx8, idx4, idx2


def verify(dump, start, item):
    seg = dump[start:start + item.size]
    if len(seg) != item.size:
        return False
    return (int.from_bytes(seg, 'little') & item.maskint) == item.maskedint


def exact_search(item, idx8, idx4, idx2, dump, cs, ce):
    res = []
    if item.anchor is not None:
        off, win = item.anchor
        cands = (idx8 if len(win) == 8 else idx4).get(win, [])
        for c in cands:
            s = c - off
            if s < cs or s + item.size > ce or (s & 1):
                continue
            if verify(dump, s, item):
                res.append(s)
        return res
    # no fully-unmasked 4-byte window (call chains, effect stubs): masked scan.
    if item.size < 2:
        return []
    if item.mask[0] == 0xFF and item.mask[1] == 0xFF:
        cands = idx2.get(item.raw[0:2], [])
        for c in cands:
            if c + item.size <= ce and verify(dump, c, item):
                res.append(c)
        return res
    L = min(item.size, 16)
    pm = int.from_bytes(item.mask[:L], 'little')
    pv = int.from_bytes(item.masked[:L], 'little')
    for o in range(cs, ce - L + 1, 2):
        if (int.from_bytes(dump[o:o + L], 'little') & pm) == pv and verify(dump, o, item):
            res.append(o)
    return res


def decode_bl(dump, off, base):
    """Decode a Thumb-2 BL/B.W at file offset off; return absolute target or None."""
    if off + 4 > len(dump):
        return None
    hw1 = dump[off] | (dump[off + 1] << 8)
    hw2 = dump[off + 2] | (dump[off + 3] << 8)
    if (hw1 & 0xF800) != 0xF000 or (hw2 & 0xC000) != 0xC000 or not (hw2 & 0x1000):
        # not BL (0xF...D...) nor B.W T4 (0xF...9...)
        if (hw1 & 0xF800) == 0xF000 and (hw2 & 0xD000) == 0x9000:
            pass
        else:
            return None
    S = (hw1 >> 10) & 1
    imm10 = hw1 & 0x3FF
    J1 = (hw2 >> 13) & 1
    J2 = (hw2 >> 11) & 1
    imm11 = hw2 & 0x7FF
    I1 = (~(J1 ^ S)) & 1
    I2 = (~(J2 ^ S)) & 1
    imm = (S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1)
    if imm & (1 << 24):
        imm -= 1 << 25
    return base + off + 4 + imm


def decode_branch_out(dump, off, base):
    """Decode any B (T1..T4) / BL at file offset off, return target or None."""
    hw1 = dump[off] | (dump[off + 1] << 8)
    if (hw1 & 0xF800) == 0xF000:
        hw2 = dump[off + 2] | (dump[off + 3] << 8)
        if (hw2 & 0x1000) or (hw2 & 0xD000) == 0xD000:
            return decode_bl(dump, off, base)
        if (hw2 & 0xD000) == 0x8000:  # T3 conditional b.w
            S = (hw1 >> 10) & 1
            imm6 = hw1 & 0x3F
            J1 = (hw2 >> 13) & 1
            J2 = (hw2 >> 11) & 1
            imm11 = hw2 & 0x7FF
            imm = (S << 20) | (J2 << 19) | (J1 << 18) | (imm6 << 12) | (imm11 << 1)
            if imm & (1 << 20):
                imm -= 1 << 21
            return base + off + 4 + imm
        return None
    if (hw1 & 0xF000) == 0xD000:  # T1 conditional
        imm8 = hw1 & 0xFF
        if imm8 & 0x80:
            imm8 -= 0x100
        return base + off + 4 + imm8 * 2
    if (hw1 & 0xF800) == 0xE000:  # T2 unconditional
        imm11 = hw1 & 0x7FF
        if imm11 & 0x400:
            imm11 -= 0x800
        return base + off + 4 + imm11 * 2
    if (hw1 & 0xF500) == 0xB100:  # cbz/cbnz
        i = (hw1 >> 9) & 1
        imm5 = (hw1 >> 3) & 0x1F
        return base + off + 4 + ((i << 6) | (imm5 << 1))
    return None


def le32(b, i):
    return b[i] | (b[i + 1] << 8) | (b[i + 2] << 16) | (b[i + 3] << 24)


class Match(object):
    def __init__(self, start, size, kind):
        self.start = start          # file offset
        self.size = size
        self.kind = kind            # 'exact' | 'exact-ambiguous' | 'fuzzy' | 'fuzzy-anchored' | 'data' | 'data-ambiguous'
        self.names = {}             # name -> set(elfs)
        self.fns = {}               # name -> RefFn/RefObj (one representative)
        self.primary = None
        self.score = 1.0
        self.notes = []
        self.voted = False
        self.dump_calls = None      # [(off, target)] decoded from dump body

    def end(self):
        return self.start + self.size

    def label(self):
        return self.primary or '|'.join(sorted(self.names))

    def elfs(self):
        if self.primary:
            return sorted(self.names.get(self.primary, []))
        s = set()
        for v in self.names.values():
            s |= v
        return sorted(s)

    def ref(self):
        return self.fns.get(self.primary) if self.primary else None


def gap_runs(owner, cs, ce):
    runs = []
    i = cs
    while i < ce:
        if owner[i] == -1:
            j = i
            while j < ce and owner[j] == -1:
                j += 1
            runs.append((i, j))
            i = j
        else:
            i += 1
    return runs


def region_stats(seg):
    n = len(seg)
    if n == 0:
        return 'empty'
    ff = seg.count(0xFF) / n
    zz = seg.count(0) / n
    printable = sum(1 for c in seg if 32 <= c < 127 or c in (10, 13, 9)) / n
    if ff > 0.9:
        return 'erased(0xFF)'
    if zz > 0.9:
        return 'zeros'
    if printable > 0.8:
        return 'ascii-strings'
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dump')
    ap.add_argument('refs', nargs='+')
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=0x8000)
    ap.add_argument('--code-end', type=lambda x: int(x, 0), default=None)
    ap.add_argument('--out-dir', default=None)
    ap.add_argument('--fuzzy', type=float, default=0.85)
    ap.add_argument('--anchored', type=float, default=0.5)
    ap.add_argument('--min-region', type=int, default=32)
    ap.add_argument('--hooks', default=None, help='comma-separated extra hook names')
    ap.add_argument('--no-fuzzy', action='store_true')
    args = ap.parse_args()

    dump = open(args.dump, 'rb').read()
    base = args.base
    cs = args.code_start
    ce = args.code_end
    if ce is None:
        ce = len(dump)
        while ce > cs and dump[ce - 1] == 0xFF:
            ce -= 1
    ce = min(ce, len(dump))
    outdir = args.out_dir or os.path.dirname(os.path.abspath(args.dump))
    os.makedirs(outdir, exist_ok=True)
    log = []

    def P(*a):
        s = ' '.join(str(x) for x in a)
        print(s)
        log.append(s)

    P('dump %s: %d bytes, code region file 0x%X-0x%X (flash 0x%08X-0x%08X, %d bytes)' %
      (args.dump, len(dump), cs, ce, base + cs, base + ce, ce - cs))

    fns, objs, elfs = load_refs(args.refs)
    elf_order = [e['name'] for e in elfs]
    P('references: %s ; %d functions, %d objects' % (', '.join(elf_order), len(fns), len(objs)))
    idx8, idx4, idx2 = build_index(dump, cs, ce)

    # ---------------- 1. exact function matching ----------------
    claims = {}   # (start,size) -> {name: set(elfs)}, fns
    n_anchorless = 0
    n_tiny = 0
    for fn in fns:
        if fn.anchor is None:
            n_anchorless += 1
        if fn.size < 8:
            n_tiny += 1
        for s in exact_search(fn, idx8, idx4, idx2, dump, cs, ce):
            c = claims.setdefault((s, fn.size), ({}, {}))
            c[0].setdefault(fn.name, set()).add(fn.elf)
            c[1].setdefault(fn.name, fn)
    P('exact: %d candidate ranges from %d reference functions (%d needed masked-scan fallback, %d tiny <8B bodies gated by votes/adjacency)' %
      (len(claims), len(fns), n_anchorless, n_tiny))

    owner = array('i', [-1]) * len(dump)
    matches = []

    def place(m):
        for k in range(m.start, m.end()):
            if owner[k] != -1:
                return False
        mid = len(matches)
        matches.append(m)
        for k in range(m.start, m.end()):
            owner[k] = mid
        return True

    tiny_claims = []
    for (s, size), (names, fmap) in sorted(claims.items(), key=lambda kv: (-kv[0][1], kv[0][0])):
        m = Match(s, size, 'exact' if len(names) == 1 else 'exact-ambiguous')
        m.names = names
        m.fns = fmap
        if len(names) == 1:
            m.primary = next(iter(names))
        if any(getattr(f, 'inferred', False) for f in fmap.values()):
            m.notes.append('size inferred from next symbol (asm routine)')
        if size < 8:
            anyfn = next(iter(fmap.values()))
            bits = sum(bin(b).count('1') for b in anyfn.mask)
            # a lone masked 'b.n X' / 'b.w X' body matches every branch of that width: only a
            # caller vote may place it (never adjacency)
            m.weak_body = bits < 16
            tiny_claims.append(m)
            continue
        place(m)

    # ---------------- 2. votes ----------------
    votes = defaultdict(lambda: defaultdict(list))     # abs addr -> name -> [evidence]
    data_votes = defaultdict(lambda: defaultdict(list))  # name -> value -> [evidence]
    xrefs_to = defaultdict(list)                         # abs target -> [(caller label, caller addr, kind)]

    def emit_votes(m):
        fn = m.ref()
        if fn is None:
            return
        caddr = base + m.start
        for (off, tgt, tname) in fn.calls:
            T = decode_bl(dump, m.start + off, base)
            if T is None:
                continue
            xrefs_to[T].append((fn.name, caddr, 'bl'))
            if tname:
                votes[T][tname].append('bl from %s@0x%08X+0x%X' % (fn.name, caddr, off))
        for (off, tgt, tname) in fn.bouts:
            T = decode_branch_out(dump, m.start + off, base)
            if T is None:
                continue
            xrefs_to[T].append((fn.name, caddr, 'b'))
            if tname:
                votes[T][tname].append('b.w from %s@0x%08X+0x%X' % (fn.name, caddr, off))
        for (off, v, msk, names) in fn.lits:
            if not msk or m.start + off + 4 > len(dump):
                continue
            V = le32(dump, m.start + off)
            for nm in names:
                data_votes[nm][V].append('lit in %s@0x%08X+0x%X' % (fn.name, caddr, off))
            if (V & 1) and base + cs <= V < base + ce:
                xrefs_to[V - 1].append((fn.name, caddr, 'ptr'))
                for nm in names:
                    votes[V - 1][nm].append('fnptr lit in %s@0x%08X+0x%X' % (fn.name, caddr, off))

    # vector-table votes (from the first reference)
    if elfs and elfs[0]['vectors']:
        for (i, v, nm) in elfs[0]['vectors']:
            if i + 4 <= len(dump) and nm:
                V = le32(dump, i)
                if (V & 1) and base + cs <= V < base + ce:
                    votes[V - 1][nm].append('vector slot 0x%X' % i)
                    xrefs_to[V - 1].append(('_vectors', base + i, 'vec'))

    def vote_resolve_loop():
        changed = True
        while changed:
            changed = False
            for m in matches:
                if m.kind == 'exact-ambiguous' and m.primary is None:
                    inc = votes.get(base + m.start)
                    if inc:
                        inter = set(inc) & set(m.names)
                        if len(inter) == 1:
                            m.primary = inter.pop()
                            m.notes.append('ambiguous body {%s} resolved by caller: %s' %
                                           ('|'.join(sorted(m.names)), inc[m.primary][0]))
                            changed = True
                        elif len(inter) > 1:
                            # choose the one with most votes if strictly dominant
                            cnt = sorted(((len(inc[n]), n) for n in inter), reverse=True)
                            if cnt[0][0] > cnt[1][0]:
                                m.primary = cnt[0][1]
                                m.notes.append('ambiguous body resolved by majority of callers (%d vs %d)' %
                                               (cnt[0][0], cnt[1][0]))
                                changed = True
                if m.primary and not m.voted and m.kind in ('exact', 'exact-ambiguous'):
                    emit_votes(m)
                    m.voted = True
                    changed = True

    vote_resolve_loop()

    def place_tiny_round():
        placed = 0
        ends = set(m.end() for m in matches)
        starts = set(m.start for m in matches)
        rest = []
        for m in tiny_claims:
            if any(owner[k] != -1 for k in range(m.start, m.end())):
                continue
            v = votes.get(base + m.start, {})
            gate = None
            if set(v) & set(m.names):
                gate = 'vote'
            elif getattr(m, 'weak_body', False):
                gate = None
            elif m.start in ends and m.end() in starts:
                gate = 'adjacent-both'
            elif m.start in ends or m.end() in starts:
                gate = 'adjacent'
            if gate:
                m.notes.append('tiny body placed (%s)' % gate)
                if place(m):
                    placed += 1
            else:
                rest.append(m)
        tiny_claims[:] = rest
        return placed
    rounds = 0
    while True:
        n = place_tiny_round()
        rounds += 1
        vote_resolve_loop()
        if n == 0 or rounds > 20:
            break
    n_amb = sum(1 for m in matches if m.kind == 'exact-ambiguous' and m.primary is None)
    P('exact: placed %d ranges (%d tiny bodies left unplaced: no vote/adjacency); %d still ambiguous after caller voting' %
      (len(matches), len(tiny_claims), n_amb))

    # ---------------- 3. data objects ----------------
    obj_claims = {}
    for o in objs:
        if o.anchor is None or o.size < 8:
            continue
        for s in exact_search(o, idx8, idx4, idx2, dump, cs, ce):
            c = obj_claims.setdefault((s, o.size), ({}, {}))
            c[0].setdefault(o.name, set()).add(o.elf)
            c[1].setdefault(o.name, o)
    # objects that match at several places are unreliable unless unique per name
    name_places = defaultdict(set)
    for (s, size), (names, _) in obj_claims.items():
        for n in names:
            name_places[n].add(s)
    n_data = 0
    for (s, size), (names, omap) in sorted(obj_claims.items(), key=lambda kv: (-kv[0][1], kv[0][0])):
        uniq = [n for n in names if len(name_places[n]) == 1]
        m = Match(s, size, 'data' if uniq else 'data-ambiguous')
        m.names = names
        m.fns = omap
        if len(uniq) >= 1:
            m.primary = sorted(uniq)[0]
            if len(names) > 1:
                m.notes.append('other objects with same bytes: %s' % '|'.join(sorted(set(names) - {m.primary})))
        else:
            m.notes.append('object bytes occur at %d places' % max(len(name_places[n]) for n in names))
        if place(m):
            n_data += 1
    P('data: placed %d object ranges' % n_data)

    # ---------------- 4. fuzzy ----------------
    def fn_key_assigned():
        s = set()
        for m in matches:
            if m.kind.startswith('exact') or m.kind.startswith('fuzzy'):
                s |= set(m.names)
        return s

    def collect_candidates():
        cands = set()
        for (a, b) in gap_runs(owner, cs, ce):
            cands.add(a)
        for T in list(votes.keys()) + list(xrefs_to.keys()):
            cands.add(T - base)
        # literal function pointers anywhere in the image
        for o in range(0, min(len(dump), ce) - 3, 4):
            V = le32(dump, o)
            if (V & 1) and base + cs <= V < base + ce:
                cands.add(V - 1 - base)
        # BL targets from linear disassembly of the gaps
        for (a, b) in gap_runs(owner, cs, ce):
            nz = RS.normalize(dump[a:b], base + a, base + a, base + b)
            for (off, tgt) in nz['calls'] + nz['bouts']:
                if base + cs <= tgt < base + ce:
                    cands.add(tgt - base)
        out = set()
        for c in cands:
            if cs <= c < ce and (c & 1) == 0 and owner[c] == -1:
                out.add(c)
        return sorted(out)

    fuzzy_cache = {}
    FUZZY_MAX = 6144

    def dump_items(c, limit):
        # normalise once per candidate start up to the gap end (capped); callers slice by byte limit
        if c in fuzzy_cache:
            return fuzzy_cache[c]
        e = c
        while e < ce and owner[e] == -1 and e - c < FUZZY_MAX:
            e += 1
        nz = RS.normalize(dump[c:e], base + c, base + c, base + e)
        fuzzy_cache[c] = (nz, e)
        return fuzzy_cache[c]

    def score_at(fn, c, gap_end, cand_set):
        n = fn.size
        lo, hi = int(n * 0.9), int(n * 1.1) + 4
        nz, e = dump_items(c, hi)
        items = [it for it in nz['items'] if it[0] + it[1] <= hi]
        toks = [t for (_, _, t) in items]
        if not toks:
            return None
        sm = difflib.SequenceMatcher(None, fn.skel, toks, autojunk=False)
        if sm.quick_ratio() < min(args.fuzzy, args.anchored):
            return None
        r = sm.ratio()
        # size estimate: next candidate boundary within window, else last matching block end
        size = None
        for nc in cand_set:
            if nc > c and lo <= nc - c <= hi:
                size = nc - c
                break
        if size is None and gap_end is not None and lo <= gap_end - c <= hi:
            size = gap_end - c
        if size is None:
            blocks = [b for b in sm.get_matching_blocks() if b.size > 0]
            if blocks:
                last = blocks[-1]
                it = items[last.b + last.size - 1]
                size = it[0] + it[1]
        if size is None or not (lo <= size <= hi):
            return (r, None, nz)
        return (r, size, nz)

    fuzzy_report = []
    if not args.no_fuzzy:
        assigned = fn_key_assigned()
        leftovers = {}
        for fn in fns:
            if fn.name in assigned or fn.size < 10 or len(fn.skel) < 4:
                continue
            leftovers.setdefault((fn.name, fn.masked, fn.mask), fn)
        cand_list = collect_candidates()
        cand_set = sorted(cand_list)
        gaps = gap_runs(owner, cs, ce)

        def gap_of(c):
            for (a, b) in gaps:
                if a <= c < b:
                    return (a, b)
            return None
        P('fuzzy: %d leftover reference bodies vs %d function-start candidates in %d gaps' %
          (len(leftovers), len(cand_list), len(gaps)))
        proposals = []
        for fn in leftovers.values():
            per_fn = []
            for c in cand_list:
                g = gap_of(c)
                if g is None or g[1] - c < int(fn.size * 0.9):
                    continue
                anchored = fn.name in votes.get(base + c, {})
                if not anchored and (fn.size < 16 or len(fn.skel) < 6):
                    continue
                res = score_at(fn, c, g[1], cand_set)
                if res is None:
                    continue
                r, size, nz = res
                thr = args.anchored if anchored else args.fuzzy
                if r >= thr and size:
                    per_fn.append((r, anchored, fn, c, size, nz))
                elif anchored:
                    fuzzy_report.append('anchored candidate %s @0x%08X: skeleton ratio %.3f size_est=%s (below %.2f or size out of 10%%)' %
                                        (fn.name, base + c, r, size, thr))
            if not per_fn:
                continue
            per_fn.sort(key=lambda p: (-p[1], -p[0], p[3]))
            best = per_fn[0]
            if not best[1]:
                # unanchored: require a unique winner (margin 0.03) among unanchored candidates
                others = [p for p in per_fn[1:] if p[3] != best[3]]
                if others and others[0][0] >= best[0] - 0.03:
                    fuzzy_report.append('unanchored fuzzy for %s ambiguous: 0x%08X (%.3f) vs 0x%08X (%.3f) - not placed' %
                                        (fn.name, base + best[3], best[0], base + others[0][3], others[0][0]))
                    continue
            proposals.append(best)
            for p in per_fn[1:]:
                if p[1]:
                    proposals.append(p)
        proposals.sort(key=lambda p: (-p[0], p[3]))
        used_names = set()
        n_f = 0
        for (r, anchored, fn, c, size, nz) in proposals:
            if fn.name in used_names:
                continue
            m = Match(c, size, 'fuzzy-anchored' if anchored else 'fuzzy')
            m.names = {fn.name: {fn.elf}}
            m.fns = {fn.name: fn}
            m.primary = fn.name
            m.score = r
            if anchored:
                m.notes.append('call-anchored: %s' % votes[base + c][fn.name][0])
            if place(m):
                used_names.add(fn.name)
                n_f += 1
                # fuzzy votes: pair BLs in order if counts equal
                for key, tag in (('calls', 'bl'), ('bouts', 'b.w')):
                    dl = [(off, tgt) for (off, tgt) in nz[key] if off < size]
                    rl = getattr(fn, key)
                    if len(dl) == len(rl) and dl:
                        for (doff, dt), (roff, rt, rname) in zip(dl, rl):
                            if rname:
                                votes[dt][rname].append('%s(fuzzy-paired) from %s@0x%08X+0x%X' % (tag, fn.name, base + c, doff))
                                xrefs_to[dt].append((fn.name, base + c, tag + '~'))
                m.voted = True
        P('fuzzy: accepted %d (%d proposals)' % (n_f, len(proposals)))
        vote_resolve_loop()

    # ---------------- 5. reports ----------------
    def name_at(T):
        o = T - base
        if 0 <= o < len(dump) and owner[o] != -1:
            m = matches[owner[o]]
            if m.start == o:
                return m.label()
            return '%s+0x%X' % (m.label(), o - m.start)
        return None

    fn_bytes = defaultdict(int)
    for m in matches:
        fn_bytes[m.kind] += m.size
    exact_bytes = fn_bytes['exact'] + fn_bytes['exact-ambiguous']
    fuzzy_bytes = fn_bytes['fuzzy']
    anch_bytes = fn_bytes['fuzzy-anchored']
    data_bytes = fn_bytes['data'] + fn_bytes['data-ambiguous']
    total = ce - cs

    # per-elf participation
    elf_bytes = defaultdict(int)
    elf_only = defaultdict(int)
    for m in matches:
        if not m.kind.startswith('exact'):
            continue
        es = set()
        for v in m.names.values():
            es |= v
        for e in es:
            elf_bytes[e] += m.size
        if len(es) == 1:
            elf_only[next(iter(es))] += m.size

    # CSV
    rows = []
    for m in sorted(matches, key=lambda m: m.start):
        ref = m.ref()
        ref_addr = ''
        elfl = m.elfs()
        if ref is not None:
            ref_addr = '0x%08X' % ref.addr
        elif m.names:
            anyfn = next(iter(m.fns.values()))
            ref_addr = '0x%08X' % anyfn.addr
        notes = list(m.notes)
        if m.kind == 'exact-ambiguous' and m.primary is None:
            notes.append('identical body for: %s' % '|'.join(sorted(m.names)))
        elif m.primary and len(m.names) > 1 and m.kind.startswith('exact'):
            alts = sorted(set(m.names) - {m.primary})
            notes.append('same body also matches: %s' % '|'.join(alts))
        xr = xrefs_to.get(base + m.start)
        if xr:
            notes.append('xrefs: ' + ' '.join('%s@0x%08X(%s)' % x for x in xr[:4]) + (' ...' if len(xr) > 4 else ''))
        rows.append({'dump_addr': '0x%08X' % (base + m.start), 'size': m.size, 'ref_symbol': m.label(),
                     'ref_elf': ','.join(elfl), 'ref_addr': ref_addr, 'match_type': m.kind,
                     'score': '%.3f' % m.score, 'notes': ' ; '.join(notes)})
    with open(os.path.join(outdir, 'functions_matched.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=['dump_addr', 'size', 'ref_symbol', 'ref_elf', 'ref_addr', 'match_type',
                                          'score', 'notes'])
        w.writeheader()
        for r in rows:
            w.writerow(r)

    # hooks
    hook_names = list(DEFAULT_HOOKS)
    if args.hooks:
        hook_names += [h.strip() for h in args.hooks.split(',') if h.strip()]
    for T, v in votes.items():
        for nm in v:
            if (nm.endswith('_user') or nm.endswith('_kb')) and nm not in hook_names:
                hook_names.append(nm)
    by_name = defaultdict(list)
    for m in matches:
        if m.primary:
            by_name[m.primary].append(m)

    # every plausible function start in the image: match starts, vote/xref targets,
    # BL targets found by disassembling the unmatched gaps, literal function pointers
    starts = set(m.start for m in matches)
    for T in list(votes.keys()) + list(xrefs_to.keys()):
        starts.add(T - base)
    for (a, b) in gap_runs(owner, cs, ce):
        nz = RS.normalize(dump[a:b], base + a, base + a, base + b)
        for (off, tgt) in nz['calls'] + nz['bouts']:
            if base + cs <= tgt < base + ce:
                starts.add(tgt - base)
    for o in range(0, min(len(dump), ce) - 3, 4):
        V = le32(dump, o)
        if (V & 1) and base + cs <= V < base + ce:
            starts.add(V - 1 - base)
    starts = sorted(x for x in starts if cs <= x < ce and (x & 1) == 0)

    def next_boundary(o):
        e = o
        while e < ce and owner[e] == -1:
            e += 1
        return e

    def next_start(o):
        for x in starts:
            if x > o:
                return x
        return ce

    def est_size(o):
        return min(next_boundary(o), next_start(o)) - o

    # unmatched regions
    regions = []
    text_end = max([m.end() for m in matches if m.kind.startswith('exact') or m.kind.startswith('fuzzy')] or [cs])
    for (a, b) in gap_runs(owner, cs, ce):
        size = b - a
        seg = dump[a:b]
        kind = region_stats(seg)
        if kind is None and a >= text_end:
            kind = 'post-text(rodata/.data image)'
        callers = []
        callees = []
        sugg = []
        if (kind is None or kind.startswith('post-text')) and size >= 4:
            nz = RS.normalize(seg, base + a, base + a, base + b)
            bad = sum(1 for it in nz['items'] if it[2] == 'BAD')
            if kind is None:
                if len(nz['items']) and bad / len(nz['items']) > 0.3:
                    kind = 'data-like(%d%% undecodable)' % int(100 * bad / len(nz['items']))
                else:
                    kind = 'code'
            for (off, tgt) in nz['calls'] + nz['bouts']:
                nm = name_at(tgt)
                callees.append('0x%08X->%s' % (base + a + off, nm or ('0x%08X' % tgt)))
        for T in range(a, b, 2):
            xr = xrefs_to.get(base + T)
            if xr:
                for (cn, ca, k) in xr[:3]:
                    callers.append('0x%08X<-%s@0x%08X(%s)' % (base + T, cn, ca, k))
            v = votes.get(base + T)
            if v:
                for nm in sorted(v):
                    sugg.append('0x%08X=%s' % (base + T, nm))
        inner = [x for x in starts if a < x < b]
        regions.append({'start': '0x%08X' % (base + a), 'size': size, 'kind': kind or 'code',
                        'fn_starts': ' '.join('0x%08X' % (base + x) for x in inner[:24]) + (' ...' if len(inner) > 24 else ''),
                        'suggested_names': ' '.join(sugg[:12]), 'callers': ' '.join(callers[:12]),
                        'callees': ' '.join(callees[:16])})
    with open(os.path.join(outdir, 'unmatched_regions.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=['start', 'size', 'kind', 'fn_starts', 'suggested_names', 'callers', 'callees'])
        w.writeheader()
        for r in regions:
            if r['size'] >= args.min_region:
                w.writerow(r)
    big = [r for r in regions if r['size'] >= args.min_region]

    hook_rows = []
    for nm in hook_names:
        ms = by_name.get(nm, [])
        vaddrs = sorted(T for T, v in votes.items() if nm in v)
        if not ms and not vaddrs:
            hook_rows.append({'hook': nm, 'dump_addr': '', 'size': '', 'status': 'not-found', 'ref_elf': '',
                              'evidence': 'no body match, no caller vote'})
            continue
        seen = set()
        for m in ms:
            seen.add(m.start)
            ev = []
            v = votes.get(base + m.start, {})
            for n2, e2 in v.items():
                ev.append('%s:%s' % (n2, e2[0]))
            status = m.kind + ('' if m.primary else '(unresolved:%s)' % '|'.join(sorted(m.names)))
            hook_rows.append({'hook': nm, 'dump_addr': '0x%08X' % (base + m.start), 'size': m.size,
                              'status': status, 'ref_elf': ','.join(m.elfs()), 'evidence': ' ; '.join(ev[:4])})
        for T in vaddrs:
            o = T - base
            if o in seen:
                continue
            ev = ['%s' % e for e in votes[T][nm][:3]]
            others = sorted(set(votes[T]) - {nm})
            if 0 <= o < len(dump) and owner[o] != -1:
                m = matches[owner[o]]
                status = 'vote points inside %s@0x%08X+0x%X (%s)' % (m.label(), base + m.start, o - m.start, m.kind)
                size = ''
            else:
                status = 'UNMATCHED-custom-code-candidate'
                size = est_size(o) if 0 <= o < len(dump) else ''
            if others:
                ev.append('other names voted here: %s' % '|'.join(others))
            hook_rows.append({'hook': nm, 'dump_addr': '0x%08X' % T, 'size': size, 'status': status, 'ref_elf': '',
                              'evidence': ' ; '.join(ev)})
    # tap dance table + .data mapping
    td_lines = []

    def dv(name):
        d = data_votes.get(name)
        if not d:
            return None
        best = sorted(d.items(), key=lambda kv: -len(kv[1]))[0]
        return best[0], best[1][0], len(d)
    tdb = dbs = den = None
    # primary evidence: the crt0 data-copy literal triple (ldr r1,=__textdata_base__; ldr r2,=__data_base__;
    # ldr r3,=__data_end__) in the literal pool of _crt0_entry: (flash, ram, ram) ascending, ram span < 16 KB
    for o in range(cs, cs + 0x200, 4):
        a_, b_, c_ = le32(dump, o), le32(dump, o + 4), le32(dump, o + 8)
        if base + cs <= a_ < base + ce and 0x20000000 <= b_ < c_ < 0x20010000 and (c_ - b_) < 0x4000:
            td_lines.append('crt0 literal triple at 0x%08X (words %08X %08X %08X): __textdata_base__=0x%08X __data_base__=0x%08X __data_end__=0x%08X (.data %d bytes)' %
                            (base + o, a_, b_, c_, a_, b_, c_, c_ - b_))
            tdb, dbs, den = (a_, 'crt0-scan', 1), (b_, 'crt0-scan', 1), (c_, 'crt0-scan', 1)
            break
    v3 = tuple(dv(n) for n in ('__textdata_base__', '__data_base__', '__data_end__'))
    td_lines.append('cross-check, literal votes from matched code (may alias objects at the same address): __textdata_base__=%s __data_base__=%s __data_end__=%s' %
                    tuple(('0x%08X (%s%s)' % (x[0], x[1], '' if x[2] == 1 else ', %d distinct values' % x[2])) if x else 'n/a' for x in v3))
    if not (tdb and dbs and den):
        tdb, dbs, den = v3
    tda = dv('tap_dance_actions')
    td_lines.append('tap_dance_actions RAM address (literal votes): %s' %
                    ('0x%08X via %s%s' % (tda[0], tda[1], '' if tda[2] == 1 else ' (%d distinct values!)' % tda[2]) if tda else 'n/a'))
    td_entries = []
    if tda and tdb and dbs:
        ram = tda[0]
        fl = tdb[0] + (ram - dbs[0])
        fo = fl - base
        td_lines.append('tap_dance_actions init image in flash: 0x%08X (file 0x%X)' % (fl, fo))
        for i in range(16):
            e = fo + i * 28
            if e + 28 > len(dump):
                break
            st = dump[e:e + 8]
            ptrs = [le32(dump, e + 8 + 4 * k) for k in range(4)]
            ud = le32(dump, e + 24)
            okp = all(p == 0 or ((p & 1) and base + cs <= p < base + ce) for p in ptrs)
            if not okp or any(st) or not any(ptrs):
                break
            names = []
            for p in ptrs:
                if p == 0:
                    names.append('NULL')
                else:
                    nm = name_at(p - 1)
                    names.append('0x%08X(%s)' % (p, nm or 'UNMATCHED'))
            td_entries.append((i, ptrs, ud, names))
            td_lines.append('  td[%d]: on_each_tap=%s on_dance_finished=%s on_reset=%s on_each_release=%s user_data=0x%08X' %
                            (i, names[0], names[1], names[2], names[3], ud))
        if not td_entries:
            td_lines.append('  no valid tap_dance_action_t entries parsed at that location')
        else:
            # region sizes for callbacks
            for (i, ptrs, ud, names) in td_entries:
                for p in ptrs:
                    if p:
                        o = p - 1 - base
                        if 0 <= o < len(dump) and owner[o] == -1:
                            td_lines.append('  callback 0x%08X is in unmatched code, estimated extent (to next function start): %d bytes' %
                                            (p, est_size(o)))
                        elif 0 <= o < len(dump):
                            m = matches[owner[o]]
                            td_lines.append('  callback 0x%08X -> %s (%s, size %d)' % (p, m.label(), m.kind, m.size))

    for (i, ptrs, ud, names) in td_entries:
        for k, fld in enumerate(('on_each_tap', 'on_dance_finished', 'on_reset', 'on_each_release')):
            p_ = ptrs[k]
            if not p_:
                continue
            o = p_ - 1 - base
            if owner[o] != -1:
                m = matches[owner[o]]
                st = '%s@0x%08X+0x%X (%s)' % (m.label(), base + m.start, o - m.start, m.kind)
                sz = m.size if m.start == o else ''
            else:
                st = 'UNMATCHED-custom-code-candidate'
                sz = est_size(o)
            hook_rows.append({'hook': 'tap_dance_actions[%d].fn.%s' % (i, fld), 'dump_addr': '0x%08X' % (p_ - 1), 'size': sz,
                              'status': st, 'ref_elf': '', 'evidence': 'pointer 0x%08X in tap_dance_actions init image' % p_})
    with open(os.path.join(outdir, 'hooks.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=['hook', 'dump_addr', 'size', 'status', 'ref_elf', 'evidence'])
        w.writeheader()
        for r in hook_rows:
            w.writerow(r)

    # coverage.txt
    lines = []
    lines.append('funcmatch coverage report')
    lines.append('dump: %s' % os.path.abspath(args.dump))
    lines.append('refs: %s' % ', '.join(os.path.abspath(r) for r in args.refs))
    lines.append('code region: flash 0x%08X-0x%08X (%d bytes)' % (base + cs, base + ce, total))
    lines.append('')
    lines.append('exact function bytes       : %6d (%.2f%%)  [%d ranges, %d ambiguous-unresolved]' %
                 (exact_bytes, 100.0 * exact_bytes / total,
                  sum(1 for m in matches if m.kind.startswith('exact')),
                  sum(1 for m in matches if m.kind == 'exact-ambiguous' and m.primary is None)))
    lines.append('fuzzy function bytes       : %6d (%.2f%%)  [%d ranges, threshold %.2f]' %
                 (fuzzy_bytes, 100.0 * fuzzy_bytes / total, sum(1 for m in matches if m.kind == 'fuzzy'), args.fuzzy))
    lines.append('fuzzy-anchored bytes       : %6d (%.2f%%)  [%d ranges, threshold %.2f; NOT stock, similar-only]' %
                 (anch_bytes, 100.0 * anch_bytes / total, sum(1 for m in matches if m.kind == 'fuzzy-anchored'), args.anchored))
    lines.append('data object bytes          : %6d (%.2f%%)  [%d ranges]' %
                 (data_bytes, 100.0 * data_bytes / total, sum(1 for m in matches if m.kind.startswith('data'))))
    matched_fn = exact_bytes + fuzzy_bytes
    lines.append('function coverage (exact+fuzzy) : %.2f%%' % (100.0 * matched_fn / total))
    lines.append('total assigned (incl. data, anchored): %.2f%%' % (100.0 * (matched_fn + anch_bytes + data_bytes) / total))
    unm = sum(r['size'] for r in regions)
    lines.append('unmatched bytes            : %6d (%.2f%%) in %d regions (%d regions >= %d bytes, %d bytes)' %
                 (unm, 100.0 * unm / total, len(regions), len(big), args.min_region, sum(r['size'] for r in big)))
    lines.append('')
    lines.append('per-reference-ELF participation in exact matches (bytes; "only" = matched by no other ELF):')
    for e in elf_order:
        lines.append('  %-22s %6d bytes  only-this-elf %6d' % (e, elf_bytes.get(e, 0), elf_only.get(e, 0)))
    nfn_by_elf = defaultdict(int)
    for m in matches:
        if m.kind.startswith('exact'):
            es = set()
            for v in m.names.values():
                es |= v
            for e in es:
                nfn_by_elf[e] += 1
    lines.append('  functions exact-matched per ELF: ' + ', '.join('%s=%d' % (e, nfn_by_elf.get(e, 0)) for e in elf_order))
    lines.append('')
    lines.append('key objects:')
    for m in matches:
        if m.kind.startswith('data') and m.primary in ('keymaps', 'encoder_map', 'g_led_config', 'tap_dance_actions',
                                                       'macro_buffer', 'g_rgb_matrix', 'rgb_matrix_effects'):
            lines.append('  %-16s at 0x%08X size %d (%s)' % (m.primary, base + m.start, m.size, m.kind))
    km = [m for m in matches if m.kind.startswith('data') and 'keymaps' in m.names]
    if not km:
        lines.append('  keymaps: NOT found as exact data object')
    lines.append('')
    lines.append('tap dance / .data mapping:')
    lines.extend('  ' + l for l in td_lines)
    lines.append('')
    lines.append('hooks (see hooks.csv):')
    for r in hook_rows:
        if r['status'] != 'not-found':
            lines.append('  %-36s %-12s %-6s %s  %s' % (r['hook'], r['dump_addr'], r['size'], r['status'], r['evidence'][:160]))
    nf = [r['hook'] for r in hook_rows if r['status'] == 'not-found']
    lines.append('  not found (no body, no caller vote): ' + ', '.join(nf))
    lines.append('')
    lines.append('unmatched regions >= %d bytes:' % args.min_region)
    for r in big:
        lines.append('  %s size %5d %-28s starts[%s] sugg[%s] callers[%s] callees[%s]' %
                     (r['start'], r['size'], r['kind'], r['fn_starts'][:160], r['suggested_names'][:160], r['callers'][:200], r['callees'][:200]))
    if fuzzy_report:
        lines.append('')
        lines.append('anchored-but-rejected fuzzy candidates:')
        lines.extend('  ' + l for l in fuzzy_report)
    lines.append('')
    lines.append('log:')
    lines.extend('  ' + l for l in log)
    with open(os.path.join(outdir, 'coverage.txt'), 'w') as f:
        f.write('\n'.join(lines) + '\n')

    # machine-readable
    jm = []
    for m in matches:
        jm.append({'dump_addr': base + m.start, 'size': m.size, 'kind': m.kind, 'primary': m.primary,
                   'names': {n: sorted(v) for n, v in m.names.items()}, 'score': m.score, 'notes': m.notes})
    jv = {('0x%08X' % T): {n: e for n, e in v.items()} for T, v in votes.items()}
    jd = {n: {('0x%08X' % val): e for val, e in v.items()} for n, v in data_votes.items()}
    with open(os.path.join(outdir, 'matches.json'), 'w') as f:
        json.dump({'dump': os.path.abspath(args.dump), 'base': base, 'code_start': cs, 'code_end': ce,
                   'matches': jm, 'votes': jv, 'data_votes': jd, 'regions': regions, 'hooks': hook_rows,
                   'tap_dance': td_lines}, f, indent=1)
    print('\n'.join(lines[:14]))
    print('wrote %s/{functions_matched.csv,unmatched_regions.csv,coverage.txt,hooks.csv,matches.json}' % outdir)


if __name__ == '__main__':
    main()
