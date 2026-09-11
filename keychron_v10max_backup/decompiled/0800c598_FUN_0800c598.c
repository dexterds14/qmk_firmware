// FUN_0800c598 @ 0x0800c598  size=40  body=[[0800c598, 0800c5bf]]

void FUN_0800c598(void)

{
  char cVar1;
  uint uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  
  if ((DAT_20000d06 != '\0') && (uVar2 = FUN_08012508(), uVar2 < 1000)) {
    FUN_0800c54c(uVar2,extraout_r1,extraout_r2,extraout_r3);
    cVar1 = FUN_0800bbb4();
    if (cVar1 == '\x02') {
      FUN_0800a298();
    }
    DAT_20000d06 = '\0';
  }
  return;
}

