// FUN_08013e74 @ 0x08013e74  size=46  body=[[08013e74, 08013ea1]]

void FUN_08013e74(int param_1,undefined1 param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6,undefined4 param_7)

{
  *(undefined1 *)(param_1 + 8) = param_2;
  *(int *)(param_1 + 0x1c) = param_4 + 4;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = param_6;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(int *)(param_1 + 0xc) = param_5;
  *(int *)(param_1 + 0x14) = param_3;
  *(int *)(param_1 + 0x10) = param_3;
  *(int *)(param_1 + 0x18) = (param_4 + 4) * param_5 + param_3;
  *(int *)(param_1 + 0x20) = param_5;
  *(int *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x34) = param_7;
  return;
}

