// FUN_08010c70 @ 0x08010c70  size=78  body=[[08010c70, 08010cbd]]

uint FUN_08010c70(void)

{
  bool bVar1;
  uint uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined6 uVar3;
  
  FUN_080114b0();
  DAT_20004814 = 0;
  DAT_20001f4d = 0;
  FUN_08008798(&DAT_2000482d,0xff,0x10);
  DAT_20001f1b = 0;
  uVar3 = FUN_08008798(&DAT_20001f34,0xff,0x10);
  bVar1 = FUN_0800e5e0((int)uVar3,(ushort)((uint6)uVar3 >> 0x20),extraout_r2);
  if (!bVar1) {
    thunk_FUN_0800e634(0,extraout_r1,extraout_r2_00);
    FUN_0800fe14();
  }
  bVar1 = FUN_0800fc00();
  if (DAT_20004808 < 4) {
    uVar2 = FUN_0800fe14();
    return uVar2;
  }
  return (uint)bVar1;
}

