// FUN_0800fae4 @ 0x0800fae4  size=114  body=[[0800fae4, 0800fb55]]

uint FUN_0800fae4(uint param_1,short param_2,int param_3,uint param_4,ushort param_5)

{
  uint uVar1;
  undefined4 local_14;
  
  if (param_4 < 0x49) {
    uVar1 = param_5 - param_4 & 0xffff;
    if (0xfe < uVar1) {
      uVar1 = 0xff;
    }
  }
  else {
    uVar1 = 0xff;
  }
  if ((0x10 < (ushort)(param_2 + 8U)) && (0x10 < (param_3 + 8U & 0xffff))) {
    uVar1 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~uVar1 & 0xff);
  if (param_3 < 0) {
    param_3 = param_3 + 3;
  }
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_14 = CONCAT31((int3)(param_1 >> 8),DAT_20004809 + (char)(param_3 >> 2));
  local_14 = local_14 & 0xffff;
  return local_14 | (uVar1 & 0xff) << 0x10;
}

