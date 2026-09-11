// FUN_08013598 @ 0x08013598  size=18  body=[[08013598, 080135a9]]

void FUN_08013598(void)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    iVar2 = getBasePriority();
  }
  if (iVar2 == 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      getCurrentExceptionNumber();
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
  }
  return;
}

