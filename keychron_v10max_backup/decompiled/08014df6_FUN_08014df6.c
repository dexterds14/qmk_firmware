// FUN_08014df6 @ 0x08014df6  size=70  body=[[08014df6, 08014e3b]]

undefined4 FUN_08014df6(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 4) != '\x05') {
    *(undefined1 *)(param_1 + 4) = 5;
    iVar1 = *(int *)(param_1 + 0x1c);
    *(undefined4 *)(iVar1 + 0xc) = 0xffff;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 2;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xffffff07;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xfffffcff;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | param_2 << 3 | 0x200;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x10000;
    return 0;
  }
  return 1;
}

