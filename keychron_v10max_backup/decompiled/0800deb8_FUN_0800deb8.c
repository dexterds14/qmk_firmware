// FUN_0800deb8 @ 0x0800deb8  size=56  body=[[0800deb8, 0800deef]]

undefined4 FUN_0800deb8(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = (uint)DAT_20001632;
  while( true ) {
    if (uVar1 == DAT_20001633) {
      return 0;
    }
    if ((((byte)(&DAT_20001635)[uVar1 * 8] == param_2) &&
        ((byte)(&DAT_20001634)[uVar1 * 8] == param_1)) &&
       ((byte)(&DAT_20001639)[uVar1 * 8] != param_3)) break;
    uVar1 = uVar1 + 1 & 7;
  }
  return 1;
}

