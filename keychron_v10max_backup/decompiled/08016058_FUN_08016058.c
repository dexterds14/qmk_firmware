// FUN_08016058 @ 0x08016058  size=212  body=[[08016058, 0801612b]]

void FUN_08016058(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  uint uVar12;
  
  uVar11 = (uint)(*(int *)(param_2 + 4) << 5) / 32000;
  uVar7 = uVar11 / 10;
  uVar5 = uVar7 / 6;
  uVar8 = uVar5 / 10;
  uVar12 = uVar8 / 6;
  bVar1 = param_2[2];
  bVar2 = param_2[1];
  bVar4 = *param_2;
  uVar9 = bVar2 & 0xf;
  FUN_08013598();
  iVar6 = FUN_08015e74();
  puVar10 = *(uint **)(param_1 + 4);
  bVar3 = param_2[1];
  *puVar10 = uVar11 % 10 | (uVar7 % 6) * 0x10 | (uVar5 % 10) * 0x100 | (uVar8 % 6) * 0x1000 |
             (uVar12 % 10) * 0x10000 | uVar12 / 10 << 0x14;
  puVar10[1] = (bVar1 & 0x1f) % 10 | (uint)(bVar2 >> 5) << 0xd | ((uint)bVar4 % 10) * 0x10000 |
               (uVar9 % 10) * 0x100 | uVar9 / 10 << 0xc | (bVar1 & 0x1f) / 10 << 4 |
               ((bVar4 / 10) % 10) * 0x100000;
  puVar10[2] = puVar10[2] & 0xfffbffff | ((bVar3 & 0x1f) >> 4) << 0x12;
  *(uint *)(DAT_20004b48 + 0xc) = *(uint *)(DAT_20004b48 + 0xc) & 0xffffff7f;
  FUN_080135aa(iVar6);
  return;
}

