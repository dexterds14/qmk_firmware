// FUN_08009fd8 @ 0x08009fd8  size=196  body=[[08009fd8, 0800a09b]]

void FUN_08009fd8(undefined4 *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte abStack_68 [4];
  uint local_64;
  
  uVar3 = (uint)(short)param_2[3];
  if ((int)(uVar3 << 0x1e) < 0) {
    param_2[4] = (int)param_2 + 0x47U;
    param_2[5] = 1;
    *param_2 = (int)param_2 + 0x47U;
    return;
  }
  if (-1 < *(short *)((int)param_2 + 0xe)) {
    iVar1 = FUN_080166be(param_1,(int)*(short *)((int)param_2 + 0xe),abStack_68);
    if (-1 < iVar1) {
      uVar3 = FUN_08009758(param_1,0x400);
      if (uVar3 != 0) {
        *param_2 = uVar3;
        *(ushort *)(param_2 + 3) = (ushort)param_2[3] | 0x80;
        param_2[4] = uVar3;
        param_2[5] = 0x400;
        if ((local_64 & 0xf000) != 0x2000) {
          return;
        }
        iVar1 = FUN_080166d6();
        if (iVar1 == 0) {
          return;
        }
        *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfffc | 1;
        return;
      }
      goto LAB_0800a07c;
    }
    uVar3 = (uint)(short)param_2[3];
  }
  if ((uVar3 & 0x80) == 0) {
    uVar3 = 0x400;
  }
  else {
    uVar3 = 0x40;
  }
  uVar2 = FUN_08009758(param_1,uVar3);
  if (uVar2 != 0) {
    *param_2 = uVar2;
    param_2[4] = uVar2;
    param_2[5] = uVar3;
    *(ushort *)(param_2 + 3) = (ushort)param_2[3] | 0x80;
    return;
  }
LAB_0800a07c:
  if (-1 < (int)(short)(ushort)param_2[3] << 0x16) {
    param_2[4] = (int)param_2 + 0x47U;
    param_2[5] = 1;
    *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfffc | 2;
    *param_2 = (int)param_2 + 0x47U;
  }
  return;
}

