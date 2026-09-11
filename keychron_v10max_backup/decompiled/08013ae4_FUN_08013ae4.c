// FUN_08013ae4 @ 0x08013ae4  size=22  body=[[08013ae4, 08013af9]]

void FUN_08013ae4(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (param_1 != piVar1) {
    iVar2 = *piVar1;
    *param_1 = iVar2;
    *(int **)(iVar2 + 4) = param_1;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
    return;
  }
  return;
}

