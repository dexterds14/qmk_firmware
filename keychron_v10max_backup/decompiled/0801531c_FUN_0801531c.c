// FUN_0801531c @ 0x0801531c  size=22  body=[[0801531c, 08015331]]

void FUN_0801531c(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_20004a64;
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 2;
  } while (iVar2 != 0x10);
  return;
}

