// FUN_08013ef4 @ 0x08013ef4  size=50  body=[[08013ef4, 08013f25]]

int FUN_08013ef4(int param_1,uint param_2)

{
  int iVar1;
  
  while( true ) {
    if (*(int *)(param_1 + 0xc) != 0) {
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x10) + 4;
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x1c);
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

