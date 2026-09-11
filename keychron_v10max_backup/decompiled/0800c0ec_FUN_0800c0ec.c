// FUN_0800c0ec @ 0x0800c0ec  size=84  body=[[0800c0ec, 0800c13f]]

char FUN_0800c0ec(void)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = (uint)DAT_20000d04;
  if (0x1004 < uVar2) {
    return 'd';
  }
  if (uVar2 < 0xdad) {
    if (uVar2 < 0xce5) {
      return '\0';
    }
    cVar1 = (char)((uVar2 * 0x14 - 66000) / 200);
  }
  else {
    cVar1 = (char)((uVar2 * 0x50 - 280000) / 600) + '\x14';
  }
  return cVar1;
}

