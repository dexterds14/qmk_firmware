// FUN_08015522 @ 0x08015522  size=20  body=[[08015522, 08015535]]

void FUN_08015522(int param_1,int param_2)

{
  *(uint *)(param_1 + 0x10) = param_2 << 6 | 0x20;
  do {
  } while (*(int *)(param_1 + 0x10) << 0x1a < 0);
  FUN_080135c8(0x12);
  return;
}

