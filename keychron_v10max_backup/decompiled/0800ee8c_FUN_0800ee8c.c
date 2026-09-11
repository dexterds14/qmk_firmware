// FUN_0800ee8c @ 0x0800ee8c  size=98  body=[[0800ee8c, 0800eeed]]

undefined1 FUN_0800ee8c(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  FUN_08008798((byte *)&local_28,0,0x18);
  uVar4 = 0;
  uVar5 = 1;
  do {
    uVar3 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    FUN_0800edb8((int)&local_28,uVar3,uVar5);
    uVar5 = uVar5 << 1;
  } while (uVar4 != 0x12);
  iVar2 = FUN_080089d4(&DAT_200047d8,&local_28,0x18);
  if (iVar2 != 0) {
    DAT_200047d8 = local_28;
    DAT_200047dc = uStack_24;
    DAT_200047e0 = uStack_20;
    DAT_200047e4 = uStack_1c;
    DAT_200047e8 = local_18;
    DAT_200047ec = uStack_14;
  }
  uVar1 = FUN_0800ef30(0x200047d8,0x200047f0,6,(uint)(iVar2 != 0));
  FUN_0800ed18();
  return uVar1;
}

