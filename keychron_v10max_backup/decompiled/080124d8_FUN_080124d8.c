// FUN_080124d8 @ 0x080124d8  size=32  body=[[080124d8, 080124f7]]

void FUN_080124d8(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  DAT_20002038 = FUN_08013cfa();
  DAT_20002034 = 0;
  DAT_20002030 = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

