// Vector48_IRQ2_TAMP_STAMP @ 0x08015ef4  size=94  body=[[08015ef4, 08015f51]]

void Vector48_IRQ2_TAMP_STAMP(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_20004b48;
  uVar2 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar2 & 0xffff87ff;
  DAT_40013c14 = 0x200000;
  if (DAT_20004b4c != (code *)0x0) {
    if (*(int *)(iVar1 + 8) << 0x10 < 0) {
      if ((int)(uVar2 << 0x14) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,2);
      }
      if ((int)(uVar2 << 0x13) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,3);
      }
    }
    if (*(int *)(DAT_20004b48 + 0x40) << 0x1d < 0) {
      if ((int)(uVar2 << 0x12) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,4);
      }
      if ((int)(uVar2 << 0x11) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,5);
      }
    }
  }
  FUN_08013c7c();
  return;
}

