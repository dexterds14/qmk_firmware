// FUN_080141ac @ 0x080141ac  size=38  body=[[08013a94, 08013aa9] [080141ac, 080141bb]]

undefined4 FUN_080141ac(char *param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_200049ec;
  if (*param_1 != '\x03') {
    return 0;
  }
  if (param_2 != 0) {
    *(int *)(param_1 + 8) = DAT_200049ec;
    *(char **)(iVar1 + 0x18) = param_1 + 8;
    uVar2 = FUN_080138d4(3,param_2);
    return uVar2;
  }
  return 0xffffffff;
}

