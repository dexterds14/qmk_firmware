// FUN_08008de4 @ 0x08008de4  size=762  body=[[08008de4, 080090dd]]

undefined4 FUN_08008de4(uint *param_1,uint *param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  byte *pbVar5;
  ushort uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  int *piVar13;
  int *piVar14;
  int iVar15;
  undefined4 *puVar16;
  byte *pbVar17;
  code *pcVar18;
  uint *puVar19;
  byte *local_30;
  
  if (param_3[2] == 0) {
    return 0;
  }
  uVar6 = (ushort)param_2[3];
  if (((uVar6 & 8) == 0) || (param_2[4] == 0)) {
    iVar15 = FUN_08009b00(param_1,param_2);
    if (iVar15 != 0) {
      return 0xffffffff;
    }
    uVar6 = (ushort)param_2[3];
    piVar13 = (int *)*param_3;
  }
  else {
    piVar13 = (int *)*param_3;
  }
  if ((uVar6 & 2) != 0) {
    iVar15 = 0;
    pcVar18 = (code *)param_2[10];
    uVar4 = param_2[8];
    uVar10 = 0;
    do {
      uVar8 = uVar10;
      if (0x7ffffbff < uVar10) {
        uVar8 = 0x7ffffc00;
      }
      while (uVar10 != 0) {
        iVar2 = (*pcVar18)(param_1,uVar4,iVar15,uVar8);
        if (iVar2 < 1) goto LAB_08008fc8;
        iVar7 = param_3[2];
        iVar15 = iVar15 + iVar2;
        uVar10 = uVar10 - iVar2;
        param_3[2] = iVar7 - iVar2;
        if (iVar7 - iVar2 == 0) {
          return 0;
        }
        pcVar18 = (code *)param_2[10];
        uVar4 = param_2[8];
        uVar8 = uVar10;
        if (0x7ffffbff < uVar10) {
          uVar8 = 0x7ffffc00;
        }
      }
      iVar15 = *piVar13;
      uVar10 = piVar13[1];
      piVar13 = piVar13 + 2;
    } while( true );
  }
  if ((uVar6 & 1) == 0) {
    puVar9 = (undefined4 *)*param_2;
    uVar4 = param_2[2];
    uVar10 = 0;
    puVar16 = (undefined4 *)0x0;
    while( true ) {
      while (uVar10 == 0) {
        puVar16 = (undefined4 *)*piVar13;
        puVar19 = (uint *)(piVar13 + 1);
        piVar13 = piVar13 + 2;
        uVar10 = *puVar19;
      }
      if ((uVar6 & 0x200) == 0) {
        if (((undefined4 *)param_2[4] < puVar9) || (uVar8 = param_2[5], uVar10 < uVar8)) {
          if (uVar10 <= uVar4) {
            uVar4 = uVar10;
          }
          FUN_08009914(puVar9,puVar16,uVar4);
          uVar8 = param_2[2];
          param_2[2] = uVar8 - uVar4;
          *param_2 = *param_2 + uVar4;
          if ((uVar8 - uVar4 == 0) && (iVar15 = FUN_0800968c(param_1,(int *)param_2), iVar15 != 0))
          goto LAB_08008fc8;
        }
        else {
          uVar4 = 0x7fffffff;
          if (uVar10 < 0x80000000) {
            uVar4 = uVar10;
          }
          uVar4 = (*(code *)param_2[10])
                            (param_1,param_2[8],puVar16,uVar8 * ((int)uVar4 / (int)uVar8));
          if ((int)uVar4 < 1) goto LAB_08008fc8;
        }
        uVar8 = uVar10 - uVar4;
      }
      else {
        uVar8 = uVar10;
        if ((uVar4 <= uVar10) && (uVar8 = uVar4, (uVar6 & 0x480) != 0)) {
          uVar11 = (int)puVar9 - (int)param_2[4];
          uVar4 = (int)(param_2[5] * 3) / 2;
          uVar8 = uVar11 + 1 + uVar10;
          if (uVar4 < uVar8) {
            uVar4 = uVar8;
          }
          if ((uVar6 & 0x400) == 0) {
            puVar3 = FUN_08009bc4(param_1,(undefined4 *)param_2[4],uVar4);
            if (puVar3 == (undefined4 *)0x0) {
              FUN_08009858(param_1,param_2[4]);
              uVar4 = param_2[3];
              *param_1 = 0xc;
              uVar6 = (ushort)uVar4 & 0xff7f;
              goto LAB_08008fcc;
            }
          }
          else {
            puVar3 = (undefined4 *)FUN_08009758(param_1,uVar4);
            if (puVar3 == (undefined4 *)0x0) {
              uVar6 = (ushort)param_2[3];
              *param_1 = 0xc;
              goto LAB_08008fcc;
            }
            memcpy(puVar3,(undefined4 *)param_2[4],uVar11);
            *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfb7f | 0x80;
          }
          puVar9 = (undefined4 *)((int)puVar3 + uVar11);
          param_2[5] = uVar4;
          param_2[4] = (uint)puVar3;
          param_2[2] = uVar4 - uVar11;
          *param_2 = (uint)puVar9;
          uVar8 = uVar10;
        }
        FUN_08009914(puVar9,puVar16,uVar8);
        param_2[2] = param_2[2] - uVar8;
        *param_2 = uVar8 + *param_2;
        uVar8 = 0;
        uVar4 = uVar10;
      }
      iVar15 = param_3[2];
      puVar16 = (undefined4 *)((int)puVar16 + uVar4);
      param_3[2] = iVar15 - uVar4;
      if (iVar15 - uVar4 == 0) break;
      puVar9 = (undefined4 *)*param_2;
      uVar4 = param_2[2];
      uVar6 = (ushort)param_2[3];
      uVar10 = uVar8;
    }
  }
  else {
    bVar1 = false;
    pbVar12 = (byte *)0x0;
    puVar19 = (uint *)0x0;
    local_30 = (byte *)0x0;
    do {
      if (pbVar12 == (byte *)0x0) {
        do {
          piVar14 = piVar13;
          pbVar12 = (byte *)piVar14[1];
          piVar13 = piVar14 + 2;
        } while (pbVar12 == (byte *)0x0);
        puVar19 = (uint *)*piVar14;
LAB_08008fee:
        local_30 = FUN_08009a60(puVar19,10,(uint)pbVar12);
        if (local_30 == (byte *)0x0) {
          local_30 = pbVar12 + 1;
        }
        else {
          local_30 = local_30 + (1 - (int)puVar19);
        }
      }
      else if (!bVar1) goto LAB_08008fee;
      puVar9 = (undefined4 *)*param_2;
      pbVar5 = local_30;
      if (pbVar12 <= local_30) {
        pbVar5 = pbVar12;
      }
      if (((undefined4 *)param_2[4] < puVar9) &&
         (pbVar17 = (byte *)(param_2[2] + param_2[5]), (int)pbVar17 < (int)pbVar5)) {
        FUN_08009914(puVar9,puVar19,(uint)pbVar17);
        *param_2 = (uint)(pbVar17 + *param_2);
        iVar15 = FUN_0800968c(param_1,(int *)param_2);
        if (iVar15 != 0) {
LAB_08008fc8:
          uVar6 = (ushort)param_2[3];
LAB_08008fcc:
          *(ushort *)(param_2 + 3) = uVar6 | 0x40;
          return 0xffffffff;
        }
      }
      else if ((int)pbVar5 < (int)param_2[5]) {
        FUN_08009914(puVar9,puVar19,(uint)pbVar5);
        param_2[2] = param_2[2] - (int)pbVar5;
        *param_2 = (uint)(pbVar5 + *param_2);
        pbVar17 = pbVar5;
      }
      else {
        pbVar17 = (byte *)(*(code *)param_2[10])(param_1,param_2[8],puVar19);
        if ((int)pbVar17 < 1) goto LAB_08008fc8;
      }
      local_30 = local_30 + -(int)pbVar17;
      if (local_30 == (byte *)0x0) {
        iVar15 = FUN_0800968c(param_1,(int *)param_2);
        bVar1 = false;
        if (iVar15 != 0) goto LAB_08008fc8;
      }
      else {
        bVar1 = true;
      }
      iVar15 = param_3[2];
      puVar19 = (uint *)((int)puVar19 + (int)pbVar17);
      pbVar12 = pbVar12 + -(int)pbVar17;
      param_3[2] = iVar15 - (int)pbVar17;
    } while (iVar15 - (int)pbVar17 != 0);
  }
  return 0;
}

