// FUN_080135aa @ 0x080135aa  size=30  body=[[080135aa, 080135c7]]

void FUN_080135aa(int param_1)

{
  bool bVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    uVar2 = 0;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      uVar2 = getCurrentExceptionNumber();
      uVar2 = uVar2 & 0x1ff;
    }
    if (uVar2 == 0) {
      FUN_08013950();
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    else {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
  }
  return;
}

