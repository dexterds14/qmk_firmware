// FUN_0800e43c @ 0x0800e43c  size=34  body=[[0800e43c, 0800e45d]]

byte FUN_0800e43c(void)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = DAT_200016d0 | DAT_200016cf;
  if (DAT_200016a6 != 0) {
    bVar2 = bVar2 | DAT_200016a6;
    cVar1 = FUN_080121e8();
    if (cVar1 != '\0') {
      FUN_0800e424();
    }
  }
  return bVar2;
}

