// FUN_08014cfc @ 0x08014cfc  size=12  body=[[08014cfc, 08014d07]]

void FUN_08014cfc(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x10) =
       *(uint *)(*(int *)(param_1 + 0x1c) + 0x10) | 0x80000000;
  return;
}

