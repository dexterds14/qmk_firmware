// FUN_08015e60 @ 0x08015e60  size=20  body=[[08015e60, 08015e73]]

void FUN_08015e60(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0x900) = *(uint *)(iVar1 + 0x900) & 0xffdfffff;
  return;
}

