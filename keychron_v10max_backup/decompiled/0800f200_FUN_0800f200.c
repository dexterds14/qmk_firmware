// FUN_0800f200 @ 0x0800f200  size=28  body=[[0800f200, 0800f21b]]

undefined1 FUN_0800f200(void)

{
  bool bVar1;
  undefined1 uVar2;
  
  if (DAT_20001f08 == '\0') {
    bVar1 = FUN_0800f55c();
    uVar2 = 0;
    if (bVar1) {
      uVar2 = 1;
      DAT_20001f08 = '\x01';
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

