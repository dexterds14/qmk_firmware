// FUN_08012da8 @ 0x08012da8  size=52  body=[[08012da8, 08012ddb]]

void FUN_08012da8(int param_1)

{
  *(int *)(param_1 + 0x4c) = param_1 + 0x5c;
  if (*(char *)(param_1 + 0x84) != '\0') {
    *(int *)(param_1 + 0x50) = param_1 + 0x70;
  }
  FUN_08013e74(param_1,1,*(int *)(param_1 + 0x98),*(int *)(param_1 + 0x94),*(int *)(param_1 + 0x90),
               0x8012d31,param_1);
  return;
}

