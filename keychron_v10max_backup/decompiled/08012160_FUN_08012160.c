// FUN_08012160 @ 0x08012160  size=16  body=[[08012160, 0801216f]]

void FUN_08012160(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = DAT_20002028;
  if (DAT_20002028 != 0) {
    *param_1 = 6;
                    // WARNING: Could not recover jumptable at 0x0801216c. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(iVar1 + 8))();
    return;
  }
  return;
}

