// FUN_0800aa20 @ 0x0800aa20  size=58  body=[[0800aa20, 0800aa59]]

void FUN_0800aa20(void)

{
  uint uVar1;
  
  uVar1 = FUN_0801258c(DAT_20001514);
  if (3000 < uVar1) {
    DAT_20001514 = FUN_08012508();
    DAT_40020018 = 0x100000;
    FUN_08013a7a(1000);
    DAT_40020018 = 0x10;
    FUN_08013a7a(30000);
    return;
  }
  return;
}

