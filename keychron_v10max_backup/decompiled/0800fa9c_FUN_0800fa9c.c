// FUN_0800fa9c @ 0x0800fa9c  size=72  body=[[0800fa9c, 0800fae3]]

uint FUN_0800fa9c(uint param_1,undefined4 param_2,undefined4 param_3,short param_4,short param_5)

{
  uint uVar1;
  undefined4 local_c;
  
  uVar1 = (uint)(ushort)(param_5 + param_4 * 5);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~uVar1 & 0xff);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_c = param_1 & 0xffff;
  return local_c | (uVar1 & 0xff) << 0x10;
}

