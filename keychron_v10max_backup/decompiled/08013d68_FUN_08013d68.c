// FUN_08013d68 @ 0x08013d68  size=20  body=[[08013d68, 08013d7b]]

int FUN_08013d68(int param_1)

{
  if ((*(int *)(param_1 + 0x10) == *(int *)(param_1 + 0x14)) && (*(int *)(param_1 + 0xc) != 0)) {
    return 0;
  }
  return *(int *)(param_1 + 0x10) + 4;
}

