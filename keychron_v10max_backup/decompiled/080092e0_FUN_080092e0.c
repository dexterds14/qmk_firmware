// FUN_080092e0 @ 0x080092e0  size=94  body=[[080092e0, 0800933d]]

undefined4 FUN_080092e0(uint param_1)

{
  uint uVar1;
  code *pcVar2;
  undefined4 *puVar3;
  
  puVar3 = DAT_20000c00;
  if (0x1f < param_1) {
    return 0xffffffff;
  }
  uVar1 = DAT_20000c00[0xf];
  if (uVar1 == 0) {
    uVar1 = FUN_08009758(DAT_20000c00,0x80);
    puVar3[0xf] = uVar1;
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    puVar3 = (undefined4 *)(uVar1 - 4);
    do {
      puVar3 = puVar3 + 1;
      *puVar3 = 0;
    } while (puVar3 != (undefined4 *)(uVar1 + 0x7c));
  }
  pcVar2 = *(code **)(uVar1 + param_1 * 4);
  if (pcVar2 == (code *)0x0) {
    return 1;
  }
  if (pcVar2 == (code *)0xffffffff) {
    return 2;
  }
  if (pcVar2 != (code *)0x1) {
    *(undefined4 *)(uVar1 + param_1 * 4) = 0;
    (*pcVar2)(param_1);
    return 0;
  }
  return 3;
}

