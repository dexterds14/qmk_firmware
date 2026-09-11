// FUN_08013c34 @ 0x08013c34  size=58  body=[[08013c34, 08013c6d]]

void FUN_08013c34(void)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  enableIRQinterrupts();
  uVar2 = DAT_e000ed0c;
  DAT_e000ed0c = uVar2 & 0xf8ff | 0x5fa0300;
  uVar2 = DAT_e000edfc;
  DAT_e000edfc = uVar2 | 0x1000000;
  uVar2 = DAT_e0001000;
  DAT_e0001000 = uVar2 | 1;
  DAT_e000ed1f = 0x20;
  DAT_e000ed22 = 0x30;
  return;
}

