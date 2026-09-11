// FUN_080152b0 @ 0x080152b0  size=104  body=[[080152b0, 08015317]]

void FUN_080152b0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = ~param_1;
  if ((param_2 & 3) == 0) {
    uVar2 = DAT_40013c00;
    DAT_40013c00 = uVar2 & uVar1;
    uVar2 = DAT_40013c04;
    DAT_40013c04 = uVar2 & uVar1;
    uVar2 = DAT_40013c08;
    DAT_40013c08 = uVar2 & uVar1;
    uVar2 = DAT_40013c0c;
    DAT_40013c0c = uVar1 & uVar2;
    DAT_40013c14 = param_1;
  }
  else {
    uVar2 = DAT_40013c08;
    if ((param_2 & 1) == 0) {
      uVar2 = uVar2 & uVar1;
    }
    else {
      uVar2 = uVar2 | param_1;
    }
    DAT_40013c08 = uVar2;
    uVar2 = DAT_40013c0c;
    if ((param_2 & 2) == 0) {
      uVar2 = uVar2 & uVar1;
    }
    else {
      uVar2 = uVar2 | param_1;
    }
    DAT_40013c0c = uVar2;
    if ((int)(param_2 << 0x1d) < 0) {
      uVar2 = DAT_40013c04;
      DAT_40013c04 = param_1 | uVar2;
      uVar2 = DAT_40013c00;
      DAT_40013c00 = uVar1 & uVar2;
    }
    else {
      uVar2 = DAT_40013c00;
      DAT_40013c00 = uVar2 | param_1;
      uVar2 = DAT_40013c04;
      DAT_40013c04 = uVar1 & uVar2;
    }
  }
  return;
}

