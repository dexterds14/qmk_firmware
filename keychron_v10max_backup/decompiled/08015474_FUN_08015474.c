// FUN_08015474 @ 0x08015474  size=76  body=[[08015474, 080154bf]]

void FUN_08015474(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = DAT_40013c08;
  uVar3 = DAT_40013c0c;
  uVar4 = 1 << (param_2 & 0xff);
  if (((uVar2 | uVar3) & uVar4) != 0) {
    uVar1 = DAT_40013c00;
    DAT_40013c00 = uVar1 & ~uVar4;
    uVar1 = DAT_40013c04;
    DAT_40013c04 = uVar1 & ~uVar4;
    DAT_40013c08 = uVar2 & ~uVar4;
    DAT_40013c0c = uVar3 & ~uVar4;
    DAT_40013c14 = uVar4;
    (&DAT_20004a64)[param_2 * 2] = 0;
    (&DAT_20004a68)[param_2 * 2] = 0;
  }
  return;
}

