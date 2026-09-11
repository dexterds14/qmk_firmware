// FUN_0800f5f4 @ 0x0800f5f4  size=110  body=[[0800f5f4, 0800f661]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_0800f5f4(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  DAT_20001f10 = &DAT_20004a40;
  FUN_0800f5e4();
  iVar1 = (**(code **)(*DAT_20001f10 + 4))();
  uVar4 = (uint)_DAT_1fff7a22;
  uVar3 = 0;
  uVar5 = 0;
  do {
    if (*(int *)(iVar1 + 8) - 1U <= uVar3) goto LAB_0800f642;
    uVar3 = uVar3 + 1;
    iVar2 = FUN_0801404a(DAT_20001f10,uVar3);
    uVar5 = uVar5 + iVar2;
  } while (uVar5 < 0x1000);
  DAT_20000ea4 = uVar3;
  DAT_20000ea8 = FUN_08014030(DAT_20001f10,1);
LAB_0800f642:
  if ((DAT_20000ea4 == 0xffff) || (uVar4 << 10 <= DAT_20000ea8)) {
    FUN_0801357c();
  }
  return 1;
}

