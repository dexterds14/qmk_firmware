// FUN_0800e408 @ 0x0800e408  size=22  body=[[0800e408, 0800e41d]]

void FUN_0800e408(uint param_1)

{
  uint uVar1;
  
  if ((DAT_200016a6 & param_1) != 0) {
    uVar1 = (uint)DAT_200016a6 & ~param_1;
    DAT_200016a6 = (byte)uVar1;
    FUN_0800e3e4(uVar1);
  }
  return;
}

