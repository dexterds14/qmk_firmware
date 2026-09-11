// FUN_0800f94c @ 0x0800f94c  size=50  body=[[0800f94c, 0800f97d]]

uint FUN_0800f94c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,char param_5)

{
  undefined3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(param_5 + (char)((uint)(param_4 * 3) >> 1)) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}

