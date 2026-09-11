// FUN_0800fbaa @ 0x0800fbaa  size=68  body=[[0800fbaa, 0800fbed]]

uint FUN_0800fbaa(uint param_1,undefined4 param_2,undefined4 param_3,int param_4,ushort param_5)

{
  uint uVar1;
  undefined4 local_c;
  
  uVar1 = (uint)param_5 - param_4 & 0xffff;
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

