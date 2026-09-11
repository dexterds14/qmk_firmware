// FUN_08008abc @ 0x08008abc  size=598  body=[[08008abc, 08008d11]]

// WARNING: Removing unreachable block (ram,0x08008bd0)
// WARNING: Type propagation algorithm not settling

int FUN_08008abc(uint *param_1,uint *param_2,byte *param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint local_9c;
  int *local_8c;
  uint local_88;
  int local_84;
  undefined4 uStack_80;
  int local_7c;
  int local_74;
  byte local_70;
  undefined2 local_6f;
  undefined1 local_45;
  undefined4 local_30;
  
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  if ((((int)((uint)(ushort)param_2[3] << 0x1c) < 0) && (param_2[4] != 0)) ||
     (iVar1 = FUN_08009b00(param_1,param_2), iVar1 == 0)) {
    local_74 = 0;
    local_6f = 0x3020;
    bVar4 = *param_3;
    local_8c = param_4;
    while (pbVar8 = param_3, bVar4 != 0) {
      do {
        if (bVar4 == 0x25) {
          pbVar7 = pbVar8 + -(int)param_3;
          if (pbVar7 != (byte *)0x0) goto LAB_08008c22;
          bVar4 = *pbVar8;
          goto LAB_08008b22;
        }
        pbVar8 = pbVar8 + 1;
        bVar4 = *pbVar8;
      } while (bVar4 != 0);
      pbVar7 = pbVar8 + -(int)param_3;
      if (pbVar7 == (byte *)0x0) break;
LAB_08008c22:
      pbVar5 = param_3 + -1;
      do {
        uVar2 = FUN_08008a30(param_1,(uint)pbVar5[1],param_2);
        pbVar6 = pbVar5 + (2 - (int)param_3);
        if (uVar2 == 0xffffffff) goto LAB_08008bf8;
        pbVar5 = pbVar5 + 1;
      } while (pbVar6 < pbVar7);
      local_74 = local_74 + (int)pbVar7;
      bVar4 = *pbVar8;
LAB_08008b22:
      if (bVar4 == 0) break;
      local_84 = -1;
      uStack_80 = 0;
      local_88 = 0;
      local_7c = 0;
      local_45 = 0;
      local_30 = 0;
      pbVar8 = pbVar8 + 1;
      while( true ) {
        pbVar5 = pbVar8 + 1;
        pbVar7 = FUN_08009a60((uint *)"#-0+ ",(uint)*pbVar8,5);
        if (pbVar7 == (byte *)0x0) break;
        local_88 = local_88 | 1 << ((uint)(pbVar7 + -0x8017708) & 0xff);
        pbVar8 = pbVar5;
      }
      if ((int)(local_88 << 0x1b) < 0) {
        local_45 = 0x20;
      }
      uVar2 = (uint)*pbVar8;
      if ((int)(local_88 << 0x1c) < 0) {
        local_45 = 0x2b;
      }
      if (uVar2 == 0x2a) {
        local_7c = *local_8c;
        local_8c = local_8c + 1;
        if (local_7c < 0) {
          local_7c = -local_7c;
          local_88 = local_88 | 2;
        }
        uVar2 = (uint)pbVar8[1];
        pbVar8 = pbVar5;
      }
      else {
        uVar3 = uVar2 - 0x30;
        if (uVar3 < 10) {
          while( true ) {
            uVar2 = (uint)*pbVar5;
            local_7c = uVar3 + local_7c * 10;
            uVar3 = uVar2 - 0x30;
            pbVar8 = pbVar5;
            if (9 < uVar3) break;
            pbVar5 = pbVar5 + 1;
          }
        }
      }
      if (uVar2 == 0x2e) {
        uVar2 = (uint)pbVar8[1];
        if (uVar2 == 0x2a) {
          uVar2 = (uint)pbVar8[2];
          local_84 = *local_8c;
          local_8c = local_8c + 1;
          pbVar8 = pbVar8 + 2;
          if (local_84 < 0) {
            local_84 = -1;
          }
        }
        else {
          local_84 = 0;
          pbVar8 = pbVar8 + 1;
          while (uVar2 - 0x30 < 10) {
            pbVar8 = pbVar8 + 1;
            local_84 = (uVar2 - 0x30) + local_84 * 10;
            uVar2 = (uint)*pbVar8;
          }
        }
      }
      pbVar7 = FUN_08009a60((uint *)&DAT_08017710,uVar2,3);
      if (pbVar7 != (byte *)0x0) {
        local_88 = local_88 | 0x40 << ((uint)(pbVar7 + -0x8017710) & 0xff);
        pbVar8 = pbVar8 + 1;
      }
      param_3 = pbVar8 + 1;
      local_70 = *pbVar8;
      pbVar8 = FUN_08009a60((uint *)"efgEFG",(uint)local_70,6);
      if (pbVar8 == (byte *)0x0) {
        local_9c = FUN_08009d4c(param_1,&local_88,param_2,(undefined *)0x8008a6d,(int *)&local_8c);
        if (local_9c == 0xffffffff) break;
      }
      else {
        local_8c = (int *)(((int)local_8c + 7U & 0xfffffff8) + 8);
      }
      local_74 = local_74 + local_9c;
      bVar4 = *param_3;
    }
LAB_08008bf8:
    if (-1 < (int)((uint)(ushort)param_2[3] << 0x19)) {
      return local_74;
    }
  }
  return -1;
}

