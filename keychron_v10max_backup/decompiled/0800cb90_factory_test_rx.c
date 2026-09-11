// factory_test_rx @ 0x0800cb90  size=392  body=[[0800af2c, 0800af57] [0800af5c, 0800af87] [0800cb90, 0800cbc9] [0800cbd4, 0800ccc9]]

// INFERRED: 0xAB case target of kc_raw_hid_rx; 392 bytes; references build-date string 0x080167AC

void factory_test_rx(byte *param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  undefined2 local_28;
  byte local_26 [3];
  undefined1 local_23;
  undefined1 auStack_22 [4];
  undefined4 auStack_1e [5];
  
  if (*param_1 != 0xab) {
    return;
  }
  uVar6 = 0;
  pbVar5 = param_1;
  do {
    pbVar5 = pbVar5 + 1;
    uVar7 = uVar6 + *pbVar5;
    uVar6 = uVar7 & 0xffff;
  } while (pbVar5 != param_1 + 0x1c);
  if ((uint)param_1[0x1e] != (uVar7 & 0xff)) {
    return;
  }
  if ((uint)param_1[0x1f] != uVar6 >> 8) {
    return;
  }
  switch(param_1[1]) {
  case 1:
    DAT_200015d0 = param_1[2];
    DAT_200015d4 = 0;
    break;
  case 2:
    DAT_200015c9 = param_1[2] != 0;
    break;
  case 4:
    if (param_1[2] == 0xa1) {
      bVar1 = param_1[3];
      iVar4 = FUN_08008798(&DAT_2000151a,0,0x3e);
      *(undefined1 *)(iVar4 + -2) = 0x72;
      *(bool *)(iVar4 + -1) = bVar1 != 0;
      FUN_0800aa64((byte *)(iVar4 + -2),2,'\0',0);
      return;
    }
    if (param_1[2] == 0xa2) {
      if (param_1[3] == 0) {
        DAT_40020018._2_2_ = 0x10;
      }
      else {
        DAT_40020018._0_2_ = 0x10;
      }
    }
    break;
  case 5:
    local_28 = CONCAT11(local_28._1_1_,5);
    uVar3 = FUN_0800bbb4();
    local_28 = CONCAT11(uVar3,(undefined1)local_28);
    uVar2 = DAT_40020410;
    local_26[0] = (byte)uVar2 & 1;
    uVar6 = 3;
    goto LAB_0800cc3a;
  case 7:
    bVar1 = param_1[2];
    if (bVar1 < 0x4f) {
      iVar4 = FUN_08008798(&DAT_2000151a,0,0x3e);
      *(undefined1 *)(iVar4 + -2) = 0x73;
      *(byte *)(iVar4 + -1) = bVar1;
      FUN_0800aa64((byte *)(iVar4 + -2),3,'\0',0);
      return;
    }
    break;
  case 8:
    local_28 = 0x7608;
    itoa(1,local_26,0x10);
    local_26[1] = 0x2e;
    itoa(0,local_26 + 2,0x10);
    local_23 = 0x2e;
    itoa(0,auStack_22,0x10);
    auStack_22[1] = 0x20;
    memcpy((undefined4 *)(auStack_22 + 2),(undefined4 *)"2024-07-09-13:57:36",0x14);
    uVar6 = 0x1c;
    goto LAB_0800cc3a;
  case 9:
    local_28 = 0xc09;
    memcpy((undefined4 *)local_26,(undefined4 *)0x1fff7a10,4);
    memcpy((undefined4 *)auStack_22,(undefined4 *)0x1fff7a20,4);
    memcpy(auStack_1e,(undefined4 *)0x1fff7a30,4);
    uVar6 = 0xe;
LAB_0800cc3a:
    FUN_0800cb44((undefined4 *)&local_28,uVar6);
  }
  return;
}

