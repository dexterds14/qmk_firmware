// FUN_0800a570 @ 0x0800a570  size=396  body=[[0800a570, 0800a6fb]]

void FUN_0800a570(void)

{
  int iVar1;
  byte bVar2;
  code *pcVar3;
  byte bVar4;
  bool bVar5;
  char cVar6;
  byte bVar7;
  uint extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 uVar8;
  undefined4 extraout_r2_00;
  uint uVar9;
  uint uVar10;
  
LAB_0800a578:
  bVar4 = DAT_20001501;
  uVar9 = (uint)DAT_20002591;
  bVar5 = false;
switchD_0800a6f8_default:
  if (DAT_20002590 == uVar9) {
    if (bVar5) {
      DAT_20002591 = DAT_20002590;
    }
    return;
  }
  iVar1 = uVar9 * 2;
  bVar7 = (&DAT_20002571)[uVar9 * 2];
  uVar10 = (uint)bVar7;
  uVar9 = uVar9 + 1 & 0xf;
  bVar5 = true;
  bVar2 = (byte)uVar9;
  switch((byte)(&DAT_20002570)[iVar1] - 1) {
  case 0:
    goto switchD_0800a6f8_caseD_0;
  case 1:
    DAT_20001501 = 4;
    DAT_20001503 = bVar7;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(4,uVar10);
    FUN_0800a42c();
    goto LAB_0800a578;
  case 2:
    DAT_20001501 = 5;
    DAT_20001503 = bVar7;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(5,uVar10);
    FUN_0800a42e();
    goto LAB_0800a578;
  case 3:
    DAT_20001501 = 3;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(3,uVar10);
    DAT_20001503 = bVar7;
    FUN_0800db44();
    FUN_0800a430();
    bVar5 = FUN_0800c144();
    if (bVar5) {
      FUN_0800b3ec(1);
    }
    pcVar3 = DAT_20000c98;
    if (DAT_20000c98 != (code *)0x0) {
      cVar6 = FUN_0800c0ec();
      (*pcVar3)((int)cVar6);
    }
    goto LAB_0800a578;
  case 4:
    DAT_20001502 = 0;
    DAT_20002591 = bVar2;
    bVar7 = FUN_0800bbb4();
    if ((bVar7 & 6) != 0) {
      FUN_0800b91c();
    }
    uVar9 = 2;
    DAT_20001501 = 2;
    if (bVar4 == 3) {
      FUN_0800bc70();
      uVar9 = 6;
    }
    FUN_0800b6ac(uVar9,uVar10);
    FUN_0800a7cc();
    DAT_20001504 = 0;
    FUN_0800c598();
    FUN_0800b3ec(0);
    uVar9 = extraout_r1;
    uVar8 = extraout_r2;
    break;
  case 5:
    DAT_200047d4 = DAT_200047d4 & 0xff7f;
    DAT_20001500 = 1;
    DAT_20002591 = bVar2;
    FUN_0800a432();
    goto LAB_0800a578;
  case 6:
    DAT_20002591 = bVar2;
    DAT_200047d4 = FUN_0800e600((uint)DAT_20002590,1,(byte)(&DAT_20002570)[iVar1] - 1);
    DAT_20001500 = 0;
    FUN_0800a434();
    goto LAB_0800a578;
  case 7:
    DAT_20001502 = 0;
    DAT_20002591 = bVar2;
    if (DAT_20001501 != 4) goto LAB_0800a578;
    DAT_20001501 = 6;
    FUN_0800a436();
    FUN_0800b6ac((uint)DAT_20001501,0);
    FUN_0800b3ec(0);
    uVar9 = extraout_r1_00;
    uVar8 = extraout_r2_00;
    break;
  case 8:
    DAT_20000c70 = 0;
    DAT_20002591 = bVar2;
    goto LAB_0800a578;
  case 9:
    DAT_20001502 = bVar7;
    DAT_20002591 = bVar2;
    goto LAB_0800a578;
  case 10:
    DAT_20002591 = bVar2;
    FUN_0800a8bc(bVar7);
    goto LAB_0800a578;
  default:
    goto switchD_0800a6f8_default;
  }
  FUN_0800b420(0,uVar9,uVar8);
  goto LAB_0800a578;
switchD_0800a6f8_caseD_0:
  DAT_20001501 = 0;
  DAT_20002591 = bVar2;
  thunk_FUN_0800c54c(uVar10,1,0,&DAT_20001501);
  goto LAB_0800a578;
}

