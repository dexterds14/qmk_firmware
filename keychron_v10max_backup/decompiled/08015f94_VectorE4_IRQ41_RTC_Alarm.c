// VectorE4_IRQ41_RTC_Alarm @ 0x08015f94  size=66  body=[[08015f94, 08015fd5]]

void VectorE4_IRQ41_RTC_Alarm(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_20004b48;
  uVar1 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar1 & 0xfffffcff;
  DAT_40013c14 = 0x20000;
  if (DAT_20004b4c != (code *)0x0) {
    iVar2 = *(int *)(iVar2 + 8);
    if ((iVar2 << 0x13 < 0) && ((int)(uVar1 << 0x17) < 0)) {
      (*DAT_20004b4c)(&DAT_20004b44,0);
    }
    if ((iVar2 << 0x12 < 0) && ((int)(uVar1 << 0x16) < 0)) {
      (*DAT_20004b4c)(&DAT_20004b44,1);
    }
  }
  FUN_08013c7c();
  return;
}

