// FUN_08013ed6 @ 0x08013ed6  size=30  body=[[08013ed6, 08013ef3]]

void FUN_08013ed6(int *param_1)

{
  int iVar1;
  
  param_1[3] = param_1[3] + 1;
  iVar1 = param_1[5];
  param_1[5] = iVar1 + param_1[7];
  if ((uint)param_1[6] <= (uint)(iVar1 + param_1[7])) {
    param_1[5] = param_1[9];
  }
  FUN_08013ae4(param_1,0);
  return;
}

