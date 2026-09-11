// thunk_FUN_0800f244 @ 0x0800f1c8  size=4  body=[[0800f1c8, 0800f1cb]]

uint thunk_FUN_0800f244(void)

{
  byte bVar1;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  uint uVar2;
  
  bVar1 = FUN_0800f200();
  uVar2 = (uint)bVar1;
  if (uVar2 == 0) {
    FUN_0800f220();
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0800f574(uVar2,extraout_r1,extraout_r2,extraout_r3);
    FUN_0800f1e0();
    if (uVar2 == 1) {
      iVar4 = FUN_0800f220();
      if (iVar4 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = uVar3 & 1;
      }
    }
  }
  return uVar3;
}

