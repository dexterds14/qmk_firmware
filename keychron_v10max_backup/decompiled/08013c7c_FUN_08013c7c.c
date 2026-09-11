// FUN_08013c7c @ 0x08013c7c  size=66  body=[[08013c7c, 08013cbd]]

void FUN_08013c7c(void)

{
  uint uVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(0x30);
  }
  uVar1 = DAT_e000ed04;
  if ((uVar1 & 0x800) == 0) {
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
  }
  else {
    iVar4 = getProcessStackPointer();
    *(undefined4 *)(iVar4 + -0x4c) = 0x1000000;
    uVar3 = DAT_e000ef3c;
    *(undefined4 *)(iVar4 + -8) = uVar3;
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setProcessStackPointer(iVar4 + -0x68);
    }
    bVar2 = FUN_08013910();
    if (bVar2) {
      uVar3 = 0x800814f;
    }
    else {
      uVar3 = 0x8008152;
    }
    *(undefined4 *)(iVar4 + -0x50) = uVar3;
  }
  return;
}

