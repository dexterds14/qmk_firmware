// FUN_08012f60 @ 0x08012f60  size=66  body=[[08012f60, 08012fa1]]

void FUN_08012f60(int param_1,int param_2)

{
  bool bVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + (param_2 + 9) * 4);
  if (piVar2 != (int *)0x0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x18) + 4) != 0) {
      FUN_08013d7c(piVar2,*(undefined4 *)
                           (*(int *)(*(int *)(piVar2[0x1c] + (uint)*(byte *)(piVar2 + 0x1d) * 4 +
                                             0xc) + 0x18) + 4));
    }
    FUN_08012d6a((int)piVar2);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}

