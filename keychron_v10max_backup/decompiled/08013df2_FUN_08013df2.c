// FUN_08013df2 @ 0x08013df2  size=130  body=[[08013df2, 08013e73]]

uint FUN_08013df2(int param_1,undefined4 *param_2,uint param_3,uint param_4)

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
    if ((*(int *)(param_1 + 0x28) == 0) && (iVar2 = FUN_08013d9c(param_1,param_4), iVar2 != 0)) {
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
      memcpy(param_2,puVar3,uVar5);
      param_2 = (undefined4 *)((int)param_2 + uVar5);
      uVar4 = *(int *)(param_1 + 0x28) + uVar5;
      uVar6 = uVar6 + uVar5;
    }
    else {
      memcpy(param_2,puVar3,0x40);
      param_2 = param_2 + 0x10;
      uVar4 = *(int *)(param_1 + 0x28) + 0x40;
      uVar6 = uVar6 + 0x40;
    }
    *(uint *)(param_1 + 0x28) = uVar4;
    if (*(uint *)(param_1 + 0x2c) <= uVar4) {
      FUN_08013dce(param_1);
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

