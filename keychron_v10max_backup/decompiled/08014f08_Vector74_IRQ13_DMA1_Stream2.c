// Vector74_IRQ13_DMA1_Stream2 @ 0x08014f08  size=34  body=[[08014f08, 08014f29]]

void Vector74_IRQ13_DMA1_Stream2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_200024e4 != (code *)0x0) {
    (*DAT_200024e4)(DAT_200024e8);
  }
  FUN_08013c7c();
  return;
}

