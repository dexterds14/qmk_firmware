// FUN_08010a4c @ 0x08010a4c  size=456  body=[[08010a4c, 08010a91] [08010aaa, 08010c2b]]

void FUN_08010a4c(uint param_1,undefined4 param_2,uint param_3)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 extraout_r1;
  uint uVar5;
  uint extraout_r2;
  undefined1 uVar6;
  uint uVar7;
  uint extraout_r3;
  undefined4 local_28;
  
  if (DAT_20000eb4 == param_1) {
    DAT_20000eb3 = '\0';
    if ((DAT_20004808 & 3) != DAT_20000eb5) {
      DAT_20000eb3 = '\x01';
    }
  }
  else {
    DAT_20000eb3 = '\x01';
  }
  uVar5 = (uint)DAT_20000eb2;
  uVar7 = (uint)DAT_2000480d;
  if (uVar5 != uVar7) {
    DAT_20000eb2 = DAT_2000480d;
    thunk_FUN_08011378(0,0,0);
    param_2 = extraout_r1;
    uVar5 = extraout_r2;
    uVar7 = extraout_r3;
  }
  switch(param_1) {
  case 0:
    if (DAT_20000eb3 != '\0') {
      thunk_FUN_08011378(0,0,0);
      FUN_0801016e();
    }
  default:
    uVar5 = 0;
    break;
  case 1:
    bVar1 = FUN_08010788(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 2:
    bVar1 = FUN_080107fc(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 3:
    bVar1 = FUN_08010284(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 4:
    bVar1 = FUN_08010410(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 5:
    bVar1 = FUN_0801041c(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 6:
    bVar1 = FUN_08010428(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 7:
    bVar1 = FUN_08010434(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 8:
    bVar1 = FUN_08010290(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 9:
    bVar1 = FUN_08010360(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 10:
    bVar1 = FUN_0801036c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xb:
    bVar1 = FUN_0801029c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xc:
    bVar1 = FUN_08010500(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xd:
    bVar1 = FUN_0801050c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xe:
    bVar1 = FUN_080108b0(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xf:
    uVar5 = FUN_0801017e(DAT_20000eb1);
    if (DAT_20001f14 < DAT_20004810) {
      uVar2 = FUN_0800f7f8();
      uVar7 = (short)uVar2 * 0x58 >> 8;
      if (((&DAT_20000e23)[uVar7] & DAT_20000eb2) != 0) {
        uVar2 = FUN_0800f7f8();
        if ((int)((uint)uVar2 << 0x1e) < 0) {
          local_28 = param_3 & 0xffff0000;
          uVar6 = 0;
        }
        else {
          uVar2 = FUN_0800f7f8();
          uVar3 = FUN_0800f7f8();
          local_28._2_2_ = (undefined2)(param_3 >> 0x10);
          local_28._0_2_ = CONCAT11((char)((int)((uint)uVar3 << 0x10) >> 0x11) + '\x7f',(char)uVar2)
          ;
          uVar6 = DAT_2000480b;
        }
        local_28._0_3_ = CONCAT12(uVar6,(undefined2)local_28);
        uVar4 = FUN_0800fd30(local_28);
        FUN_0800fe78(uVar7,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
        uVar7 = DAT_2000480c + 0x10;
        if (0xfe < uVar7) {
          uVar7 = 0xff;
        }
        DAT_20001f14 = 500 / (uVar7 >> 4) + DAT_20004810;
      }
    }
    uVar5 = (uint)((uVar5 & 0xffff) >> 8 < 0x58);
    break;
  case 0x10:
    bVar1 = FUN_08010920(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x11:
    uVar5 = FUN_0800fef0(0x20000eb1);
    break;
  case 0x12:
    bVar1 = FUN_080105f8(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x13:
    bVar1 = FUN_08010730(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x14:
    bVar1 = FUN_08010740(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x15:
    bVar1 = FUN_08010750(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x16:
    bVar1 = FUN_0801076c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
  }
  DAT_20000eb1 = DAT_20000eb1 + '\x01';
  if (((uVar5 == 0) && (DAT_20000eb0 = 2, DAT_20000eb3 == '\0')) && (param_1 == 0)) {
    DAT_20000eb0 = 3;
  }
  return;
}

