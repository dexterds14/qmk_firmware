import sys,csv,struct,subprocess
from elftools.elf.elffile import ELFFile
K='/Users/dexter/code/qmk-keychron/keychron_v10max_backup'
S='/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/verify_cfg'
dump=open(K+'/dump_a.bin','rb').read(); BASE=0x08000000
elf=ELFFile(open(S+'/vc.elf','rb'))
# build address->bytes for loaded segments
segs=[]
for seg in elf.iter_segments():
    if seg['p_type']=='PT_LOAD' and seg['p_filesz']>0:
        segs.append((seg['p_paddr'],seg['p_filesz'],seg.data()))
def rbytes(addr,n):
    for pa,sz,d in segs:
        if pa<=addr<pa+sz: return d[addr-pa:addr-pa+n]
    return None
# symbols
syms={}
symtab=elf.get_section_by_name('.symtab')
for s in symtab.iter_symbols():
    if s['st_info']['type']=='STT_FUNC' and s['st_size']>0:
        syms[s.name]=(s['st_value']&~1,s['st_size'])
def mask(b):
    b=bytearray(b); i=0; out=[]
    while i+1<len(b):
        hw=b[i]|(b[i+1]<<8)
        if (hw&0xF800)==0xF000 and i+3<len(b):
            hw2=b[i+2]|(b[i+3]<<8)
            if (hw2&0xD000) in (0xD000,0x9000):
                out.append('BL' if hw2&0x4000 else 'B.W'); i+=4; continue
        out.append(hw); i+=2
    return out
def lit_mask(words):
    res=[]; i=0
    while i<len(words):
        if i+1<len(words) and isinstance(words[i],int) and isinstance(words[i+1],int) and words[i+1] in (0x2000,0x0801,0x0800,0x4002,0x4001,0x4000,0xe000):
            res.append('LIT'); i+=2; continue
        res.append(words[i]); i+=1
    return res
def norm(b): return tuple(lit_mask(mask(b)))
targets=[('get_tapping_term',0x0800DEFC,4),('waiting_buffer_scan_tap',0x0800DF00,148),('process_tapping',0x0800DF94,648),
('action_tapping_process',0x0800E21C,196),('waiting_buffer_typed.isra.0',0x0800DEB8,68),('process_action',0x0800D698,1052),('action_exec',0x0800D50C,64),
('set_oneshot_layer',0x0800E504,48),('add_oneshot_mods',0x0800E3EC,28),('del_oneshot_mods',0x0800E408,28),('clear_oneshot_mods',0x0800E424,24),
('reset_oneshot_layer',0x0800E534,20),('get_mods_for_report',0x0800E43C,48),('leader_sequence_timed_out',0x080119C0,28),('process_leader',0x080118F4,74),
('leader_reset_timer',0x080119F8,16),('leader_sequence_add',0x0801199C,36),('move_unit',0x08011A8C,136),('wheel_unit',0x08011B14,112),('mousekey_on',0x08011B84,196),
('mousekey_task',0x08011DF0,412),('eeconfig_update_rgb_matrix_default',0x0800FE14,44),('process_record_quantum',0x0800D3B6,166),('quantum_task',0x0800E7A4,20),
('action_for_keycode',0x0800E8B0,436),('debounce',0x0800EF30,304),('debounce_init',0x0800EEF8,36),('bootmagic_lite',0x0800EC98,42),('tap_dance_task',0x080120D0,80),
('eeconfig_init_quantum',0x0800E634,144),('rgb_matrix_mode_eeprom_helper',0x08010D04,60),('process_rgb_matrix',0x08010060,268),('keyboard_init',0x0800E788,28),
('pre_process_record_quantum',0x0800D34C,18),('rgb_matrix_increase_val_helper',0x08010E4C,44),('rgb_matrix_decrease_val_helper',0x08010F1C,56),('rgb_matrix_timeouted',0x08010FB0,28),
('keyboard_task',0x0800E7B8,248),('encoder_read',0x080116D0,372),('process_rgb_matrix_typing_heatmap',0x0800FD38,220),('send_nkro_report',0x0800E4A4,56)]
print('== targeted compare (masked BL/B.W + literal pools) ==')
bad=[]
for n,da,ds in targets:
    if n not in syms: print(f'{n:36s} NOT IN REBUILD'); bad.append(n); continue
    ra,rs=syms[n]
    db=dump[da-BASE:da-BASE+ds]; rb=rbytes(ra,rs)
    dm=norm(db); rm=norm(rb)
    same=(dm==rm)
    flag='' if same else '  <-- DIFF'
    print(f'{n:36s} dump {da:#010x}/{ds:4d}  rebuild {ra:#010x}/{rs:4d}  masked-identical={same}{flag}')
    if not same:
        bad.append(n)
        for k,(a,b) in enumerate(zip(dm,rm)):
            if a!=b: print(f'     first diff at halfword {k} (dump off {da+2*k:#x}): dump={a if isinstance(a,str) else hex(a)} rebuild={b if isinstance(b,str) else hex(b)}'); break
print('DIFFS:',bad)
# broad sweep
print('\n== broad sweep: rebuild functions with no masked-identical dump function ==')
dfuncs=[]
with open(K+'/functions_final.csv') as f:
    for r in csv.DictReader(f):
        dfuncs.append((int(r['dump_addr'],16),int(r['size']),r['name']))
dhash={}
for da,ds,dn in dfuncs:
    dhash.setdefault(norm(dump[da-BASE:da-BASE+ds]),[]).append((da,ds,dn))
rhash={}
for n,(ra,rs) in syms.items():
    b=rbytes(ra,rs)
    if b is None: continue
    rhash.setdefault(norm(b),[]).append((ra,rs,n))
unm=[]
for h,lst in rhash.items():
    if h not in dhash:
        for ra,rs,n in lst: unm.append((ra,rs,n))
unm.sort()
print(f'rebuild funcs: {len(syms)}; with masked-identical dump match: {sum(1 for h in rhash if h in dhash)} ; unmatched: {len(unm)}')
for ra,rs,n in unm: print(f'  {ra:#010x} {rs:5d} {n}')
print('\n== dump functions (functions_final.csv) with no masked-identical rebuild function ==')
dun=[]
for h,lst in dhash.items():
    if h not in rhash:
        for da,ds,dn in lst: dun.append((da,ds,dn))
dun.sort()
print(f'dump funcs: {len(dfuncs)}; unmatched: {len(dun)}')
for da,ds,dn in dun: print(f'  {da:#010x} {ds:5d} {dn}')
