// FUN_0800ba9c @ 0x0800ba9c  size=258  body=[[0800ba9c, 0800bb9d]]

void FUN_0800ba9c(uint param_1)

{
  bool bVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  undefined4 uVar6;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  uint uVar7;
  undefined4 extraout_r2_02;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  undefined4 uVar8;
  undefined4 extraout_r2_05;
  undefined4 extraout_r2_06;
  undefined8 uVar9;
  
  if (DAT_2000157a == param_1) {
    return;
  }
  if ((DAT_2000157a == 1) ||
     (cVar3 = FUN_0800a77c(), uVar6 = extraout_r1_02, uVar8 = extraout_r2_02, cVar3 == '\x03')) {
    FUN_0800db44();
    uVar6 = extraout_r1;
    uVar8 = extraout_r2;
  }
  DAT_2000157a = (byte)param_1;
  if (param_1 == 2) {
    FUN_0800b9f8(0,uVar6,uVar8);
    FUN_08013a7a(100);
    FUN_0800b990(1,extraout_r1_03,extraout_r2_03);
    uVar6 = extraout_r1_04;
    uVar8 = extraout_r2_04;
LAB_0800bb66:
    FUN_0800ba60(0,uVar6,uVar8);
    FUN_0800bc70();
    uVar7 = (uint)DAT_20001579;
    DAT_20001579 = DAT_20001579 & 0xfe | (byte)DAT_200047d4 >> 7;
    uVar7 = (uVar7 & 2) >> 1;
  }
  else {
    if (param_1 == 4) {
      FUN_0800b990(0,uVar6,uVar8);
      FUN_08013a7a(100);
      FUN_0800b9f8(1,extraout_r1_05,extraout_r2_05);
      uVar6 = extraout_r1_06;
      uVar8 = extraout_r2_06;
      goto LAB_0800bb66;
    }
    if (param_1 != 1) goto LAB_0800baf8;
    FUN_0800ba60(1,uVar6,uVar8);
    FUN_0800b990(0,extraout_r1_00,extraout_r2_00);
    FUN_08013a7a(500);
    FUN_0800b9f8(0,extraout_r1_01,extraout_r2_01);
    FUN_0800a41c();
    FUN_0800bca4();
    uVar7 = DAT_20001579 & 0xfffffffd | (uint)((byte)DAT_200047d4 >> 7) << 1;
    DAT_20001579 = (byte)uVar7;
  }
  DAT_200047d4._0_1_ = (byte)DAT_200047d4 & 0x7f | (byte)((uVar7 & 1) << 7);
LAB_0800baf8:
  FUN_0800b328();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar4 = FUN_08013cfa();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  do {
    iVar5 = FUN_08013cfa();
    lVar2 = (ulonglong)(uint)(iVar5 - iVar4) * 1000 + 99999;
    uVar9 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
  } while ((uint)uVar9 < 100);
  FUN_08010c70();
  FUN_08010f98(0xffffffff);
  FUN_08010fa4();
  return;
}

