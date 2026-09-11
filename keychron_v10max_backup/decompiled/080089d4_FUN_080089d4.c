// FUN_080089d4 @ 0x080089d4  size=92  body=[[080089d4, 08008a2f]]

int FUN_080089d4(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if (3 < param_3) {
    piVar1 = param_1;
    piVar2 = param_2;
    if ((((uint)param_2 | (uint)param_1) & 3) != 0) goto LAB_08008a0a;
    do {
      param_2 = piVar2 + 1;
      param_1 = piVar1 + 1;
      if (*piVar1 != *piVar2) goto LAB_08008a0a;
      param_3 = param_3 - 4;
      piVar2 = param_2;
      piVar1 = param_1;
    } while (3 < param_3);
  }
  piVar1 = param_1;
  piVar2 = param_2;
  if (param_3 == 0) {
    return 0;
  }
LAB_08008a0a:
  pbVar4 = (byte *)((int)piVar1 + -1);
  pbVar3 = (byte *)((int)piVar2 + -1);
  do {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if ((uint)*pbVar4 != (uint)*pbVar3) {
      return (uint)*pbVar4 - (uint)*pbVar3;
    }
  } while ((byte *)((int)piVar1 + (param_3 - 1)) != pbVar4);
  return 0;
}

