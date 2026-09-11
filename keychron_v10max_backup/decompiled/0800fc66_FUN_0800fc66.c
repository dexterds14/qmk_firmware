// FUN_0800fc66 @ 0x0800fc66  size=70  body=[[0800fc66, 0800fcab]]

uint FUN_0800fc66(undefined4 param_1,uint param_2,int param_3,short param_4,byte param_5)

{
  byte bVar1;
  uint uVar2;
  undefined4 local_1c;
  
  uVar2 = FUN_0800fc20(param_3,param_2);
  bVar1 = (byte)((uint)param_1 >> 0x10);
  bVar1 = (byte)((uint)((int)(short)(((param_4 - (ushort)param_5) + (ushort)bVar1 & 0xff) -
                                     (short)uVar2 & 0xff) * (int)(short)(ushort)bVar1) >> 8);
  local_1c = (uint)CONCAT12(bVar1,(short)param_1);
  return local_1c & 0xffff | (uint)bVar1 << 0x10;
}

