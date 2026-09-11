// FUN_0800a180 @ 0x0800a180  size=16  body=[[0800a180, 0800a18f]]

int FUN_0800a180(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + -4) + -4;
  if (*(int *)(param_2 + -4) < 0) {
    iVar1 = iVar1 + *(int *)(param_2 + iVar1);
  }
  return iVar1;
}

