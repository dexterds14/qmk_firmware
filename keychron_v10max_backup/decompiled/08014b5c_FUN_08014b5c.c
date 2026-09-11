// FUN_08014b5c @ 0x08014b5c  size=212  body=[[08014b5c, 08014c2f]]

void FUN_08014b5c(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  DAT_40023840 = 0x10000000;
  DAT_40007000 = 0x4000;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 1;
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 0x1e);
  uVar2 = DAT_40023808;
  DAT_40023808 = uVar2 & 0xfffffffc;
  do {
    uVar2 = DAT_40023808;
  } while ((uVar2 & 0xc) != 0);
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 & 0xf9;
  DAT_40023808 = 0;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 0x10000;
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 0xe);
  uVar2 = DAT_40023874;
  DAT_40023874 = uVar2 | 1;
  do {
    iVar1 = DAT_40023874;
  } while (-1 < iVar1 << 0x1e);
  DAT_40023804 = 0x4411808;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 0x1000000;
  do {
    iVar1 = DAT_40007004;
  } while (-1 < iVar1 << 0x11);
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 6);
  DAT_40023808 = 0x38881000;
  DAT_4002388c = 3;
  iVar1 = DAT_e0042000;
  if ((iVar1 == 0x20006411) && (iVar1 = DAT_e000ed00, iVar1 == 0x410fc241)) {
    uVar3 = 0x101;
  }
  else {
    uVar3 = 0x701;
  }
  DAT_40023c00 = uVar3;
  do {
    uVar2 = DAT_40023c00;
  } while ((uVar2 & 0xf) != 1);
  uVar2 = DAT_40023808;
  DAT_40023808 = uVar2 | 2;
  do {
    uVar2 = DAT_40023808;
  } while ((uVar2 & 0xc) != 8);
  uVar2 = DAT_40023844;
  DAT_40023844 = uVar2 | 0x4000;
  uVar2 = DAT_40023864;
  DAT_40023864 = uVar2 | 0x4000;
  uVar3 = DAT_40023864;
  return;
}

