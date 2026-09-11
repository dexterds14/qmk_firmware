// FUN_08009858 @ 0x08009858  size=182  body=[[08009858, 0800990d]]

void FUN_08009858(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  if (param_2 == 0) {
    return;
  }
  piVar5 = (int *)(param_2 + -4);
  if (*(int *)(param_2 + -4) < 0) {
    piVar5 = (int *)((int)piVar5 + *(int *)(param_2 + -4));
  }
  FUN_08009fd0();
  if (DAT_200014f8 != (int *)0x0) {
    piVar4 = DAT_200014f8;
    if (DAT_200014f8 <= piVar5) {
      do {
        piVar3 = piVar4;
        piVar4 = (int *)piVar3[1];
        if (piVar4 == (int *)0x0) {
          piVar1 = (int *)((int)piVar3 + *piVar3);
          if (piVar5 != piVar1) {
            if (piVar1 <= piVar5) goto LAB_080098a6;
            goto LAB_08009900;
          }
          *piVar3 = *piVar5 + *piVar3;
          goto LAB_080098aa;
        }
      } while (piVar4 <= piVar5);
      piVar1 = (int *)((int)piVar3 + *piVar3);
      if (piVar1 == piVar5) {
        iVar2 = *piVar3 + *piVar5;
        *piVar3 = iVar2;
        if (piVar4 == (int *)((int)piVar3 + iVar2)) {
          iVar6 = piVar4[1];
          *piVar3 = iVar2 + *piVar4;
          piVar3[1] = iVar6;
        }
      }
      else {
        if (piVar5 <= piVar1) {
LAB_08009900:
          *param_1 = 0xc;
          FUN_08009fd4();
          return;
        }
        if (piVar4 == (int *)((int)piVar5 + *piVar5)) {
          iVar2 = piVar4[1];
          *piVar5 = *piVar4 + *piVar5;
          piVar5[1] = iVar2;
          piVar3[1] = (int)piVar5;
        }
        else {
LAB_080098a6:
          piVar5[1] = (int)piVar4;
          piVar3[1] = (int)piVar5;
        }
      }
LAB_080098aa:
      FUN_08009fd4();
      return;
    }
    if (DAT_200014f8 == (int *)((int)piVar5 + *piVar5)) {
      iVar2 = *DAT_200014f8;
      DAT_200014f8 = (int *)DAT_200014f8[1];
      *piVar5 = iVar2 + *piVar5;
    }
  }
  piVar5[1] = (int)DAT_200014f8;
  DAT_200014f8 = piVar5;
  FUN_08009fd4();
  return;
}

