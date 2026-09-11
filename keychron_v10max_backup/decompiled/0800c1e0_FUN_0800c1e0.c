// FUN_0800c1e0 @ 0x0800c1e0  size=178  body=[[0800c1e0, 0800c291]]

void FUN_0800c1e0(undefined4 param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  undefined4 extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  bool bVar8;
  undefined8 uVar9;
  
  uVar6 = FUN_0800c4a8(DAT_200015a0,param_2,param_3);
  bVar2 = FUN_0800bbb4();
  if (((bVar2 & 6) != 0) && ((cVar3 = FUN_0800a77c(), cVar3 == '\x03' || (DAT_2000159d < 0xf)))) {
    uVar7 = FUN_0800bcb8();
    if ((uVar7 != 0) && (3000 < uVar6)) {
      iVar1 = DAT_40020810;
      if (iVar1 << 0x11 < 0) {
        uVar4 = 2;
      }
      else {
        uVar4 = 1;
      }
      FUN_0800ae58(uVar4);
    }
    if ((0xe < DAT_2000159d) || (bVar5 = FUN_0800b36a(), bVar5)) {
      bVar8 = 2999 < uVar6;
      bVar5 = uVar6 == 3000;
    }
    else {
      bVar8 = 199 < uVar6;
      bVar5 = uVar6 == 200;
    }
    if (bVar8 && !bVar5) {
      FUN_0800c16c();
      uVar9 = FUN_0800c1ac();
      uVar6 = FUN_0800c48c((uint)uVar9,(uint)((ulonglong)uVar9 >> 0x20),extraout_r2);
      DAT_200015a0 = uVar6;
      if (86400000 < uVar6) {
        DAT_200015a0 = 0;
        FUN_0800c46c(uVar6,extraout_r1,extraout_r2_00);
      }
      FUN_0800c06a();
      if (DAT_2000159d < 0xf) {
        DAT_2000159d = DAT_2000159d + 1;
      }
    }
  }
  if ((DAT_2000159f != '\0' || DAT_2000159e != '\0') && (uVar6 = FUN_0800bcb8(), uVar6 != 0)) {
    DAT_2000159f = 0;
    DAT_2000159e = 0;
    FUN_0800b3ec(0);
    FUN_0800b420(0,extraout_r1_00,extraout_r2_01);
    return;
  }
  return;
}

