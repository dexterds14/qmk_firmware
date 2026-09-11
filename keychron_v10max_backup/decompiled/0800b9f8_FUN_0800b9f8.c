// FUN_0800b9f8 @ 0x0800b9f8  size=90  body=[[0800b9f8, 0800ba51]]

void FUN_0800b9f8(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int local_18;
  int iStack_14;
  undefined4 uStack_10;
  
  local_18 = param_1;
  iStack_14 = param_2;
  uStack_10 = param_3;
  if (param_1 != 0) {
    FUN_08012120(&DAT_20000c5c);
    FUN_0800a41c();
    iVar2 = FUN_08012508();
    while (uVar3 = FUN_0801258c(iVar2), uVar3 < 0x32) {
      (*DAT_20000c9c)();
    }
    FUN_0800a3d4(0x18,0);
    return;
  }
  FUN_0800b3c4();
  cVar1 = FUN_0800a77c();
  if ((cVar1 == '\x03') && (DAT_2000157a == '\x04')) {
    local_18 = param_1;
    iStack_14 = param_1;
    (*DAT_20000c60)(&local_18);
  }
  return;
}

