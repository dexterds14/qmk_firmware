// FUN_08013854 @ 0x08013854  size=28  body=[[08013854, 0801386f]]

void FUN_08013854(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined1 *)(param_1 + 5) = 0;
  piVar2 = (int *)param_1[4];
  do {
    piVar2 = (int *)*piVar2;
  } while ((uint)param_1[2] < (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_1 = (int)piVar2;
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  piVar2[1] = (int)param_1;
  return;
}

