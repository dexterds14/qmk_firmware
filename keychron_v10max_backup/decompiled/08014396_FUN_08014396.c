// FUN_08014396 @ 0x08014396  size=112  body=[[08014396, 08014405]]

void FUN_08014396(undefined1 *param_1)

{
  bool bVar1;
  int *piVar2;
  
  *param_1 = 2;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  piVar2 = (int *)(param_1 + 8);
  *piVar2 = 0;
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 != 0) {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      if (*(int *)(*piVar2 + 0x14) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x14) + 0xc),-2);
      }
      if (*(int *)(*piVar2 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x18) + 0xc),-2);
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    *piVar2 = 0;
  } while (piVar2 != (int *)(param_1 + 0x18));
  param_1[0x34] = 0;
  FUN_08015668((int)param_1);
  if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08014400. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0);
    return;
  }
  return;
}

