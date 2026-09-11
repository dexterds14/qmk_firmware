// FUN_08015e4c @ 0x08015e4c  size=20  body=[[08015e4c, 08015e5f]]

void FUN_08015e4c(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0xb00) = *(uint *)(iVar1 + 0xb00) & 0xffdfffff;
  return;
}

