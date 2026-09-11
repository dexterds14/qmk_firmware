// Vector4C_IRQ3_RTC_WKUP @ 0x08015f5c  size=48  body=[[08015f5c, 08015f8b]]

void Vector4C_IRQ3_RTC_WKUP(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_20004b48;
  uVar2 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar2 & 0xfffffbff;
  DAT_40013c14 = 0x400000;
  if (((DAT_20004b4c != (code *)0x0) && (*(int *)(iVar1 + 8) << 0x11 < 0)) &&
     ((int)(uVar2 << 0x15) < 0)) {
    (*DAT_20004b4c)(&DAT_20004b44,7);
  }
  FUN_08013c7c();
  return;
}

