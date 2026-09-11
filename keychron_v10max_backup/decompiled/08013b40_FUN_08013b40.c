// FUN_08013b40 @ 0x08013b40  size=94  body=[[08013b40, 08013b9d]]

void FUN_08013b40(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int extraout_r1;
  int *piVar4;
  int iVar5;
  
  piVar1 = DAT_200049ec;
  piVar3 = (int *)param_1[2];
  if (piVar3 == (int *)0x0) {
    iVar5 = DAT_200049ec[8];
    param_1[2] = (int)DAT_200049ec;
    param_1[3] = iVar5;
    piVar1[8] = (int)param_1;
    return;
  }
  do {
    if ((uint)piVar1[2] <= (uint)piVar3[2]) {
LAB_08013b8a:
      FUN_08013b16(param_1,piVar1);
      piVar1[6] = (int)param_1;
      FUN_080138b8(6);
      return;
    }
    piVar3[2] = piVar1[2];
    if ((char)piVar3[5] == '\0') {
      piVar2 = (int *)piVar3[1];
      iVar5 = *piVar3;
      *piVar2 = iVar5;
      *(int **)(iVar5 + 4) = piVar2;
      thunk_FUN_08013838(piVar3);
      goto LAB_08013b8a;
    }
    if ((char)piVar3[5] != '\x06') goto LAB_08013b8a;
    iVar5 = *piVar3;
    piVar4 = (int *)piVar3[1];
    piVar2 = (int *)piVar3[6];
    *piVar4 = iVar5;
    *(int **)(iVar5 + 4) = piVar4;
    FUN_08013b16(piVar2,piVar3);
    piVar3 = *(int **)(*(int *)(extraout_r1 + 0x18) + 8);
  } while( true );
}

