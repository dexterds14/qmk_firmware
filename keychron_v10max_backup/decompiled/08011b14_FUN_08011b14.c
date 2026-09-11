// FUN_08011b14 @ 0x08011b14  size=94  body=[[08011b14, 08011b71]]

undefined4 FUN_08011b14(void)

{
  uint uVar1;
  
  if ((DAT_20002012 & 1) == 0) {
    if ((int)((uint)DAT_20002012 << 0x1d) < 0) {
      uVar1 = 0x32;
    }
    else if ((DAT_20002010 == '\0') || (DAT_2000200e == 0)) {
      uVar1 = 0x40;
    }
    else {
      uVar1 = (uint)DAT_20000ec2;
      if (uVar1 != 0x20) {
        uVar1 = FUN_0801257e((uint)DAT_2000200e);
        uVar1 = uVar1 / 0x32 & 0xffff;
        uVar1 = uVar1 + 0x40 + ((int)(uVar1 * uVar1) >> 1) & 0xffff;
        if (0x1f < uVar1) {
          uVar1 = 0x20;
        }
      }
    }
  }
  else {
    uVar1 = 8;
  }
  DAT_20000ec2 = (short)(1000 / uVar1);
  return 1;
}

