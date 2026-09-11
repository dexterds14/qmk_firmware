// FUN_08014c54 @ 0x08014c54  size=36  body=[[08014c54, 08014c77]]

undefined4 FUN_08014c54(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x1c) + 0xc);
  *(uint *)(*(int *)(param_1 + 0x1c) + 0xc) = uVar2 & 0xffff;
  if ((int)(uVar2 << 0x1b) < 0) {
    uVar1 = 6;
  }
  else {
    uVar1 = 0;
    if ((uVar2 & 0x62) != 0) {
      if (*(char *)(param_1 + 4) == '\x04') {
        uVar1 = 3;
      }
      else {
        uVar1 = 4;
      }
      return uVar1;
    }
  }
  return uVar1;
}

