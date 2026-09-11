// FUN_08013708 @ 0x08013708  size=102  body=[[08013708, 0801376d]]

void FUN_08013708(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 == DAT_200049f0) {
    DAT_200049f0 = (int *)*param_1;
    DAT_200049f0[1] = (int)&DAT_200049f0;
    *param_1 = 0;
    if ((int **)DAT_200049f0 == &DAT_200049f0) {
      FUN_08013d12();
      return;
    }
    DAT_200049f0[2] = DAT_200049f0[2] + param_1[2];
    iVar1 = FUN_08013cfa();
    if ((uint)(iVar1 - DAT_200049fc) < (uint)DAT_200049f0[2]) {
      FUN_08013616(iVar1,(DAT_200049fc + DAT_200049f0[2]) - iVar1);
      return;
    }
  }
  else {
    iVar3 = *param_1;
    piVar2 = (int *)param_1[1];
    iVar1 = param_1[2];
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
    *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + iVar1;
    *param_1 = 0;
    DAT_200049f8 = 0xffffffff;
  }
  return;
}

