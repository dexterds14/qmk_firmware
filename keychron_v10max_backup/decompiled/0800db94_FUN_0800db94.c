// FUN_0800db94 @ 0x0800db94  size=90  body=[[0800db52, 0800dbab]]

bool FUN_0800db94(undefined2 *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  if (*(char *)(param_1 + 2) == '\0') {
    return false;
  }
  uVar1 = FUN_0800ddf8(*param_1,param_2);
  uVar2 = (uVar1 & 0xffff) >> 0xc;
  uVar1 = uVar1 & 0xff;
  if (uVar2 == 6) {
    if (uVar1 < 0xe8) {
      return true;
    }
    bVar3 = uVar1 == 0xf1;
  }
  else {
    if (uVar2 < 7) {
      uVar2 = uVar2 + 0xe;
    }
    else {
      uVar2 = uVar2 + 6;
    }
    if (1 < (uVar2 & 0xf)) {
      return false;
    }
    if (uVar1 == 0xf0) {
      return true;
    }
    if (uVar1 < 0xf1) {
      return uVar1 < 0xe8;
    }
    bVar3 = uVar1 == 0xf4;
  }
  return bVar3;
}

