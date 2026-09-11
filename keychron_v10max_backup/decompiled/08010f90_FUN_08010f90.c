// FUN_08010f90 @ 0x08010f90  size=22  body=[[08010f7c, 08010f8b] [08010f90, 08010f95]]

void FUN_08010f90(void)

{
  DAT_2000480c = (byte)(DAT_2000480c - 0x10) & ~(byte)((int)(DAT_2000480c - 0x10) >> 0x1f);
  FUN_0800fbf0(1);
  return;
}

