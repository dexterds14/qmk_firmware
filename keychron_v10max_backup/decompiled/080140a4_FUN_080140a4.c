// FUN_080140a4 @ 0x080140a4  size=28  body=[[080140a4, 080140bf]]

undefined4 FUN_080140a4(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  FUN_08014cd4(param_1);
  *(undefined1 *)(param_1 + 4) = 2;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return 0;
}

