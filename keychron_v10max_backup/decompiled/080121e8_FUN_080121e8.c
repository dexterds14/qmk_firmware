// FUN_080121e8 @ 0x080121e8  size=64  body=[[080121e8, 08012227]]

char FUN_080121e8(void)

{
  char cVar1;
  char *pcVar2;
  int iVar4;
  int iVar5;
  char *pcVar3;
  
  if ((DAT_20000ec6 == '\0') || (-1 < (char)DAT_200047d4)) {
    iVar5 = 6;
    iVar4 = DAT_20000e9c;
  }
  else {
    iVar5 = 0x1e;
    iVar4 = DAT_20000e98;
  }
  cVar1 = '\0';
  pcVar3 = (char *)(iVar4 + 2);
  do {
    pcVar2 = pcVar3 + 1;
    if (*pcVar3 != '\0') {
      cVar1 = cVar1 + '\x01';
    }
    pcVar3 = pcVar2;
  } while (((uint)((char *)(iVar4 + 2) + (iVar5 - (int)pcVar2 & 0xff)) & 0xff) != 0);
  return cVar1;
}

