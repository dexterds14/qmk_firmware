// FUN_0800e6c8 @ 0x0800e6c8  size=50  body=[[0800e6c8, 0800e6f9]]

void FUN_0800e6c8(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint extraout_r2;
  uint local_18;
  uint local_14;
  
  uVar1 = FUN_08012574();
  if (DAT_200016d2 != uVar1) {
    local_18 = FUN_08012574();
    local_14 = param_2 & 0xffff0000;
    local_18 = local_18 << 0x10;
    FUN_0800d50c(local_18,local_14,extraout_r2,&stack0xfffffff0);
    DAT_200016d2 = (ushort)uVar1;
  }
  return;
}

