// FUN_08012150 @ 0x08012150  size=12  body=[[08012150, 0801215b]]

void FUN_08012150(void)

{
  if (DAT_20002028 != 0) {
                    // WARNING: Could not recover jumptable at 0x08012158. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(DAT_20002028 + 4))();
    return;
  }
  return;
}

