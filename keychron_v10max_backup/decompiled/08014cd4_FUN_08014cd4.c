// FUN_08014cd4 @ 0x08014cd4  size=26  body=[[08014cd4, 08014ced]]

void FUN_08014cd4(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x1c);
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x45670123;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0xcdef89ab;
  DAT_40023c10 = 0;
  return;
}

