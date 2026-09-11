// FUN_08008d44 @ 0x08008d44  size=134  body=[[08008d44, 08008dc9]]

uint FUN_08008d44(uint *param_1,byte param_2,uint *param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  param_3[2] = param_3[6];
  if ((-1 < (int)((uint)(ushort)param_3[3] << 0x1c)) || (uVar3 = param_3[4], uVar3 == 0)) {
    iVar1 = FUN_08009b00(param_1,param_3);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    uVar3 = param_3[4];
  }
  pbVar2 = (byte *)*param_3;
  uVar4 = (uint)param_2;
  if ((int)((int)pbVar2 - uVar3) < (int)param_3[5]) {
    uVar3 = ((int)pbVar2 - uVar3) + 1;
  }
  else {
    iVar1 = FUN_0800968c(param_1,(int *)param_3);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    pbVar2 = (byte *)*param_3;
    uVar3 = 1;
  }
  param_3[2] = param_3[2] - 1;
  *param_3 = (uint)(pbVar2 + 1);
  *pbVar2 = param_2;
  if (param_3[5] != uVar3) {
    if (-1 < (int)((uint)(ushort)param_3[3] << 0x1f)) {
      return uVar4;
    }
    if (uVar4 != 10) {
      return uVar4;
    }
  }
  iVar1 = FUN_0800968c(param_1,(int *)param_3);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  return uVar4;
}

