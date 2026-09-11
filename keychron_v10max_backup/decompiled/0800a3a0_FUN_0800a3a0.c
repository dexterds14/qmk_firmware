// FUN_0800a3a0 @ 0x0800a3a0  size=44  body=[[0800a3a0, 0800a3cb]]

void FUN_0800a3a0(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20001501 == '\x03') {
      if (DAT_20000c94 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a3be. Too many branches
                    // WARNING: Treating indirect jump as call
        (*DAT_20000c94)(param_1);
        return;
      }
    }
    else if (DAT_20001501 != '\0') {
      FUN_0800a298();
      return;
    }
  }
  return;
}

