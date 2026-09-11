// thunk_FUN_08013838 @ 0x080138b4  size=4  body=[[080138b4, 080138b7]]

void thunk_FUN_08013838(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined1 *)(param_1 + 5) = 0;
  piVar2 = (int *)param_1[4];
  do {
    piVar2 = (int *)*piVar2;
  } while ((uint)param_1[2] <= (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_1 = (int)piVar2;
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  piVar2[1] = (int)param_1;
  return;
}

