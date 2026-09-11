// unregister_code @ 0x0800d600  size=114  body=[[0800d600, 0800d671]]

// VERIFIED mirror of register_code: 0x08012350 del_key, 0x0800E32C del_mods, 0x08012188(0),
// 0x080121B8(0), 0x08011C48 mousekey_off

void unregister_code(uint param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return;
  }
  if ((param_1 - 4 & 0xff) < 0xa1) {
    FUN_08012350(param_1);
  }
  else {
    if (7 < (param_1 + 0x20 & 0xff)) {
      if ((param_1 + 0x5b & 0xff) < 3) {
        FUN_08012188(0);
        return;
      }
      if (0x1a < (param_1 + 0x58 & 0xff)) {
        if (0x12 < (param_1 + 0x33 & 0xff)) {
          return;
        }
        FUN_08011c48(param_1);
        FUN_08011d68();
        return;
      }
      FUN_080121b8(0);
      return;
    }
    FUN_0800e32c((byte)(1 << (param_1 & 7)));
  }
  FUN_0800e4dc();
  return;
}

