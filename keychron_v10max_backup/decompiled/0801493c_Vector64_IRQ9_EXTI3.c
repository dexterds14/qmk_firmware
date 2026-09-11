// Vector64_IRQ9_EXTI3 @ 0x0801493c  size=32  body=[[0801493c, 0801495b]]

void Vector64_IRQ9_EXTI3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 8;
  if (((uVar1 & 8) != 0) && (DAT_20004a7c != (code *)0x0)) {
    (*DAT_20004a7c)(DAT_20004a80);
  }
  FUN_08013c7c();
  return;
}

