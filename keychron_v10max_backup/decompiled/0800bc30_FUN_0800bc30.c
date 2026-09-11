// FUN_0800bc30 @ 0x0800bc30  size=58  body=[[0800bc30, 0800bc69]]

void FUN_0800bc30(void)

{
  char cVar1;
  uint *puVar2;
  
  cVar1 = '\0';
  puVar2 = &DAT_20000ca4;
  do {
    FUN_08015338((uint *)(*puVar2 & 0xfffffff0),1 << (*puVar2 & 0xf),1);
    cVar1 = cVar1 + '\x01';
    *(short *)((*puVar2 & 0xfffffff0) + 0x1a) = (short)(1 << (*puVar2 & 0xf));
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\x12');
  return;
}

