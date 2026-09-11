// FUN_08012eca @ 0x08012eca  size=150  body=[[08012eca, 08012f5f]]

void FUN_08012eca(int param_1,uint param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int *piVar6;
  uint local_1c;
  undefined4 uStack_18;
  
  piVar6 = *(int **)(param_1 + param_2 * 4 + 0x18);
  if (piVar6 == (int *)0x0) {
    return;
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined1 *)(piVar6 + 0x28) = 0;
  local_1c = param_2;
  uStack_18 = param_3;
  if (((piVar6[4] != piVar6[5]) || (piVar6[3] == 0)) &&
     (**(int **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x14) != 0)) {
    if (piVar6[0x29] != 0) {
      iVar3 = param_1;
      iVar2 = FUN_08013eba((int)piVar6,(int *)&local_1c);
      puVar4 = (undefined4 *)piVar6[0x29];
      (*(code *)puVar4[2])(*puVar4,iVar2,local_1c,puVar4,iVar3);
    }
    FUN_08013ed6(piVar6);
  }
  iVar3 = FUN_08013eba((int)piVar6,(int *)&local_1c);
  uVar5 = local_1c;
  if (iVar3 == 0) {
    piVar6 = *(int **)(param_1 + param_2 * 4 + 0xc);
    if (((*piVar6 != 2) || (*(uint *)piVar6[5] == 0)) ||
       ((*(ushort *)(piVar6 + 4) - 1 & *(uint *)piVar6[5]) != 0)) goto LAB_08012f34;
    iVar3 = param_1 + 0x44;
    uVar5 = 0;
  }
  FUN_08014334(param_1,param_2,iVar3,uVar5);
LAB_08012f34:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

