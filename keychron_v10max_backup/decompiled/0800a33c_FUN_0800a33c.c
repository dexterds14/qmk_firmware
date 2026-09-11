// FUN_0800a33c @ 0x0800a33c  size=88  body=[[0800a33c, 0800a393]]

void FUN_0800a33c(undefined4 *param_1)

{
  bool bVar1;
  undefined1 local_34 [2];
  undefined4 auStack_32 [9];
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20001501 == '\x04') {
      if (DAT_20001500 == '\0') {
        return;
      }
    }
    else if (DAT_20001501 != '\x03') {
      if (DAT_20001501 == '\0') {
        return;
      }
      FUN_0800a298();
      return;
    }
    if (DAT_20000c88 != (code *)0x0) {
      local_34[0] = 2;
      memcpy(auStack_32,param_1,0x20);
      FUN_0800a808((undefined4 *)local_34);
      (*DAT_20000c88)((int)param_1 + 1);
    }
  }
  return;
}

