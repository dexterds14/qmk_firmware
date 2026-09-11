// FUN_08013a00 @ 0x08013a00  size=70  body=[[08013a00, 08013a45]]

int FUN_08013a00(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  *(int *)(iVar2 + -0x1c) = iVar2 + -0x8c;
  *(undefined4 *)(iVar2 + -0x4c) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(iVar2 + -0x48) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(iVar2 + -0x2c) = 0x800813d;
  *(undefined1 *)(iVar2 + -0x14) = 2;
  *(undefined4 **)(iVar2 + -0x18) = &DAT_200049e0;
  *(undefined4 *)(iVar2 + -0x20) = uVar1;
  *(undefined1 *)(iVar2 + -0x13) = 0;
  *(undefined4 *)(iVar2 + -4) = uVar1;
  *(undefined4 *)(iVar2 + -8) = 0;
  *(undefined4 *)(iVar2 + -0xc) = 0;
  return iVar2 + -0x28;
}

