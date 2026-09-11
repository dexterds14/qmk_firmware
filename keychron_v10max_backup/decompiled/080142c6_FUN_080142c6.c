// FUN_080142c6 @ 0x080142c6  size=84  body=[[080142c6, 0801430f] [08015844, 0801584d]]

void FUN_080142c6(int param_1)

{
  int iVar1;
  int *piVar2;
  
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0x10001;
  piVar2 = (int *)(param_1 + 0xc);
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 != 0) {
      iVar1 = *(int *)(*piVar2 + 0x14);
      if (iVar1 != 0) {
        FUN_08013ab0((undefined4 *)(iVar1 + 0xc),-2);
      }
      if (*(int *)(*piVar2 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x18) + 0xc),-2);
      }
    }
    *piVar2 = 0;
  } while (piVar2 != (int *)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x5c) = **(undefined4 **)(param_1 + 0x58);
  FUN_080154cc(param_1);
  return;
}

