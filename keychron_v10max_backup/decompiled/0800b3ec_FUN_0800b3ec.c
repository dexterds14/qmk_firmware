// FUN_0800b3ec @ 0x0800b3ec  size=38  body=[[0800b3ec, 0800b411]]

void FUN_0800b3ec(int param_1)

{
  if (param_1 == 0) {
    DAT_4002041a = 0x1000;
  }
  else if (DAT_20001568 == 0) {
    DAT_20001568 = FUN_08012508();
    DAT_2000156c = DAT_20001568;
  }
  else {
    DAT_20001568 = FUN_08012508();
  }
  return;
}

