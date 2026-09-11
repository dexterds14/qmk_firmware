// FUN_08011528 @ 0x08011528  size=6  body=[[08011528, 0801152d]]

void FUN_08011528(int param_1,undefined *UNRECOVERED_JUMPTABLE,undefined *UNRECOVERED_JUMPTABLE_00)

{
  if (param_1 != 0) {
                    // WARNING: Could not recover jumptable at 0x0801152a. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)UNRECOVERED_JUMPTABLE_00)();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x0801152c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}

