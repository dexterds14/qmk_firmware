// FUN_0800a2dc @ 0x0800a2dc  size=82  body=[[0800a2dc, 0800a32d]]

uint FUN_0800a2dc(undefined4 *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_2c [2];
  undefined4 auStack_2a [8];
  
  bVar1 = FUN_0800c158();
  uVar2 = (uint)bVar1;
  if (uVar2 == 0) {
    if (DAT_20001501 == '\x04') {
      if (DAT_20001500 == '\0') {
        return 0;
      }
    }
    else if (DAT_20001501 != '\x03') {
      if (DAT_20001501 == '\0') {
        return 0;
      }
      uVar2 = FUN_0800a298();
      return uVar2;
    }
    if (DAT_20000c84 != 0) {
      local_2c[0] = 1;
      memcpy(auStack_2a,param_1,8);
      bVar1 = FUN_0800a808((undefined4 *)local_2c);
      uVar2 = (uint)bVar1;
    }
  }
  return uVar2;
}

