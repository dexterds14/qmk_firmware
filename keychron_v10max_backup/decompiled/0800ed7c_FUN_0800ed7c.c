// FUN_0800ed7c @ 0x0800ed7c  size=52  body=[[0800ed7c, 0800edaf]]

void FUN_0800ed7c(void)

{
  char cVar1;
  uint *puVar2;
  
  cVar1 = '\x12';
  puVar2 = &DAT_08016f34;
  do {
    if (*puVar2 != 0xffffffff) {
      FUN_0800ed58(*puVar2);
    }
    cVar1 = cVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\0');
  cVar1 = '\x06';
  puVar2 = &DAT_08016f7c;
  do {
    if (*puVar2 != 0xffffffff) {
      FUN_0800ed58(*puVar2);
    }
    cVar1 = cVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\0');
  return;
}

