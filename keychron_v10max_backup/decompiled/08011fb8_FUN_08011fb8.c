// FUN_08011fb8 @ 0x08011fb8  size=66  body=[[08011fb8, 08011ff9]]

void FUN_08011fb8(undefined4 *param_1)

{
  if (-1 < (int)((uint)*(byte *)((int)param_1 + 5) << 0x1e)) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 2;
    FUN_0800e354(*(byte *)((int)param_1 + 3));
    FUN_0800e31c(*(byte *)(param_1 + 1));
    FUN_0800e4dc();
    FUN_08011f8c(param_1,param_1[6],(undefined *)param_1[3]);
  }
  DAT_2000201c = 0;
  if (-1 < (int)((uint)*(byte *)((int)param_1 + 5) << 0x1f)) {
    FUN_08011f92(param_1);
    return;
  }
  return;
}

