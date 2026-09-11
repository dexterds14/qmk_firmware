// FUN_080134f4 @ 0x080134f4  size=82  body=[[080134f4, 08013545]]

void FUN_080134f4(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  
  piVar7 = &DAT_080172c8;
  iVar8 = 8;
  do {
    puVar4 = (undefined4 *)piVar7[2];
    puVar5 = (undefined4 *)(*piVar7 + -4);
    puVar1 = (undefined4 *)piVar7[1];
    for (puVar3 = puVar1; puVar3 < puVar4; puVar3 = puVar3 + 1) {
      puVar5 = puVar5 + 1;
      *puVar3 = *puVar5;
    }
    uVar6 = (int)puVar4 + (3 - (int)puVar1) & 0xfffffffc;
    if (puVar4 < (undefined4 *)((int)puVar1 - 3U)) {
      uVar6 = 0;
    }
    pbVar2 = (byte *)((int)puVar1 + uVar6);
    uVar6 = (uint)((byte *)piVar7[3] + (3 - (int)pbVar2)) & 0xfffffffc;
    if ((byte *)piVar7[3] < pbVar2 + -3) {
      uVar6 = 0;
    }
    FUN_08008798(pbVar2,0,uVar6);
    iVar8 = iVar8 + -1;
    piVar7 = piVar7 + 4;
  } while (iVar8 != 0);
  return;
}

