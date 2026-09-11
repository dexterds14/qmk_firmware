// FUN_080091ac @ 0x080091ac  size=96  body=[[080091ac, 0800920b]]

undefined4 FUN_080091ac(undefined4 *param_1,uint param_2)

{
  code *pcVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (0x1f < param_2) {
    return 0xffffffff;
  }
  uVar3 = param_1[0xf];
  if (uVar3 == 0) {
    uVar3 = FUN_08009758(param_1,0x80);
    param_1[0xf] = uVar3;
    if (uVar3 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar3 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
  }
  pcVar1 = *(code **)(uVar3 + param_2 * 4);
  if (pcVar1 == (code *)0x0) {
    return 1;
  }
  if (pcVar1 == (code *)0xffffffff) {
    return 2;
  }
  if (pcVar1 == (code *)0x1) {
    return 3;
  }
  *(undefined4 *)(uVar3 + param_2 * 4) = 0;
  (*pcVar1)(param_2);
  return 0;
}

