// FUN_0800fa68 @ 0x0800fa68  size=52  body=[[0800fa68, 0800fa9b]]

uint FUN_0800fa68(undefined4 param_1,byte param_2)

{
  byte bVar1;
  undefined4 local_c;
  
  bVar1 = (byte)((uint)((int)(short)(ushort)(byte)~param_2 *
                       (int)(short)(ushort)(byte)((uint)param_1 >> 0x10)) >> 8);
  local_c = (uint)CONCAT12(bVar1,(short)param_1);
  return local_c & 0xffff | (uint)bVar1 << 0x10;
}

