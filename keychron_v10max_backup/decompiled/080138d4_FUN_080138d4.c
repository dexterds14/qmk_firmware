// FUN_080138d4 @ 0x080138d4  size=52  body=[[080138d4, 08013907]]

undefined4 FUN_080138d4(undefined1 param_1,uint param_2)

{
  int iVar1;
  int local_28 [7];
  
  iVar1 = DAT_200049ec;
  if (param_2 == 0xffffffff) {
    FUN_080138b8(param_1);
  }
  else {
    FUN_080136f4(local_28,param_2,0x8013871,DAT_200049ec);
    FUN_080138b8(param_1);
    if (local_28[0] != 0) {
      FUN_08013708(local_28);
    }
  }
  return *(undefined4 *)(iVar1 + 0x18);
}

