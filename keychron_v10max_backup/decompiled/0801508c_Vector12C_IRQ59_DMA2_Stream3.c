// Vector12C_IRQ59_DMA2_Stream3 @ 0x0801508c  size=34  body=[[0801508c, 080150ad]]

void Vector12C_IRQ59_DMA2_Stream3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000252c != (code *)0x0) {
    (*DAT_2000252c)(DAT_20002530);
  }
  FUN_08013c7c();
  return;
}

