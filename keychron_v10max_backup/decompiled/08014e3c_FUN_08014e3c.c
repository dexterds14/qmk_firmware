// FUN_08014e3c @ 0x08014e3c  size=50  body=[[08014e3c, 08014e6d]]

undefined4 FUN_08014e3c(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    iVar2 = *(int *)(param_1 + 0x1c);
    if (*(int *)(iVar2 + 0xc) << 0xf < 0) {
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = 5;
      }
      uVar1 = 1;
    }
    else {
      *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) & 0xfffffff9;
      uVar1 = FUN_08014c54(param_1);
      *(undefined1 *)(param_1 + 4) = 2;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

