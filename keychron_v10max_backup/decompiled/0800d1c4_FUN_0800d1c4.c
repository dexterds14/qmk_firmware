// FUN_0800d1c4 @ 0x0800d1c4  size=38  body=[[0800d1c4, 0800d1e9]]

undefined4 FUN_0800d1c4(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 2) != '\x01') {
    if (*(char *)(param_1 + 2) == '\x02') {
      uVar1 = 4;
    }
    else {
      uVar1 = 1;
    }
    return uVar1;
  }
  if (-1 < (int)((uint)*(byte *)(param_1 + 5) << 0x1f)) {
    return 2;
  }
  if ((*(byte *)(param_1 + 5) & 4) == 0) {
    uVar1 = 3;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

