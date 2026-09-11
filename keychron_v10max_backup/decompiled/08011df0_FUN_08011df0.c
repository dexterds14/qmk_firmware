// FUN_08011df0 @ 0x08011df0  size=374  body=[[08011df0, 08011f65]]

void FUN_08011df0(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  short extraout_r2;
  short extraout_r2_00;
  char cVar6;
  undefined4 uStack_10;
  undefined4 local_c;
  
  uStack_10 = param_1;
  local_c = param_2;
  memcpy(&uStack_10,(undefined4 *)&DAT_20002013,6);
  DAT_20002015 = '\0';
  DAT_20002016 = '\0';
  DAT_20002017 = '\0';
  DAT_20002018 = '\0';
  if (uStack_10._2_1_ != '\0' || uStack_10._3_1_ != '\0') {
    uVar3 = FUN_0801257e((uint)DAT_2000200c);
    if (DAT_20002011 == '\0') {
      if ((int)((uint)DAT_20002009 * 10) < (int)uVar3) {
LAB_08011e80:
        DAT_20002011 = DAT_20002011 + '\x01';
        goto LAB_08011e8a;
      }
    }
    else if ((int)(uint)DAT_20000ec5 < (int)uVar3) {
      if (DAT_20002011 != -1) goto LAB_08011e80;
LAB_08011e8a:
      if (uStack_10._2_1_ != '\0') {
        bVar2 = FUN_08011a8c();
        if (uStack_10._2_1_ < '\x01') {
          cVar6 = -1;
        }
        else {
          cVar6 = '\x01';
        }
        DAT_20002015 = bVar2 * cVar6;
      }
      if (uStack_10._3_1_ != '\0') {
        bVar2 = FUN_08011a8c();
        if (uStack_10._3_1_ < '\x01') {
          cVar6 = -1;
        }
        else {
          cVar6 = '\x01';
        }
        DAT_20002016 = bVar2 * cVar6;
      }
      if ((DAT_20002015 != '\0') && (DAT_20002016 != '\0')) {
        iVar5 = FUN_08011a62((short)DAT_20002015);
        if (iVar5 == 0) {
          iVar5 = 1;
        }
        DAT_20002015 = (char)iVar5;
        iVar5 = FUN_08011a62(extraout_r2);
        if (iVar5 == 0) {
          DAT_20002016 = '\x01';
        }
        else {
          DAT_20002016 = (char)iVar5;
        }
      }
    }
  }
  if ((char)local_c == '\0' && local_c._1_1_ == '\0') goto LAB_08011e4e;
  uVar3 = FUN_0801257e((uint)DAT_2000200a);
  if (DAT_20002010 == '\0') {
    if ((int)uVar3 <= (int)((uint)DAT_20000ec4 * 10)) goto LAB_08011e4e;
LAB_08011efa:
    DAT_20002010 = DAT_20002010 + '\x01';
  }
  else {
    if ((int)uVar3 <= (int)(uint)DAT_20000ec2) goto LAB_08011e4e;
    if (DAT_20002010 != -1) goto LAB_08011efa;
  }
  if ((char)local_c != '\0') {
    uVar4 = FUN_08011b14();
    if ((char)local_c < '\x01') {
      cVar6 = -1;
    }
    else {
      cVar6 = '\x01';
    }
    DAT_20002017 = (char)uVar4 * cVar6;
  }
  if (local_c._1_1_ != '\0') {
    uVar4 = FUN_08011b14();
    if (local_c._1_1_ < '\x01') {
      cVar6 = -1;
    }
    else {
      cVar6 = '\x01';
    }
    DAT_20002018 = (char)uVar4 * cVar6;
  }
  if ((DAT_20002017 != '\0') && (DAT_20002018 != '\0')) {
    iVar5 = FUN_08011a62((short)DAT_20002017);
    if (iVar5 == 0) {
      iVar5 = 1;
    }
    DAT_20002017 = (char)iVar5;
    iVar5 = FUN_08011a62(extraout_r2_00);
    if (iVar5 == 0) {
      DAT_20002018 = '\x01';
    }
    else {
      DAT_20002018 = (char)iVar5;
    }
  }
LAB_08011e4e:
  bVar1 = FUN_080123bc(0x20002013,(int)&uStack_10);
  if ((bVar1) || (bVar1 = FUN_08011dcc(0x20002013), bVar1)) {
    FUN_08011d68();
  }
  memcpy((undefined4 *)&DAT_20002013,&uStack_10,6);
  return;
}

