// FUN_080092ac @ 0x080092ac  size=48  body=[[080092ac, 080092db]]

undefined4 FUN_080092ac(void)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = DAT_20000c00;
  if (DAT_20000c00[0xf] == 0) {
    uVar1 = FUN_08009758(DAT_20000c00,0x80);
    puVar2[0xf] = uVar1;
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

