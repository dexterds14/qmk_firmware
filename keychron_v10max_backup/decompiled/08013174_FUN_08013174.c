// FUN_08013174 @ 0x08013174  size=38  body=[[08013174, 08013199]]

void FUN_08013174(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  piVar3 = (int *)(param_1 + -4);
  do {
    piVar3 = piVar3 + 1;
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      FUN_08008798((byte *)(iVar1 + 8),0,*(uint *)(iVar1 + 0x48));
      puVar2 = (undefined4 *)*piVar3;
      *puVar2 = 0;
      puVar2[1] = 0;
    }
  } while (piVar3 != (int *)(param_1 + 0x20));
  return;
}

