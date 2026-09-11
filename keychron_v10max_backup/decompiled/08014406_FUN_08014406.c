// FUN_08014406 @ 0x08014406  size=92  body=[[08014406, 08014461]]

void FUN_08014406(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  code *pcVar2;
  int *piVar3;
  
  if (*param_1 != '\x05') {
    param_1[0x50] = *param_1;
    *param_1 = '\x05';
    pcVar2 = (code *)**(undefined4 **)(param_1 + 4);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(param_1,4,param_3,pcVar2,param_4);
    }
    piVar3 = (int *)(param_1 + 8);
    *piVar3 = 0;
    do {
      piVar3 = piVar3 + 1;
      if (*piVar3 != 0) {
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        if (*(int *)(*piVar3 + 0x14) != 0) {
          FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x14) + 0xc),-2);
        }
        if (*(int *)(*piVar3 + 0x18) != 0) {
          FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x18) + 0xc),-2);
        }
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0);
        }
      }
    } while (piVar3 != (int *)(param_1 + 0x18));
  }
  return;
}

