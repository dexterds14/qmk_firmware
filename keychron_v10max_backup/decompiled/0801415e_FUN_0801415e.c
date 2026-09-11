// FUN_0801415e @ 0x0801415e  size=28  body=[[0801415e, 08014179]]

void FUN_0801415e(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(short *)(*(int *)(*(int *)(param_1 + 4) + 0xc) + 0x1a) =
       (short)(1 << (*(uint *)(*(int *)(param_1 + 4) + 0x10) & 0xff));
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

