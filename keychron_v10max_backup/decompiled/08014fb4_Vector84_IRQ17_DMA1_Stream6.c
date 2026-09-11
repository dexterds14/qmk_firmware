// Vector84_IRQ17_DMA1_Stream6 @ 0x08014fb4  size=34  body=[[08014fb4, 08014fd5]]

void Vector84_IRQ17_DMA1_Stream6(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002504 != (code *)0x0) {
    (*DAT_20002504)(DAT_20002508);
  }
  FUN_08013c7c();
  return;
}

