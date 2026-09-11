// FUN_0800e8b0 @ 0x0800e8b0  size=432  body=[[0800e8b0, 0800ea5f]]

uint FUN_0800e8b0(uint param_1)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar1 = FUN_0800eab4(param_1);
  if (uVar1 < 0x5200) {
    if (uVar1 < 0x5000) {
      if (uVar1 < 0xe0) {
        if (uVar1 < 0xcd) {
          if (0xa7 < uVar1) {
            if ((uVar1 - 0xa8 & 0xffff) < 0x1b) {
              return *(ushort *)(&UNK_08016efe + (uVar1 + 0x58 & 0xff) * 2) | 0x4400;
            }
            goto LAB_0800e8f4;
          }
          if (uVar1 < 0xa5) {
            if (uVar1 == 1) {
              return 1;
            }
            if ((uVar1 - 4 & 0xffff) < 0xa1) {
              return uVar1;
            }
            return 0;
          }
          uVar3 = (ushort)uVar1 - 0x24 | 0x4000;
        }
        else {
          uVar3 = (ushort)uVar1 | 0x5000;
        }
      }
      else {
        if (0x3fff < uVar1) {
          uVar2 = FUN_0800eab4(uVar1 & 0xff);
          return uVar2 & 0xffff | uVar1 & 0xf00 | 0xa000;
        }
        if (0x1fff < uVar1) {
          uVar2 = FUN_0800ebbc((uVar1 & 0x1fff) >> 8);
          uVar1 = FUN_0800eab4(uVar1 & 0xff);
          return (uVar2 & 0x1f) << 8 | uVar1 & 0xffff | 0x2000;
        }
        if (uVar1 < 0xe8) {
          return uVar1;
        }
        if (0x1eff < (uVar1 - 0x100 & 0xffff)) goto LAB_0800e8f4;
        uVar2 = FUN_0800ebbc((uVar1 & 0xffff) >> 8);
        uVar1 = FUN_0800eab4(uVar1 & 0xff);
        uVar3 = (ushort)uVar1 | (ushort)((uVar2 & 0x1f) << 8);
      }
    }
    else {
      uVar2 = FUN_0800ebbc(uVar1 & 0x1f);
      uVar3 = (ushort)uVar2;
      if ((int)(uVar2 << 0x1b) < 0) {
        uVar3 = (ushort)(uVar2 << 4);
      }
      uVar3 = (ushort)(((uVar1 & 0x1ff) >> 5) << 8) | uVar3 | 0x9000;
    }
    uVar1 = (uint)uVar3;
  }
  else {
    if (uVar1 < 0x5280) {
      if (uVar1 < 0x5260) {
        if (uVar1 < 0x5240) {
          if (0x521f < uVar1) {
            return (uVar1 & 0x1f) << 8 | 0xa0f1;
          }
          uVar3 = (ushort)(1 << (uVar1 & 3)) | (ushort)(((uVar1 & 0xff) >> 2) << 5) | 0x8d00;
        }
        else {
          uVar3 = (ushort)(1 << (uVar1 & 3)) | (ushort)(((uVar1 & 0x1f) >> 2) << 5) | 0x8c00;
        }
      }
      else {
        uVar3 = (ushort)(1 << (uVar1 & 3)) | (ushort)(((uVar1 & 0x1f) >> 2) << 5) | 0x8a00;
      }
      return (uint)uVar3;
    }
    if (uVar1 < 0x52c0) {
      if (uVar1 < 0x52a0) {
        return (uVar1 & 0x1f) << 8 | 0xa0f4;
      }
      uVar1 = FUN_0800ebbc(uVar1 & 0x1f);
      return (uVar1 & 0x1f) << 8 | 0x2000;
    }
    if ((uVar1 - 0x52c0 & 0xffff) < 0x20) {
      return (uVar1 & 0x1f) << 8 | 0xa0f0;
    }
LAB_0800e8f4:
    uVar1 = 0;
  }
  return uVar1;
}

