// FUN_08013fd2 @ 0x08013fd2  size=32  body=[[08013fd2, 08013ff1]]

void FUN_08013fd2(int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  if ((*(int *)(param_1 + 0x28) != 0) &&
     (iVar2 = (*(int *)(param_1 + 0x28) + -4) - *(int *)(param_1 + 0x10), iVar2 != 0)) {
    FUN_08013f26(param_1,iVar2);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

