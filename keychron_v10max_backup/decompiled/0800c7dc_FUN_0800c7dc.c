// FUN_0800c7dc @ 0x0800c7dc  size=42  body=[[0800c7dc, 0800c805]]

void FUN_0800c7dc(void)

{
  uint uVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  
  if ((DAT_200015c8 != '\0') && (uVar1 = FUN_0801258c(DAT_200015c4), 500 < uVar1)) {
    unregister_code(0xe3,extraout_r1);
    unregister_code(0x2c,extraout_r1_00);
    DAT_200015c8 = '\0';
    DAT_200015c4 = 0;
  }
  return;
}

