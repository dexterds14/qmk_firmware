// FUN_0800ed58 @ 0x0800ed58  size=34  body=[[0800ed58, 0800ed79]]

void FUN_0800ed58(uint param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015338((uint *)(param_1 & 0xfffffff0),1 << (param_1 & 0xf),0x20);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

