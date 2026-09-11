// FUN_0800a154 @ 0x0800a154  size=34  body=[[0800a154, 0800a175]]

void FUN_0800a154(undefined4 param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  
  iVar1 = FUN_08016698();
  if (iVar1 == -1) {
    uVar2 = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    uVar2 = *(ushort *)(param_2 + 0xc) | 0x1000;
    *(int *)(param_2 + 0x54) = iVar1;
  }
  *(ushort *)(param_2 + 0xc) = uVar2;
  return;
}

