// FUN_0800f220 @ 0x0800f220  size=30  body=[[0800f220, 0800f23d]]

undefined4 FUN_0800f220(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_20001f08 == '\0') {
    uVar2 = 2;
  }
  else {
    iVar1 = FUN_0800f5e4();
    uVar2 = 0;
    if (iVar1 != 0) {
      DAT_20001f08 = '\0';
      uVar2 = 1;
    }
  }
  return uVar2;
}

