// FUN_08013040 @ 0x08013040  size=56  body=[[08013040, 08013077]]

undefined4 FUN_08013040(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  if (*(int *)(param_1 + 0x10) == *(int *)(param_1 + 0x14)) {
    if (*(int *)(param_1 + 0xc) == 0) {
      uVar2 = 0;
    }
    else if ((1 << *(sbyte *)(param_1 + 0x8c) & (uint)*(ushort *)(*(int *)(param_1 + 0x88) + 8)) ==
             0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return uVar2;
}

