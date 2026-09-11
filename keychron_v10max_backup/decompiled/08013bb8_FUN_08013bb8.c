// FUN_08013bb8 @ 0x08013bb8  size=86  body=[[08013bb8, 08013c0d]]

void FUN_08013bb8(int *param_1)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = DAT_200049ec;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  piVar4 = (int *)param_1[3];
  piVar2 = (int *)*param_1;
  *(int **)(DAT_200049ec + 0x20) = piVar4;
  if (piVar2 == param_1) {
    piVar2[2] = 0;
  }
  else {
    uVar3 = *(uint *)(iVar5 + 0x24);
    for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[3]) {
      if ((piVar4 != (int *)*piVar4) && (uVar6 = ((int *)*piVar4)[2], uVar3 < uVar6)) {
        uVar3 = uVar6;
      }
    }
    *(uint *)(iVar5 + 8) = uVar3;
    piVar2 = (int *)*param_1;
    iVar5 = *piVar2;
    *param_1 = iVar5;
    *(int **)(iVar5 + 4) = param_1;
    iVar5 = piVar2[8];
    param_1[2] = (int)piVar2;
    param_1[3] = iVar5;
    piVar2[8] = (int)param_1;
    thunk_FUN_08013838(piVar2);
    FUN_08013950();
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

