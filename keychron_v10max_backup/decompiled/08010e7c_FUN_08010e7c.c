// FUN_08010e7c @ 0x08010e7c  size=46  body=[[08010e7c, 08010ea9]]

void FUN_08010e7c(undefined4 param_1)

{
  DAT_20004808 = DAT_20004808 ^ 1;
  DAT_20000eb0 = 0;
  FUN_0800fbf0((byte)param_1);
  while (((DAT_20004808 & 3) != 0 && (DAT_2000480b < 0x20))) {
    FUN_08010e4c(param_1);
  }
  return;
}

