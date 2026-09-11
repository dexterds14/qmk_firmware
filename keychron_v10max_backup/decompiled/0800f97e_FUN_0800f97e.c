// FUN_0800f97e @ 0x0800f97e  size=72  body=[[0800f97e, 0800f9c5]]

uint FUN_0800f97e(undefined4 param_1,char param_2,int param_3,char param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined3 uStack_13;
  
  iVar2 = (int)param_2;
  if (iVar2 < 0) {
    iVar2 = (int)-param_2;
  }
  sVar1 = 0x38 - (short)iVar2;
  uVar3 = FUN_0800f7aa((int)sVar1 * (int)sVar1 + param_3 * param_3 & 0xffff);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(param_4 + (char)uVar3 + (char)(uVar3 << 1)) | (uStack_13 & 0xff) << 8 |
         (uStack_13 & 0xff00) << 8;
}

