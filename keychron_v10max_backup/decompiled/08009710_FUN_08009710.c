// FUN_08009710 @ 0x08009710  size=68  body=[[08009710, 08009753]]

uint FUN_08009710(undefined4 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_200014f4 == 0) {
    DAT_200014f4 = FUN_080166a4(param_1,0);
  }
  uVar1 = FUN_080166a4(param_1,param_2);
  if ((uVar1 != 0xffffffff) &&
     ((uVar3 = uVar1 + 3 & 0xfffffffc, uVar1 == uVar3 ||
      (iVar2 = FUN_080166a4(param_1,uVar3 - uVar1), iVar2 != -1)))) {
    return uVar3;
  }
  return 0xffffffff;
}

