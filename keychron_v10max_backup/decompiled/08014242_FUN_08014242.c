// FUN_08014242 @ 0x08014242  size=82  body=[[08014242, 08014293]]

void FUN_08014242(char *param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015624(param_1);
  param_1[4] = '\0';
  param_1[5] = '\0';
  param_1[6] = '\0';
  param_1[7] = '\0';
  piVar3 = (int *)(param_1 + 8);
  *param_1 = '\x01';
  do {
    piVar3 = piVar3 + 1;
    if (*piVar3 != 0) {
      iVar2 = *(int *)(*piVar3 + 0x14);
      if (iVar2 != 0) {
        FUN_08013ab0((undefined4 *)(iVar2 + 0xc),-2);
      }
      if (*(int *)(*piVar3 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x18) + 0xc),-2);
      }
    }
    *piVar3 = 0;
  } while (piVar3 != (int *)(param_1 + 0x18));
  FUN_08013950();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

