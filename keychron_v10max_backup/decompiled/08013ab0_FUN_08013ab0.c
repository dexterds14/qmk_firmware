// FUN_08013ab0 @ 0x08013ab0  size=18  body=[[08013ab0, 08013ac1]]

void FUN_08013ab0(undefined4 *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    *param_1 = 0;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
    return;
  }
  return;
}

