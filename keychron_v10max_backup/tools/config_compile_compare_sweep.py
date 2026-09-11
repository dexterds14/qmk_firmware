import csv
from elftools.elf.elffile import ELFFile
K='/Users/dexter/code/qmk-keychron/keychron_v10max_backup'
S='/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/verify_cfg'
dump=open(K+'/dump_a.bin','rb').read(); BASE=0x08000000
elf=ELFFile(open(S+'/vc.elf','rb'))
segs=[(s['p_paddr'],s['p_filesz'],s.data()) for s in elf.iter_segments() if s['p_type']=='PT_LOAD' and s['p_filesz']>0]
def rbytes(addr,n):
    for pa,sz,d in segs:
        if pa<=addr<pa+sz: return d[addr-pa:addr-pa+n]
syms={}
for s in elf.get_section_by_name('.symtab').iter_symbols():
    if s['st_info']['type']=='STT_FUNC' and s['st_size']>0: syms[s.name]=(s['st_value']&~1,s['st_size'])
def mask(b):
    b=bytearray(b); i=0; out=[]
    while i+1<len(b):
        hw=b[i]|(b[i+1]<<8)
        if (hw&0xF800)==0xF000 and i+3<len(b):
            hw2=b[i+2]|(b[i+3]<<8)
            if (hw2&0xD000) in (0xD000,0x9000): out.append('BL' if hw2&0x4000 else 'B.W'); i+=4; continue
        out.append(hw); i+=2
    return out
def lit_mask(w):
    res=[]; i=0
    while i<len(w):
        if i+1<len(w) and isinstance(w[i],int) and isinstance(w[i+1],int) and w[i+1] in (0x2000,0x0801,0x0800,0x4002,0x4001,0x4000,0xe000): res.append('LIT'); i+=2; continue
        res.append(w[i]); i+=1
    return res
def norm(b): return tuple(lit_mask(mask(b)))
dfuncs=[]
for r in csv.DictReader(open(K+'/functions_final.csv')): dfuncs.append((int(r['dump_addr'],16),int(r['size']),r['name']))
dh={}
for da,ds,dn in dfuncs: dh.setdefault(norm(dump[da-BASE:da-BASE+ds]),[]).append((da,ds,dn))
# pad-tolerant: also index dump prefixes trimmed by 2 and 4 bytes
dh2={}
for da,ds,dn in dfuncs:
    for t in (2,4):
        if ds>t: dh2.setdefault(norm(dump[da-BASE:da-BASE+ds-t]),[]).append((da,ds,dn,t))
still=[]
for n,(ra,rs) in sorted(syms.items(),key=lambda x:x[1]):
    b=rbytes(ra,rs)
    if b is None: continue
    h=norm(b)
    if h in dh: continue
    if h in dh2: continue
    still.append((ra,rs,n))
print('rebuild functions still unmatched after pad tolerance:',len(still))
for ra,rs,n in still: print(f'  {ra:#010x} {rs:5d} {n}')
