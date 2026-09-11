// FUN_0800fcac @ 0x0800fcac  size=48  body=[[0800fcac, 0800fcdb]]

uint FUN_0800fcac(undefined4 param_1,uint param_2,int param_3,char param_4)

{
  uint uVar1;
  undefined3 uStack_13;
  
  uVar1 = FUN_0800fc20(param_3,param_2);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((char)uVar1 + param_4) | (uStack_13 & 0xff) << 8 | (uStack_13 & 0xff00) << 8;
}

