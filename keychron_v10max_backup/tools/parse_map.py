#!/usr/bin/env python3
"""Parse a GNU ld map file into an ordered list of input sections.
Usage: parse_map.py file.map [outsection-prefix ...]  -> prints TSV: outsec, insec_name, addr, size, object, symbols
"""
import re, sys, json

def parse_map(path):
    lines = open(path, errors='replace').read().split('\n')
    # find "Linker script and memory map"
    try:
        start = next(i for i,l in enumerate(lines) if l.startswith('Linker script and memory map'))
    except StopIteration:
        start = 0
    entries = []   # dicts: outsec, name, addr, size, obj, syms
    cur_out = None
    i = start+1
    re_out = re.compile(r'^(\.[\w.]+)\s+(0x[0-9a-f]+)\s+(0x[0-9a-f]+)')
    re_out_only = re.compile(r'^(\.[\w.]+)\s*$')
    re_in_full = re.compile(r'^ (\.[^\s]+|\*fill\*|COMMON)\s+(0x[0-9a-f]+)\s+(0x[0-9a-f]+)(?:\s+(.*))?$')
    re_in_name = re.compile(r'^ (\.[^\s]+|COMMON)\s*$')
    re_in_cont = re.compile(r'^\s+(0x[0-9a-f]+)\s+(0x[0-9a-f]+)\s+(.*)$')
    re_sym = re.compile(r'^\s+(0x[0-9a-f]+)\s+([A-Za-z_$.][\w$.]*)\s*$')
    pending = None
    while i < len(lines):
        l = lines[i]
        m = re_out.match(l)
        if m and not l.startswith(' '):
            cur_out = m.group(1); i += 1; continue
        m = re_out_only.match(l)
        if m and not l.startswith(' '):
            cur_out = m.group(1)
            # next line may have addr size
            i += 1; continue
        m = re_in_full.match(l)
        if m:
            name, addr, size, obj = m.group(1), int(m.group(2),16), int(m.group(3),16), (m.group(4) or '').strip()
            e = dict(outsec=cur_out, name=name, addr=addr, size=size, obj=obj, syms=[])
            entries.append(e); i += 1; continue
        m = re_in_name.match(l)
        if m and i+1 < len(lines):
            m2 = re_in_cont.match(lines[i+1])
            if m2:
                e = dict(outsec=cur_out, name=m.group(1), addr=int(m2.group(1),16), size=int(m2.group(2),16), obj=m2.group(3).strip(), syms=[])
                entries.append(e); i += 2; continue
        m = re_sym.match(l)
        if m and entries and not l.strip().startswith('0x') is False:
            a = int(m.group(1),16); s = m.group(2)
            if entries and entries[-1]['addr'] <= a <= entries[-1]['addr']+max(entries[-1]['size'],1):
                entries[-1]['syms'].append((a, s))
        i += 1
    return entries

if __name__ == '__main__':
    path = sys.argv[1]
    prefixes = sys.argv[2:] or ['.text']
    ents = parse_map(path)
    for e in ents:
        if e['outsec'] and any(e['outsec'].startswith(p) for p in prefixes):
            syms = ';'.join(f"{s}@{a:08x}" for a,s in e['syms'])
            print(f"{e['outsec']}\t{e['name']}\t{e['addr']:08x}\t{e['size']:x}\t{e['obj']}\t{syms}")
