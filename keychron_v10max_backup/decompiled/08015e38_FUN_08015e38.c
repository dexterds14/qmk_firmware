// FUN_08015e38 @ 0x08015e38  size=20  body=[[08015e38, 08015e4b]]

void FUN_08015e38(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0x900) = *(uint *)(iVar1 + 0x900) | 0x200000;
  return;
}

