// FUN_080134d8 @ 0x080134d8  size=20  body=[[080134d8, 080134eb]]

void FUN_080134d8(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080134ac(param_1,param_2,param_3);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

