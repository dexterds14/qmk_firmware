// Vector120_IRQ56_DMA2_Stream0 @ 0x0801500c  size=30  body=[[0801500c, 08015029]]

void Vector120_IRQ56_DMA2_Stream0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = uVar1 & 0x3d;
  if (DAT_20002514 != (code *)0x0) {
    (*DAT_20002514)(DAT_20002518);
  }
  FUN_08013c7c();
  return;
}

