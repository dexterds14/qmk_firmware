// FUN_0800f6c0 @ 0x0800f6c0  size=190  body=[[0800f6c0, 0800f74f] [0800f76c, 0800f799]]

uint FUN_0800f6c0(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar7 = (param_1 & 0xffff) >> 8;
  uVar3 = (param_1 & 0xffffff) >> 0x10;
  if ((param_1 & 0xff00) == 0) {
    uVar7 = uVar3;
    uVar5 = uVar3;
    if (param_2 != 0) {
      uVar3 = (uint)(byte)(&DAT_08016fb4)[uVar3];
      uVar7 = uVar3;
      uVar5 = uVar3;
    }
  }
  else {
    uVar2 = uVar3;
    if (param_2 != 0) {
      uVar2 = (uint)(byte)(&DAT_08016fb4)[uVar3];
    }
    uVar1 = ((param_1 & 0xff) * 6) / 0xff;
    uVar3 = (uVar1 * -0x55 + (param_1 & 0xff) * 2) * 3 & 0xff;
    uVar4 = (uVar2 * (0xff - uVar7) & 0xffff) >> 8;
    uVar6 = (uVar2 * (0xff - ((int)(short)(ushort)(byte)(param_1 >> 8) * (int)(short)uVar3 >> 8)) &
            0xffff) >> 8;
    uVar5 = (uVar2 * (0xff - ((int)(uVar7 * (0xff - uVar3)) >> 8)) & 0xffff) >> 8;
    uVar3 = uVar2;
    uVar7 = uVar4;
    switch(uVar1) {
    case 0:
    case 6:
      break;
    case 1:
      uVar3 = uVar6;
      uVar5 = uVar2;
      break;
    case 2:
      uVar3 = uVar4;
      uVar7 = uVar5;
      uVar5 = uVar2;
      break;
    case 3:
      uVar3 = uVar4;
      uVar7 = uVar2;
      uVar5 = uVar6;
      break;
    case 4:
      uVar3 = uVar5;
      uVar7 = uVar2;
      uVar5 = uVar4;
      break;
    default:
      uVar7 = uVar6;
      uVar5 = uVar4;
    }
  }
  return uVar5 | uVar3 << 8 | uVar7 << 0x10;
}

