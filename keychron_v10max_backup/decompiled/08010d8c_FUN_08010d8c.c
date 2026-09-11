// FUN_08010d8c @ 0x08010d8c  size=32  body=[[08010d6c, 08010d85] [08010d8c, 08010d91]]

void FUN_08010d8c(void)

{
  uint uVar1;
  
  uVar1 = (DAT_20004808 >> 2) - 1 & 0xff;
  if (uVar1 == 0) {
    uVar1 = 0x16;
  }
  FUN_08010d04(uVar1,1);
  return;
}

