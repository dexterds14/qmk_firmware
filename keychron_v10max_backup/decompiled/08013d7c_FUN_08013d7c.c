// FUN_08013d7c @ 0x08013d7c  size=32  body=[[08013d7c, 08013d9b]]

void FUN_08013d7c(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)param_1[4];
  *puVar1 = param_2;
  param_1[3] = param_1[3] + 1;
  uVar2 = (int)puVar1 + param_1[7];
  param_1[4] = uVar2;
  if ((uint)param_1[6] <= uVar2) {
    param_1[4] = param_1[9];
  }
  FUN_08013ae4(param_1,0);
  return;
}

