// Vector5C_IRQ7_EXTI1 @ 0x080148ec  size=32  body=[[080148ec, 0801490b]]

void Vector5C_IRQ7_EXTI1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 2;
  if (((uVar1 & 2) != 0) && (DAT_20004a6c != (code *)0x0)) {
    (*DAT_20004a6c)(DAT_20004a70);
  }
  FUN_08013c7c();
  return;
}

