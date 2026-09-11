// FUN_0801354c @ 0x0801354c  size=34  body=[[0801354c, 0801356d]]

void FUN_0801354c(void)

{
  bool bVar1;
  
  DAT_200049d8 = 1;
  DAT_200049dc = 0;
  FUN_08013494();
  FUN_0801396c(0x200049e0,0x8017348);
  DAT_200049d8 = 2;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

