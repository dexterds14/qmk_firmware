// FUN_08013448 @ 0x08013448  size=68  body=[[08013448, 0801348b]]

undefined4 FUN_08013448(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      (*(code *)puVar1[4])(*puVar1,*(byte *)(param_1 + 0x46),*(undefined1 *)(param_1 + 0x47));
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

