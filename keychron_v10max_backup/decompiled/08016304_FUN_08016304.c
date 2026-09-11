// FUN_08016304 @ 0x08016304  size=56  body=[[08016304, 0801633b]]

void FUN_08016304(undefined1 *param_1,uint param_2)

{
  bool bVar1;
  
  if ((param_2 & 0xc) != 0) {
    FUN_0801357c();
    FUN_0801625c(param_1);
    if (*(code **)(*(int *)(param_1 + 4) + 8) != (code *)0x0) {
      (**(code **)(*(int *)(param_1 + 4) + 8))(param_1);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08013ab0((undefined4 *)(param_1 + 8),0);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}

