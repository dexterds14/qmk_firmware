// FUN_0800e3ec @ 0x0800e3ec  size=22  body=[[0800e3ec, 0800e401]]

void FUN_0800e3ec(uint param_1)

{
  if ((param_1 & ~(uint)DAT_200016a6) != 0) {
    DAT_200016a6 = DAT_200016a6 | (byte)param_1;
    FUN_0800e3e4(param_1);
  }
  return;
}

