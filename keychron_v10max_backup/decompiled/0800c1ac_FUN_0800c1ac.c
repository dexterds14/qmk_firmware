// FUN_0800c1ac @ 0x0800c1ac  size=44  body=[[0800c1ac, 0800c1d7]]

void FUN_0800c1ac(void)

{
  byte bVar1;
  bool bVar2;
  
  if (DAT_20000d04 < 0xce4) {
    if ((DAT_2000159e < 0x15) &&
       (bVar1 = DAT_2000159e + 1, bVar2 = DAT_2000159e == 0x14, DAT_2000159e = bVar1, bVar2)) {
      FUN_0800a4e8();
      return;
    }
  }
  else if (DAT_2000159e < 0x15) {
    DAT_2000159e = 0;
  }
  return;
}

