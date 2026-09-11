// Vector68_IRQ10_EXTI4 @ 0x08014964  size=32  body=[[08014964, 08014983]]

void Vector68_IRQ10_EXTI4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0x10;
  if (((uVar1 & 0x10) != 0) && (DAT_20004a84 != (code *)0x0)) {
    (*DAT_20004a84)(DAT_20004a88);
  }
  FUN_08013c7c();
  return;
}

