// FUN_08011d68 @ 0x08011d68  size=58  body=[[08011d68, 08011d91] [08012174, 08012183]]

void FUN_08011d68(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012574();
  if (DAT_20002015 != '\0' || DAT_20002016 != '\0') {
    DAT_2000200c = (short)uVar1;
  }
  if (DAT_20002017 != '\0' || DAT_20002018 != '\0') {
    DAT_2000200a = (short)uVar1;
  }
  if (DAT_20002028 == 0) {
    return;
  }
  DAT_20002013 = 2;
                    // WARNING: Could not recover jumptable at 0x08012180. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(DAT_20002028 + 0xc))();
  return;
}

