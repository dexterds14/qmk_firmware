// FUN_08014064 @ 0x08014064  size=16  body=[[08014064, 08014073]]

int FUN_08014064(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  return *(int *)(iVar1 + 0x14) + param_2;
}

