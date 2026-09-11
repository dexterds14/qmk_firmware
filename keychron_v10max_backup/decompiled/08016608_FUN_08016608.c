// FUN_08016608 @ 0x08016608  size=118  body=[[08016608, 0801667d]]

void FUN_08016608(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int extraout_r2;
  int extraout_r2_00;
  int extraout_r2_01;
  int extraout_r2_02;
  int extraout_r2_03;
  
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 | 0x9f;
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 & 0xffffff60;
  uVar2 = DAT_40023810;
  uVar1 = DAT_40023830;
  DAT_40023830 = uVar1 | 0x9f;
  uVar1 = DAT_40023850;
  DAT_40023850 = uVar1 | 0x9f;
  uVar2 = DAT_40023850;
  iVar3 = FUN_080165e8((undefined4 *)&DAT_40020000,(undefined4 *)&DAT_080175b4);
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2 + 0x1c));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_00 + 0x38));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_01 + 0x54));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_02 + 0x70));
  FUN_080165e8((undefined4 *)(iVar3 + 0xc00),(undefined4 *)(extraout_r2_03 + 0x8c));
  FUN_08014b5c();
  return;
}

