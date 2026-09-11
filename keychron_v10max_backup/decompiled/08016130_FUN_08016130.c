// FUN_08016130 @ 0x08016130  size=240  body=[[08016130, 0801621f]]

void FUN_08016130(int param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  iVar1 = FUN_08013598();
  puVar2 = *(uint **)(param_1 + 4);
  do {
  } while (-1 < (int)(puVar2[3] << 0x1a));
  do {
    uVar4 = puVar2[10];
    uVar5 = *puVar2;
    uVar6 = puVar2[1];
  } while (uVar4 != puVar2[10]);
  uVar3 = puVar2[2];
  puVar2[3] = puVar2[3] & 0xffffffdf;
  FUN_080135aa(iVar1);
  *(byte *)param_2 = (byte)((uVar6 << 0xc) >> 0x1c) + ((byte)(uVar6 >> 0x10) >> 4) * '\n';
  *param_2 = uVar3 >> 6 & 0x1000 |
             (((uVar6 & 0xfff) >> 8) + ((int)(uVar6 << 0x13) >> 0x1f) * -10 & 0xf) << 8 |
             uVar6 & 0xe000 | ((uVar6 & 0xf) + ((uVar6 & 0x3f) >> 4) * 10 & 0x1f) << 0x10 |
             *param_2 & 0xffe000ff;
  param_2[1] = param_2[1] & 0xf8000000 |
               (((uVar5 & 0x7f) >> 4) * 10000 +
                ((uVar5 & 0xfff) >> 8) * 60000 +
                ((uVar5 & 0x7fff) >> 0xc) * 600000 +
                (uVar5 & 0xf) * 1000 +
                ((uVar5 & 0x3fffff) >> 0x14) * 36000000 + ((uVar5 & 0xfffff) >> 0x10) * 3600000 &
               0x7ffffff) + (uVar4 * -1000 + 0xf9c18 >> 10) & 0x7ffffff;
  return;
}

