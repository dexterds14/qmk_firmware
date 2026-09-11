import subprocess,sys,struct
S=sys.argv[1]; X=sys.argv[2]
dump=open('/Users/dexter/code/qmk-keychron/keychron_v10max_backup/dump_a.bin','rb').read()
ref=open('/Users/dexter/code/qmk-keychron/keychron_v10max_backup/refs/ref1011_leader_verify_gcc13.bin','rb').read()
BASE=0x08000000
# name -> (dump_addr, dump_size)
dumpf={'leader_start_user':(0x0800CDF4,10),'leader_end_user':(0x0800CDFE,0x162),
 'process_leader':(0x080118F4,0x4A),'leader_start':(0x08011940,0x3C),'leader_end':(0x0801197C,0x14),
 'leader_sequence_active':(0x08011990,12),'leader_sequence_add':(0x0801199C,0x24),
 'leader_sequence_timed_out':(0x080119C0,0x1C),'leader_task':(0x080119DC,0x1C),'leader_reset_timer':(0x080119F8,0x10),
 'leader_sequence_is':(0x08011A08,0x34),'leader_sequence_one_key':(0x08011A3C,0x14),'leader_sequence_two_keys':(0x08011A50,0x12)}
nm=subprocess.run([X+'/arm-none-eabi-nm','-S','/Users/dexter/code/qmk-keychron/keychron_v10max_backup/refs/ref1011_leader_verify_gcc13.elf'],capture_output=True,text=True).stdout
reff={}
for l in nm.splitlines():
    p=l.split()
    if len(p)==4 and p[3] in dumpf: reff[p[3]]=(int(p[0],16),int(p[1],16))
def mask(b):
    # mask BL / B.W (T1/T2 32-bit branch) immediates and 32-bit-aligned words that look like RAM/flash addresses (literal pool)
    b=bytearray(b); i=0
    out=[]
    while i+1<len(b):
        hw=b[i]|(b[i+1]<<8)
        if (hw&0xF800)==0xF000 and i+3<len(b):
            hw2=b[i+2]|(b[i+3]<<8)
            if (hw2&0xD000) in (0xD000,0x9000):  # BL or B.W
                out.append(('BL' if hw2&0x4000 else 'B.W'))
                i+=4; continue
        out.append(hw); i+=2
    return out
def lit_mask(words):
    # replace literal pool words (0x2000xxxx / 0x0801xxxx pairs) 
    res=[]; i=0
    while i<len(words):
        if i+1<len(words) and isinstance(words[i],int) and isinstance(words[i+1],int) and words[i+1] in (0x2000,0x0801,0x0800):
            res.append('LIT'); i+=2; continue
        res.append(words[i]); i+=1
    return res
for n,(da,ds) in dumpf.items():
    if n not in reff: print(f'{n:28s} NOT IN REF BUILD'); continue
    ra,rs=reff[n]
    db=dump[da-BASE:da-BASE+ds]; rb=ref[ra-BASE:ra-BASE+rs]
    dm=lit_mask(mask(db)); rm=lit_mask(mask(rb))
    same = dm==rm
    print(f'{n:28s} dump {da:#010x} size {ds:4d} | gcc13 {ra:#010x} size {rs:4d} | masked-identical: {same}')
    if not same:
        for k,(a,b) in enumerate(zip(dm,rm)):
            if a!=b: print(f'   first diff at unit {k}: dump={a if isinstance(a,str) else hex(a)} ref={b if isinstance(b,str) else hex(b)}'); break
