// FUN_0801231c @ 0x0801231c  size=60  body=[[080122e0, 080122f9] [0801231c, 0801233d]]

void FUN_0801231c(uint param_1)

{
  int iVar1;
  
  if ((DAT_20000ec6 != '\0') && ((char)DAT_200047d4 < '\0')) {
    if (param_1 < 0xf0) {
      iVar1 = DAT_20000e98 + (param_1 >> 3);
      *(byte *)(iVar1 + 2) = (byte)(1 << (param_1 & 7)) | *(byte *)(iVar1 + 2);
    }
    return;
  }
  FUN_0801229c(DAT_20000e9c,param_1);
  return;
}

