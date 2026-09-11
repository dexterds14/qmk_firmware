// FUN_080135ec @ 0x080135ec  size=42  body=[[080135ec, 08013615]]

void FUN_080135ec(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  
  for (piVar1 = (int *)*param_1; (uint)piVar1[2] < param_3; piVar1 = (int *)*piVar1) {
    param_3 = param_3 - piVar1[2];
  }
  puVar2 = (undefined4 *)piVar1[1];
  param_2[2] = param_3;
  *param_2 = (int)piVar1;
  param_2[1] = (int)puVar2;
  *puVar2 = param_2;
  piVar1[1] = (int)param_2;
  piVar1[2] = piVar1[2] - param_3;
  param_1[2] = -1;
  return;
}

