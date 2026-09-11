// FUN_0800e3c8 @ 0x0800e3c8  size=22  body=[[0800e3c8, 0800e3dd]]

void FUN_0800e3c8(uint param_1)

{
  uint uVar1;
  
  if ((DAT_200016a5 & param_1) != 0) {
    uVar1 = (uint)DAT_200016a5 & ~param_1;
    DAT_200016a5 = (byte)uVar1;
    FUN_0800e38c(uVar1);
  }
  return;
}

