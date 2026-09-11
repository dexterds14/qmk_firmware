// FUN_0800e504 @ 0x0800e504  size=40  body=[[0800e504, 0800e52b]]

void FUN_0800e504(char param_1,byte param_2)

{
  if ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0) {
    DAT_200016a4 = param_2 | param_1 << 3;
    FUN_0800dc64();
    FUN_0800e4fc((uint)(DAT_200016a4 >> 3));
    return;
  }
  FUN_0800dc64();
  return;
}

