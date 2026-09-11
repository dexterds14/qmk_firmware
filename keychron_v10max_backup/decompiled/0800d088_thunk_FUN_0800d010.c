// thunk_FUN_0800d010 @ 0x0800d088  size=4  body=[[0800d088, 0800d08b]]

void thunk_FUN_0800d010(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x22;
  if ((uVar1 == 0) && (DAT_200015de != '\0')) {
    thunk_FUN_08011378(0,0,0);
    DAT_200015de = '\0';
  }
  else {
    if ((param_1 & 0xffffff88) == 0) {
      if (DAT_200015dd != '\0') {
        thunk_FUN_08011378(0,0,0);
        DAT_200015dd = '\0';
      }
      if (uVar1 == 0) {
        return;
      }
    }
    else if (uVar1 == 0) goto LAB_0800d030;
    if (DAT_200015de == '\0') {
      thunk_FUN_08011378(0xff,0xff,0xff);
      DAT_200015de = '\x01';
    }
  }
  if ((param_1 & 0xffffff88) == 0) {
    return;
  }
LAB_0800d030:
  if (DAT_200015dd == '\0') {
    thunk_FUN_08011378(0xff,0xff,0);
    DAT_200015dd = '\x01';
  }
  return;
}

