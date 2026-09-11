// FUN_08014030 @ 0x08014030  size=26  body=[[08014030, 08014049]]

int FUN_08014030(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  if (*(int *)(iVar1 + 0xc) == 0) {
    iVar1 = param_2 * *(int *)(iVar1 + 0x10);
  }
  else {
    iVar1 = *(int *)(*(int *)(iVar1 + 0xc) + param_2 * 8);
  }
  return iVar1;
}

