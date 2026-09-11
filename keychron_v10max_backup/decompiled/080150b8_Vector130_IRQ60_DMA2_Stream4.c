// Vector130_IRQ60_DMA2_Stream4 @ 0x080150b8  size=30  body=[[080150b8, 080150d5]]

void Vector130_IRQ60_DMA2_Stream4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = uVar1 & 0x3d;
  if (DAT_20002534 != (code *)0x0) {
    (*DAT_20002534)(DAT_20002538);
  }
  FUN_08013c7c();
  return;
}

