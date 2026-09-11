// FUN_080132a8 @ 0x080132a8  size=84  body=[[080132a8, 080132fb]]

undefined8 FUN_080132a8(int param_1,uint param_2)

{
  bool bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  undefined8 uVar7;
  
  if ((param_2 < 9) && (param_2 = (uint)(short)param_2, *(int *)(param_1 + param_2 * 4) != 0)) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    puVar5 = *(uint **)(param_1 + param_2 * 4);
    uVar3 = *puVar5;
    uVar6 = puVar5[1];
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (uVar3 != 0) {
      iVar4 = FUN_08013cfa();
      lVar2 = (ulonglong)(iVar4 - uVar6) * 1000 + 99999;
      uVar7 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
      param_2 = (uint)((ulonglong)uVar7 >> 0x20);
      uVar3 = (uint)(uVar3 <= (uint)uVar7);
      goto LAB_080132b0;
    }
  }
  uVar3 = 0;
LAB_080132b0:
  return CONCAT44(param_2,uVar3);
}

