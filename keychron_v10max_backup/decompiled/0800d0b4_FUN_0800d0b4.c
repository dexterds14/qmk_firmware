// FUN_0800d0b4 @ 0x0800d0b4  size=66  body=[[0800d0b4, 0800d0f5]]

undefined4 FUN_0800d0b4(uint param_1)

{
  char cVar1;
  byte bVar2;
  ushort *puVar3;
  undefined4 uVar4;
  
  puVar3 = FUN_0800d090(param_1);
  if (puVar3 == (ushort *)0x0) {
    uVar4 = 1;
  }
  else {
    cVar1 = FUN_0800e310();
    if ((cVar1 != '\0') && (*puVar3 != param_1)) {
      FUN_0800e424();
      FUN_0800e3b0();
      bVar2 = FUN_0800e380();
      FUN_0800d684((uint)bVar2);
      DAT_200015e0 = 0;
      DAT_200015e4 = 0;
      DAT_200015de = 0;
      DAT_200015dd = 0;
    }
    uVar4 = 0;
  }
  return uVar4;
}

