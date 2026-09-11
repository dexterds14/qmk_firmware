// thunk_FUN_08013a60 @ 0x08013a70  size=10  body=[[08013a70, 08013a79]]

void thunk_FUN_08013a60(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013a60(param_1);
  return;
}

