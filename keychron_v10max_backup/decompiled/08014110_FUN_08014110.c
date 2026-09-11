// FUN_08014110 @ 0x08014110  size=16  body=[[08014110, 0801411f]]

void FUN_08014110(undefined1 *param_1)

{
  *param_1 = 1;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  FUN_08013b34((int)(param_1 + 0xc));
  return;
}

