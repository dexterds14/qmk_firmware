// FUN_0800dd0c @ 0x0800dd0c  size=38  body=[[0800dd0c, 0800dd31]]

uint FUN_0800dd0c(uint param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  uVar3 = 0;
  do {
    pbVar1 = (byte *)(param_2 + (param_1 >> 3) * 4 + uVar4);
    uVar2 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    uVar3 = uVar3 | (*pbVar1 >> (param_1 & 7) & 1) << uVar2 & 0xff;
  } while (uVar4 != 4);
  return uVar3;
}

