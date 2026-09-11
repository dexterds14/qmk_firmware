// Vector9C_IRQ23_EXTI9_5 @ 0x0801498c  size=90  body=[[0801498c, 080149e5]]

void Vector9C_IRQ23_EXTI9_5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0x3e0;
  if (((int)(uVar1 << 0x1a) < 0) && (DAT_20004a8c != (code *)0x0)) {
    (*DAT_20004a8c)(DAT_20004a90);
  }
  if (((int)(uVar1 << 0x19) < 0) && (DAT_20004a94 != (code *)0x0)) {
    (*DAT_20004a94)(DAT_20004a98);
  }
  if (((int)(uVar1 << 0x18) < 0) && (DAT_20004a9c != (code *)0x0)) {
    (*DAT_20004a9c)(DAT_20004aa0);
  }
  if (((int)(uVar1 << 0x17) < 0) && (DAT_20004aa4 != (code *)0x0)) {
    (*DAT_20004aa4)(DAT_20004aa8);
  }
  if (((int)(uVar1 << 0x16) < 0) && (DAT_20004aac != (code *)0x0)) {
    (*DAT_20004aac)(DAT_20004ab0);
  }
  FUN_08013c7c();
  return;
}

