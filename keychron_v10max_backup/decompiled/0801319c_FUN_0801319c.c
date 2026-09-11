// FUN_0801319c @ 0x0801319c  size=74  body=[[0801319c, 080131e5]]

undefined4 FUN_0801319c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      (*(code *)puVar1[1])
                (*puVar1,*(byte *)(param_1 + 0x46),&DAT_200022a0,(code *)puVar1[1],param_4);
      *(undefined **)(param_1 + 0x38) = &DAT_200022a8;
      *(undefined4 *)(param_1 + 0x3c) = DAT_200022e8;
      *(undefined4 *)(param_1 + 0x40) = 0;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

