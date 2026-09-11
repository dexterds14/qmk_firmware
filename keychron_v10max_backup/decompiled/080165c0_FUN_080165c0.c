// FUN_080165c0 @ 0x080165c0  size=40  body=[[080165c0, 080165e7]]

void FUN_080165c0(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = DAT_40000010;
  uVar2 = DAT_4000000c;
  DAT_40000010 = ~(uVar2 & uVar3 & 0xff);
  if ((int)((uVar2 & uVar3) << 0x1e) < 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    thunk_FUN_08013774();
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}

