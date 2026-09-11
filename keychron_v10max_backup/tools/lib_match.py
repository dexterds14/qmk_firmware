#!/usr/bin/env python3
"""Match the .text of every member of one or more static libraries (libc_nano.a, libgcc.a, ...) against a
flash dump, to identify which toolchain's newlib/libgcc build was linked into the firmware.

For each archive member the .text section is extracted with arm-none-eabi-objcopy; the member's bytes are
matched against the dump using 16-byte windows *excluding windows that contain a relocation site*
(relocation offsets are read from arm-none-eabi-objdump -r).  A member "matches" when >= --min-frac of its
relocation-free windows are found in the dump and its longest exact run is >= --min-run bytes.

Usage:
  python3 tools/lib_match.py DUMP --lib label=/path/libc_nano.a [--lib ...] --out DIR [--bindir DIR]
Writes lib_match.md/.json.  Needs arm-none-eabi-{ar,objcopy,objdump} (QMK toolchain bin dir by default).
"""
import argparse, collections, datetime, json, os, re, shutil, subprocess, sys, tempfile

DEF_BINDIR = os.path.expanduser('~/Library/Application Support/qmk/bin')


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, capture_output=True, text=True, **kw).stdout


def member_text(bindir, obj):
    """Return a list of (section name, bytes, set of reloc byte offsets) for every non-empty .text* section of an
    object file (newlib built with -ffunction-sections has one .text.<fn> section per function)."""
    objcopy, objdump = os.path.join(bindir, 'arm-none-eabi-objcopy'), os.path.join(bindir, 'arm-none-eabi-objdump')
    try:
        hdr = run([objdump, '-h', obj])
    except subprocess.CalledProcessError:
        return []
    secs = [(m.group(1), int(m.group(2), 16)) for m in re.finditer(r'^\s*\d+\s+(\.text\S*)\s+([0-9a-f]{8})', hdr, re.M)]
    secs = [(n, sz) for n, sz in secs if sz > 0]
    if not secs:
        return []
    relocs = {}
    try:
        cur = None
        for line in run([objdump, '-r', obj]).splitlines():
            m = re.match(r'RELOCATION RECORDS FOR \[(\S+)\]', line)
            if m:
                cur = m.group(1)
                continue
            m = re.match(r'^([0-9a-f]{8}) +(\S+)', line)
            if m and cur:
                off = int(m.group(1), 16)
                relocs.setdefault(cur, set()).update(range(off, off + 4))
    except subprocess.CalledProcessError:
        pass
    out = []
    for name, _ in secs:
        binp = obj + '.' + re.sub(r'[^A-Za-z0-9_.]', '_', name) + '.bin'
        try:
            run([objcopy, '-O', 'binary', '--only-section=' + name, obj, binp])
        except subprocess.CalledProcessError:
            continue
        data = open(binp, 'rb').read() if os.path.exists(binp) else b''
        if data:
            out.append((name, data, relocs.get(name, set())))
    return out


def match_member(data, relocs, dump_windows, dump, k=16):
    total = hit = 0
    for i in range(0, len(data) - k + 1):
        if any((i + j) in relocs for j in range(k)):
            continue
        total += 1
        if data[i:i + k] in dump_windows:
            hit += 1
    # longest exact run (relocation-free) using the first window hit as a seed
    longest, where = 0, None
    for i in range(0, len(data) - k + 1):
        w = data[i:i + k]
        if w in dump_windows and not any((i + j) in relocs for j in range(k)):
            for pos in dump_windows[w][:4]:
                L = k
                while i + L < len(data) and pos + L < len(dump) and data[i + L] == dump[pos + L]:
                    L += 1
                if L > longest:
                    longest, where = L, (i, pos)
    return total, hit, longest, where


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('dump')
    ap.add_argument('--lib', action='append', default=[], help='label=path/to/lib.a')
    ap.add_argument('--out', default='.')
    ap.add_argument('--bindir', default=DEF_BINDIR)
    ap.add_argument('--min-frac', type=float, default=0.9)
    ap.add_argument('--min-run', type=int, default=48)
    ap.add_argument('--min-text', type=int, default=32, help='ignore members with .text smaller than this')
    a = ap.parse_args()
    dump = open(a.dump, 'rb').read()
    k = 16
    windows = collections.defaultdict(list)
    for i in range(0, len(dump) - k + 1):
        w = dump[i:i + k]
        if w.count(0) != k and w.count(0xFF) != k:
            windows[w].append(i)
    ar = os.path.join(a.bindir, 'arm-none-eabi-ar')
    results = collections.OrderedDict()
    for it in a.lib:
        label, path = it.split('=', 1)
        tmp = tempfile.mkdtemp(prefix='libmatch_')
        run([ar, 'x', os.path.abspath(path)], cwd=tmp)
        members = []
        for name in sorted(os.listdir(tmp)):
            if not name.endswith('.o'):
                continue
            secs = member_text(a.bindir, os.path.join(tmp, name))
            text_len = sum(len(d_) for _, d_, _ in secs)
            if not secs or text_len < a.min_text:
                continue
            total = hit = longest = 0
            where, nreloc = None, 0
            for sname, data, relocs in secs:
                t, h, lg, wh = match_member(data, relocs, windows, dump, k)
                total += t
                hit += h
                nreloc += len(relocs)
                if lg > longest:
                    longest, where = lg, wh
            frac = hit / total if total else 0.0
            members.append({'member': name, 'sections': len(secs), 'text_len': text_len, 'reloc_bytes': nreloc, 'windows': total, 'hits': hit,
                            'frac': round(frac, 3), 'longest_run': longest,
                            'dump_off': where[1] if where else None, 'member_off': where[0] if where else None,
                            'match': frac >= a.min_frac and longest >= a.min_run and total > 0})
        shutil.rmtree(tmp, ignore_errors=True)
        results[label] = {'path': os.path.abspath(path), 'members_considered': len(members),
                          'members_matched': sum(1 for m in members if m['match']),
                          'matched_text_bytes': sum(m['text_len'] for m in members if m['match']),
                          'members': members}
    res = {'dump': os.path.abspath(a.dump), 'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
           'window': k, 'min_frac': a.min_frac, 'min_run': a.min_run, 'libs': results}
    os.makedirs(a.out, exist_ok=True)
    json.dump(res, open(os.path.join(a.out, 'lib_match.json'), 'w'), indent=1)
    L = ['# Library member match: %s\n' % os.path.basename(a.dump),
         'Generated %s by tools/lib_match.py. Member .text matched with %d-byte relocation-free windows; a member counts as matched when '
         '>= %.0f%% of its windows occur in the dump and its longest exact run is >= %d B. Members with .text < %d B ignored.\n'
         % (res['generated'], k, 100 * a.min_frac, a.min_run, a.min_text)]
    L.append('| library | members considered | matched | matched .text bytes |\n|---|---|---|---|')
    for lb, r in results.items():
        L.append('| %s (`%s`) | %d | %d | %d |' % (lb, r['path'], r['members_considered'], r['members_matched'], r['matched_text_bytes']))
    L.append('')
    for lb, r in results.items():
        L.append('## %s\n' % lb)
        L.append('Matched members (dump offset of the longest run):\n')
        L.append('| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |\n|---|---|---|---|---|---|---|---|---|')
        for m in sorted(r['members'], key=lambda m: (-m['match'], -m['frac'], -m['text_len'])):
            if m['match'] or m['frac'] >= 0.5:
                L.append('| %s | %d | %d | %d | %d | %.2f | %d | %s | %s |' % (m['member'], m['text_len'], m['reloc_bytes'], m['windows'], m['hits'], m['frac'],
                                                                              m['longest_run'], '0x%X' % m['dump_off'] if m['dump_off'] is not None else '-',
                                                                              '0x%X' % m['member_off'] if m['member_off'] is not None else '-'))
        L.append('')
        L.append('Unmatched members with >= 20%% window hits (partial similarity): %s\n' % (', '.join(
            '%s (%.0f%%)' % (m['member'], 100 * m['frac']) for m in r['members'] if not m['match'] and m['frac'] >= 0.2) or 'none'))
    open(os.path.join(a.out, 'lib_match.md'), 'w').write('\n'.join(L) + '\n')
    print('wrote lib_match.md/.json')
    for lb, r in results.items():
        print('%-40s members=%d matched=%d bytes=%d' % (lb, r['members_considered'], r['members_matched'], r['matched_text_bytes']))


if __name__ == '__main__':
    main()
