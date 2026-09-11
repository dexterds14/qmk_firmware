// FUN_0800bff4 @ 0x0800bff4  size=82  body=[[0800bff4, 0800c045]]

void FUN_0800bff4(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = DAT_40023808;
  DAT_40023808 = uVar1 & 0xfffffffc;
  do {
    uVar1 = DAT_40023808;
  } while ((uVar1 & 0xc) != 0);
  uVar1 = DAT_40023800;
  DAT_40023800 = uVar1 & 0xfffeffff;
  do {
    iVar2 = DAT_40023800;
  } while (iVar2 << 0xe < 0);
  FUN_08015338((uint *)&DAT_40021c00,1,0x40);
  FUN_08015338((uint *)&DAT_40021c00,2,0x40);
  WaitForInterrupt();
  uVar1 = DAT_e000ed10;
  DAT_e000ed10 = uVar1 & 0xfffffffb;
  DAT_40020018._2_2_ = 0x10;
  FUN_08014b5c();
  DAT_40020018._0_2_ = 0x10;
  return;
}

