// FUN_08011a8c @ 0x08011a8c  size=120  body=[[08011a8c, 08011b03]]

byte FUN_08011a8c(void)

{
  byte bVar1;
  uint uVar2;
  
  if ((int)((uint)DAT_20002012 << 0x1f) < 0) {
    uVar2 = 400;
  }
  else if ((int)((uint)DAT_20002012 << 0x1d) < 0) {
    uVar2 = 3000;
  }
  else if ((DAT_20002011 == '\0') || (DAT_2000200e == 0)) {
    uVar2 = 0x1e;
  }
  else {
    uVar2 = FUN_0801257e((uint)DAT_2000200e);
    uVar2 = uVar2 / 0x32 & 0xffff;
    uVar2 = uVar2 * 0x2d + 0x1e + ((int)(uVar2 * uVar2 * 0x2d) >> 1) & 0xffff;
    if (0x5db < uVar2) {
      uVar2 = 0x5dc;
    }
  }
  bVar1 = (byte)((ulonglong)uVar2 / (1000 / (ulonglong)DAT_20000ec5));
  if (bVar1 == 0) {
    bVar1 = 1;
  }
  if (0x7e < bVar1) {
    bVar1 = 0x7f;
  }
  return bVar1;
}

