// FUN_08013d9c @ 0x08013d9c  size=50  body=[[08013d9c, 08013dcd]]

int FUN_08013d9c(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  
  while( true ) {
    if (*(int *)(param_1 + 0xc) != 0) {
      piVar2 = *(int **)(param_1 + 0x14) + 1;
      iVar1 = **(int **)(param_1 + 0x14);
      *(int **)(param_1 + 0x28) = piVar2;
      *(int *)(param_1 + 0x2c) = (int)piVar2 + iVar1;
      return 0;
    }
    if (*(char *)(param_1 + 8) != '\0') break;
    iVar1 = FUN_08013ac4(param_1,param_2);
    if (iVar1 < 0) {
      return iVar1;
    }
  }
  return -2;
}

