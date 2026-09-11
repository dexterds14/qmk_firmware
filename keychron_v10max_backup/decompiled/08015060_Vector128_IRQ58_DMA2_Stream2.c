// Vector128_IRQ58_DMA2_Stream2 @ 0x08015060  size=34  body=[[08015060, 08015081]]

void Vector128_IRQ58_DMA2_Stream2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002524 != (code *)0x0) {
    (*DAT_20002524)(DAT_20002528);
  }
  FUN_08013c7c();
  return;
}

