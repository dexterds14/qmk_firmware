// Vector154_IRQ69_DMA2_Stream6 @ 0x0801510c  size=34  body=[[0801510c, 0801512d]]

void Vector154_IRQ69_DMA2_Stream6(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002544 != (code *)0x0) {
    (*DAT_20002544)(DAT_20002548);
  }
  FUN_08013c7c();
  return;
}

