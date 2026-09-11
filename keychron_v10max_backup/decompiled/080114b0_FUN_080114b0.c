// FUN_080114b0 @ 0x080114b0  size=70  body=[[080114b0, 080114f5]]

void FUN_080114b0(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_08015338((uint *)&DAT_40020400,0x80,1);
  DAT_40020418 = 0x80;
  FUN_08012674();
  FUN_0801124c(0);
  FUN_0801124c(1);
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    FUN_08011398(uVar1,1,1,1);
  } while (uVar2 != 0x58);
  FUN_08011480(0);
  FUN_08011480(1);
  return;
}

