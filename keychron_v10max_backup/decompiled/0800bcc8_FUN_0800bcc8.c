// FUN_0800bcc8 @ 0x0800bcc8  size=242  body=[[0800bcc8, 0800bdb9]]

int FUN_0800bcc8(uint param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  uint *puVar5;
  
  if (((param_1 < 2) || (uVar3 = FUN_0800bcb8(), uVar3 == 0)) &&
     (iVar2 = FUN_0800bf94(param_1), iVar2 != 0)) {
    FUN_08014242(&DAT_20004ae4);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020400,1,2);
    cVar4 = '\0';
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020400,0,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020000,10,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020000,9,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    puVar5 = &DAT_20000cec;
    do {
      if (*puVar5 != 0xffffffff) {
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        FUN_08015410(*puVar5 & 0xfffffff0,*puVar5 & 0xf,3);
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0);
        }
      }
      cVar4 = cVar4 + '\x01';
      puVar5 = puVar5 + 1;
    } while (cVar4 != '\x06');
    FUN_0800bc30();
    FUN_08015338((uint *)&DAT_40020000,0x20,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x1000,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x800,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x100,0x40);
    FUN_0800c068();
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

