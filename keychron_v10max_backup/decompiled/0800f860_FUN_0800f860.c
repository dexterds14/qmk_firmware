// FUN_0800f860 @ 0x0800f860  size=38  body=[[0800f860, 0800f885]]

uint FUN_0800f860(undefined4 param_1,undefined4 param_2,byte param_3)

{
  undefined3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)param_3 | (uStack_b & 0xff) << 8 | (uStack_b & 0xff00) << 8;
}

