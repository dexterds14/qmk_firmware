// FUN_0800e2fc @ 0x0800e2fc  size=14  body=[[0800e2fc, 0800e309]]

byte FUN_0800e2fc(void)

{
  byte bVar1;
  
  bVar1 = DAT_200016a4 & 7;
  if ((DAT_200016a4 & 7) != 0) {
    bVar1 = 1;
  }
  return bVar1;
}

