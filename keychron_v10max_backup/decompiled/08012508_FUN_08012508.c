// FUN_08012508 @ 0x08012508  size=82  body=[[08012508, 08012559]]

int FUN_08012508(void)

{
  bool bVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar3 = FUN_08013cfa();
  uVar4 = iVar3 - DAT_20002038;
  if (uVar4 < DAT_20002034) {
    DAT_20002038 = DAT_20002038 + -0x106e0;
    DAT_20002030 = DAT_20002030 + 0x28f5988;
    uVar4 = uVar4 + 0x106e0;
  }
  iVar3 = DAT_20002030;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  lVar2 = (ulonglong)uVar4 * 1000 + 99999;
  DAT_20002034 = uVar4;
  uVar5 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
  return (int)uVar5 + iVar3;
}

