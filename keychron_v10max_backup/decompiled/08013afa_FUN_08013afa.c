// FUN_08013afa @ 0x08013afa  size=28  body=[[08013afa, 08013b15]]

void FUN_08013afa(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  while (piVar1 = (int *)*param_1, param_1 != piVar1) {
    iVar2 = *piVar1;
    *param_1 = iVar2;
    *(int **)(iVar2 + 4) = param_1;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
  }
  return;
}

