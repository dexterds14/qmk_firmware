// FUN_080120d0 @ 0x080120d0  size=66  body=[[080120d0, 08012111]]

void FUN_080120d0(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_2000201c != 0) {
    uVar1 = FUN_0801257e((uint)DAT_2000201a);
    uVar2 = FUN_0800defc();
    if ((uVar2 < uVar1) &&
       (-1 < (int)((uint)(byte)(&DAT_20000e81)[(uint)(byte)DAT_2000201c * 0x1c] << 0x1d))) {
      FUN_08011fb8((undefined4 *)(&DAT_20000e7c + (uint)(byte)DAT_2000201c * 0x1c));
      return;
    }
  }
  return;
}

