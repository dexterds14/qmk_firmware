// FUN_080096c4 @ 0x080096c4  size=60  body=[[080096c4, 080096ff]]

uint FUN_080096c4(int *param_1)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = DAT_20000c00;
  if (param_1 == (int *)0x0) {
    uVar2 = FUN_08009a14(&DAT_20000c04,(undefined *)0x800968d,&DAT_20000c50);
    return uVar2;
  }
  if (param_1[4] != 0) {
    if ((DAT_20000c00 != (uint *)0x0) && (DAT_20000c00[8] == 0)) {
      FUN_08009518((int)DAT_20000c00);
    }
    if ((short)param_1[3] != 0) {
      uVar2 = FUN_08009568(puVar1,param_1);
      return uVar2;
    }
  }
  return 0;
}

