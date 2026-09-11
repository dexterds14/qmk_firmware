// Vector70_IRQ12_DMA1_Stream1 @ 0x08014edc  size=34  body=[[08014edc, 08014efd]]

void Vector70_IRQ12_DMA1_Stream1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_200024dc != (code *)0x0) {
    (*DAT_200024dc)(DAT_200024e0);
  }
  FUN_08013c7c();
  return;
}

