// FUN_08013100 @ 0x08013100  size=28  body=[[08013100, 0801311b]]

void FUN_08013100(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    FUN_08008798((byte *)(iVar1 + 8),0,*(uint *)(iVar1 + 0x48));
    puVar2 = (undefined4 *)*param_1;
    *puVar2 = 0;
    puVar2[1] = 0;
  }
  return;
}

