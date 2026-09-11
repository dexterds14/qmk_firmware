# Emulate the control flow of sub_0800d010 (from the objdump listing) and compare
# with the proposed C rendering, over all combinations of inputs.
import itertools
def compiled(S,G,sf,gf):
    acts=[]
    r5=S; r4=G
    if not r5:                      # 0800d01a bne
        if sf:                      # 0800d020 cbz
            acts.append('black'); sf=0          # 0800d028 set_color_all(r5,r5,r5)=(0,0,0); 0800d02c strb
            if not r4: return acts,sf,gf        # 0800d02e cbz r4 -> d042
            if not gf: acts.append('yellow'); gf=1   # 0800d030..d040
            return acts,sf,gf
    # 0800d044
    if not r4:                      # 0800d048 cbnz r4 -> d078
        if gf: acts.append('black'); gf=0       # 0800d04a..d05a set_color_all(r6,r6,r6)=(0,0,0)
        if not r5: return acts,sf,gf            # 0800d05c/d05e
        if sf: return acts,sf,gf                # 0800d060..d066 bne d02e -> cbz r4 -> ret
        acts.append('white'); sf=1              # 0800d068..d074, b d02e -> ret
        return acts,sf,gf
    # 0800d078 (r4 != 0)
    if r5:
        if not sf: acts.append('white'); sf=1   # d060..d074 then d02e -> d030
        if not gf: acts.append('yellow'); gf=1  # d030..d040
        return acts,sf,gf
    if not gf: acts.append('yellow'); gf=1      # d07c b d030
    return acts,sf,gf

def proposed(S,G,sf,gf):
    acts=[]
    if (not S) and sf:
        acts.append('black'); sf=0
    elif (not G) and gf:
        acts.append('black'); gf=0
    if S and not sf:
        acts.append('white'); sf=1
    if G and not gf:
        acts.append('yellow'); gf=1
    return acts,sf,gf

def dactyl_chain(S,G,sf,gf):
    acts=[]
    if S and not sf: acts.append('white'); sf=1; return acts,sf,gf
    elif G and not gf: acts.append('yellow'); gf=1; return acts,sf,gf
    elif (not S) and sf: acts.append('black'); sf=0; return acts,sf,gf
    elif (not S) and gf: acts.append('black'); gf=0; return acts,sf,gf
    return acts,sf,gf

ok=True; dact_diff=[]
for S,G,sf,gf in itertools.product([0,1],repeat=4):
    c=compiled(S,G,sf,gf); p=proposed(S,G,sf,gf); d=dactyl_chain(S,G,sf,gf)
    if c!=p: ok=False; print("MISMATCH proposed", (S,G,sf,gf), c, p)
    if c!=d: dact_diff.append(((S,G,sf,gf),c,d))
print("proposed rendering == compiled for all 16 cases:", ok)
print("cases where the dactyl LM handle_oneshots chain differs from the compiled code:", len(dact_diff))
for x in dact_diff: print("  S,G,sf,gf=%s compiled=%s dactyl=%s"%x)
