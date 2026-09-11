// FUN_08009b00 @ 0x08009b00  size=190  body=[[08009b00, 08009bbd]]

undefined4 FUN_08009b00(undefined4 *param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  
  if ((DAT_20000c00 != 0) && (*(int *)(DAT_20000c00 + 0x20) == 0)) {
    FUN_08009518(DAT_20000c00);
  }
  uVar3 = param_2[3];
  uVar4 = (uint)(short)(ushort)uVar3;
  if ((int)(uVar4 << 0x1c) < 0) {
    uVar3 = param_2[4];
  }
  else {
    if (-1 < (int)(uVar4 << 0x1b)) {
      *param_1 = 9;
      *(ushort *)(param_2 + 3) = (ushort)uVar3 | 0x40;
      return 0xffffffff;
    }
    if ((int)(uVar4 << 0x1d) < 0) {
      puVar2 = (uint *)param_2[0xd];
      if (puVar2 != (uint *)0x0) {
        if (puVar2 != param_2 + 0x11) {
          FUN_08009858(param_1,(int)puVar2);
          uVar4 = (uint)(short)param_2[3];
        }
        param_2[0xd] = 0;
      }
      uVar3 = param_2[4];
      *param_2 = uVar3;
      param_2[1] = 0;
      uVar4 = uVar4 & 0xffffffdb;
    }
    else {
      uVar3 = param_2[4];
    }
    uVar4 = uVar4 | 8;
    *(short *)(param_2 + 3) = (short)uVar4;
  }
  if ((uVar3 == 0) && ((uVar4 & 0x280) != 0x200)) {
    FUN_08009fd8(param_1,param_2);
    uVar4 = (uint)(short)param_2[3];
    uVar3 = param_2[4];
  }
  if ((uVar4 & 1) == 0) {
    uVar1 = 0;
    if (-1 < (int)(uVar4 << 0x1e)) {
      uVar1 = param_2[5];
    }
    param_2[2] = uVar1;
  }
  else {
    param_2[2] = 0;
    param_2[6] = -param_2[5];
  }
  if ((uVar3 == 0) && ((int)(uVar4 << 0x18) < 0)) {
    *(ushort *)(param_2 + 3) = (ushort)uVar4 | 0x40;
    return 0xffffffff;
  }
  return 0;
}

