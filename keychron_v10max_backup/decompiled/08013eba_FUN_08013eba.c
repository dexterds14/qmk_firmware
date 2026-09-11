// FUN_08013eba @ 0x08013eba  size=28  body=[[08013eba, 08013ed5]]

int FUN_08013eba(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = *(int **)(param_1 + 0x14);
  if ((*(int **)(param_1 + 0x10) == piVar1) && (*(int *)(param_1 + 0xc) != 0)) {
    piVar3 = (int *)0x0;
    iVar2 = (int)piVar3;
  }
  else {
    piVar3 = piVar1 + 1;
    iVar2 = *piVar1;
  }
  *param_2 = iVar2;
  return (int)piVar3;
}

