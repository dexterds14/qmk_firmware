// FUN_0800f888 @ 0x0800f888  size=50  body=[[0800f888, 0800f8b9]]

uint FUN_0800f888(undefined4 param_1,int param_2,char param_3)

{
  uint3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((&DAT_20000d73)[param_2 * 2] - param_3) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}

