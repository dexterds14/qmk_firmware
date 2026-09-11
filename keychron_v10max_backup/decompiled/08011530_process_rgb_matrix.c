// process_rgb_matrix @ 0x08011530  size=128  body=[[08011530, 0801154f] [08011566, 080115c5]]

// VERIFIED: switch over 0x7820..0x783x (QK_RGB_MATRIX_* keycodes)

undefined1 process_rgb_matrix(undefined4 param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  code *UNRECOVERED_JUMPTABLE;
  code *UNRECOVERED_JUMPTABLE_00;
  
  if (*(char *)(param_2 + 5) != '\0') {
switchD_0801154c_caseD_782f:
    return 1;
  }
  bVar1 = FUN_0800e310();
  switch(param_1) {
  case 0x7820:
    FUN_08010eb4();
    return 0;
  case 0x7821:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010d8d;
    UNRECOVERED_JUMPTABLE = (code *)0x8010d65;
    break;
  case 0x7822:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010d65;
    UNRECOVERED_JUMPTABLE = (code *)0x8010d8d;
    break;
  case 0x7823:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010df1;
    UNRECOVERED_JUMPTABLE = (code *)0x8010dcd;
    break;
  case 0x7824:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010dcd;
    UNRECOVERED_JUMPTABLE = (code *)0x8010df1;
    break;
  case 0x7825:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010e45;
    UNRECOVERED_JUMPTABLE = (code *)0x8010e1d;
    break;
  case 0x7826:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010e1d;
    UNRECOVERED_JUMPTABLE = (code *)0x8010e45;
    break;
  case 0x7827:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f55;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f15;
    break;
  case 0x7828:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f15;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f55;
    break;
  case 0x7829:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f91;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f75;
    break;
  case 0x782a:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f75;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f91;
    break;
  case 0x782b:
    uVar2 = 1;
    goto LAB_080115b0;
  case 0x782c:
    uVar2 = 2;
    goto LAB_080115b0;
  case 0x782d:
    uVar2 = 5;
    goto LAB_080115b0;
  case 0x782e:
    uVar2 = 10;
LAB_080115b0:
    FUN_08010d40(uVar2);
    return 0;
  case 0x782f:
  case 0x7830:
  case 0x7831:
  case 0x7832:
  case 0x7833:
  case 0x7834:
    goto switchD_0801154c_caseD_782f;
  default:
    goto switchD_0801154c_caseD_782f;
  }
  FUN_08011528(bVar1 & 0x22,UNRECOVERED_JUMPTABLE,UNRECOVERED_JUMPTABLE_00);
switchD_0801154c_caseD_782f:
  return 0;
}

