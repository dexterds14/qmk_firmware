// FUN_080111a0 @ 0x080111a0  size=86  body=[[080111a0, 080111f5]]

char FUN_080111a0(uint param_1,byte param_2,undefined1 param_3,uint param_4,byte param_5)

{
  char cVar1;
  int iVar2;
  
  if (param_1 < 2) {
    cVar1 = FUN_080126e8(*(uint *)(&DAT_20000eb8 + param_1 * 4),0,0,0x10);
    if (cVar1 != '\0') {
      DAT_20001fbe = param_2 & 0xf | 0x20;
      DAT_20001fbf = param_3;
      iVar2 = FUN_080127c4(0x20001fbe,2);
      if ((iVar2 == 0) && (iVar2 = FUN_080127c4(param_4,(uint)param_5), iVar2 == 0)) {
        FUN_080127d8();
        return cVar1;
      }
    }
    FUN_080127d8();
  }
  return '\0';
}

