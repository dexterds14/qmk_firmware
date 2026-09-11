#!/usr/bin/env python3
# Place Ubuntu noble libnewlib 4.4.0.20231231-2 libc_nano.a members (matched by tools/lib_match.py, see lib_match.json)
# into the dump and emit per-symbol addresses.  Needs the extracted .deb under the session scratchpad (refs/toolchain_debs_SOURCES.txt).
# Output: libc_members_placed.json (copied to keychron_v10max_backup/).
import json, subprocess, os, re, sys
BK='/Users/dexter/code/qmk-keychron/keychron_v10max_backup/'
S='/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/'
BIN='/Users/dexter/Library/Application Support/qmk/bin/'
d=json.load(open(BK+'lib_match.json'))
lib=[L for L in d['libs'].values() if '4.4.0.20231231' in L['path']][0]
LIBC=lib['path']
dump=open(BK+'dump_a.bin','rb').read()
out=S+'libc_members'; os.makedirs(out,exist_ok=True)
rows=[]
for m in lib['members']:
    if m['dump_off'] is None: continue
    if not (m['match'] or (m['frac']>=0.95 and m['hits']>=5)): continue
    start=m['dump_off']-m['member_off']
    if not (0x8448<=start<0xA1C0): continue
    # extract member
    subprocess.run([BIN+'arm-none-eabi-ar','x',LIBC,m['member']],cwd=out,check=True,capture_output=True)
    subprocess.run([BIN+'arm-none-eabi-objcopy','-O','binary','-j','.text',out+'/'+m['member'],out+'/'+m['member']+'.text'],check=True,capture_output=True)
    tb=open(out+'/'+m['member']+'.text','rb').read()
    seg=dump[start:start+len(tb)]
    eq=sum(1 for x,y in zip(tb,seg) if x==y)/max(1,len(tb))
    nm=subprocess.run([BIN+'arm-none-eabi-nm','-S','--radix=x','--defined-only',out+'/'+m['member']],capture_output=True,text=True).stdout
    syms=[]
    for l in nm.splitlines():
        p=l.split()
        if len(p)==4 and p[2] in 'TtWw':
            syms.append((int(p[0],16),int(p[1],16),p[3]))
    rows.append(dict(member=m['member'],start=start,text_len=len(tb),eq=eq,windows=m['windows'],hits=m['hits'],frac=m['frac'],syms=sorted(syms)))
rows.sort(key=lambda r:r['start'])
prev_end=0
for r in rows:
    flag='' if r['start']>=prev_end else ' OVERLAP'
    print(f"0x{0x08000000+r['start']:08X}-0x{0x08000000+r['start']+r['text_len']:08X} {r['member']:28s} len={r['text_len']:4d} eqbytes={r['eq']:.3f} win={r['windows']}/{r['hits']}{flag}")
    for off,sz,name in r['syms']:
        print(f"      0x{0x08000000+r['start']+off:08X} {sz:4d} {name}")
    prev_end=max(prev_end,r['start']+r['text_len'])
json.dump(rows,open(S+'libc_place.json','w'),indent=1)
