// FUN_08013158 @ 0x08013158  size=28  body=[[08013158, 08013173]]

void FUN_08013158(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if ((param_2 < 9) && (iVar1 = *(int *)(param_1 + param_2 * 4), iVar1 != 0)) {
    uVar2 = *(uint *)(iVar1 + 0x48);
    *(uint *)(param_3 + 0x48) = uVar2;
    memcpy((undefined4 *)(param_3 + 8),(undefined4 *)(iVar1 + 8),uVar2);
    return;
  }
  return;
}

