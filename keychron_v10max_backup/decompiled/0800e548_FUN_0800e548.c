// FUN_0800e548 @ 0x0800e548  size=44  body=[[0800e548, 0800e573]]

void FUN_0800e548(byte param_1)

{
  byte bVar1;
  
  bVar1 = DAT_200016a4;
  DAT_200016a4 = DAT_200016a4 & ~param_1;
  if ((((DAT_200016a4 & 7) == 0) && (DAT_200016a4 != bVar1)) &&
     ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0)) {
    FUN_0800dc7c();
    FUN_0800e534();
    return;
  }
  return;
}

