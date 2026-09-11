// FUN_08010060 @ 0x08010060  size=250  body=[[08010060, 08010159]]

void FUN_08010060(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte *local_34;
  byte abStack_30 [12];
  
  iVar5 = FUN_0800e75c();
  if (iVar5 != 0) {
    DAT_20001f48 = 0;
    if (param_3 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = FUN_0800fe44(param_1,param_2,(int)abStack_30);
    }
    if (8 < (int)(DAT_20001f1b + uVar6)) {
      uVar9 = 8 - uVar6;
      memcpy((undefined4 *)&DAT_20001f1c,(undefined4 *)(&DAT_20001f1c + uVar6),uVar9);
      memcpy((undefined4 *)&DAT_20001f24,(undefined4 *)(&DAT_20001f24 + uVar6),uVar9);
      memcpy((undefined4 *)&DAT_20001f34,(undefined4 *)(&DAT_20001f34 + (short)uVar6 * 2),uVar9 * 2)
      ;
      memcpy((undefined4 *)&DAT_20001f2c,(undefined4 *)(&DAT_20001f2c + uVar6),uVar9);
      DAT_20001f1b = (byte)uVar9;
    }
    bVar4 = DAT_20001f1b;
    uVar10 = (uint)DAT_20001f1b;
    iVar7 = 0;
    local_34 = abStack_30;
    for (uVar9 = 0; uVar8 = uVar10 + (uVar9 & 0xff) & 0xff, (uVar9 & 0xff) < uVar6;
        uVar9 = uVar9 + 1) {
      bVar3 = *local_34;
      iVar7 = (bVar3 + 0x34) * 2;
      iVar1 = (uVar8 + 0xc) * 2;
      uVar2 = (&DAT_20000d0c)[iVar7];
      (&DAT_20001f1c)[uVar8] = (&DAT_20000d0b)[iVar7];
      (&DAT_20001f24)[uVar8] = uVar2;
      (&DAT_20001f2c)[uVar8] = bVar3;
      (&DAT_20001f1c)[iVar1] = 0;
      (&DAT_20001f1d)[iVar1] = 0;
      iVar7 = iVar5;
      local_34 = local_34 + 1;
    }
    if (iVar7 != 0) {
      DAT_20001f1b = (char)uVar6 + bVar4;
    }
    if ((param_3 != 0) && ((DAT_20004808 & 0xfc) == 0x40)) {
      FUN_0800fd38(param_1,param_2);
    }
  }
  return;
}

