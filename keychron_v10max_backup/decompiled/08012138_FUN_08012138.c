// FUN_08012138 @ 0x08012138  size=12  body=[[08012138, 08012143]]

void FUN_08012138(void)

{
  if (DAT_20002028 != (undefined4 *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08012140. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)*DAT_20002028)();
    return;
  }
  return;
}

