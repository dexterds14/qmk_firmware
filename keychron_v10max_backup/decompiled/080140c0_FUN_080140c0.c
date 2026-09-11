// FUN_080140c0 @ 0x080140c0  size=26  body=[[080140c0, 080140d9]]

void FUN_080140c0(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08014cfc(param_1);
  *(undefined1 *)(param_1 + 4) = 1;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

