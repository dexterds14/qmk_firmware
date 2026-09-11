// FUN_0800a458 @ 0x0800a458  size=80  body=[[0800a458, 0800a4a7]]

uint FUN_0800a458(uint param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_2c [2];
  undefined2 local_2a;
  
  if (DAT_20001501 == '\x03') {
    bVar1 = FUN_0800a874();
    if ((bVar1) && (bVar1 = FUN_0800a89c(), bVar1)) {
      if (DAT_20000c8c != (code *)0x0) {
        (*DAT_20000c8c)(param_1);
      }
      uVar2 = FUN_0800a88c();
      return uVar2;
    }
    local_2c[0] = 3;
    local_2a = (undefined2)param_1;
    bVar1 = FUN_0800a808((undefined4 *)local_2c);
    param_1 = (uint)bVar1;
  }
  else if (DAT_20001501 != '\0') {
    uVar2 = FUN_0800a298();
    return uVar2;
  }
  return param_1;
}

