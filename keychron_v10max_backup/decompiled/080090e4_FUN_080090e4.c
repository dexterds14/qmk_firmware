// FUN_080090e4 @ 0x080090e4  size=44  body=[[080090e4, 0800910f]]

undefined4 FUN_080090e4(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1[0xf] == 0) {
    uVar1 = FUN_08009758(param_1,0x80);
    param_1[0xf] = uVar1;
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar1 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar1 + 0x7c));
  }
  return 0;
}

