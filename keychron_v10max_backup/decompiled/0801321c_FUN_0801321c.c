// FUN_0801321c @ 0x0801321c  size=72  body=[[0801321c, 08013263]]

undefined8 FUN_0801321c(int *param_1,undefined4 param_2)

{
  bool bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  
  if (*param_1 != 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    uVar3 = *(uint *)*param_1;
    uVar5 = ((uint *)*param_1)[1];
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (uVar3 != 0) {
      iVar4 = FUN_08013cfa();
      lVar2 = (ulonglong)(iVar4 - uVar5) * 1000 + 99999;
      uVar6 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
      param_2 = (undefined4)((ulonglong)uVar6 >> 0x20);
      uVar3 = (uint)(uVar3 <= (uint)uVar6);
      goto LAB_08013224;
    }
  }
  uVar3 = 0;
LAB_08013224:
  return CONCAT44(param_2,uVar3);
}

