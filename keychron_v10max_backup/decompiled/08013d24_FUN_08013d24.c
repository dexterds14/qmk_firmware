// FUN_08013d24 @ 0x08013d24  size=46  body=[[08013d24, 08013d51]]

void FUN_08013d24(int param_1,undefined1 param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6,undefined4 param_7)

{
  *(undefined1 *)(param_1 + 8) = param_2;
  *(int *)(param_1 + 0x1c) = param_4 + 4;
  *(undefined4 *)(param_1 + 0x30) = param_6;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(int *)(param_1 + 0x14) = param_3;
  *(int *)(param_1 + 0x10) = param_3;
  *(int *)(param_1 + 0x18) = param_5 * (param_4 + 4) + param_3;
  *(int *)(param_1 + 0x20) = param_5;
  *(int *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x34) = param_7;
  return;
}

