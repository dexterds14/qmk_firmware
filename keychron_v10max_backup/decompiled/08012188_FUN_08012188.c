// FUN_08012188 @ 0x08012188  size=36  body=[[08012188, 080121ab]]

void FUN_08012188(uint param_1)

{
  if (DAT_20002026 != param_1) {
    DAT_20002026 = (ushort)param_1;
    if (DAT_20002028 != 0) {
      DAT_20002022 = (undefined1)param_1;
      DAT_20002023 = (undefined1)(param_1 >> 8);
      DAT_20002021 = 3;
                    // WARNING: Could not recover jumptable at 0x080121a8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(DAT_20002028 + 0x10))();
      return;
    }
  }
  return;
}

