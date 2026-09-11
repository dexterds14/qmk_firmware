// FUN_0801417a @ 0x0801417a  size=28  body=[[0801417a, 08014195]]

void FUN_0801417a(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(short *)(*(int *)(*(int *)(param_1 + 4) + 0xc) + 0x18) =
       (short)(1 << (*(uint *)(*(int *)(param_1 + 4) + 0x10) & 0xff));
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

