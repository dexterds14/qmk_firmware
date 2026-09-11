// FUN_08012e08 @ 0x08012e08  size=32  body=[[08012e08, 08012e27]]

void FUN_08012e08(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(int *)(*(int *)(param_1 + 0x88) + (uint)*(byte *)(param_1 + 0x8c) * 4 + 0x18) = param_1;
  *(undefined1 *)(param_1 + 0xa0) = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

