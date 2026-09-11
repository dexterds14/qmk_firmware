// FUN_08010cd4 @ 0x08010cd4  size=24  body=[[08010cd4, 08010ceb]]

void FUN_08010cd4(void)

{
  if ((DAT_20004808 & 3) != 0) {
    DAT_20000eb0 = 0;
  }
  DAT_20004808 = DAT_20004808 & 0xfc;
  return;
}

