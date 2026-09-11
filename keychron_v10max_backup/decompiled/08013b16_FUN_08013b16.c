// FUN_08013b16 @ 0x08013b16  size=30  body=[[08013b16, 08013b33]]

void FUN_08013b16(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  piVar2 = param_1;
  do {
    piVar2 = (int *)*piVar2;
    if (param_1 == piVar2) break;
  } while ((uint)param_2[2] <= (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_2 = (int)piVar2;
  param_2[1] = (int)puVar1;
  *puVar1 = param_2;
  piVar2[1] = (int)param_2;
  return;
}

