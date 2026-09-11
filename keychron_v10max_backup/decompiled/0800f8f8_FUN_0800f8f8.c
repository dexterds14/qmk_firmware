// FUN_0800f8f8 @ 0x0800f8f8  size=80  body=[[0800f8f8, 0800f947]]

uint FUN_0800f8f8(undefined4 param_1,int param_2,char param_3)

{
  char cVar1;
  uint3 uStack_1b;
  
  cVar1 = (&DAT_20000d0c)[(param_2 + 0x34) * 2] + -0x20;
  if (cVar1 < '\0') {
    cVar1 = ' ' - (&DAT_20000d0c)[(param_2 + 0x34) * 2];
  }
  uStack_1b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((char)param_1 + ((&DAT_20000d0b)[(param_2 + 0x34) * 2] - param_3) + cVar1) |
         (uStack_1b & 0xff) << 8 | (uStack_1b & 0xff00) << 8;
}

