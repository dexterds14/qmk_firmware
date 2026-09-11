// FUN_0800df00 @ 0x0800df00  size=132  body=[[0800df00, 0800df83]]

void FUN_0800df00(void)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (((byte)DAT_2000167a < 0x10) && (DAT_20001678._1_1_ != '\0')) {
    for (uVar5 = (uint)DAT_20001632; DAT_20001633 != uVar5; uVar5 = uVar5 + 1 & 7) {
      if (((&DAT_20001638)[uVar5 * 8] != '\0') &&
         (*(short *)(&DAT_20001634 + (short)uVar5 * 8) == DAT_20001674)) {
        iVar1 = uVar5 * 8;
        if ((&DAT_20001639)[iVar1] == '\0') {
          uVar4 = (uint)DAT_20001676;
          uVar2 = *(ushort *)(&DAT_20001636 + iVar1);
          get_record_keycode((uint *)&DAT_20001674,0);
          uVar3 = FUN_0800defc();
          if ((uVar2 - uVar4 & 0xffff) < uVar3) {
            DAT_2000167a._0_1_ = (byte)DAT_2000167a & 0xf | 0x10;
            (&DAT_2000163a)[iVar1] = (&DAT_2000163a)[iVar1] & 0xf | 0x10;
            FUN_0800dad8((uint *)&DAT_20001674);
            FUN_0800de58();
            return;
          }
        }
      }
    }
  }
  return;
}

