#!/usr/bin/env python3
"""Compare a flash dump against reference firmware images (same board, other builds).

Writes compare_images.md (+ .json) into --out.  Stdlib only.

Usage:
  python3 tools/compare_images.py keychron_v10max_backup/dump_a.bin --out keychron_v10max_backup \
      --image stock_via=keyboards/keychron/v10_max/firmware/keychron_v10_max_ansi_encoder_via.bin \
      --image off_v1.0.0=/path/v10_max_ansi_encoder_v1.0.0.bin ... \
      --newlib-lib ubuntu_noble_newlib4.4=/path/libc_nano.a ...   (optional: rand.c path form per libc)

Metrics (all restricted to the code+rodata span [--code-start, image end) of the *row* image; fill
windows that are all 0x00 or all 0xFF are excluded from numerator and denominator):
  * block-hit fraction: share of aligned K-byte blocks of image A found *anywhere* (any alignment)
    in image B, for K = 64 (task metric) and K = 16 (sensitivity).  Computed for every ordered pair so
    that same-compiler pairs among the references calibrate the dump's numbers.
  * longest common runs: maximal identical byte runs (seeded by 32-byte windows) between the dump
    and each image, with the offset delta (image_off - dump_off); a dominant delta means the two
    layouts are merely shifted.
  * vector table: number of identical words among the 120 vectors.
  * toolchain markers: the newlib __FILE__ path embedded by newlib's assert in rand.c, plus greps for
    GCC/GNU/crosstool/xpack/Arm GNU/homebrew/jenkins/clang and dotted version strings.
"""
import argparse, collections, datetime, hashlib, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dump_triage import classify_blocks, image_end  # noqa: E402

NEWLIB_RE = re.compile(rb'[\x20-\x7e]{0,200}newlib/libc/stdlib/rand\.c')
DATE_RE = re.compile(rb'\d{4}-\d{2}-\d{2}-\d{2}:\d{2}:\d{2}')
MARKERS = [b'GCC:', b'GCC ', b'GNU', b'crosstool', b'xpack', b'xPack', b'Arm GNU', b'homebrew', b'Homebrew',
           b'jenkins', b'Jenkins', b'clang', b'LLVM', b'newlib', b'nano', b'picolibc']
VERSION_RE = re.compile(rb'(?<![\x20-\x7e])[\x20-\x7e]{0,24}\d+\.\d+\.\d+[\x20-\x7e]{0,24}')


def is_fill(w):
    return w.count(0) == len(w) or w.count(0xFF) == len(w)


def window_hashes(img, k):
    s = set()
    for i in range(0, len(img) - k + 1):
        w = img[i:i + k]
        if not is_fill(w):
            s.add(hash(w))
    return s


def block_hit_fraction(a, a_lo, a_hi, b_hashes, k):
    tot = hit = 0
    for off in range(a_lo, a_hi - k + 1, k):
        w = a[off:off + k]
        if is_fill(w):
            continue
        tot += 1
        if hash(w) in b_hashes:
            hit += 1
    return hit, tot, (hit / tot if tot else 0.0)


def common_runs(a, b, a_lo, a_hi, seed=32, min_len=48, top=20):
    idx = {}
    for j in range(0, len(b) - seed + 1):
        w = b[j:j + seed]
        if is_fill(w):
            continue
        idx.setdefault(w, []).append(j)   # bytes key: exact, no hash collisions
    runs, i = [], a_lo
    while i < a_hi - seed:
        w = a[i:i + seed]
        cands = idx.get(w)
        if cands and not is_fill(w):
            best = (0, 0)
            for j in cands[:8]:
                L = seed
                while i + L < len(a) and j + L < len(b) and a[i + L] == b[j + L]:
                    L += 1
                if L > best[0]:
                    best = (L, j)
            L, j = best
            if L >= min_len:
                runs.append({'dump_off': i, 'img_off': j, 'len': L, 'delta': j - i})
            i += max(L, 1)
        else:
            i += 1
    runs.sort(key=lambda r: -r['len'])
    deltas = collections.Counter()
    for r in runs:
        deltas[r['delta']] += r['len']
    return runs[:top], len(runs), sum(r['len'] for r in runs), deltas.most_common(6)


def toolchain_info(img):
    m = NEWLIB_RE.search(img)
    path = m.group(0).decode('ascii') if m else None
    hits = {}
    for mk in MARKERS:
        n = img.count(mk)
        if n:
            hits[mk.decode()] = n
    versions = sorted({v.group(0).decode('ascii', 'replace').strip() for v in VERSION_RE.finditer(img)})[:12]
    dates = [d.decode() for d in DATE_RE.findall(img)]
    tc = 'unknown'
    if path:
        if 'GCC-10-pipeline' in path:
            tc = 'Arm GNU Toolchain 10.3-2021.10 (GCC 10) Jenkins build'
        elif '/GNU-toolchain/arm-11/' in path:
            tc = 'Arm GNU Toolchain 11.x Jenkins build'
        elif '/GNU-toolchain/arm-' in path:
            tc = 'Arm GNU Toolchain (%s) Jenkins build' % re.search(r'arm-(\d+)', path).group(0)
        elif 'crosstool' in path or path.startswith('/t/build/'):
            tc = 'crosstool-NG build (qmk/qmk_toolchains style)'
        elif path.startswith('../'):
            lv = path.count('../')
            tc = 'relative srcdir, %d levels (in-tree build/ dir; newlib %s automake layout)' % (lv, '>=4.2 non-recursive' if lv == 6 else '<=4.1 recursive' if lv == 8 else '?')
    return {'newlib_rand_path': path, 'newlib_path_offset': m.start() if m else None, 'marker_hits': hits,
            'version_like_strings': versions, 'build_dates': dates, 'toolchain_guess': tc}


def libc_rand_path(path):
    data = open(path, 'rb').read()
    return sorted({m.group(0).decode('ascii') for m in NEWLIB_RE.finditer(data)})


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('dump')
    ap.add_argument('--out', default='.')
    ap.add_argument('--image', action='append', default=[], help='label=path (repeatable)')
    ap.add_argument('--newlib-lib', action='append', default=[], help='label=path to a libc(_nano).a to read its rand.c __FILE__ form')
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=0x8000)
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--blocks', default='64,16')
    ap.add_argument('--rodata-start', type=lambda x: int(x, 0), default=None, help='dump file offset where .rodata starts (default: heuristic)')
    a = ap.parse_args()

    imgs = collections.OrderedDict()
    imgs['dump'] = open(a.dump, 'rb').read()
    for it in a.image:
        label, path = it.split('=', 1)
        imgs[label] = open(path, 'rb').read()
    paths = {'dump': os.path.abspath(a.dump)}
    for it in a.image:
        label, path = it.split('=', 1)
        paths[label] = os.path.abspath(path)
    ks = [int(x) for x in a.blocks.split(',')]

    info = collections.OrderedDict()
    for label, img in imgs.items():
        end = image_end(img)
        info[label] = {'path': paths[label], 'size': len(img), 'sha256': hashlib.sha256(img).hexdigest(), 'image_end': end,
                       'code_rodata_bytes': end - a.code_start, 'sp': int.from_bytes(img[0:4], 'little'),
                       'reset': int.from_bytes(img[4:8], 'little'), **toolchain_info(img)}
        m = re.search(rb'Keychron V10 Max', img)
        info[label]['product_ascii_offset'] = m.start() if m else None
    dump = imgs['dump']
    d_end = info['dump']['image_end']

    # vector table agreement
    vt = {}
    dv = [dump[i:i + 4] for i in range(0, 0x1E0, 4)]
    for label, img in imgs.items():
        if label == 'dump':
            continue
        iv = [img[i:i + 4] for i in range(0, 0x1E0, 4)]
        vt[label] = sum(1 for x, y in zip(dv, iv) if x == y)

    # pairwise block-hit matrices
    hashes = {k: {label: window_hashes(img, k) for label, img in imgs.items()} for k in ks}
    matrix = {k: collections.OrderedDict() for k in ks}
    for k in ks:
        for la, A in imgs.items():
            row = collections.OrderedDict()
            for lb in imgs:
                hit, tot, frac = block_hit_fraction(A, a.code_start, info[la]['image_end'], hashes[k][lb], k)
                row[lb] = {'hit': hit, 'total': tot, 'frac': round(frac, 4)}
            matrix[k][la] = row
    # extra: dump vector table + rodata-only fraction (dump rodata = after last code block)
    classes, _ = classify_blocks(dump, a.base, 256)
    code_blocks = [i for i, c in enumerate(classes) if c == 'code']
    rodata_start = a.rodata_start if a.rodata_start is not None else ((code_blocks[-1] + 1) * 256 if code_blocks else a.code_start)
    split = collections.OrderedDict()
    for lb in imgs:
        if lb == 'dump':
            continue
        hc, tc_, fc = block_hit_fraction(dump, a.code_start, rodata_start, hashes[ks[0]][lb], ks[0])
        hr, tr, fr = block_hit_fraction(dump, rodata_start, d_end, hashes[ks[0]][lb], ks[0])
        split[lb] = {'code': {'hit': hc, 'total': tc_, 'frac': round(fc, 4)}, 'rodata': {'hit': hr, 'total': tr, 'frac': round(fr, 4)}}

    runs = collections.OrderedDict()
    for lb, img in imgs.items():
        if lb == 'dump':
            continue
        top, nruns, covered, deltas = common_runs(dump, img, a.code_start, d_end)
        for r in top:
            r['dump_block_class'] = 'rodata/data' if r['dump_off'] >= rodata_start else classes[r['dump_off'] // 256]
        runs[lb] = {'top': top, 'run_count': nruns, 'bytes_in_runs_ge48': covered,
                    'top_deltas': [{'delta': d_, 'bytes': n} for d_, n in deltas]}

    libcs = collections.OrderedDict()
    for it in a.newlib_lib:
        label, path = it.split('=', 1)
        libcs[label] = {'path': os.path.abspath(path), 'rand_paths': libc_rand_path(path)}
    dump_path = info['dump']['newlib_rand_path']
    for label, l in libcs.items():
        l['matches_dump'] = dump_path in l['rand_paths']
        l['matches_images'] = [lb for lb, x in info.items() if lb != 'dump' and x['newlib_rand_path'] in l['rand_paths']]

    res = {'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'), 'code_start': a.code_start,
           'dump_rodata_start': rodata_start, 'images': info, 'vector_table_equal_words_of_120': vt,
           'block_hit_matrix': {str(k): v for k, v in matrix.items()}, 'dump_code_vs_rodata_hits_k%d' % ks[0]: split,
           'common_runs': runs, 'newlib_libs': libcs}
    os.makedirs(a.out, exist_ok=True)
    json.dump(res, open(os.path.join(a.out, 'compare_images.json'), 'w'), indent=1)
    open(os.path.join(a.out, 'compare_images.md'), 'w').write(render(res, ks))
    print('wrote compare_images.md/.json')


def render(r, ks):
    inf = r['images']
    labels = list(inf)
    L = ['# Image comparison: dump vs reference builds\n',
         'Generated %s by tools/compare_images.py. Metrics use the code+rodata span [0x%X, image end) of the row image; '
         'all-0x00/0xFF windows excluded. Block hits are exact byte matches of aligned K-byte blocks found at *any* offset of the column image.\n'
         % (r['generated'], r['code_start'])]
    L.append('## Images\n')
    L.append('| label | size | image end | code+rodata B | sha256 (16) | build date | SP / Reset | product str @ | newlib rand.c __FILE__ | toolchain guess |\n|---|---|---|---|---|---|---|---|---|---|')
    for lb, x in inf.items():
        L.append('| %s | %d | 0x%X | %d | `%s` | %s | 0x%08X / 0x%08X | %s | `%s` @0x%X | %s |' % (
            lb, x['size'], x['image_end'], x['code_rodata_bytes'], x['sha256'][:16], ', '.join(x['build_dates']) or '-', x['sp'], x['reset'],
            '0x%X' % x['product_ascii_offset'] if x['product_ascii_offset'] is not None else '-',
            x['newlib_rand_path'], x['newlib_path_offset'] or 0, x['toolchain_guess']))
    L.append('')
    L.append('Identical to dump: ' + ', '.join('%s=%s' % (lb, 'YES' if inf[lb]['sha256'] == inf['dump']['sha256'] else 'no') for lb in labels if lb != 'dump') + '\n')
    L.append('Vector table words equal to the dump (of 120): ' + ', '.join('%s=%d' % kv for kv in r['vector_table_equal_words_of_120'].items()) + '\n')
    L.append('## Toolchain marker strings per image\n')
    L.append('| label | marker hits (count) | dotted-version-like strings |\n|---|---|---|')
    for lb, x in inf.items():
        L.append('| %s | %s | %s |' % (lb, ', '.join('%s:%d' % kv for kv in x['marker_hits'].items()) or '-',
                                       ', '.join('`%s`' % v.replace('|', '\\|') for v in x['version_like_strings']) or '-'))
    L.append('')
    if r['newlib_libs']:
        L.append('## newlib rand.c __FILE__ forms in reference libc archives\n')
        L.append('| libc archive | rand.c __FILE__ strings found | matches dump | matches images |\n|---|---|---|---|')
        for lb, l in r['newlib_libs'].items():
            L.append('| %s (`%s`) | %s | %s | %s |' % (lb, l['path'], ', '.join('`%s`' % p for p in l['rand_paths']) or '-',
                                                        'YES' if l['matches_dump'] else 'no', ', '.join(l['matches_images']) or '-'))
        L.append('')
    for k in ks:
        M = r['block_hit_matrix'][str(k)]
        L.append('## %d-byte block hit fraction (row blocks found anywhere in column image)\n' % k)
        L.append('| row \\ col | ' + ' | '.join(labels) + ' |\n|---|' + '---|' * len(labels))
        for la in labels:
            L.append('| %s (%d blk) | ' % (la, M[la][la]['total']) + ' | '.join(
                ('%.1f%%' % (100 * M[la][lb]['frac'])) if la != lb else '-' for lb in labels) + ' |')
        L.append('')
    key = [k for k in r if k.startswith('dump_code_vs_rodata')][0]
    L.append('## Dump code vs rodata split (%s; rodata assumed from 0x%X)\n' % (key.split('_')[-1], r['dump_rodata_start']))
    L.append('| image | code blocks hit | rodata blocks hit |\n|---|---|---|')
    for lb, x in r[key].items():
        L.append('| %s | %d/%d (%.1f%%) | %d/%d (%.1f%%) |' % (lb, x['code']['hit'], x['code']['total'], 100 * x['code']['frac'],
                                                             x['rodata']['hit'], x['rodata']['total'], 100 * x['rodata']['frac']))
    L.append('')
    L.append('## Longest common byte runs (dump vs each image; seeded by 32-byte windows, runs >= 48 B)\n')
    for lb, x in r['common_runs'].items():
        L.append('### %s: %d runs >= 48 B covering %d B of the dump; dominant deltas (img_off - dump_off): %s\n' % (
            lb, x['run_count'], x['bytes_in_runs_ge48'], ', '.join('%+d (%d B)' % (d['delta'], d['bytes']) for d in x['top_deltas']) or '-'))
        L.append('| dump off | image off | len | delta | dump block class |\n|---|---|---|---|---|')
        for t in x['top'][:12]:
            L.append('| 0x%X | 0x%X | %d | %+d | %s |' % (t['dump_off'], t['img_off'], t['len'], t['delta'], t['dump_block_class']))
        L.append('')
    return '\n'.join(L) + '\n'


if __name__ == '__main__':
    main()
