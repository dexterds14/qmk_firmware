// FUN_08011058 @ 0x08011058  size=246  body=[[08011058, 080110bb] [080110c0, 08011151]]

void FUN_08011058(void)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 *extraout_r2;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  iVar3 = FUN_0801258c(DAT_20001f44);
  iVar4 = FUN_08012508();
  uVar10 = (uint)DAT_20001f1b;
  uVar9 = DAT_20001f48 + iVar3;
  uVar8 = 0;
  bVar2 = false;
  uVar5 = uVar10;
  puVar6 = extraout_r2;
  DAT_20001f44 = iVar4;
  DAT_20001f48 = uVar9;
  while ((uVar8 & 0xff) < uVar10) {
    iVar1 = (uVar8 + 0xc) * 2;
    puVar6 = &DAT_20001f1b + iVar1;
    uVar8 = uVar8 + 1;
    if (0xffffU - iVar3 < (uint)*(ushort *)(&DAT_20001f1c + iVar1)) {
      uVar5 = uVar5 - 1 & 0xff;
      bVar2 = true;
    }
    else {
      iVar7 = (uint)*(ushort *)(&DAT_20001f1c + iVar1) + iVar3;
      (&DAT_20001f1c)[iVar1] = (char)iVar7;
      (&DAT_20001f1d)[iVar1] = (char)((uint)iVar7 >> 8);
    }
  }
  if (bVar2) {
    DAT_20001f1b = (byte)uVar5;
  }
  if (DAT_20001f4c == '\0') {
    uVar8 = 0;
    if ((uVar9 <= DAT_20000eac) && (uVar8 = DAT_20004808 & 3, (DAT_20004808 & 3) != 0)) {
      uVar8 = (uint)(DAT_20004808 >> 2);
    }
  }
  else {
    uVar8 = 0;
  }
  switch(DAT_20000eb0) {
  case '\0':
    DAT_20000eb1 = 0;
    DAT_20004810 = iVar4;
    memcpy((undefined4 *)&DAT_20004814,(undefined4 *)&DAT_20001f1b,0x29);
    DAT_20000eb0 = '\x01';
    break;
  case '\x01':
    FUN_08010a4c(uVar8,uVar5,(uint)puVar6);
    if (uVar8 != 0) {
      if (DAT_20000eb0 == '\x02') {
        FUN_0800c702();
      }
      FUN_08010c54(&DAT_20000eb1);
      return;
    }
    break;
  case '\x02':
    FUN_08011008(uVar8);
    return;
  case '\x03':
    if (DAT_20001f1a != '\0') {
      FUN_0800fd14();
    }
    uVar5 = FUN_0801258c(DAT_20004810);
    if (0xf < uVar5) {
      DAT_20000eb0 = '\0';
    }
  }
  return;
}

