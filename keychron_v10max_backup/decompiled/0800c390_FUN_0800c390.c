// FUN_0800c390 @ 0x0800c390  size=134  body=[[0800c390, 0800c415]]

void FUN_0800c390(void)

{
  byte bVar1;
  
  if (DAT_200015b4 == '\x02') {
    if (DAT_200015ad < 0x1e) {
      DAT_200015a6 = 0xff;
      DAT_200015a5 = 0;
    }
    else {
      DAT_200015a6 = 0;
      DAT_200015a5 = 0xff;
    }
    DAT_200015a4 = 0;
    DAT_200015a8 = 3000;
    DAT_200015b4 = '\x03';
  }
  else if (DAT_200015b4 == '\x03') {
    DAT_200015b4 = '\0';
    FUN_0800b378();
    if ((DAT_200047cd == '\0') && (bVar1 = FUN_08010cf4(), bVar1 == 0)) {
      thunk_FUN_08010cd4();
    }
    FUN_0800bc70();
  }
  else if (DAT_200015b4 == '\x01') {
    if (DAT_200015ac < DAT_200015ad) {
      DAT_200015ac = DAT_200015ac + 10;
    }
    else {
      if (DAT_200015ac == 0) {
        DAT_200015ac = 10;
      }
      DAT_200015b4 = '\x02';
    }
  }
  DAT_200015b0 = FUN_08012508();
  return;
}

