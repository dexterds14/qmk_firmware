// FUN_08013b34 @ 0x08013b34  size=10  body=[[08013b34, 08013b3d]]

void FUN_08013b34(int param_1)

{
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

