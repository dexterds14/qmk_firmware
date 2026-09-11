// FUN_0800d698 @ 0x0800d698  size=1010  body=[[0800d698, 0800d707] [0800d720, 0800d98d] [0800d994, 0800d9d9] [0800d9e0, 0800daad]]

void FUN_0800d698(uint *param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint extraout_r1;
  uint uVar4;
  uint extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 uVar5;
  undefined4 extraout_r1_02;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  bool bVar11;
  
  bVar3 = *(byte *)((int)param_1 + 6);
  uVar8 = (uint)*(byte *)((int)param_1 + 5);
  bVar1 = FUN_0800e2fc();
  bVar3 = bVar3 >> 4;
  bVar2 = 0;
  uVar4 = extraout_r1;
  if ((bVar1 != 0) && (bVar2 = 0, uVar8 != 0)) {
    uVar6 = (param_2 & 0xffff) >> 8;
    if ((uVar6 & 0xf0) != 0x40) {
      uVar4 = param_2 & 0xff;
      if ((uVar4 + 0x20 & 0xff) < 8) {
LAB_0800d720:
        bVar2 = 0;
        goto LAB_0800d6fa;
      }
      if ((uVar6 & 0xe0) == 0x20) {
        if (uVar4 < 2) goto LAB_0800d720;
        if (bVar3 == 0) {
          bVar2 = 0;
          goto LAB_0800d6fa;
        }
      }
    }
    bVar2 = DAT_200047d4._1_1_ & 4;
    if ((DAT_200047d4._1_1_ & 4) != 0) {
      FUN_0800e548(2);
      bVar2 = FUN_0800e2fc();
      bVar2 = bVar2 ^ 1;
      uVar4 = extraout_r1_00;
    }
  }
LAB_0800d6fa:
  uVar6 = (param_2 & 0xffff) >> 0xc;
  switch(uVar6) {
  case 0:
  case 1:
    uVar9 = (param_2 & 0xfff) >> 8;
    if (0xf < (param_2 & 0xffff) >> 8) {
      uVar9 = uVar9 << 4;
    }
    uVar7 = param_2 & 0xff;
    bVar3 = (byte)uVar9;
    if (uVar8 == 0) {
      unregister_code(uVar7,uVar4);
      if (uVar9 == 0) break;
      if (((uVar7 + 0x20 & 0xff) < 8) || (uVar7 == 0)) {
LAB_0800d772:
        FUN_0800e32c((byte)uVar9);
      }
      else {
        FUN_0800e364(bVar3);
      }
      FUN_0800e4dc();
      break;
    }
    if (uVar9 != 0) {
      if (((uVar7 + 0x20 & 0xff) < 8) || (uVar7 == 0)) {
        FUN_0800e31c(bVar3);
      }
      else {
        FUN_0800e354(bVar3);
      }
      FUN_0800e4dc();
    }
LAB_0800d752:
    uVar4 = param_2 & 0xff;
    goto LAB_0800d7c0;
  case 2:
  case 3:
    uVar9 = (param_2 & 0xfff) >> 8;
    uVar7 = param_2 & 0xff;
    if (((param_2 & 0xffff) >> 8 & 0xf0) != 0x20) {
      uVar9 = uVar9 << 4;
    }
    if (uVar7 != 0) {
      if (uVar7 == 1) {
        if (uVar8 == 0) {
          if (4 < bVar3) break;
          goto LAB_0800d886;
        }
        if (5 < bVar3) break;
      }
      else {
        if (uVar8 == 0) {
          if (bVar3 != 0) {
            if (uVar7 == 0x39) {
              uVar4 = 8000;
            }
            else {
              uVar4 = 1;
            }
            FUN_08013a7a(uVar4);
            uVar5 = extraout_r1_01;
            goto LAB_0800d8a4;
          }
LAB_0800d886:
          FUN_0800d684(uVar9);
          break;
        }
        if (bVar3 != 0) goto LAB_0800d752;
      }
LAB_0800d81c:
      FUN_0800d672(uVar9);
      break;
    }
    if ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0) {
      if (uVar8 == 0) {
        if ((bVar3 == 0) || ((bVar3 == 1 && (bVar3 = FUN_0800e310(), (bVar3 & uVar9) != 0)))) {
          FUN_0800d684(uVar9);
          FUN_0800e408(uVar9);
          FUN_0800e3c8(uVar9);
        }
        break;
      }
      if (bVar3 != 0) {
        if (bVar3 == 1) {
          FUN_0800e3ec(uVar9);
        }
        else if (bVar3 == 2) {
          FUN_0800d672(uVar9);
          FUN_0800e408(uVar9);
          FUN_0800e394(uVar9);
        }
        break;
      }
      goto LAB_0800d81c;
    }
    if (uVar8 == 0) {
      unregister_code(0,uVar4);
      if (uVar9 == 0) break;
      goto LAB_0800d772;
    }
    if (uVar9 != 0) {
      FUN_0800e31c((byte)uVar9);
      FUN_0800e4dc();
    }
    uVar4 = 0;
LAB_0800d7c0:
    register_code(uVar4);
    break;
  case 4:
    if ((param_2 & 0xc00) == 0) {
      if (uVar8 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = param_2 & 0x3ff;
      }
      FUN_08012188(uVar4);
    }
    else if ((param_2 & 0xfff) >> 10 == 1) {
      if (uVar8 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = param_2 & 0x3ff;
      }
      FUN_080121b8(uVar4);
    }
    break;
  case 5:
    FUN_0800d55a(param_2 & 0xff,uVar8);
    break;
  case 8:
    if ((param_2 & 0x300) == 0) {
      if (uVar8 == 0) {
        uVar4 = (param_2 & 0xfff) >> 10;
        if (uVar4 == 2) {
          FUN_0800dc08();
        }
        else if (uVar4 == 3) {
          thunk_FUN_0800dbd0();
        }
        else if (uVar4 == 1) {
          FUN_0800dbe8();
        }
        else {
          FUN_0800dbf8();
        }
      }
    }
    else {
      uVar4 = (param_2 & 0x3ff) >> 8;
      if (uVar8 == 0) {
        if (uVar4 < 2) break;
      }
      else if (-1 < (int)(uVar4 << 0x1f)) break;
      uVar4 = (param_2 & 0xfff) >> 10;
      if (uVar4 == 2) {
        FUN_0800dcc8();
      }
      else if (uVar4 == 3) {
        FUN_0800dc24();
      }
      else if (uVar4 == 1) {
        FUN_0800dca8();
      }
      else {
        FUN_0800dcb8();
      }
    }
    break;
  case 9:
    uVar9 = param_2 & 0xff;
    if (uVar8 != 0) {
      FUN_0800dc64();
      goto LAB_0800d81c;
    }
    FUN_0800d684(uVar9);
    goto LAB_0800d9c6;
  case 10:
  case 0xb:
    uVar4 = param_2 & 0xff;
    switch(uVar4) {
    case 0xf0:
      if (uVar8 == 0) {
        bVar11 = 4 < bVar3;
        bVar10 = bVar3 == 5;
      }
      else {
        bVar11 = 3 < bVar3;
        bVar10 = bVar3 == 4;
      }
      if (!bVar11 || bVar10) {
        FUN_0800dc90();
      }
      break;
    case 0xf2:
      if (uVar8 != 0) goto LAB_0800d9c6;
      goto LAB_0800da02;
    case 0xf3:
      if (uVar8 == 0) {
        FUN_0800dc34();
      }
      else {
        FUN_0800dc58();
      }
      break;
    case 0xf4:
      if ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0) {
        if (uVar8 == 0) {
          if (bVar3 < 2) {
            FUN_0800e548(1);
          }
          else {
            FUN_0800e534();
            bVar2 = 4;
            bVar3 = (byte)((param_2 << 0x13) >> 0x18);
LAB_0800da5a:
            FUN_0800e504(bVar3 >> 3,bVar2);
          }
        }
        else {
          bVar2 = FUN_0800e2ec();
          if (bVar2 == 4) {
            FUN_0800e534();
            FUN_0800dc7c();
          }
          else if (bVar3 < 2) {
            bVar3 = (byte)((param_2 << 0x13) >> 0x18);
            FUN_0800dc64();
            bVar2 = 3;
            goto LAB_0800da5a;
          }
        }
        bVar2 = 0;
        break;
      }
    case 0xf1:
      if (uVar8 == 0) {
LAB_0800d9c6:
        FUN_0800dc7c();
      }
      else {
LAB_0800da02:
        FUN_0800dc64();
      }
      break;
    default:
      if (uVar8 != 0) {
        if (bVar3 != 0) goto LAB_0800d7c0;
        goto LAB_0800da02;
      }
      if (bVar3 != 0) {
        if (uVar4 == 0x39) {
          uVar4 = 8000;
        }
        else {
          uVar4 = 1;
        }
        FUN_08013a7a(uVar4);
        uVar5 = extraout_r1_02;
LAB_0800d8a4:
        unregister_code(param_2 & 0xff,uVar5);
        break;
      }
      goto LAB_0800d9c6;
    }
  }
  if (uVar6 - 8 < 4) {
    FUN_08012138();
    FUN_0800d4ba();
  }
  if (bVar2 != 0) {
    bVar3 = FUN_0800e2ec();
    if ((bVar3 & 1) == 0) {
      *(byte *)((int)param_1 + 5) = bVar3 & 1;
      FUN_0800e2e0();
      FUN_0800dc64();
      FUN_0800dad8(param_1);
      FUN_0800e2e0();
      FUN_0800dc7c();
      return;
    }
  }
  return;
}

