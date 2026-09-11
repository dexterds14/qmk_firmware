// Vector6C_IRQ11_DMA1_Stream0 @ 0x08014eb4  size=30  body=[[08014eb4, 08014ed1]]

void Vector6C_IRQ11_DMA1_Stream0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = uVar1 & 0x3d;
  if (DAT_200024d4 != (code *)0x0) {
    (*DAT_200024d4)(DAT_200024d8);
  }
  FUN_08013c7c();
  return;
}

