// FUN_08012958 @ 0x08012958  size=42  body=[[08012958, 08012981]]

void FUN_08012958(int param_1)

{
  if (*(short *)(param_1 + 0x4a) == 2) {
    if ((DAT_20002064 == '\x01') || (DAT_20002064 == '\x06')) {
      DAT_20002067 = DAT_20002065;
      return;
    }
  }
  else {
    DAT_20002067 = DAT_20002064;
  }
  return;
}

