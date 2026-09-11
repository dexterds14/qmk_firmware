// FUN_08011008 @ 0x08011008  size=58  body=[[08011008, 08011041]]

void FUN_08011008(int param_1)

{
  uint uVar1;
  
  DAT_20000eb4 = (undefined1)param_1;
  DAT_20000eb5 = (byte)(((uint)DAT_20004808 << 0x1e) >> 0x1e);
  if (DAT_20001f4d != '\0') {
    FUN_08010fe4();
  }
  thunk_FUN_080114fc();
  if (((param_1 == 0) && (DAT_20001f4d == '\0')) && (uVar1 = FUN_0800b81c(), uVar1 != 0)) {
    FUN_08010fcc();
  }
  DAT_20000eb0 = 3;
  return;
}

