// Vector124_IRQ57_DMA2_Stream1 @ 0x08015034  size=34  body=[[08015034, 08015055]]

void Vector124_IRQ57_DMA2_Stream1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_2000251c != (code *)0x0) {
    (*DAT_2000251c)(DAT_20002520);
  }
  FUN_08013c7c();
  return;
}

