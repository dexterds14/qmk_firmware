// FUN_08012a98 @ 0x08012a98  size=138  body=[[08012a98, 08012b21]]

void FUN_08012a98(void)

{
  undefined *puVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  uint uVar5;
  
LAB_08012a9e:
  uVar5 = (uint)DAT_200049ce;
  bVar3 = false;
switchD_08012b1e_caseD_1:
  if (uVar5 == DAT_200049cd) {
    if (bVar3) {
      DAT_200049ce = (byte)uVar5;
    }
    return;
  }
  bVar3 = true;
  puVar1 = &DAT_200049bd + uVar5;
  uVar5 = uVar5 + 1 & 0xf;
  bVar2 = (byte)uVar5;
  switch(*puVar1) {
  case 0:
    goto switchD_08012b1e_caseD_0;
  default:
    goto switchD_08012b1e_caseD_1;
  case 2:
    cVar4 = '\0';
    if (DAT_20004b33 != '\0') {
      cVar4 = '\x01';
    }
    break;
  case 3:
    cVar4 = '\0';
    break;
  case 4:
    DAT_20002066 = 1;
    DAT_200049ce = bVar2;
    FUN_08012424();
    goto LAB_08012a9e;
  case 5:
    DAT_20002066 = 0;
    DAT_200049ce = bVar2;
    FUN_080124b0();
    thunk_FUN_08012410(DAT_20004b33 != '\0');
    goto LAB_08012a9e;
  }
  DAT_200049ce = bVar2;
  FUN_08012410(cVar4);
  goto LAB_08012a9e;
switchD_08012b1e_caseD_0:
  DAT_200049ce = bVar2;
  FUN_0801243c();
  goto LAB_08012a9e;
}

