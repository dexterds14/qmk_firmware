// Vector78_IRQ14_DMA1_Stream3 @ 0x08014f34  size=34  body=[[08014f34, 08014f55]]

void Vector78_IRQ14_DMA1_Stream3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_200024ec != (code *)0x0) {
    (*DAT_200024ec)(DAT_200024f0);
  }
  FUN_08013c7c();
  return;
}

