// FUN_08015410 @ 0x08015410  size=94  body=[[08015410, 0801546d]]

void FUN_08015410(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = 1 << (param_2 & 0xff);
  iVar3 = (param_2 & 3) << 2;
  *(uint *)(&DAT_40013808 + (param_2 & 0xfffffffc)) =
       ((param_1 & 0x3fff) >> 10) << iVar3 |
       *(uint *)(&DAT_40013808 + (param_2 & 0xfffffffc)) & ~(0xf << iVar3);
  uVar4 = DAT_40013c08;
  uVar1 = ~uVar2;
  if ((param_3 & 1) == 0) {
    uVar4 = uVar4 & uVar1;
  }
  else {
    uVar4 = uVar4 | uVar2;
  }
  DAT_40013c08 = uVar4;
  uVar4 = DAT_40013c0c;
  if ((param_3 & 2) == 0) {
    uVar4 = uVar4 & uVar1;
  }
  else {
    uVar4 = uVar4 | uVar2;
  }
  DAT_40013c0c = uVar4;
  uVar4 = DAT_40013c00;
  DAT_40013c00 = uVar2 | uVar4;
  uVar4 = DAT_40013c04;
  DAT_40013c04 = uVar4 & uVar1;
  return;
}

