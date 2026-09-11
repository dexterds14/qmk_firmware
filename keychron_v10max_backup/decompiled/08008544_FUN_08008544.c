// FUN_08008544 @ 0x08008544  size=46  body=[[08008544, 08008571]]

void FUN_08008544(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int extraout_r2;
  undefined4 extraout_r3;
  uint *puVar1;
  
  puVar1 = *(uint **)(DAT_20000c00 + 0xc);
  do {
    FUN_080089ac(puVar1,(byte *)"assertion \"%s\" failed: file \"%s\", line %d%s%s\n",param_4,
                 param_1);
    FUN_080085e8();
    param_4 = extraout_r2;
    param_1 = extraout_r3;
  } while( true );
}

