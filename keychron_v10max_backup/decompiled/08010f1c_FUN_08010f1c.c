// FUN_08010f1c @ 0x08010f1c  size=50  body=[[08010f1c, 08010f4d]]

void FUN_08010f1c(undefined4 param_1)

{
  FUN_08010d94(DAT_20004809,DAT_2000480a,
               (byte)(DAT_2000480b - 0x10) & ~(byte)((int)(DAT_2000480b - 0x10) >> 0x1f),
               (byte)param_1);
  if (((DAT_20004808 & 3) != 0) && (DAT_2000480b < 0x21)) {
    FUN_08010e7c(param_1);
    return;
  }
  return;
}

