// FUN_0800bdcc @ 0x0800bdcc  size=418  body=[[0800bdcc, 0800bf6d]]

void FUN_0800bdcc(void)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  uint *puVar6;
  
  if ((DAT_20001594 == '\0') && (uVar4 = FUN_0801258c(DAT_20001598), 1000 < uVar4)) {
    DAT_20001594 = '\x01';
    DAT_20001598 = 0;
  }
  uVar4 = FUN_0800bcb8();
  if ((uVar4 != 0) && (DAT_20004ae4 == '\x01')) {
    FUN_08012a74();
    FUN_08012b50(&DAT_20004ae4);
  }
  cVar1 = FUN_0800bbb4();
  if ((((((cVar1 == '\x02') || (cVar1 = FUN_0800bbb4(), cVar1 == '\x04')) && (DAT_20001594 != '\0'))
       && ((bVar2 = FUN_0800b39c(), !bVar2 && (bVar2 = FUN_0800cdb8(), bVar2)))) &&
      ((bVar3 = FUN_08010cf4(), bVar3 == 0 ||
       ((bVar3 = FUN_08010cf4(), bVar3 != 0 && (cVar1 = FUN_08010ffc(), cVar1 != '\0')))))) &&
     ((iVar5 = FUN_080089d4((int *)&DAT_200047f0,(int *)&DAT_2000157c,0x18), iVar5 == 0 &&
      (iVar5 = FUN_0800bcc8(2), iVar5 != 0)))) {
    FUN_0800bff4();
    FUN_08015338((uint *)&DAT_40020000,0x800,0x51a);
    FUN_08015338((uint *)&DAT_40020000,0x1000,0x51a);
    FUN_08015338((uint *)&DAT_40020000,0x20,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x282);
    FUN_08013cd0();
    FUN_0800c810();
    if (DAT_20000c74 != (code *)0x0) {
      (*DAT_20000c74)(1);
    }
    FUN_0800c058();
    cVar1 = '\0';
    puVar6 = &DAT_20000cec;
    do {
      if (*puVar6 != 0xffffffff) {
        bVar2 = (bool)isCurrentModePrivileged();
        if (bVar2) {
          setBasePriority(0x30);
        }
        FUN_08015474(*puVar6 & 0xfffffff0,*puVar6 & 0xf);
        bVar2 = (bool)isCurrentModePrivileged();
        if (bVar2) {
          setBasePriority(0);
        }
      }
      cVar1 = cVar1 + '\x01';
      puVar6 = puVar6 + 1;
    } while (cVar1 != '\x06');
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020400,1);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020000,10);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020000,9);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020400,0);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    uVar4 = FUN_0800bcb8();
    if (uVar4 != 0) {
      FUN_08012a74();
      FUN_08012b50(&DAT_20004ae4);
    }
    FUN_080118d8();
    FUN_0801189c(1,extraout_r1,extraout_r2);
    FUN_0800ef1c();
    FUN_0800ee58();
    FUN_0800bc70();
    FUN_0800a7cc();
    FUN_0800bf94(0);
  }
  return;
}

