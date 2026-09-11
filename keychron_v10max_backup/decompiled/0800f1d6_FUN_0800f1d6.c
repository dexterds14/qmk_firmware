// FUN_0800f1d6 @ 0x0800f1d6  size=206  body=[[0800f1d6, 0800f1df] [0800f394, 0800f457]]

uint FUN_0800f1d6(int *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar4;
  undefined4 extraout_r1;
  undefined4 uVar5;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar6;
  undefined4 extraout_r2_01;
  uint uVar7;
  undefined8 uVar8;
  undefined1 local_30 [4];
  int *local_2c;
  uint uStack_28;
  uint uVar3;
  
  if (param_2 + param_3 < 0x801) {
    local_30 = (undefined1  [4])param_2;
    local_2c = param_1;
    uStack_28 = param_3;
    iVar2 = FUN_080089d4(param_1,(int *)(&DAT_20001704 + param_2),param_3);
    if (iVar2 == 0) {
      return 1;
    }
    memcpy((undefined4 *)(&DAT_20001704 + param_2),param_1,param_3);
    bVar1 = FUN_0800f200();
    uVar3 = (uint)bVar1;
    uVar7 = uVar3;
    uVar5 = extraout_r1;
    uVar6 = extraout_r2;
    if (uVar3 == 0) {
      FUN_0800f220();
    }
    else {
      while (param_3 != 0) {
        uVar7 = param_3;
        if (4 < param_3) {
          uVar7 = 5;
        }
        local_2c = (int *)0x0;
        local_30[1] = (char)(param_2 >> 8);
        local_30[0] = (byte)((param_2 << 0xd) >> 0x1d) | (byte)(uVar7 << 3);
        local_30[2] = (char)param_2;
        local_30[3] = 0;
        memcpy((undefined4 *)(local_30 + 3),param_1,uVar7);
        uVar8 = FUN_0800f36c((uint)local_30);
        uVar5 = (undefined4)((ulonglong)uVar8 >> 0x20);
        uVar4 = (uint)uVar8;
        if (uVar4 != 1) {
LAB_0800f44a:
          if ((uVar4 & 0xfd) != 0) {
            uVar4 = 0;
          }
          goto LAB_0800f3d8;
        }
        uVar6 = extraout_r2_00;
        if (param_3 != 1) {
          uVar8 = FUN_0800f36c((uint)local_2c);
          uVar5 = (undefined4)((ulonglong)uVar8 >> 0x20);
          uVar4 = (uint)uVar8;
          uVar6 = extraout_r2_01;
          if (uVar4 != 1) goto LAB_0800f44a;
        }
        param_2 = param_2 + uVar7;
        param_1 = (int *)((int)param_1 + uVar7);
        param_3 = param_3 - uVar7;
        uVar7 = 1;
      }
      uVar4 = FUN_0800f354(uVar7,uVar5,uVar6);
LAB_0800f3d8:
      if (uVar3 != 1) {
        return uVar4;
      }
      iVar2 = FUN_0800f220();
      if (iVar2 != 0) {
        return uVar4;
      }
    }
  }
  return 0;
}

