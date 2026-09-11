// FUN_0801189c @ 0x0801189c  size=48  body=[[0801189c, 080118cb]]

void FUN_0801189c(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = DAT_40020010;
  uVar1 = ~(uVar1 >> 8) & 1;
  DAT_20001ffa = (byte)uVar1;
  if ((DAT_20001ff9 != uVar1) || (param_1 != 0)) {
    FUN_0800cd18(0,uVar1,param_3);
    FUN_08011894();
    DAT_20001ff9 = DAT_20001ffa;
  }
  return;
}

