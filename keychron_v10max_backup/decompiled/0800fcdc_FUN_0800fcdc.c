// FUN_0800fcdc @ 0x0800fcdc  size=54  body=[[0800fcdc, 0800fd11]]

uint FUN_0800fcdc(undefined4 param_1,uint param_2,int param_3,char param_4,char param_5)

{
  uint uVar1;
  undefined3 uStack_13;
  
  uVar1 = FUN_0800fc20(param_3,param_2);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((param_4 - param_5) - (char)uVar1) | (uStack_13 & 0xff) << 8 |
         (uStack_13 & 0xff00) << 8;
}

