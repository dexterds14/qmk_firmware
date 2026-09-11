// FUN_08008a30 @ 0x08008a30  size=58  body=[[08008a30, 08008a69]]

uint FUN_08008a30(uint *param_1,uint param_2,uint *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  uVar2 = param_3[2] - 1;
  param_3[2] = uVar2;
  bVar1 = (byte)param_2;
  if (-1 < (int)uVar2) {
    pbVar3 = (byte *)*param_3;
    *param_3 = (uint)(pbVar3 + 1);
    *pbVar3 = bVar1;
    return param_2;
  }
  if (((int)param_3[6] <= (int)uVar2) && (param_2 != 10)) {
    pbVar3 = (byte *)*param_3;
    *param_3 = (uint)(pbVar3 + 1);
    *pbVar3 = bVar1;
    return param_2;
  }
  uVar2 = FUN_08008d44(param_1,bVar1,param_3);
  return uVar2;
}

