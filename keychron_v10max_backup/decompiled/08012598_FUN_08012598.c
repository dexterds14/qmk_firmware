// FUN_08012598 @ 0x08012598  size=26  body=[[08012598, 080125b1]]

void FUN_08012598(void)

{
  uint uVar1;
  
  DataSynchronizationBarrier(0xf);
  uVar1 = DAT_e000ed0c;
  DAT_e000ed0c = uVar1 & 0x700 | 0x5fa0004;
  DataSynchronizationBarrier(0xf);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

