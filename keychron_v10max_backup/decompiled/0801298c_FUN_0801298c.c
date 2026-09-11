// FUN_0801298c @ 0x0801298c  size=28  body=[[0801298c, 080129a7]]

void FUN_0801298c(undefined1 param_1)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  bool bVar4;
  
  uVar1 = (uint)DAT_200049cd;
  puVar3 = (undefined *)(uint)DAT_200049ce;
  puVar2 = (undefined *)(uVar1 + 1 & 0xf);
  bVar4 = puVar3 != puVar2;
  if (bVar4) {
    puVar3 = &DAT_200049bd;
    DAT_200049cd = (byte)puVar2;
  }
  if (bVar4) {
    puVar3[uVar1] = param_1;
  }
  return;
}

