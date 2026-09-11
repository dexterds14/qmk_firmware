// FUN_08008584 @ 0x08008584  size=56  body=[[08008584, 080085bb]]

undefined1 * FUN_08008584(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint extraout_r2;
  undefined8 uVar4;
  
  uVar4 = FUN_08008544(param_1,param_2,0,param_3);
  puVar2 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
  uVar1 = (uint)uVar4;
  while (0x22 < extraout_r2 - 2) {
    *puVar2 = 0;
    uVar1 = 0;
  }
  puVar3 = puVar2;
  if ((extraout_r2 == 10) && ((int)uVar1 < 0)) {
    puVar3 = puVar2 + 1;
    *puVar2 = 0x2d;
    uVar1 = -uVar1;
  }
  FUN_080085f8(uVar1,puVar3,extraout_r2);
  return puVar2;
}

