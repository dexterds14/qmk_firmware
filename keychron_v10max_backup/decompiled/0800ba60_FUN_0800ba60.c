// FUN_0800ba60 @ 0x0800ba60  size=52  body=[[0800ba60, 0800ba93]]

void FUN_0800ba60(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  int local_10;
  int iStack_c;
  undefined4 uStack_8;
  
  local_10 = param_1;
  uStack_8 = param_3;
  if (param_1 == 0) {
    if (DAT_20004ae4 == '\x04') {
      iStack_c = param_1;
      (*DAT_20000ecc)(&local_10);
    }
  }
  else {
    iStack_c = param_2;
    puVar1 = (undefined *)FUN_0801212c();
    if (puVar1 != &DAT_20000ec8) {
      FUN_08012120(&DAT_20000ec8);
      return;
    }
  }
  return;
}

