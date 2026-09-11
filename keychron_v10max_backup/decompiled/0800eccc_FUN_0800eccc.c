// FUN_0800eccc @ 0x0800eccc  size=52  body=[[0800eccc, 0800ecff]]

void FUN_0800eccc(undefined4 param_1,ushort param_2,undefined4 param_3)

{
  bool bVar1;
  ushort extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined8 uVar3;
  undefined4 uVar2;
  
  bVar1 = FUN_0800e5e0(param_1,param_2,param_3);
  uVar3 = CONCAT44(extraout_r1_00,(uint)bVar1);
  uVar2 = extraout_r2;
  if (bVar1 == 0) {
    uVar3 = thunk_FUN_0800e634(0,extraout_r1_00,extraout_r2);
    uVar2 = extraout_r2_00;
  }
  DAT_200016f8 = FUN_0800e5f4((int)uVar3,(uint3)((ulonglong)uVar3 >> 0x20),uVar2);
  DAT_200047d4 = FUN_0800e600((uint)DAT_200016f8,extraout_r1,extraout_r2_01);
  uVar3 = FUN_0800ecc2();
  FUN_0800e5fa((int)uVar3,(uint3)((ulonglong)uVar3 >> 0x20),extraout_r2_02);
  thunk_FUN_0800dbd0();
  FUN_0800dc1a();
  return;
}

