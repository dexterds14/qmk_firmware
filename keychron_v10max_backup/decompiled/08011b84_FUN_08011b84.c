// FUN_08011b84 @ 0x08011b84  size=164  body=[[08011b84, 08011bb9] [08011bce, 08011c3b]]

void FUN_08011b84(int param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (DAT_2000200e == 0) {
    uVar2 = FUN_08012574();
    DAT_2000200e = (short)uVar2;
  }
  if (((DAT_20002015 != 0 || DAT_20002016 != 0) || DAT_20002018 != '\0') || DAT_20002017 != '\0') {
    uVar2 = FUN_08012574();
    DAT_2000200e = (short)uVar2 + -0xa0;
  }
  switch(param_1) {
  case 0xcd:
    bVar1 = FUN_08011a8c();
    DAT_20002016 = -bVar1;
    break;
  case 0xce:
    DAT_20002016 = FUN_08011a8c();
    break;
  case 0xcf:
    bVar1 = FUN_08011a8c();
    DAT_20002015 = -bVar1;
    break;
  case 0xd0:
    DAT_20002015 = FUN_08011a8c();
    break;
  case 0xd1:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xd8:
    DAT_20002014 = (byte)(1 << (param_1 - 0xd1U & 0xff)) | DAT_20002014;
    break;
  case 0xd9:
    uVar3 = FUN_08011b14();
    DAT_20002017 = (char)uVar3;
    break;
  case 0xda:
    uVar3 = FUN_08011b14();
    DAT_20002017 = -(char)uVar3;
    break;
  case 0xdb:
    uVar3 = FUN_08011b14();
    DAT_20002018 = -(char)uVar3;
    break;
  case 0xdc:
    uVar3 = FUN_08011b14();
    DAT_20002018 = (char)uVar3;
    break;
  case 0xdd:
    DAT_20002012 = DAT_20002012 | 1;
    break;
  case 0xde:
    DAT_20002012 = DAT_20002012 | 2;
    break;
  case 0xdf:
    DAT_20002012 = DAT_20002012 | 4;
  }
  return;
}

