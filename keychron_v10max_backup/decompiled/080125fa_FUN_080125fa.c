// FUN_080125fa @ 0x080125fa  size=6  body=[[080125fa, 080125ff]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_080125fa(void)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 extraout_r3;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  FUN_08012598();
  uVar8 = 0x8012601;
  uVar7 = extraout_r3;
  bVar3 = FUN_080125cc();
  if (bVar3) {
    uVar4 = FUN_080125e4();
    disableIRQinterrupts();
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    uVar2 = DAT_e000ed24;
    DAT_e000ed24 = uVar2 & 0xfffeffff;
    uVar2 = DAT_e000ed94;
    DAT_e000ed94 = uVar2 & 0xfffffffe;
    DAT_e000e010 = 0;
    DAT_e000e018 = 0;
    DAT_e000e014 = 0;
    iVar5 = 0;
    do {
      iVar6 = iVar5 + 1;
      (&DAT_e000e180)[iVar5] = 0xffffffff;
      (&DAT_e000e280)[iVar5] = 0xffffffff;
      iVar5 = iVar6;
    } while (iVar6 != 8);
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setThreadModePrivileged(1);
      bVar3 = (bool)isThreadMode();
      if (bVar3) {
        cVar1 = isUsingMainStack();
        setStackMode(cVar1 == '\x01');
      }
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setMainStackPointer(_DAT_1fff0000);
    }
    enableIRQinterrupts();
    (*_DAT_1fff0004)(uVar4,0xffffffff,_DAT_1fff0000,_DAT_1fff0004,uVar7,uVar8);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  return;
}

