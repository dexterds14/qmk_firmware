// thunk_FUN_08008000 @ 0x0800811c  size=2  body=[[0800811c, 0800811d]]

void thunk_FUN_08008000(void)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  code *pcVar5;
  
  disableIRQinterrupts();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setMainStackPointer(0x20000400);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(0x20000c00);
  }
  DAT_e000ed08 = 0x8000000;
  DAT_e000ef34 = 0xc0000000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ed88 = 0xf00000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ef3c = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setThreadModePrivileged(1);
    bVar1 = (bool)isThreadMode();
    if (bVar1) {
      cVar2 = isUsingMainStack();
      setStackMode(cVar2 == '\x01');
    }
  }
  InstructionSynchronizationBarrier(0xf);
  FUN_080134ec();
  FUN_08012c4c();
  for (puVar3 = &DAT_20000000; puVar3 < &DAT_20000400; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  for (puVar3 = &DAT_20000400; puVar3 < &DAT_20000c00; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  puVar3 = &DAT_0801774c;
  for (puVar4 = &DAT_20000c00; puVar4 < &DAT_200013b8; puVar4 = puVar4 + 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
  }
  for (puVar3 = &DAT_200013b8; puVar3 < &DAT_20004b88; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  FUN_080134f4();
  FUN_080134ee();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  FUN_0800f084();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

