// Vector158_IRQ70_DMA2_Stream7 @ 0x08015138  size=36  body=[[08015138, 0801515b]]

void Vector158_IRQ70_DMA2_Stream7(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000254c != (code *)0x0) {
    (*DAT_2000254c)(DAT_20002550);
  }
  FUN_08013c7c();
  return;
}

