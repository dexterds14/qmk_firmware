// FUN_08009260 @ 0x08009260  size=70  body=[[08009260, 080092a5]]

undefined4 FUN_08009260(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  puVar2 = DAT_20000c00;
  if (0x1f < param_1) {
    *DAT_20000c00 = 0x16;
    return 0xffffffff;
  }
  uVar3 = DAT_20000c00[0xf];
  if (uVar3 == 0) {
    uVar3 = FUN_08009758(DAT_20000c00,0x80);
    puVar2[0xf] = uVar3;
    if (uVar3 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar3 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
  }
  uVar1 = *(undefined4 *)(uVar3 + param_1 * 4);
  *(undefined4 *)(uVar3 + param_1 * 4) = param_2;
  return uVar1;
}

