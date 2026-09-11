// Vector60_IRQ8_EXTI2 @ 0x08014914  size=32  body=[[08014914, 08014933]]

void Vector60_IRQ8_EXTI2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 4;
  if (((uVar1 & 4) != 0) && (DAT_20004a74 != (code *)0x0)) {
    (*DAT_20004a74)(DAT_20004a78);
  }
  FUN_08013c7c();
  return;
}

