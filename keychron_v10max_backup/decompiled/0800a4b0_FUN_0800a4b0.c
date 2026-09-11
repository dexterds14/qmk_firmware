// FUN_0800a4b0 @ 0x0800a4b0  size=78  body=[[0800a438, 0800a44f] [0800a4b0, 0800a4e5]]

uint FUN_0800a4b0(char *param_1)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = FUN_0800c158();
  if (bVar1 == 0) {
    if (*param_1 == '\x03') {
      if (DAT_20001501 == '\x03') {
        if (DAT_20000c90 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a446. Too many branches
                    // WARNING: Treating indirect jump as call
          uVar2 = (*DAT_20000c90)();
          return uVar2;
        }
      }
      else if (DAT_20001501 != '\0') {
        uVar2 = FUN_0800a298();
        return uVar2;
      }
      return (uint)*(ushort *)(param_1 + 1);
    }
    if (*param_1 == '\x04') {
      uVar2 = FUN_0800a458((uint)*(ushort *)(param_1 + 1));
      return uVar2;
    }
  }
  return (uint)bVar1;
}

