// FUN_08009568 @ 0x08009568  size=286  body=[[08009568, 08009685]]

undefined4 FUN_08009568(uint *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  ushort uVar4;
  uint uVar5;
  code *pcVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  
  uVar5 = (uint)(short)param_2[3];
  if ((int)(uVar5 << 0x1c) < 0) {
    iVar2 = param_2[4];
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = uVar5 << 0x1e;
    bVar9 = iVar1 == 0;
    iVar7 = *param_2;
    if (bVar9) {
      iVar1 = param_2[5];
    }
    *param_2 = iVar2;
    if (!bVar9) {
      iVar1 = 0;
    }
    iVar7 = iVar7 - iVar2;
    param_2[2] = iVar1;
    do {
      if (iVar7 < 1) {
        return 0;
      }
      iVar1 = (*(code *)param_2[10])(param_1,param_2[8],iVar2,iVar7);
      iVar7 = iVar7 - iVar1;
      iVar2 = iVar2 + iVar1;
    } while (0 < iVar1);
LAB_08009634:
    uVar4 = *(ushort *)(param_2 + 3);
LAB_08009638:
    *(ushort *)(param_2 + 3) = uVar4 | 0x40;
    return 0xffffffff;
  }
  if ((param_2[1] < 1) && (param_2[0x10] < 1)) {
    return 0;
  }
  pcVar6 = (code *)param_2[0xb];
  if (pcVar6 == (code *)0x0) {
    return 0;
  }
  uVar8 = *param_1;
  *param_1 = 0;
  iVar2 = param_2[8];
  if ((uVar5 & 0x1000) == 0) {
    iVar1 = (*pcVar6)(param_1,iVar2,0,1);
    if ((iVar1 == -1) && (uVar5 = *param_1, uVar5 != 0)) {
      if ((uVar5 == 0x1d) || (uVar5 == 0x16)) {
        *param_1 = uVar8;
        return 0;
      }
      goto LAB_08009634;
    }
    uVar5 = (uint)(short)param_2[3];
    pcVar6 = (code *)param_2[0xb];
    iVar2 = param_2[8];
  }
  else {
    iVar1 = param_2[0x15];
  }
  if (((int)(uVar5 << 0x1d) < 0) && (iVar1 = iVar1 - param_2[1], param_2[0xd] != 0)) {
    iVar1 = iVar1 - param_2[0x10];
  }
  iVar2 = (*pcVar6)(param_1,iVar2,iVar1,0);
  if (iVar2 == -1) {
    uVar5 = *param_1;
    uVar4 = *(ushort *)(param_2 + 3);
    if ((0x1d < uVar5) || (-1 < (int)((0x20400001U >> (uVar5 & 0xff)) << 0x1f))) goto LAB_08009638;
    *param_2 = param_2[4];
    param_2[1] = 0;
    if ((-1 < (int)(short)uVar4 << 0x13) || (uVar5 != 0)) goto LAB_080095d4;
  }
  else {
    param_2[1] = 0;
    *param_2 = param_2[4];
    if (-1 < (int)((uint)*(ushort *)(param_2 + 3) << 0x13)) goto LAB_080095d4;
  }
  param_2[0x15] = iVar2;
LAB_080095d4:
  piVar3 = (int *)param_2[0xd];
  *param_1 = uVar8;
  if (piVar3 != (int *)0x0) {
    if (piVar3 != param_2 + 0x11) {
      FUN_08009858(param_1,(int)piVar3);
    }
    param_2[0xd] = 0;
  }
  return 0;
}

