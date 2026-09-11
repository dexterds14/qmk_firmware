// FUN_08010ebc @ 0x08010ebc  size=42  body=[[08010ebc, 08010ee5]]

void FUN_08010ebc(void)

{
  if ((DAT_20004808 & 3) == 0) {
    DAT_20000eb0 = DAT_20004808 & 3;
  }
  DAT_20004808 = DAT_20004808 & 0xfc | 1;
  while (DAT_2000480b < 0x20) {
    FUN_08010e4c(0);
  }
  return;
}

