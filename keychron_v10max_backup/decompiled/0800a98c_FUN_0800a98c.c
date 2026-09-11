// FUN_0800a98c @ 0x0800a98c  size=130  body=[[0800a98c, 0800aa0d]]

void FUN_0800a98c(int param_1)

{
  if (param_1 == 0) {
    FUN_08015338((uint *)&DAT_40020800,0x10,1);
    DAT_4002081a = 0x10;
    FUN_08013a7a(100);
    DAT_40020818 = 0x10;
  }
  if (DAT_20004b50 == '\0') {
    FUN_08015338((uint *)&DAT_40020000,0x20,1);
    DAT_40020018._0_2_ = 0x20;
    FUN_08015338((uint *)&DAT_40020000,0x20,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x282);
    if (param_1 != 0) {
      thunk_FUN_080163c8();
      return;
    }
    thunk_FUN_080163c8();
  }
  FUN_08015338((uint *)&DAT_40020000,0x10,1);
  DAT_40020018._0_2_ = 0x10;
  FUN_08015338((uint *)&DAT_40020400,2,0x20);
  return;
}

