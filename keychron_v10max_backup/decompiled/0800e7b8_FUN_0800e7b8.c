// FUN_0800e7b8 @ 0x0800e7b8  size=240  body=[[0800e7b8, 0800e8a7]]

void FUN_0800e7b8(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r2;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  uint *puVar10;
  uint uVar11;
  bool bVar12;
  longlong lVar13;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar2 = FUN_0800e73c();
  iVar3 = 0;
  uVar7 = extraout_r1;
  if (iVar2 == 0) {
LAB_0800e7c4:
    FUN_0800e6c8(iVar3,uVar7);
  }
  else {
    FUN_0800ee8c();
    uVar7 = 0;
    piVar9 = &DAT_200016d4;
    do {
      iVar2 = *piVar9;
      iVar3 = FUN_0800ed20(uVar7 & 0xff);
      if (uVar7 == 5) {
        uVar7 = extraout_r1_01;
        if (iVar2 == iVar3) goto LAB_0800e7c4;
        break;
      }
      uVar7 = uVar7 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar2 == iVar3);
    if ((int)((uint)DAT_200016f8 << 0x1e) < 0) {
      FUN_0800ed2c();
    }
    iVar3 = FUN_0800e760();
    uVar7 = 0;
    puVar10 = &DAT_200016d4;
    do {
      uVar4 = FUN_0800ed20(uVar7 & 0xff);
      uVar6 = *puVar10;
      if (uVar4 != uVar6) {
        uVar8 = 0;
        uVar11 = 1;
        do {
          if (((uVar6 ^ uVar4) & uVar11) != 0) {
            bVar12 = (uVar4 & uVar11) != 0;
            if (iVar3 != 0) {
              uVar5 = FUN_08012574();
              local_30 = CONCAT22((short)uVar5,CONCAT11((char)uVar7,(char)uVar8));
              local_2c._0_2_ = CONCAT11(bVar12,1);
              FUN_0800d50c(local_30,local_2c,extraout_r2,1);
            }
            FUN_08010060(uVar7 & 0xff,uVar8,(uint)bVar12);
          }
          uVar8 = uVar8 + 1 & 0xff;
          uVar11 = uVar11 << 1;
        } while (uVar8 != 0x12);
        *puVar10 = uVar4;
      }
      uVar7 = uVar7 + 1;
      puVar10 = puVar10 + 1;
    } while (uVar7 != 6);
    FUN_0800e700();
  }
  FUN_0800e7a4();
  FUN_08011058();
  bVar1 = FUN_080116d0();
  lVar13 = (ulonglong)extraout_r1_00 << 0x20;
  if (bVar1 != 0) {
    lVar13 = FUN_0800e718();
  }
  FUN_08011df0((int)lVar13,(int)((ulonglong)lVar13 >> 0x20));
  FUN_0800d4e0();
  return;
}

