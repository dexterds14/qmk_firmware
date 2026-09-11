// FUN_08013304 @ 0x08013304  size=232  body=[[08013304, 080133eb]]

void FUN_08013304(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  char cVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  
  cVar6 = DAT_200022ec;
  if (DAT_200022ec != '\0') {
    uVar5 = 0;
    puVar7 = &DAT_20000f64;
    cVar6 = '\0';
    do {
      puVar4 = *(undefined4 **)(puVar7 + 0xa4);
      if (puVar4 != (undefined4 *)0x0) {
        if (uVar5 == 0) {
          uVar8 = 1;
          do {
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0x30);
            }
            uVar9 = uVar8 & 0xff;
            iVar2 = (*(code *)puVar4[5])(*puVar4,uVar9);
            if (iVar2 != 0) {
              cVar6 = '\x01';
            }
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0);
            }
            iVar2 = FUN_08013040(0x20000f64);
            if ((iVar2 != 0) && (iVar2 = (*(code *)puVar4[6])(*puVar4,uVar9), iVar2 != 0)) {
              bVar1 = (bool)isCurrentModePrivileged();
              if (bVar1) {
                setBasePriority(0x30);
              }
              (*(code *)puVar4[1])(*puVar4,uVar9,&DAT_20002254);
              bVar1 = (bool)isCurrentModePrivileged();
              if (bVar1) {
                setBasePriority(0);
              }
              FUN_08012bc4(0,(undefined4 *)&DAT_2000225c,DAT_2000229c);
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 != 9);
        }
        else {
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          iVar2 = (*(code *)puVar4[5])(*puVar4,0);
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0);
          }
          iVar3 = FUN_08013040((int)puVar7);
          if ((iVar3 != 0) && (iVar3 = (*(code *)puVar4[6])(*puVar4,0), iVar3 != 0)) {
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0x30);
            }
            (*(code *)puVar4[1])(*puVar4,0,&DAT_20002254);
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0);
            }
            FUN_08012bc4(uVar5 & 0xff,(undefined4 *)&DAT_2000225c,DAT_2000229c);
          }
          if (iVar2 != 0) {
            cVar6 = '\x01';
          }
        }
      }
      uVar5 = uVar5 + 1;
      puVar7 = puVar7 + 0xa8;
    } while (uVar5 != 3);
  }
  DAT_200022ec = cVar6;
  return;
}

