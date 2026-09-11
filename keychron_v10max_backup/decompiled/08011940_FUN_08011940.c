// FUN_08011940 @ 0x08011940  size=44  body=[[08011940, 0801196b]]

void FUN_08011940(void)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = DAT_20002008;
  if (DAT_20002008 == '\0') {
    FUN_0800cdf4();
    DAT_20002008 = 1;
    uVar2 = FUN_08012574();
    DAT_20002006 = (undefined2)uVar2;
    DAT_20001ffb = cVar1;
    FUN_08008798((byte *)&DAT_20001ffc,0,10);
    return;
  }
  return;
}

