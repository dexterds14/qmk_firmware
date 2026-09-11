// FUN_08013ba4 @ 0x08013ba4  size=20  body=[[08013ba4, 08013bb7]]

void FUN_08013ba4(int *param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013b40(param_1);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

