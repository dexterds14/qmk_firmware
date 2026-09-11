// FUN_08010f74 @ 0x08010f74  size=24  body=[[08010f5c, 08010f6d] [08010f74, 08010f79]]

void FUN_08010f74(void)

{
  uint uVar1;
  
  uVar1 = DAT_2000480c + 0x10;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  DAT_2000480c = (byte)uVar1;
  FUN_0800fbf0(1);
  return;
}

