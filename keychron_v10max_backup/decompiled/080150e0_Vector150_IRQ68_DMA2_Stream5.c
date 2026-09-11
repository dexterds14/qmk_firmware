// Vector150_IRQ68_DMA2_Stream5 @ 0x080150e0  size=34  body=[[080150e0, 08015101]]

void Vector150_IRQ68_DMA2_Stream5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_2000253c != (code *)0x0) {
    (*DAT_2000253c)(DAT_20002540);
  }
  FUN_08013c7c();
  return;
}

