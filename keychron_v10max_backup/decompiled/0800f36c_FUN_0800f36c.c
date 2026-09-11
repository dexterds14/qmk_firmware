// FUN_0800f36c @ 0x0800f36c  size=36  body=[[0800f36c, 0800f38f]]

void FUN_0800f36c(uint param_1)

{
  bool bVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  bVar1 = FUN_0800f5b4(DAT_20001f04,param_1);
  if (bVar1 != 0) {
    DAT_20001f04 = DAT_20001f04 + 4;
    FUN_0800f354((uint)bVar1,extraout_r1,extraout_r2);
    return;
  }
  return;
}

