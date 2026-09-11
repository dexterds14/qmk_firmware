// FUN_0800b6ac @ 0x0800b6ac  size=292  body=[[0800b6ac, 0800b6ff] [0800b706, 0800b7d5]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0800b6ac(uint param_1,uint param_2)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  cVar2 = FUN_0800bbb4();
  if (cVar2 == '\x01') {
    return;
  }
  if (param_2 == 0x18) {
    param_2 = 0x11;
  }
  bVar1 = (byte)param_2;
  if ((DAT_20001559 == param_2) || (param_1 == 2)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
    DAT_20001559 = bVar1;
  }
  if (((DAT_20001558 == param_1) && (!bVar3)) && (param_1 != 5)) {
    return;
  }
  DAT_20001558 = (char)param_1;
  DAT_20001570 = FUN_08012508();
  FUN_0800b354();
  FUN_08010fa4();
  switch(param_1) {
  case 2:
    DAT_200047bc = 0;
    DAT_200047c0 = 100;
    DAT_200047c4 = 100;
    DAT_200047c8 = 600;
    _DAT_200047cc = 0;
    DAT_200047d0 = 0;
    FUN_0800b5d0((char *)&DAT_200047bc);
    bVar3 = FUN_0800c158();
    if (bVar3) {
LAB_0800b728:
      uVar4 = 1000;
      goto LAB_0800b72c;
    }
    goto LAB_0800b73a;
  case 3:
    if (DAT_20001578 != '\x03') {
      DAT_200047bc = 3;
      DAT_200047c0 = 2000;
      DAT_200047c4 = 0xfa;
      DAT_200047c8 = 2000;
      DAT_200047d0 = 0;
      _DAT_200047cc = (uint)CONCAT11(bVar1,1);
      FUN_0800b5d0((char *)&DAT_200047bc);
    }
    if (DAT_200047c8 == 0) goto LAB_0800b7aa;
    uVar5 = 600000;
    uVar4 = DAT_200047c8;
    goto LAB_0800b770;
  case 4:
    puVar6 = &DAT_08016778;
    break;
  case 5:
    puVar6 = &DAT_08016748;
    break;
  case 6:
    DAT_200047bc = 0;
    DAT_200047c0 = 100;
    DAT_200047c4 = 100;
    DAT_200047c8 = 600;
    _DAT_200047cc = 0;
    DAT_200047d0 = 0;
    FUN_0800b5d0((char *)&DAT_200047bc);
    bVar3 = FUN_0800ca74();
    if (!bVar3) goto LAB_0800b728;
    uVar4 = 3000;
    goto LAB_0800b72c;
  default:
    goto switchD_0800b6fc_default;
  }
  DAT_200047bc = *puVar6;
  DAT_200047c0 = puVar6[1];
  DAT_200047c4 = puVar6[2];
  DAT_200047c8 = puVar6[3];
  DAT_200047d0 = puVar6[5];
  DAT_200047cc_2 = (undefined2)((uint)puVar6[4] >> 0x10);
  DAT_200047cc = (undefined1)puVar6[4];
  _DAT_200047cc = CONCAT22(DAT_200047cc_2,CONCAT11(bVar1,DAT_200047cc)) | 0x8000;
  FUN_0800b5d0((char *)&DAT_200047bc);
LAB_0800b73a:
  if (DAT_200047c8 == 0) {
LAB_0800b7aa:
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = 40000;
    uVar5 = DAT_200047c8;
LAB_0800b770:
    if (uVar4 < uVar5) {
      uVar4 = uVar5;
    }
  }
LAB_0800b72c:
  FUN_08010f98(uVar4);
switchD_0800b6fc_default:
  DAT_20001578 = (char)param_1;
  return;
}

