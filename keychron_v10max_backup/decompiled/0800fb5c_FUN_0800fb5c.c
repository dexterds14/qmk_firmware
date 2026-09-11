// FUN_0800fb5c @ 0x0800fb5c  size=78  body=[[0800fb5c, 0800fba9]]

uint FUN_0800fb5c(uint param_1,undefined4 param_2,undefined4 param_3,int param_4,ushort param_5)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_c;
  
  uVar2 = (uint)param_5 - param_4 & 0xffff;
  if (0xfe < uVar2) {
    uVar2 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~(uVar2 & 0xff) & 0xff);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_c = CONCAT31((int3)(param_1 >> 8),(char)uVar2 + (char)param_1);
  local_c = local_c & 0xffff;
  return local_c | (uVar1 & 0xff) << 0x10;
}

