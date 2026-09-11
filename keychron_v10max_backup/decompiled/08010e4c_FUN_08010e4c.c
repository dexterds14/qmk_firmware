// FUN_08010e4c @ 0x08010e4c  size=44  body=[[08010e4c, 08010e77]]

void FUN_08010e4c(undefined4 param_1)

{
  uint uVar1;
  
  if ((DAT_20004808 & 3) == 0) {
    FUN_08010e7c(param_1);
    return;
  }
  uVar1 = DAT_2000480b + 0x10;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  FUN_08010d94(DAT_20004809,DAT_2000480a,(char)uVar1,(byte)param_1);
  return;
}

