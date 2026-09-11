// FUN_08010d04 @ 0x08010d04  size=50  body=[[08010d04, 08010d35]]

void FUN_08010d04(uint param_1,byte param_2)

{
  uint uVar1;
  
  if ((DAT_20004808 & 3) != 0) {
    if (param_1 == 0) {
      uVar1 = 1;
    }
    else if (param_1 < 0x17) {
      uVar1 = param_1 & 0x3f;
    }
    else {
      uVar1 = 0x16;
    }
    DAT_20004808 = DAT_20004808 & 3 | (byte)(uVar1 << 2);
    DAT_20000eb0 = 0;
    FUN_0800fbf0(param_2);
    return;
  }
  return;
}

