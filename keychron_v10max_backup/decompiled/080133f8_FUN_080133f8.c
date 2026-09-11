// FUN_080133f8 @ 0x080133f8  size=68  body=[[080133f8, 0801343b]]

undefined4 FUN_080133f8(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      DAT_20002250 = (*(code *)puVar1[5])(*puVar1);
      *(undefined1 **)(param_1 + 0x38) = &DAT_20002250;
      uVar2 = 1;
      *(undefined4 *)(param_1 + 0x3c) = 1;
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

