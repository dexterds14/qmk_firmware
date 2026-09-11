// Vector80_IRQ16_DMA1_Stream5 @ 0x08014f88  size=34  body=[[08014f88, 08014fa9]]

void Vector80_IRQ16_DMA1_Stream5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_200024fc != (code *)0x0) {
    (*DAT_200024fc)(DAT_20002500);
  }
  FUN_08013c7c();
  return;
}

