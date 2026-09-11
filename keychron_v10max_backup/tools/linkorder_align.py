#!/usr/bin/env python3
"""linkorder_align.py -- method B: align the function sequence detected in a flat
firmware image (fw_funcs.py) against the link-order function sequence of a reference
build (GNU ld .map + .bin), using a banded DP sequence alignment.

  uv run --with capstone python3 linkorder_align.py --target dump.bin --target-code-end 0x16704
      --target-image-end 0x17F04 --ref-map ref.map --ref-bin ref.bin --out functions_linkorder.csv
      [--truth-map target.map]  (calibration: score assigned symbols against the target's own map)

Scoring (per candidate pair ref a / target b):
  size similarity 3*(1-|sa-sb|/max) - 1.6, BL fan-out (+0.6 equal / -0.4 far), push prologue,
  Jaccard of peripheral constants (0x4xxxxxxx / 0xE000xxxx), shared string / rodata-content
  tokens (+1.5 each, capped), shared large immediates, hard anchors (+/-15: vector-table ISRs),
  call-graph bonus in refinement rounds (+1.5 per callee / caller symbol consistent with the
  previous round's assignment). Gaps cost 0.5 + min(size,512)/300; 2:1 merges cost an extra 1.0.
"""
import sys, os, json, argparse, struct, bisect, re, csv
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from parse_map import parse_map
import fw_funcs

BASE = 0x08000000


def map_sections(map_path):
    txt = open(map_path, errors='replace').read()
    m = re.search(r'^\.text\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)', txt, re.M)
    text = (int(m.group(1), 16), int(m.group(2), 16))
    m = re.search(r'^\.rodata\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)', txt, re.M)
    rodata = (int(m.group(1), 16), int(m.group(2), 16))
    m = re.search(r'^\.data\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) load address 0x([0-9a-f]+)', txt, re.M)
    data = (int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 16))
    return dict(text=text, rodata=rodata, data=data)


def sym_of(e):
    if e['syms']:
        # prefer a symbol at the section start
        at_start = [s for a, s in e['syms'] if a == e['addr']]
        return at_start[0] if at_start else e['syms'][0][1]
    n = e['name']
    return n[6:] if n.startswith('.text.') else n


class Func:
    __slots__ = ('idx', 'addr', 'size', 'sym', 'obj', 'n_bl', 'push', 'consts', 'strs', 'ro', 'imms', 'bl',
                 'entry', 'anchor', 'callee_syms', 'caller_syms', 'end')

    def __init__(self, idx, addr, size, sym, obj, f):
        self.idx = idx; self.addr = addr; self.size = size; self.sym = sym; self.obj = obj
        self.end = addr + size
        self.n_bl = f['n_bl']; self.push = f['push']
        self.consts = frozenset(f['consts']); self.strs = frozenset(f['strings']); self.ro = frozenset(f['rodata'])
        self.imms = frozenset(f['imms']); self.bl = list(f['bl']); self.entry = f.get('entry', '')
        self.anchor = None; self.callee_syms = frozenset(); self.caller_syms = frozenset()


LIBC_RE = re.compile(r'(libc_a-|lib_a-|libg_nano|libc_nano|libm_nano|libm\.a|libc\.a|libg\.a)')


def is_libc_obj(objpath):
    return bool(LIBC_RE.search(objpath or ''))


def load_ref(map_path, bin_path, libc_front=False):
    secs = map_sections(map_path)
    ents = parse_map(map_path)
    text = [e for e in ents if e['outsec'] == '.text' and e['name'] != '*fill*' and e['size'] > 0]
    text.sort(key=lambda e: e['addr'])
    reordered = False
    if libc_front:
        # model a toolchain whose newlib has no per-function sections: its members fall into the
        # *(.text) group, i.e. right after the last plain '.text' input section of the reference
        plain = [k for k, e in enumerate(text) if e['name'] == '.text']
        cut = plain[-1] + 1 if plain else 0
        head = text[:cut]
        libc = [e for e in text[cut:] if is_libc_obj(e['obj'])]
        rest = [e for e in text[cut:] if not is_libc_obj(e['obj'])]
        text = head + libc + rest
        reordered = True
    data = open(bin_path, 'rb').read()
    text_end = secs['text'][0] + secs['text'][1]
    image_end = secs['data'][2] + secs['data'][1]
    an = fw_funcs.Analyzer(data, BASE, secs['text'][0] - BASE, text_end - BASE, image_end - BASE).analyze()
    # override ranges with the map's (contiguous in address order, fills attached to the previous function)
    by_addr = sorted(text, key=lambda e: e['addr'])
    ranges = []
    for k, e in enumerate(by_addr):
        s = e['addr']
        nxt = by_addr[k + 1]['addr'] if k + 1 < len(by_addr) else text_end
        ranges.append((s, nxt))
    an.func_ranges = ranges
    an.features()
    feat_by_addr = {f['start']: f for f in an.funcs}
    funcs = []
    for k, e in enumerate(text):
        obj = os.path.basename(e['obj'].split('(')[-1].rstrip(')')) if e['obj'] else ''
        funcs.append(Func(k, e['addr'], e['size'], sym_of(e), obj, feat_by_addr[e['addr']]))
    return funcs, an, secs, ents


def load_target(bin_path, code_end, image_end):
    data = open(bin_path, 'rb').read()
    an = fw_funcs.Analyzer(data, BASE, 0x8000, code_end, image_end).analyze()
    funcs = [Func(k, f['start'], f['size'], None, None, f) for k, f in enumerate(an.funcs)]
    return funcs, an


def containing(funcs, addr):
    starts = [f.addr for f in funcs]
    i = bisect.bisect_right(starts, addr) - 1
    if i >= 0 and funcs[i].addr <= addr < funcs[i].end:
        return funcs[i]
    return None


def vector_anchors(tan, ran, rfuncs, tfuncs):
    """Map target function -> ref symbol via identical vector-table slots."""
    anchors = {}
    for off in range(4, 0x1e0, 4):
        tv = tan.u32(BASE + off); rv = ran.u32(BASE + off)
        if not (tv & 1 and rv & 1):
            continue
        rf = containing(rfuncs, rv - 1); tf = containing(tfuncs, tv - 1)
        if rf and tf:
            anchors.setdefault(tf.idx, set()).add(rf.sym)
    out = {}
    for ti, syms in anchors.items():
        if len(syms) == 1:
            out[ti] = next(iter(syms))
    return out


# ------------------------------------------------------------------ scoring
def size_sim(sa, sb):
    if max(sa, sb) <= 4:
        return 1.0 if sa == sb else 0.5
    return 1.0 - abs(sa - sb) / max(sa, sb)


def pair_score(a, b, use_anchor=True, cg=None):
    sc = 3.0 * size_sim(a.size, b.size) - 1.6
    if a.n_bl == b.n_bl:
        sc += 0.6 if a.n_bl > 0 else 0.3
    elif abs(a.n_bl - b.n_bl) == 1:
        sc += 0.1
    else:
        sc -= 0.4
    sc += 0.2 if a.push == b.push else -0.3
    if a.consts or b.consts:
        inter = len(a.consts & b.consts); uni = len(a.consts | b.consts)
        sc += 2.0 * inter / uni - (0.6 if inter == 0 else 0.0)
    shared = len(a.strs & b.strs) + len(a.ro & b.ro)
    sc += min(shared, 3) * 1.5
    if shared == 0 and (a.strs or a.ro) and (b.strs or b.ro):
        sc -= 0.3
    sc += min(len(a.imms & b.imms), 2) * 0.3
    if cg is not None:
        sc += cg
    if use_anchor and b.anchor is not None:
        sc += 15.0 if b.anchor == a.sym else -15.0
    return sc


MERGE_MIN_SIM = 0.7


def gap_cost(size):
    return -(0.5 + min(size, 512) / 300.0)


class Merged:
    """Pseudo-function for 2:1 moves."""
    def __init__(self, x, y):
        self.size = x.size + y.size; self.n_bl = x.n_bl + y.n_bl; self.push = x.push
        self.consts = x.consts | y.consts; self.strs = x.strs | y.strs; self.ro = x.ro | y.ro
        self.imms = x.imms | y.imms; self.sym = x.sym; self.anchor = getattr(x, 'anchor', None) or getattr(y, 'anchor', None)
        self.callee_syms = x.callee_syms | y.callee_syms; self.caller_syms = x.caller_syms | y.caller_syms


def cg_bonus(a, b):
    if not (b.callee_syms or b.caller_syms):
        return 0.0
    k = len(a.callee_syms & b.callee_syms) + len(a.caller_syms & b.caller_syms)
    return min(k, 4) * 1.5


def align(A, B, band=260, use_cg=False):
    n, m = len(A), len(B)
    NEG = -1e18
    # DP over i (ref, 0..n) and j (target, 0..m); band around the diagonal
    import array
    S = [dict() for _ in range(n + 1)]
    P = [dict() for _ in range(n + 1)]
    S[0][0] = 0.0; P[0][0] = None
    ratio = n / max(m, 1)

    def get(i, j):
        return S[i].get(j, NEG)

    for i in range(0, n + 1):
        jc = int(round(i / ratio)) if ratio else 0
        jlo = max(0, jc - band); jhi = min(m, jc + band)
        for j in range(jlo, jhi + 1):
            if i == 0 and j == 0:
                continue
            best = NEG; bp = None
            if i > 0:
                v = get(i - 1, j)
                if v > NEG:
                    v += gap_cost(A[i - 1].size)
                    if v > best:
                        best, bp = v, ('gapA',)
            if j > 0:
                v = get(i, j - 1)
                if v > NEG:
                    v += gap_cost(B[j - 1].size)
                    if v > best:
                        best, bp = v, ('gapB',)
            if i > 0 and j > 0:
                v = get(i - 1, j - 1)
                if v > NEG:
                    a, b = A[i - 1], B[j - 1]
                    v += pair_score(a, b, cg=cg_bonus(a, b) if use_cg else None)
                    if v > best:
                        best, bp = v, ('match',)
            if i > 1 and j > 0:   # two refs -> one target (only when the sizes add up)
                v = get(i - 2, j)
                if v > NEG and size_sim(A[i - 2].size + A[i - 1].size, B[j - 1].size) >= MERGE_MIN_SIM:
                    a = Merged(A[i - 2], A[i - 1]); b = B[j - 1]
                    v += pair_score(a, b, cg=cg_bonus(a, b) if use_cg else None) - 1.0
                    if v > best:
                        best, bp = v, ('merge2A',)
            if i > 0 and j > 1:   # one ref -> two targets (only when the sizes add up)
                v = get(i, j - 2)
                if v > NEG and size_sim(A[i - 1].size, B[j - 2].size + B[j - 1].size) >= MERGE_MIN_SIM:
                    a = A[i - 1]; b = Merged(B[j - 2], B[j - 1])
                    v += pair_score(a, b, cg=cg_bonus(a, b) if use_cg else None) - 1.0
                    if v > best:
                        best, bp = v, ('merge2B',)
            if bp is not None:
                S[i][j] = best; P[i][j] = bp
    # traceback
    i, j = n, m
    if j not in S[n]:
        # find best reachable end
        cand = [(S[n][jj], jj) for jj in S[n]]
        j = max(cand)[1]
    ops = []
    while (i, j) != (0, 0):
        bp = P[i][j]
        if bp is None:
            break
        k = bp[0]
        if k == 'gapA':
            ops.append(('gapA', i - 1, None)); i -= 1
        elif k == 'gapB':
            ops.append(('gapB', None, j - 1)); j -= 1
        elif k == 'match':
            ops.append(('match', i - 1, j - 1)); i -= 1; j -= 1
        elif k == 'merge2A':
            ops.append(('merge2A', (i - 2, i - 1), j - 1)); i -= 2; j -= 1
        elif k == 'merge2B':
            ops.append(('merge2B', i - 1, (j - 2, j - 1))); i -= 1; j -= 2
    ops.reverse()
    return ops, S[n].get(m, max(S[n].values()))


def assignment_from_ops(ops, A, B):
    """target idx -> (ref indices tuple, kind)"""
    asg = {}
    for op in ops:
        k, ia, jb = op
        if k == 'match':
            asg[jb] = ((ia,), 'match')
        elif k == 'merge2A':
            asg[jb] = (ia, 'merge2A')
        elif k == 'merge2B':
            asg[jb[0]] = ((ia,), 'split1'); asg[jb[1]] = ((ia,), 'split2')
    return asg


def compute_callgraph_syms(A, B, asg):
    """Fill callee/caller symbol sets for ref and target functions."""
    # ref: callee syms via containing function
    rstarts = [f.addr for f in A]
    def rcont(addr):
        i = bisect.bisect_right(rstarts, addr) - 1
        return A[i] if i >= 0 and A[i].addr <= addr < A[i].end else None
    rcallers = {f.idx: set() for f in A}
    for f in A:
        cs = set()
        for t in f.bl:
            g = rcont(t)
            if g:
                cs.add(g.sym); rcallers[g.idx].add(f.sym)
        f.callee_syms = frozenset(cs)
    for f in A:
        f.caller_syms = frozenset(rcallers[f.idx])
    # target: callee syms via assignment
    tstarts = [f.addr for f in B]
    def tcont(addr):
        i = bisect.bisect_right(tstarts, addr) - 1
        return B[i] if i >= 0 and B[i].addr <= addr < B[i].end else None
    def tsym(f):
        if f.idx in asg:
            return A[asg[f.idx][0][0]].sym
        return None
    tcallers = {f.idx: set() for f in B}
    for f in B:
        cs = set()
        for t in f.bl:
            g = tcont(t)
            if g:
                s = tsym(g)
                if s:
                    cs.add(s)
                me = tsym(f)
                if me:
                    tcallers[g.idx].add(me)
        f.callee_syms = frozenset(cs)
    for f in B:
        f.caller_syms = frozenset(tcallers[f.idx])


def consistency(a, b):
    """fraction of b's resolved callees whose symbol is among a's callees (and callers likewise)."""
    tot = len(b.callee_syms) + len(b.caller_syms)
    if tot == 0:
        return None
    ok = len(a.callee_syms & b.callee_syms) + len(a.caller_syms & b.caller_syms)
    return ok / tot, ok, tot


def mnemonics(an, start, end):
    out = []
    a = start
    while a < end:
        n = an.insns.get(a)
        if n is None:
            a += 2; continue
        out.append(n.mn)
        a += n.size
    return out


def opcode_similarity(an_a, a, an_b, b):
    import difflib
    ma = mnemonics(an_a, a.addr, a.end); mb = mnemonics(an_b, b.addr, b.end)
    if not ma or not mb:
        return None
    return difflib.SequenceMatcher(None, ma, mb, autojunk=False).ratio()


def rodata_content_match(ref_ents, ref_bin, tgt_data, tgt_ro_start, tgt_ro_end):
    """Match ref .rodata input sections into the target rodata region by exact content."""
    rbin = open(ref_bin, 'rb').read()
    out = []
    ro = [e for e in ref_ents if e['outsec'] == '.rodata' and e['name'] != '*fill*' and e['size'] >= 8]
    region = tgt_data[tgt_ro_start - BASE:tgt_ro_end - BASE]
    for e in ro:
        pat = rbin[e['addr'] - BASE:e['addr'] - BASE + e['size']]
        if len(set(pat)) <= 1:   # all-zero / all-same blobs are not identifiable
            continue
        pos = region.find(pat)
        hits = []
        while pos != -1 and len(hits) < 3:
            hits.append(tgt_ro_start + pos); pos = region.find(pat, pos + 1)
        out.append((e, hits))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--target', required=True)
    ap.add_argument('--target-code-end', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--target-image-end', type=lambda x: int(x, 0), default=None)
    ap.add_argument('--ref-map', required=True)
    ap.add_argument('--ref-bin', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--truth-map', default=None)
    ap.add_argument('--rounds', type=int, default=3)
    ap.add_argument('--band', type=int, default=260)
    ap.add_argument('--json', default=None)
    ap.add_argument('--libc-front', action='store_true', help='reference newlib members modelled as plain .text (placed at the front)')
    args = ap.parse_args()

    A, ran, rsecs, rents = load_ref(args.ref_map, args.ref_bin, libc_front=args.libc_front)
    tdata = open(args.target, 'rb').read()
    timage_end = args.target_image_end if args.target_image_end is not None else len(tdata)
    B, tan = load_target(args.target, args.target_code_end, timage_end)
    anchors = vector_anchors(tan, ran, A, B)
    for ti, sym in anchors.items():
        B[ti].anchor = sym
    print(f"ref functions {len(A)} (.text 0x{rsecs['text'][0]:x}+0x{rsecs['text'][1]:x}), target functions {len(B)}, vector anchors {len(anchors)}")

    ops, total = align(A, B, band=args.band, use_cg=False)
    asg = assignment_from_ops(ops, A, B)
    print(f"round 1: score {total:.1f}, matched targets {len(asg)}")
    for r in range(2, args.rounds + 1):
        compute_callgraph_syms(A, B, asg)
        ops, total = align(A, B, band=args.band, use_cg=True)
        asg = assignment_from_ops(ops, A, B)
        print(f"round {r}: score {total:.1f}, matched targets {len(asg)}")
    compute_callgraph_syms(A, B, asg)

    # ---------------------------------------------------------------- output
    truth = None
    if args.truth_map:
        tents = parse_map(args.truth_map)
        ttext = sorted([e for e in tents if e['outsec'] == '.text' and e['name'] != '*fill*' and e['size'] > 0], key=lambda e: e['addr'])
        tstarts = [e['addr'] for e in ttext]
        def truth_sym(addr):
            i = bisect.bisect_right(tstarts, addr) - 1
            if i >= 0 and ttext[i]['addr'] <= addr < ttext[i]['addr'] + ttext[i]['size']:
                return sym_of(ttext[i])
            return None
        truth = truth_sym

    rows = []
    matched_bytes = 0; correct = 0; graded = 0; correct_bytes = 0
    inserted = []
    for b in B:
        if b.idx in asg:
            ridx, kind = asg[b.idx]
            refs = [A[i] for i in ridx]
            a = refs[0] if len(refs) == 1 else Merged(refs[0], refs[1])
            sc = pair_score(a, b, use_anchor=False)
            cons = consistency(a, b)
            notes = [kind]
            if b.entry:
                notes.append('entry=' + b.entry)
            if b.anchor:
                notes.append('anchor=vector' + ('' if b.anchor == a.sym else '(MISMATCH)'))
            if cons:
                notes.append(f"callgraph {cons[1]}/{cons[2]}")
            if b.idx in asg and kind == 'merge2A':
                notes.append('refs=' + '+'.join(r.sym for r in refs))
            sym = '+'.join(r.sym for r in refs)
            ref_addr = refs[0].addr; ref_size = sum(r.size for r in refs)
            osim = opcode_similarity(ran, refs[0], tan, b) if len(refs) == 1 else None
            if osim is not None:
                notes.append(f"opsim={osim:.2f}")
            matched_bytes += b.size
            tsym = truth(b.addr) if truth else None
            if truth:
                graded += 1
                if tsym is not None and any(tsym == r.sym for r in refs):
                    correct += 1; correct_bytes += b.size
                notes.append(f"truth={tsym}")
            rows.append(dict(dump_addr=f"0x{b.addr:08x}", size=b.size, ref_symbol=sym, ref_addr=f"0x{ref_addr:08x}",
                             ref_size=ref_size, alignment_score=f"{sc:.2f}", notes='; '.join(notes), obj=refs[0].obj,
                             opcode_sim=('' if osim is None else f"{osim:.3f}")))
        else:
            tsym = truth(b.addr) if truth else None
            inserted.append(b)
            notes = ['INSERTION (no ref function)']
            if b.entry:
                notes.append('entry=' + b.entry)
            if truth:
                notes.append(f"truth={tsym}")
            rows.append(dict(dump_addr=f"0x{b.addr:08x}", size=b.size, ref_symbol='', ref_addr='', ref_size='',
                             alignment_score='', notes='; '.join(notes), obj='', opcode_sim=''))
    # ref functions not used (deletions)
    used = set()
    for ridx, _ in asg.values():
        used.update(ridx)
    deleted = [a for a in A if a.idx not in used]

    with open(args.out, 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=['dump_addr', 'size', 'ref_symbol', 'ref_addr', 'ref_size', 'alignment_score', 'notes', 'obj', 'opcode_sim'])
        w.writeheader()
        for r in rows:
            w.writerow(r)
    text_bytes = args.target_code_end + BASE - 0x08008000
    print(f"matched target bytes {matched_bytes} of .text {text_bytes} ({100 * matched_bytes / text_bytes:.1f}%)")
    print(f"insertions: {len(inserted)} functions, {sum(b.size for b in inserted)} bytes; deletions (ref funcs unmatched): {len(deleted)}, {sum(a.size for a in deleted)} bytes")
    if truth:
        print(f"CALIBRATION: {correct}/{graded} matched functions carry the truth symbol ({100 * correct / max(graded, 1):.1f}%), by bytes {correct_bytes}/{matched_bytes} ({100 * correct_bytes / max(matched_bytes, 1):.1f}%)")
    if args.json:
        json.dump(dict(rows=rows, inserted=[dict(addr=b.addr, size=b.size, entry=b.entry, n_bl=b.n_bl, push=b.push) for b in inserted],
                       deleted=[dict(sym=a.sym, addr=a.addr, size=a.size, obj=a.obj) for a in deleted],
                       anchors={B[k].addr: v for k, v in anchors.items()}), open(args.json, 'w'), indent=1)
    return 0


if __name__ == '__main__':
    sys.exit(main())
