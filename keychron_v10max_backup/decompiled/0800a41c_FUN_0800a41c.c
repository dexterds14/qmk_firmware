// FUN_0800a41c @ 0x0800a41c  size=10  body=[[0800a41c, 0800a425]]

void FUN_0800a41c(void)

{
  if (DAT_20000c80 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a422. Too many branches
                    // WARNING: Treating indirect jump as call
    (*DAT_20000c80)();
    return;
  }
  return;
}

