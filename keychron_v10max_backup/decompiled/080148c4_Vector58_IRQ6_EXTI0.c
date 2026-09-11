// Vector58_IRQ6_EXTI0 @ 0x080148c4  size=32  body=[[080148c4, 080148e3]]

void Vector58_IRQ6_EXTI0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 1;
  if (((uVar1 & 1) != 0) && (DAT_20004a64 != (code *)0x0)) {
    (*DAT_20004a64)(DAT_20004a68);
  }
  FUN_08013c7c();
  return;
}

