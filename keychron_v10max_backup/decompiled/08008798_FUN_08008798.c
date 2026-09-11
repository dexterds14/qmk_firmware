// FUN_08008798 @ 0x08008798  size=162  body=[[08008798, 08008839]]

void FUN_08008798(byte *param_1,byte param_2,uint param_3)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  
  for (; ((uint)param_1 & 3) != 0; param_1 = param_1 + 1) {
    if (param_3 == 0) {
      return;
    }
    param_3 = param_3 - 1;
    *param_1 = param_2;
  }
  if (3 < param_3) {
    iVar1 = (uint)param_2 * 0x1010101;
    if (0xf < param_3) {
      pbVar2 = param_1;
      do {
        *(int *)pbVar2 = iVar1;
        *(int *)(pbVar2 + 4) = iVar1;
        *(int *)(pbVar2 + 8) = iVar1;
        *(int *)(pbVar2 + 0xc) = iVar1;
        pbVar2 = pbVar2 + 0x10;
      } while (pbVar2 != param_1 + (param_3 - 0x10 & 0xfffffff0) + 0x10);
      uVar4 = param_3 & 0xc;
      param_1 = param_1 + ((param_3 - 0x10 >> 4) + 1) * 0x10;
      param_3 = param_3 & 0xf;
      if (uVar4 == 0) goto joined_r0x08008814;
    }
    uVar4 = param_3 - 4;
    pbVar2 = param_1;
    do {
      pbVar3 = pbVar2 + 4;
      *(int *)pbVar2 = iVar1;
      pbVar2 = pbVar3;
    } while (param_1 + (uVar4 & 0xfffffffc) + 4 != pbVar3);
    param_3 = param_3 & 3;
    param_1 = param_1 + (uVar4 & 0xfffffffc) + 4;
  }
joined_r0x08008814:
  if (param_3 != 0) {
    pbVar2 = param_1;
    do {
      pbVar3 = pbVar2 + 1;
      *pbVar2 = param_2;
      pbVar2 = pbVar3;
    } while (pbVar3 != param_1 + param_3);
  }
  return;
}

