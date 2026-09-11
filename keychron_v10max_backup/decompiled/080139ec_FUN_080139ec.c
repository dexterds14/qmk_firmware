// FUN_080139ec @ 0x080139ec  size=20  body=[[080139ec, 080139ff]]

int FUN_080139ec(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_2 + 8) = param_4;
  *(undefined4 *)(param_2 + 0x24) = param_4;
  *(undefined4 *)(param_2 + 0x10) = param_1;
  *(undefined2 *)(param_2 + 0x14) = 2;
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  return param_2;
}

