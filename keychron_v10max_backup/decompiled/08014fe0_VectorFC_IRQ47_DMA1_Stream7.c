// VectorFC_IRQ47_DMA1_Stream7 @ 0x08014fe0  size=34  body=[[08014fe0, 08015001]]

void VectorFC_IRQ47_DMA1_Stream7(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000250c != (code *)0x0) {
    (*DAT_2000250c)(DAT_20002510);
  }
  FUN_08013c7c();
  return;
}

