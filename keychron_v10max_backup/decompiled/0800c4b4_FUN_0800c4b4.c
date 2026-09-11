// FUN_0800c4b4 @ 0x0800c4b4  size=144  body=[[0800c4b4, 0800c543]]

undefined4 FUN_0800c4b4(uint param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  
  if (param_1 == 0x7e0e) {
    cVar2 = FUN_0800bbb4();
    if (cVar2 != '\x04') {
      return 1;
    }
    if (*(char *)(param_2 + 5) != '\0') {
      DAT_200015bc = 0x18;
      DAT_200015c0 = FUN_08012508();
      return 1;
    }
  }
  else {
    if (0x7e0e < param_1) {
      if (param_1 != 0x7e0f) {
        return 1;
      }
      bVar1 = FUN_0800bbb4();
      if ((bVar1 & 6) == 0) {
        return 1;
      }
      uVar3 = FUN_0800bcb8();
      if (uVar3 != 0) {
        return 1;
      }
      cVar2 = FUN_0800c0ec();
      FUN_0800c2ac(cVar2);
      return 1;
    }
    if (2 < param_1 - 0x7e0b) {
      return 1;
    }
    cVar2 = FUN_0800bbb4();
    if (cVar2 != '\x02') {
      return 1;
    }
    if (*(char *)(param_2 + 5) != '\0') {
      DAT_200015bc = (char)param_1 - 10;
      DAT_200015c0 = FUN_08012508();
      FUN_0800a3d4((uint)DAT_200015bc,0);
      return 1;
    }
  }
  DAT_200015c0 = 0;
  DAT_200015bc = 0;
  return 1;
}

