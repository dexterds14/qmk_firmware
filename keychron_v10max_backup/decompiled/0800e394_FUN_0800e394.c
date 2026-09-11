// FUN_0800e394 @ 0x0800e394  size=22  body=[[0800e394, 0800e3a9]]

void FUN_0800e394(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & ~(uint)DAT_200016a5) != 0) {
    uVar1 = param_1 | DAT_200016a5;
    DAT_200016a5 = (byte)uVar1;
    FUN_0800e38c(uVar1);
  }
  return;
}

