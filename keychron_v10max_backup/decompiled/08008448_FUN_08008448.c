// FUN_08008448 @ 0x08008448  size=84  body=[[08008448, 0800849b]]

undefined8 FUN_08008448(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  uint extraout_r1;
  int iVar3;
  uint extraout_r2;
  uint extraout_r3;
  undefined8 uVar4;
  
  iVar1 = DAT_20000c00;
  iVar3 = *(int *)(DAT_20000c00 + 0x30);
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 0x10) = param_1;
    *(undefined4 *)(iVar3 + 0x14) = 0;
    return CONCAT44(param_2,param_1);
  }
  puVar2 = (undefined4 *)FUN_08008970(0x18);
  *(undefined4 **)(iVar1 + 0x30) = puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    puVar2[4] = 1;
    puVar2[5] = 0;
    puVar2[2] = 0x5deec;
    *puVar2 = 0xabcd330e;
    puVar2[1] = 0xe66d1234;
    *(undefined2 *)(puVar2 + 3) = 0xb;
    puVar2[4] = param_1;
    puVar2[5] = 0;
    return 0x5deecabcd330e;
  }
  FUN_08008544("../../../../../../newlib/libc/stdlib/rand.c",0x46,0,0x801765c);
  uVar4 = FUN_08008178(0,extraout_r1,extraout_r2,extraout_r3,param_4);
  return uVar4;
}

