// FUN_080136a4 @ 0x080136a4  size=72  body=[[080136a4, 080136eb]]

void FUN_080136a4(int *param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_08013cfa();
  if ((undefined4 **)DAT_200049f0 == &DAT_200049f0) {
    FUN_0801364c(param_1,iVar1,param_2);
    return;
  }
  uVar2 = param_2 + (iVar1 - DAT_200049fc);
  if (CARRY4(param_2,iVar1 - DAT_200049fc)) {
    uVar2 = param_2;
  }
  if (uVar2 < (uint)DAT_200049f0[2]) {
    FUN_08013616(iVar1,param_2);
  }
  FUN_080135ec((int *)&DAT_200049f0,param_1,uVar2);
  return;
}

