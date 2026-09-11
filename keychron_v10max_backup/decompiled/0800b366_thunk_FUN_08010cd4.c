// thunk_FUN_08010cd4 @ 0x0800b366  size=4  body=[[0800b366, 0800b369]]

void thunk_FUN_08010cd4(void)

{
  if ((DAT_20004808 & 3) != 0) {
    DAT_20000eb0 = 0;
  }
  DAT_20004808 = DAT_20004808 & 0xfc;
  return;
}

