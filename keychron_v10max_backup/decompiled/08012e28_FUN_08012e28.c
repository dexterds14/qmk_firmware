// FUN_08012e28 @ 0x08012e28  size=30  body=[[08012e28, 08012e45]]

void FUN_08012e28(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(int *)(*(int *)(param_1 + 0x70) + (*(byte *)(param_1 + 0x74) + 9) * 4) = param_1;
  *(undefined1 *)(param_1 + 0x84) = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

