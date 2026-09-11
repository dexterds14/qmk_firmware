// FUN_08009110 @ 0x08009110  size=74  body=[[08009110, 08009159]]

undefined4 FUN_08009110(undefined4 *param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (param_2 < 0x20) {
    uVar3 = param_1[0xf];
    if (uVar3 == 0) {
      uVar3 = FUN_08009758(param_1,0x80);
      param_1[0xf] = uVar3;
      if (uVar3 == 0) goto LAB_08009130;
      puVar2 = (undefined4 *)(uVar3 - 4);
      do {
        puVar2 = puVar2 + 1;
        *puVar2 = 0;
      } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
    }
    uVar1 = *(undefined4 *)(uVar3 + param_2 * 4);
    *(undefined4 *)(uVar3 + param_2 * 4) = param_3;
  }
  else {
    *param_1 = 0x16;
LAB_08009130:
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

