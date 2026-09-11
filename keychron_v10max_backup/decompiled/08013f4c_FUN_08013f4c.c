// FUN_08013f4c @ 0x08013f4c  size=134  body=[[08013f4c, 08013fd1]]

uint FUN_08013f4c(int param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  uVar6 = 0;
  while( true ) {
    if ((*(int *)(param_1 + 0x28) == 0) && (iVar2 = FUN_08013ef4(param_1,param_4), iVar2 != 0)) {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      return uVar6;
    }
    puVar3 = *(undefined4 **)(param_1 + 0x28);
    uVar5 = *(int *)(param_1 + 0x2c) - (int)puVar3;
    if (param_3 - uVar6 <= uVar5) {
      uVar5 = param_3 - uVar6;
    }
    if (uVar5 < 0x41) {
      memcpy(puVar3,param_2,uVar5);
      param_2 = (undefined4 *)((int)param_2 + uVar5);
      uVar4 = *(int *)(param_1 + 0x28) + uVar5;
      uVar6 = uVar6 + uVar5;
    }
    else {
      memcpy(puVar3,param_2,0x40);
      param_2 = param_2 + 0x10;
      uVar4 = *(int *)(param_1 + 0x28) + 0x40;
      uVar6 = uVar6 + 0x40;
    }
    *(uint *)(param_1 + 0x28) = uVar4;
    if (*(uint *)(param_1 + 0x2c) <= uVar4) {
      FUN_08013f26(param_1,*(int *)(param_1 + 0x1c) + -4);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (param_3 <= uVar6) break;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
  }
  return uVar6;
}

