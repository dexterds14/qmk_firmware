// thunk_FUN_08013774 @ 0x08013594  size=4  body=[[08013594, 08013597]]

void thunk_FUN_08013774(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  while( true ) {
    do {
      piVar2 = DAT_200049f0;
      iVar3 = FUN_08013cfa();
      uVar4 = piVar2[2];
      if ((uint)(iVar3 - DAT_200049fc) < uVar4) {
        if ((int **)DAT_200049f0 == &DAT_200049f0) {
          return;
        }
        uVar4 = (DAT_200049fc + uVar4) - iVar3;
        DAT_200049fc = iVar3;
        piVar2[2] = uVar4;
        FUN_08013616(iVar3,uVar4);
        return;
      }
      iVar3 = *piVar2;
      iVar7 = DAT_200049fc + uVar4;
      piVar5 = (int *)piVar2[1];
      DAT_200049fc = iVar7;
      *piVar5 = iVar3;
      *(int **)(iVar3 + 4) = piVar5;
      *piVar2 = 0;
      if ((int **)DAT_200049f0 == &DAT_200049f0) {
        FUN_08013d12();
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      (*(code *)piVar2[3])(piVar2,piVar2[4]);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
    } while (piVar2[5] == 0);
    iVar3 = FUN_08013cfa();
    uVar4 = iVar3 - iVar7;
    if ((uint)piVar2[5] < uVar4) {
      FUN_080135dc(2);
      uVar6 = 0;
    }
    else {
      uVar6 = (piVar2[5] + iVar7) - iVar3;
    }
    if ((int **)DAT_200049f0 == &DAT_200049f0) break;
    if (!CARRY4(uVar6,uVar4)) {
      uVar6 = uVar6 + uVar4;
    }
    FUN_080135ec((int *)&DAT_200049f0,piVar2,uVar6);
  }
  FUN_0801364c(piVar2,iVar3,uVar6);
  return;
}

