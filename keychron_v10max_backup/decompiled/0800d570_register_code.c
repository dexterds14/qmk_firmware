// register_code @ 0x0800d570  size=140  body=[[0800d570, 0800d5fb]]

// VERIFIED shape of register_code(): 0->return; (kc-4)&0xff<0xA1 basic -> add_key path
// 0x08012238/0x08012350/0x0801231C; (kc+0x20)&0xff<8 mods 0xE0-0xE7 -> 0x0800E31C(1<<(kc&7));
// 0xA5-0xA7 system -> 0x08012188(kc-0x24); 0xA8-0xC2 consumer -> 0x080121B8(u16 table @0x08016EC8);
// 0xCD-0xDF mouse -> 0x08011B84+0x08011D68; then send 0x0800E4DC

void register_code(uint param_1)

{
  bool bVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    return;
  }
  if ((param_1 - 4 & 0xff) < 0xa1) {
    bVar1 = FUN_08012238(param_1);
    if (bVar1) {
      FUN_08012350(param_1);
      FUN_0800e4dc();
    }
    FUN_0801231c(param_1);
  }
  else {
    if (7 < (param_1 + 0x20 & 0xff)) {
      if ((param_1 + 0x5b & 0xff) < 3) {
        FUN_08012188(param_1 - 0x24 & 0xffff);
        return;
      }
      uVar2 = param_1 + 0x58 & 0xff;
      if (0x1a < uVar2) {
        if (0x12 < (param_1 + 0x33 & 0xff)) {
          return;
        }
        FUN_08011b84(param_1);
        FUN_08011d68();
        return;
      }
      FUN_080121b8((uint)*(ushort *)(&consumer_usage_table + uVar2 * 2));
      return;
    }
    FUN_0800e31c((byte)(1 << (param_1 & 7)));
  }
  FUN_0800e4dc();
  return;
}

