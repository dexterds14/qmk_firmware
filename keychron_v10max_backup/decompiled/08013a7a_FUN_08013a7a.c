// FUN_08013a7a @ 0x08013a7a  size=24  body=[[08013a7a, 08013a91]]

void FUN_08013a7a(uint param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080138d4(8,param_1);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

