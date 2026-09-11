// FUN_0800a4e8 @ 0x0800a4e8  size=126  body=[[0800a4e8, 0800a565]]

void FUN_0800a4e8(void)

{
  byte *pbVar1;
  uint extraout_r1;
  undefined4 extraout_r2;
  code *pcVar2;
  byte local_28 [4];
  uint local_24;
  
  pbVar1 = local_28;
  FUN_0800b3ec(0);
  FUN_0800b420(0,extraout_r1,extraout_r2);
  FUN_0800a7cc();
  FUN_0800db44();
  FUN_08013a7a(5000);
  if ((char)DAT_200047d4 < '\0') {
    FUN_08008798(local_28,0,0x20);
    pbVar1 = local_28 + 1;
    pcVar2 = DAT_20000c88;
  }
  else {
    local_28[0] = 0;
    local_28[1] = 0;
    local_28[2] = 0;
    local_28[3] = 0;
    local_24 = 0;
    pcVar2 = DAT_20000c84;
  }
  (*pcVar2)(pbVar1);
  FUN_08013a7a(1000);
  (*DAT_20000c8c)(0);
  FUN_08013a7a(1000);
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_24 = local_24 & 0xffff0000;
  (*DAT_20000c94)(local_28);
  FUN_08013a7a(30000);
  FUN_0800a41c();
  return;
}

