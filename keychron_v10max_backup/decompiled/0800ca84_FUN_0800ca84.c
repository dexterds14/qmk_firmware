// FUN_0800ca84 @ 0x0800ca84  size=162  body=[[0800ca84, 0800cb25]]

undefined4 FUN_0800ca84(void)

{
  byte bVar1;
  uint uVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined8 uVar3;
  undefined6 uVar4;
  
  if ((DAT_200015d4 != 0) && (uVar2 = FUN_0801258c(DAT_200015d4), 3000 < uVar2)) {
    DAT_200015d4 = 0;
    if (factory_reset_state == '\a') {
      DAT_200015cc = FUN_08012508();
      DAT_200015ca = DAT_200015ca + 1;
      uVar3 = FUN_0800db44();
      uVar4 = thunk_FUN_0800e634((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),extraout_r2);
      DAT_200047d4 = FUN_0800e600((int)uVar4,(ushort)((uint6)uVar4 >> 0x20),extraout_r2_00);
      thunk_FUN_0800dbd0();
      bVar1 = FUN_08010cf4();
      if (bVar1 == 0) {
        FUN_08010ef0();
      }
      FUN_08010c70();
      FUN_0800aef8(0);
    }
    else if (factory_reset_state == '\x19') {
      bVar1 = FUN_08010cf4();
      if (bVar1 == 0) {
        FUN_08010ef0();
      }
      DAT_200015d0 = 1;
    }
    factory_reset_state = '\0';
  }
  if ((DAT_200015cc != 0) && (uVar2 = FUN_0801258c(DAT_200015cc), 0xfa < uVar2)) {
    if (DAT_200015ca < 7) {
      DAT_200015ca = DAT_200015ca + 1;
      DAT_200015cc = FUN_08012508();
    }
    else {
      DAT_200015ca = 0;
      DAT_200015cc = 0;
    }
  }
  return 1;
}

