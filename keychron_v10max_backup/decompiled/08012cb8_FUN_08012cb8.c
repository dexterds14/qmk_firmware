// FUN_08012cb8 @ 0x08012cb8  size=90  body=[[08012cb8, 08012d11]]

undefined * FUN_08012cb8(uint param_1,undefined *param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined *puVar1;
  uint uVar2;
  undefined *puVar3;
  
  uVar2 = param_1 >> 8;
  if (uVar2 == 3) {
    puVar1 = (undefined *)(param_1 & 0xff);
    if (puVar1 < (undefined *)0x3) {
      param_2 = &DAT_080170f0;
      puVar3 = (&PTR_DAT_080170f4)[(int)puVar1];
LAB_08012cec:
      puVar1 = (undefined *)(uint)(byte)puVar1[(int)param_2];
      goto LAB_08012ccc;
    }
  }
  else if (uVar2 < 4) {
    if (uVar2 == 1) {
      puVar3 = &DAT_08017197;
      puVar1 = (undefined *)0x12;
      goto LAB_08012ccc;
    }
    if (uVar2 == 2) {
      puVar1 = (undefined *)0x5b;
      puVar3 = &DAT_0801713c;
      goto LAB_08012ccc;
    }
  }
  else if (uVar2 == 0x21) {
    if (param_2 < (undefined *)0x3) {
      puVar1 = (undefined *)0x9;
      puVar3 = (&PTR_DAT_080170e4)[(int)param_2];
      goto LAB_08012ccc;
    }
  }
  else if ((uVar2 == 0x22) && (param_2 < (undefined *)0x3)) {
    puVar1 = &DAT_080170d4;
    puVar3 = (&PTR_DAT_080170d8)[(int)param_2];
    goto LAB_08012cec;
  }
  puVar1 = (undefined *)0x0;
  puVar3 = puVar1;
LAB_08012ccc:
  *param_4 = puVar3;
  return puVar1;
}

