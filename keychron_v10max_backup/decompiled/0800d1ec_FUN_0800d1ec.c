// FUN_0800d1ec @ 0x0800d1ec  size=104  body=[[0800d1ec, 0800d253]]

void FUN_0800d1ec(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0800d1c4(param_1);
  if (iVar1 == 3) {
    FUN_0800dc34();
LAB_0800d244:
    FUN_0800dc58();
    return;
  }
  if (iVar1 == 4) {
    FUN_0800dc34();
    goto LAB_0800d244;
  }
  if (iVar1 != 2) {
    return;
  }
  uVar2 = FUN_0800dc3c(4);
  if (uVar2 == 0) {
    if (user_td0_flag != '\0') {
      FUN_0800dc34();
      FUN_0800dc58();
      user_td0_flag = 0;
      return;
    }
    uVar2 = FUN_0800dc3c(1);
    if (uVar2 == 0) {
      user_td0_flag = '\x01';
      goto LAB_0800d212;
    }
  }
  else {
    DAT_200015e9 = 1;
  }
  FUN_0800dc34();
LAB_0800d212:
  FUN_0800cdda();
  return;
}

