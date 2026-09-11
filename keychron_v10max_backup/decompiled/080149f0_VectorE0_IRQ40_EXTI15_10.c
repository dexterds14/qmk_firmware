// VectorE0_IRQ40_EXTI15_10 @ 0x080149f0  size=104  body=[[080149f0, 08014a57]]

void VectorE0_IRQ40_EXTI15_10(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0xfc00;
  if (((int)(uVar1 << 0x15) < 0) && (DAT_20004ab4 != (code *)0x0)) {
    (*DAT_20004ab4)(DAT_20004ab8);
  }
  if (((int)(uVar1 << 0x14) < 0) && (DAT_20004abc != (code *)0x0)) {
    (*DAT_20004abc)(DAT_20004ac0);
  }
  if (((int)(uVar1 << 0x13) < 0) && (DAT_20004ac4 != (code *)0x0)) {
    (*DAT_20004ac4)(DAT_20004ac8);
  }
  if (((int)(uVar1 << 0x12) < 0) && (DAT_20004acc != (code *)0x0)) {
    (*DAT_20004acc)(DAT_20004ad0);
  }
  if (((int)(uVar1 << 0x11) < 0) && (DAT_20004ad4 != (code *)0x0)) {
    (*DAT_20004ad4)(DAT_20004ad8);
  }
  if (((int)(uVar1 << 0x10) < 0) && (DAT_20004adc != (code *)0x0)) {
    (*DAT_20004adc)(DAT_20004ae0);
  }
  FUN_08013c7c();
  return;
}

