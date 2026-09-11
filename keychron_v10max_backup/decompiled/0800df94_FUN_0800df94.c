// FUN_0800df94 @ 0x0800df94  size=644  body=[[0800df94, 0800e217]]

char FUN_0800df94(uint *param_1)

{
  byte bVar1;
  short sVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint extraout_r2;
  uint uVar10;
  ushort uVar11;
  bool bVar12;
  undefined2 local_38 [4];
  ushort local_30;
  short local_2e;
  char local_2c;
  undefined1 local_2b;
  byte local_2a;
  
  memcpy((undefined4 *)local_38,param_1,6);
  cVar5 = DAT_20001678._1_1_;
  uVar9 = *param_1;
  bVar1 = *(byte *)((int)param_1 + 1);
  cVar3 = *(char *)((int)param_1 + 5);
  sVar2 = *(short *)((int)param_1 + 2);
  cVar4 = (char)param_1[1];
  if ((char)DAT_20001678 == '\0') {
    if (cVar4 == '\0') {
      return '\x01';
    }
    if ((cVar3 == '\0') || (bVar6 = FUN_0800db94((undefined2 *)param_1,0), !bVar6))
    goto LAB_0800e206;
    memcpy((undefined4 *)&DAT_20001674,param_1,8);
    FUN_0800d54c(&DAT_20001674,extraout_r1);
  }
  else {
    uVar11 = sVar2 - DAT_20001676;
    if (DAT_20001678._1_1_ == '\0') {
      get_record_keycode((uint *)&DAT_20001674,0);
      uVar9 = FUN_0800defc();
      if (uVar9 <= uVar11) {
        FUN_0800dbac();
LAB_0800e14e:
        FUN_08008798((byte *)&DAT_20001674,0,8);
        FUN_0800de98();
        return '\0';
      }
      if (cVar4 == '\0') {
        return '\x01';
      }
      if (cVar3 == '\0') goto LAB_0800e206;
      if (DAT_20001674 == (ushort)*param_1) {
        if (((0xae < (ushort)(sVar2 - DAT_20001676)) ||
            (uVar9 = (uint)(byte)DAT_2000167a, (int)(uVar9 << 0x1f) < 0)) || (uVar9 < 0x10)) {
          memcpy((undefined4 *)&DAT_20001674,param_1,8);
          return '\x01';
        }
        *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
        if ((uVar9 & 0xf0) != 0xf0) {
          *(byte *)((int)param_1 + 6) =
               *(byte *)((int)param_1 + 6) & 0xf | ((*(byte *)((int)param_1 + 6) >> 4) + 1) * '\x10'
          ;
        }
        FUN_0800dad8(param_1);
        goto LAB_0800e0f0;
      }
      bVar6 = FUN_0800db94((undefined2 *)param_1,extraout_r1_02);
      if (!bVar6) {
        DAT_2000167a._0_1_ = (byte)DAT_2000167a | 1;
        goto LAB_0800e206;
      }
    }
    else {
      get_record_keycode((uint *)&DAT_20001674,0);
      uVar7 = FUN_0800defc();
      if (uVar11 < uVar7) {
        if (cVar4 == '\0') {
          return '\x01';
        }
        uVar7 = (uint)(ushort)*param_1;
        if ((byte)DAT_2000167a < 0x10) {
          if (DAT_20001674 == uVar7) {
            if (cVar3 == '\0') {
              DAT_2000167a._0_1_ = (byte)DAT_2000167a & 0xf | 0x10;
              FUN_0800de98();
              FUN_0800dad8((uint *)&DAT_20001674);
              *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
              return '\0';
            }
LAB_0800e0ce:
            DAT_2000167a._0_1_ = (byte)DAT_2000167a | 1;
            return '\0';
          }
          if (cVar3 != '\0') goto LAB_0800e0ce;
          FUN_0800deb8((uint)(byte)uVar9,(uint)bVar1,0);
          iVar8 = FUN_0800deb8((uint)(byte)uVar9,extraout_r1_00,extraout_r2);
          if (iVar8 != 0) {
            return '\0';
          }
          uVar9 = FUN_0800ddf8(local_38[0],extraout_r1_01);
          uVar7 = (uVar9 & 0xffff) >> 0xc;
          uVar10 = uVar9 & 0xff;
          if (uVar7 < 4) {
            if (uVar7 < 2) {
              if (((uVar9 & 0xf00) != 0) && (uVar10 == 0)) {
                return '\0';
              }
            }
            else if (((uVar9 & 0xf00) != 0) && (*(byte *)((int)param_1 + 6) < 0x10)) {
              return '\0';
            }
            uVar9 = uVar10 + 0x20 & 0xff;
            bVar12 = 6 < uVar9;
            bVar6 = uVar9 == 7;
          }
          else {
            if (1 < (uVar7 + 6 & 0xf)) goto LAB_0800e0a4;
            if (uVar10 < 0xf0) {
              return '\0';
            }
            uVar9 = uVar10 + 0xf & 0xff;
            bVar12 = 1 < uVar9;
            bVar6 = uVar9 == 2;
          }
          if (!bVar12 || bVar6) {
            return '\0';
          }
LAB_0800e0a4:
          FUN_0800dad8(param_1);
          return cVar5;
        }
        if ((DAT_20001674 == uVar7) && (cVar3 == '\0')) {
          *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
          FUN_0800dad8(param_1);
LAB_0800e0f0:
          memcpy((undefined4 *)&DAT_20001674,param_1,8);
          goto LAB_0800dff2;
        }
      }
      else {
        uVar7 = (uint)(byte)DAT_2000167a;
        if (uVar7 < 0x10) {
          FUN_0800dbac();
          FUN_0800dad8((uint *)&DAT_20001674);
          goto LAB_0800e14e;
        }
        if (cVar4 == '\0') {
          return '\x01';
        }
        if ((DAT_20001674 == (ushort)*param_1) && (cVar3 == '\0')) {
          *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
          FUN_0800dad8(param_1);
          FUN_08008798((byte *)&DAT_20001674,0,8);
          return '\x01';
        }
      }
      bVar6 = FUN_0800db94((undefined2 *)param_1,uVar7);
      if ((!bVar6) || (cVar3 == '\0')) {
LAB_0800e206:
        FUN_0800dad8(param_1);
        return '\x01';
      }
      if (0x1f < (byte)DAT_2000167a) {
        local_30 = DAT_20001674;
        local_2c = (char)DAT_20001678;
        local_2b = 0;
        local_2a = (byte)DAT_2000167a;
        local_2e = sVar2;
        FUN_0800dad8((uint *)&local_30);
      }
    }
    memcpy((undefined4 *)&DAT_20001674,param_1,8);
  }
  FUN_0800df00();
LAB_0800dff2:
  FUN_0800de98();
  return '\x01';
}

