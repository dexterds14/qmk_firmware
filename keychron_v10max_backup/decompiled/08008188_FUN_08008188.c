// FUN_08008188 @ 0x08008188  size=666  body=[[08008188, 0800820f] [0800822e, 0800840d] [08008412, 08008443]]

// WARNING: Removing unreachable block (ram,0x08008412)

ulonglong FUN_08008188(uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5)

{
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  undefined8 uVar13;
  
  if (param_4 == 0) {
    uVar5 = LZCOUNT(param_3);
    if (param_3 <= param_2) {
      if (uVar5 == 0) {
        uVar6 = param_2 - param_3;
        uVar9 = param_3 >> 0x10;
        uVar11 = param_3 & 0xffff;
        uVar8 = 1;
      }
      else {
        param_3 = param_3 << uVar5;
        uVar2 = param_2 >> (0x20 - uVar5 & 0xff);
        uVar6 = param_1 >> (0x20 - uVar5 & 0xff) | param_2 << uVar5;
        uVar9 = param_3 >> 0x10;
        uVar11 = param_3 & 0xffff;
        uVar8 = uVar2 / uVar9;
        uVar3 = uVar6 >> 0x10 | (uVar2 - uVar9 * uVar8) * 0x10000;
        uVar10 = uVar8 * uVar11;
        param_1 = param_1 << uVar5;
        uVar2 = uVar8;
        if (uVar3 <= uVar10 && uVar10 - uVar3 != 0) {
          bVar12 = CARRY4(param_3,uVar3);
          uVar3 = param_3 + uVar3;
          uVar2 = uVar8 - 1;
          if ((!bVar12) && (uVar3 <= uVar10 && uVar10 - uVar3 != 0)) {
            uVar2 = uVar8 - 2;
            uVar3 = uVar3 + param_3;
          }
        }
        uVar7 = (uVar3 - uVar10) / uVar9;
        uVar6 = uVar6 & 0xffff | ((uVar3 - uVar10) - uVar9 * uVar7) * 0x10000;
        uVar3 = uVar7 * uVar11;
        uVar8 = uVar7;
        if (uVar6 <= uVar3 && uVar3 - uVar6 != 0) {
          bVar12 = CARRY4(param_3,uVar6);
          uVar6 = param_3 + uVar6;
          uVar8 = uVar7 - 1;
          if ((!bVar12) && (uVar6 <= uVar3 && uVar3 - uVar6 != 0)) {
            uVar8 = uVar7 - 2;
            uVar6 = uVar6 + param_3;
          }
        }
        uVar6 = uVar6 - uVar3;
        uVar8 = uVar8 | uVar2 << 0x10;
      }
      uVar10 = uVar6 / uVar9;
      uVar6 = param_1 >> 0x10 | (uVar6 - uVar9 * uVar10) * 0x10000;
      uVar3 = uVar11 * uVar10;
      uVar2 = uVar10;
      if (uVar6 <= uVar3 && uVar3 - uVar6 != 0) {
        bVar12 = CARRY4(param_3,uVar6);
        uVar6 = param_3 + uVar6;
        uVar2 = uVar10 - 1;
        if ((!bVar12) && (uVar6 <= uVar3 && uVar3 - uVar6 != 0)) {
          uVar2 = uVar10 - 2;
          uVar6 = uVar6 + param_3;
        }
      }
      uVar10 = (uVar6 - uVar3) / uVar9;
      uVar6 = param_1 & 0xffff | ((uVar6 - uVar3) - uVar9 * uVar10) * 0x10000;
      uVar11 = uVar11 * uVar10;
      uVar3 = uVar10;
      if (uVar6 <= uVar11 && uVar11 - uVar6 != 0) {
        uVar3 = uVar10 - 1;
        if ((!CARRY4(param_3,uVar6)) &&
           (param_3 + uVar6 <= uVar11 && uVar11 - (param_3 + uVar6) != 0)) {
          uVar3 = uVar10 - 2;
        }
      }
      uVar13 = FUN_08008220(uVar3 | uVar2 << 0x10,uVar8,uVar5);
      return uVar13;
    }
    if (uVar5 != 0) {
      param_3 = param_3 << uVar5;
      param_2 = param_2 << uVar5 | param_1 >> (0x20 - uVar5 & 0xff);
      param_1 = param_1 << uVar5;
    }
    uVar10 = param_3 >> 0x10;
    uVar3 = param_2 / uVar10;
    uVar6 = param_1 >> 0x10 | (param_2 - uVar10 * uVar3) * 0x10000;
    uVar2 = uVar3 * (param_3 & 0xffff);
    uVar8 = uVar3;
    if (uVar6 <= uVar2 && uVar2 - uVar6 != 0) {
      bVar12 = CARRY4(param_3,uVar6);
      uVar6 = param_3 + uVar6;
      uVar8 = uVar3 - 1;
      if ((!bVar12) && (uVar6 <= uVar2 && uVar2 - uVar6 != 0)) {
        uVar8 = uVar3 - 2;
        uVar6 = uVar6 + param_3;
      }
    }
    uVar3 = (uVar6 - uVar2) / uVar10;
    uVar6 = param_1 & 0xffff | ((uVar6 - uVar2) - uVar10 * uVar3) * 0x10000;
    uVar10 = uVar3 * (param_3 & 0xffff);
    uVar2 = uVar3;
    if (uVar6 <= uVar10 && uVar10 - uVar6 != 0) {
      bVar12 = CARRY4(param_3,uVar6);
      uVar6 = param_3 + uVar6;
      uVar2 = uVar3 - 1;
      if ((!bVar12) && (uVar6 <= uVar10 && uVar10 - uVar6 != 0)) {
        uVar6 = uVar6 + param_3;
        uVar2 = uVar3 - 2;
      }
    }
    uVar2 = uVar2 | uVar8 << 0x10;
    if (param_5 != (uint *)0x0) {
      *param_5 = uVar6 - uVar10 >> uVar5;
      param_5[1] = 0;
    }
  }
  else {
    if (param_2 < param_4) {
      if (param_5 != (uint *)0x0) {
        *param_5 = param_1;
        param_5[1] = param_2;
      }
      uVar13 = FUN_0800822a();
      return uVar13;
    }
    iVar4 = LZCOUNT(param_4);
    if (iVar4 != 0) {
      uVar6 = 0x20 - iVar4;
      uVar11 = param_3 >> (uVar6 & 0xff) | param_4 << iVar4;
      uVar2 = param_2 >> (uVar6 & 0xff);
      uVar3 = param_1 >> (uVar6 & 0xff) | param_2 << iVar4;
      uVar10 = param_1 << iVar4;
      uVar5 = uVar11 >> 0x10;
      uVar7 = uVar2 / uVar5;
      uVar8 = uVar3 >> 0x10 | (uVar2 - uVar5 * uVar7) * 0x10000;
      uVar9 = uVar7 * (uVar11 & 0xffff);
      uVar2 = uVar7;
      if (uVar8 <= uVar9 && uVar9 - uVar8 != 0) {
        bVar12 = CARRY4(uVar11,uVar8);
        uVar8 = uVar11 + uVar8;
        uVar2 = uVar7 - 1;
        if ((!bVar12) && (uVar8 <= uVar9 && uVar9 - uVar8 != 0)) {
          uVar2 = uVar7 - 2;
          uVar8 = uVar8 + uVar11;
        }
      }
      uVar7 = (uVar8 - uVar9) / uVar5;
      uVar8 = uVar3 & 0xffff | ((uVar8 - uVar9) - uVar5 * uVar7) * 0x10000;
      uVar3 = uVar7 * (uVar11 & 0xffff);
      uVar5 = uVar7;
      if (uVar8 <= uVar3 && uVar3 - uVar8 != 0) {
        bVar12 = CARRY4(uVar11,uVar8);
        uVar8 = uVar11 + uVar8;
        uVar5 = uVar7 - 1;
        if ((!bVar12) && (uVar8 <= uVar3 && uVar3 - uVar8 != 0)) {
          uVar5 = uVar7 - 2;
          uVar8 = uVar8 + uVar11;
        }
      }
      uVar1 = (ulonglong)(uVar5 | uVar2 << 0x10) * (ulonglong)(param_3 << iVar4);
      if (CONCAT44(uVar8 - uVar3,uVar10) < uVar1) {
        uVar1 = uVar1 - CONCAT44(uVar11,param_3 << iVar4);
      }
      if (param_5 != (uint *)0x0) {
        uVar2 = ((uVar8 - uVar3) - (int)(uVar1 >> 0x20)) - (uint)(uVar10 < (uint)uVar1);
        *param_5 = uVar2 << (uVar6 & 0xff) | uVar10 - (uint)uVar1 >> iVar4;
        param_5[1] = uVar2 >> iVar4;
      }
      uVar13 = FUN_0800822a();
      return uVar13;
    }
    if ((param_4 < param_2) || (param_3 <= param_1)) {
      bVar12 = param_1 < param_3;
      param_1 = param_1 - param_3;
      param_2 = (param_2 - param_4) - (uint)bVar12;
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
    if (param_5 != (uint *)0x0) {
      *param_5 = param_1;
      param_5[1] = param_2;
      uVar13 = FUN_0800822a();
      return uVar13;
    }
  }
  return (ulonglong)uVar2;
}

