// Vector7C_IRQ15_DMA1_Stream4 @ 0x08014f60  size=30  body=[[08014f60, 08014f7d]]

void Vector7C_IRQ15_DMA1_Stream4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = uVar1 & 0x3d;
  if (DAT_200024f4 != (code *)0x0) {
    (*DAT_200024f4)(DAT_200024f8);
  }
  FUN_08013c7c();
  return;
}

