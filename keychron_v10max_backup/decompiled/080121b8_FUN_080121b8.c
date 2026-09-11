// FUN_080121b8 @ 0x080121b8  size=36  body=[[080121b8, 080121db]]

void FUN_080121b8(uint param_1)

{
  if (DAT_20002024 != param_1) {
    DAT_20002024 = (ushort)param_1;
    if (DAT_20002028 != 0) {
      DAT_2000201f = (undefined1)param_1;
      DAT_20002020 = (undefined1)(param_1 >> 8);
      DAT_2000201e = 4;
                    // WARNING: Could not recover jumptable at 0x080121d8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(DAT_20002028 + 0x10))();
      return;
    }
  }
  return;
}

