// FUN_08012674 @ 0x08012674  size=98  body=[[08012674, 080126d5]]

void FUN_08012674(void)

{
  char cVar1;
  
  cVar1 = DAT_2000203c;
  if (DAT_2000203c == '\0') {
    DAT_2000203c = '\x01';
    FUN_08015338((uint *)&DAT_40020000,0x20,0);
    FUN_08015338((uint *)&DAT_40020000,0x80,0);
    FUN_08015338((uint *)&DAT_40020000,0x40,0);
    FUN_08013a7a(1000);
    FUN_08015338((uint *)&DAT_40020000,0x20,0x29a);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x29a);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x29a);
    FUN_08014142(&DAT_20004b50);
    DAT_20002058 = cVar1;
  }
  return;
}

