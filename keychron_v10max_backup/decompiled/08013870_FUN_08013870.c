// FUN_08013870 @ 0x08013870  size=62  body=[[08013870, 08013885] [0801388c, 080138b3]]

void FUN_08013870(undefined4 param_1,int *param_2)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  switch((char)param_2[5]) {
  case '\0':
    goto switchD_08013882_caseD_0;
  case '\x03':
    *(undefined4 *)param_2[6] = 0;
    break;
  case '\x05':
    *(int *)(param_2[6] + 8) = *(int *)(param_2[6] + 8) + 1;
  case '\x04':
    piVar2 = (int *)param_2[1];
    iVar3 = *param_2;
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
  }
  param_2[6] = -1;
  FUN_08013838(param_2);
switchD_08013882_caseD_0:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

