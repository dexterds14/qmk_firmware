// FUN_08014358 @ 0x08014358  size=62  body=[[08014358, 08014395]]

void FUN_08014358(char *param_1)

{
  int iVar1;
  
  if (*param_1 == '\x05') {
    iVar1 = *(int *)(param_1 + 0x54);
    *(uint *)(iVar1 + 0x804) = *(uint *)(iVar1 + 0x804) | 1;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 8;
    *(uint *)(iVar1 + 0x18) = *(uint *)(iVar1 + 0x18) | 8;
    FUN_08013a7a(200);
    *(uint *)(*(int *)(param_1 + 0x54) + 0x804) =
         *(uint *)(*(int *)(param_1 + 0x54) + 0x804) & 0xfffffffe;
  }
  return;
}

