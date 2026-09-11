// FUN_08009d4c @ 0x08009d4c  size=570  body=[[08009d4c, 08009d77] [08009dba, 08009fc7]]

uint FUN_08009d4c(undefined4 param_1,uint *param_2,undefined4 param_3,undefined *param_4,
                 int *param_5)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  uint *puVar11;
  uint *puVar12;
  bool bVar13;
  uint local_24;
  
  uVar6 = (uint)(byte)param_2[6];
  puVar12 = (uint *)((int)param_2 + 0x43);
  puVar11 = puVar12;
  if (uVar6 == 0) {
LAB_08009dd2:
    param_2[4] = 0;
    goto LAB_08009dd8;
  }
  if (0x20 < (uVar6 - 0x58 & 0xff)) {
switchD_08009d74_caseD_1:
    *(byte *)((int)param_2 + 0x42) = (byte)param_2[6];
    uVar6 = 1;
    puVar11 = (uint *)((int)param_2 + 0x42);
    goto LAB_08009e4e;
  }
  switch(uVar6 - 0x58) {
  case 0:
    *(undefined1 *)((int)param_2 + 0x45) = 0x58;
    pcVar4 = "0123456789ABCDEF";
    uVar6 = *param_2;
    goto LAB_08009f14;
  default:
    goto switchD_08009d74_caseD_1;
  case 0xb:
    uVar9 = *(undefined4 *)*param_5;
    *param_5 = (int)((undefined4 *)*param_5 + 1);
    puVar11 = (uint *)((int)param_2 + 0x42);
    *(char *)((int)param_2 + 0x42) = (char)uVar9;
    uVar6 = 1;
    break;
  case 0xc:
  case 0x11:
    puVar7 = (uint *)*param_5;
    uVar6 = *param_2;
    *param_5 = (int)(puVar7 + 1);
    if (((int)(uVar6 << 0x18) < 0) || (-1 < (int)(uVar6 << 0x19))) {
      uVar5 = *puVar7;
    }
    else {
      uVar5 = (uint)(short)*puVar7;
    }
    uVar8 = param_2[1];
    if (-1 < (int)uVar5) {
      pcVar4 = "0123456789ABCDEF";
      uVar6 = 10;
      goto LAB_08009eaa;
    }
    param_2[2] = uVar8;
    *(undefined1 *)((int)param_2 + 0x43) = 0x2d;
    if (-1 < (int)uVar8) {
      *param_2 = uVar6 & 0xfffffffb;
    }
    uVar6 = 10;
    pcVar4 = "0123456789ABCDEF";
    uVar5 = -uVar5;
    goto LAB_08009f58;
  case 0x16:
    puVar10 = (undefined4 *)*param_5;
    uVar5 = *param_2;
    uVar6 = param_2[5];
    *param_5 = (int)(puVar10 + 1);
    puVar12 = (uint *)*puVar10;
    if (((int)(uVar5 << 0x18) < 0) || (-1 < (int)(uVar5 << 0x19))) {
      *puVar12 = uVar6;
    }
    else {
      *(short *)puVar12 = (short)uVar6;
    }
    goto LAB_08009dd2;
  case 0x17:
  case 0x1d:
    uVar5 = *(uint *)*param_5;
    if (((*param_2 & 0x80) == 0) && ((int)(*param_2 << 0x19) < 0)) {
      uVar5 = uVar5 & 0xffff;
    }
    pcVar4 = "0123456789ABCDEF";
    *param_5 = (int)((uint *)*param_5 + 1);
    if (uVar6 == 0x6f) {
      uVar6 = 8;
    }
    else {
      uVar6 = 10;
    }
    goto LAB_08009ea2;
  case 0x18:
    uVar6 = *param_2 | 0x20;
    *param_2 = uVar6;
    goto LAB_08009f0c;
  case 0x1b:
    puVar10 = (undefined4 *)*param_5;
    uVar6 = param_2[1];
    *param_5 = (int)(puVar10 + 1);
    puVar11 = (uint *)*puVar10;
    pbVar3 = FUN_08009a60(puVar11,0,uVar6);
    if (pbVar3 == (byte *)0x0) {
      uVar6 = param_2[1];
    }
    else {
      uVar6 = (int)pbVar3 - (int)puVar11;
      param_2[1] = uVar6;
    }
    break;
  case 0x20:
    uVar6 = *param_2;
LAB_08009f0c:
    pcVar4 = "0123456789abcdef";
    *(undefined1 *)((int)param_2 + 0x45) = 0x78;
LAB_08009f14:
    uVar5 = *(uint *)*param_5;
    if (((uVar6 & 0x80) == 0) && ((uVar6 & 0x40) != 0)) {
      uVar5 = uVar5 & 0xffff;
    }
    *param_5 = (int)((uint *)*param_5 + 1);
    if ((int)(uVar6 << 0x1f) < 0) {
      *param_2 = uVar6 | 0x20;
    }
    if (uVar5 == 0) {
      *param_2 = *param_2 & 0xffffffdf;
    }
    uVar6 = 0x10;
LAB_08009ea2:
    uVar8 = param_2[1];
    *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_08009eaa:
    param_2[2] = uVar8;
    if (((int)uVar8 < 0) || (*param_2 = *param_2 & 0xfffffffb, uVar5 != 0)) {
LAB_08009f58:
      do {
        bVar13 = uVar6 <= uVar5;
        puVar11 = (uint *)((int)puVar11 + -1);
        *(char *)puVar11 = pcVar4[uVar5 - uVar6 * (uVar5 / uVar6)];
        uVar5 = uVar5 / uVar6;
      } while (bVar13);
    }
    else if (uVar8 != 0) {
      *(char *)((int)param_2 + 0x42) = *pcVar4;
      puVar11 = (uint *)((int)param_2 + 0x42);
    }
    if (((uVar6 == 8) && ((int)(*param_2 << 0x1f) < 0)) && ((int)param_2[1] <= (int)param_2[4])) {
      *(char *)((int)puVar11 + -1) = '0';
      puVar11 = (uint *)((int)puVar11 + -1);
    }
    param_2[4] = (int)puVar12 - (int)puVar11;
    goto LAB_08009dd8;
  }
LAB_08009e4e:
  param_2[4] = uVar6;
  *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_08009dd8:
  iVar1 = FUN_08009c28(param_1,param_2,&local_24,param_3,param_4);
  if ((iVar1 != -1) && (iVar1 = (*(code *)param_4)(param_1,param_3,puVar11,param_2[4]), iVar1 != -1)
     ) {
    uVar6 = param_2[3];
    if (((int)(*param_2 << 0x1e) < 0) && ((int)local_24 < (int)uVar6)) {
      iVar1 = 0;
      do {
        iVar2 = (*(code *)param_4)(param_1,param_3,(int)param_2 + 0x19,1);
        iVar1 = iVar1 + 1;
        if (iVar2 == -1) {
          return 0xffffffff;
        }
        uVar6 = param_2[3];
      } while (iVar1 < (int)(uVar6 - local_24));
    }
    if ((int)uVar6 < (int)local_24) {
      uVar6 = local_24;
    }
    return uVar6;
  }
  return 0xffffffff;
}

