// FUN_0800a0ec @ 0x0800a0ec  size=34  body=[[0800a0ec, 0800a10d]]

void FUN_0800a0ec(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0801668e(param_1);
  if (-1 < iVar1) {
    *(int *)(param_2 + 0x54) = *(int *)(param_2 + 0x54) + iVar1;
    return;
  }
  *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  return;
}

