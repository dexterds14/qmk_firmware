// SVCall_Handler @ 0x08013c14  size=28  body=[[08013c14, 08013c2f]]

void SVCall_Handler(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = getProcessStackPointer();
  uVar2 = DAT_e000ef34;
  DAT_e000ef34 = uVar2 & 0xfffffffe;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(iVar3 + 0x68);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

