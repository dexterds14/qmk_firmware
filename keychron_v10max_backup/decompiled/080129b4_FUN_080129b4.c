// FUN_080129b4 @ 0x080129b4  size=160  body=[[080129b4, 080129bf] [080129c6, 08012a59]]

void FUN_080129b4(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  
  switch(param_2) {
  case 0:
  case 3:
  case 4:
    iVar3 = FUN_0801298c((char)param_2);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    if (iVar3 == 0) {
      DAT_20000ec6 = 1;
    }
    FUN_08012e46((int *)&DAT_20000f64);
    FUN_08012e46((int *)&DAT_2000100c);
    FUN_08012e46((int *)&DAT_200010b4);
    FUN_08012e6e((int *)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  default:
    return;
  case 2:
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08012e94((int *)&DAT_20000f64);
    FUN_08012e94((int *)&DAT_2000100c);
    FUN_08012e94((int *)&DAT_200010b4);
    FUN_08012eb4((int *)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (DAT_20002066 != '\0') {
      FUN_0801298c(5);
    }
    uVar2 = 2;
    break;
  case 5:
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08012e88((int)&DAT_20000f64);
    FUN_08012e88((int)&DAT_2000100c);
    FUN_08012e88((int)&DAT_200010b4);
    FUN_08012e8e((int)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    uVar2 = 5;
  }
  FUN_0801298c(uVar2);
  return;
}

