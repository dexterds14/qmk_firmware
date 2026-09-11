// FUN_0801246c @ 0x0801246c  size=36  body=[[0801246c, 0801248f]]

undefined4 FUN_0801246c(void)

{
  int iVar1;
  uint uVar2;
  
  FUN_08012454();
  FUN_0800ee8c();
  FUN_08012456();
  uVar2 = 0;
  do {
    iVar1 = FUN_0800ed20(uVar2 & 0xff);
    if (iVar1 != 0) {
      return 1;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 6);
  return 0;
}

