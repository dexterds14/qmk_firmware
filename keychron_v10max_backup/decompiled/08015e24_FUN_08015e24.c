// FUN_08015e24 @ 0x08015e24  size=20  body=[[08015e24, 08015e37]]

void FUN_08015e24(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0xb00) = *(uint *)(iVar1 + 0xb00) | 0x200000;
  return;
}

