// FUN_0801364c @ 0x0801364c  size=82  body=[[0801364c, 0801369d]]

void FUN_0801364c(int *param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  DAT_200049fc = param_2;
  param_1[2] = param_3;
  param_1[1] = (int)&DAT_200049f0;
  *param_1 = (int)DAT_200049f0;
  if (param_3 < 2) {
    param_3 = 2;
  }
  *(int **)((int)DAT_200049f0 + 4) = param_1;
  DAT_200049f0 = param_1;
  FUN_08013d02(param_2 + param_3);
  uVar2 = 2;
  while (iVar1 = FUN_08013cfa(), param_3 <= (uint)(iVar1 - param_2)) {
    param_3 = uVar2 + 1;
    FUN_08013d1c(param_2 + param_3);
    param_2 = iVar1;
    uVar2 = param_3;
  }
  if (2 < uVar2) {
    FUN_080135dc(1);
    return;
  }
  return;
}

