// ===================================================================
// FUN_08008000 @ 0x08008000  size=226  body=[[08008000, 080080df] [080134f0, 080134f1]]

void FUN_08008000(void)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  code *pcVar5;
  
  disableIRQinterrupts();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setMainStackPointer(0x20000400);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(0x20000c00);
  }
  DAT_e000ed08 = 0x8000000;
  DAT_e000ef34 = 0xc0000000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ed88 = 0xf00000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ef3c = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setThreadModePrivileged(1);
    bVar1 = (bool)isThreadMode();
    if (bVar1) {
      cVar2 = isUsingMainStack();
      setStackMode(cVar2 == '\x01');
    }
  }
  InstructionSynchronizationBarrier(0xf);
  FUN_080134ec();
  FUN_08012c4c();
  for (puVar3 = &DAT_20000000; puVar3 < &DAT_20000400; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  for (puVar3 = &DAT_20000400; puVar3 < &DAT_20000c00; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  puVar3 = &DAT_0801774c;
  for (puVar4 = &DAT_20000c00; puVar4 < &DAT_200013b8; puVar4 = puVar4 + 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
  }
  for (puVar3 = &DAT_200013b8; puVar3 < &DAT_20004b88; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  FUN_080134f4();
  FUN_080134ee();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  FUN_0800f084();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// thunk_FUN_08008000 @ 0x0800811c  size=2  body=[[0800811c, 0800811d]]

void thunk_FUN_08008000(void)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  code *pcVar5;
  
  disableIRQinterrupts();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setMainStackPointer(0x20000400);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(0x20000c00);
  }
  DAT_e000ed08 = 0x8000000;
  DAT_e000ef34 = 0xc0000000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ed88 = 0xf00000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ef3c = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setThreadModePrivileged(1);
    bVar1 = (bool)isThreadMode();
    if (bVar1) {
      cVar2 = isUsingMainStack();
      setStackMode(cVar2 == '\x01');
    }
  }
  InstructionSynchronizationBarrier(0xf);
  FUN_080134ec();
  FUN_08012c4c();
  for (puVar3 = &DAT_20000000; puVar3 < &DAT_20000400; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  for (puVar3 = &DAT_20000400; puVar3 < &DAT_20000c00; puVar3 = puVar3 + 1) {
    *puVar3 = 0x55555555;
  }
  puVar3 = &DAT_0801774c;
  for (puVar4 = &DAT_20000c00; puVar4 < &DAT_200013b8; puVar4 = puVar4 + 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
  }
  for (puVar3 = &DAT_200013b8; puVar3 < &DAT_20004b88; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  FUN_080134f4();
  FUN_080134ee();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  FUN_0800f084();
  for (pcVar5 = FUN_08008000; (int)pcVar5 < 0x8008000; pcVar5 = pcVar5 + 4) {
    (**(code **)pcVar5)();
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// _unhandled_exception @ 0x0800811e  size=4  body=[[0800811e, 08008121]]

void _unhandled_exception(void)

{
  FUN_08008122();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// FUN_08008122 @ 0x08008122  size=2  body=[[08008122, 08008123]]

void FUN_08008122(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// FUN_08008124 @ 0x08008124  size=24  body=[[08008124, 0800813b]]

void FUN_08008124(undefined4 param_1,int param_2)

{
  undefined1 auStack_64 [64];
  
  *(undefined1 **)(param_2 + 0xc) = auStack_64;
  return;
}


// ===================================================================
// FUN_0800813c @ 0x0800813c  size=18  body=[[0800813c, 0800814d]]

void FUN_0800813c(void)

{
  bool bVar1;
  code *unaff_r4;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  (*unaff_r4)();
  thunk_FUN_08013a60(0);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// FUN_0800814e @ 0x0800814e  size=8  body=[[0800814e, 08008155]]

void FUN_0800814e(void)

{
  FUN_08013928();
  software_interrupt(0);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// FUN_08008158 @ 0x08008158  size=34  body=[[08008158, 08008177] [08008444, 08008445]]

undefined8 FUN_08008158(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined8 uVar1;
  uint local_8 [2];
  
  if ((param_4 == 0) && (param_3 == 0)) {
    if (param_2 != 0 || param_1 != 0) {
      param_2 = 0xffffffff;
      param_1 = 0xffffffff;
    }
    return CONCAT44(param_2,param_1);
  }
  uVar1 = FUN_08008188(param_1,param_2,param_3,param_4,local_8);
  return uVar1;
}


// ===================================================================
// FUN_08008178 @ 0x08008178  size=16  body=[[08008178, 08008187]]

undefined8 FUN_08008178(uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5)

{
  undefined8 uVar1;
  
  uVar1 = FUN_08008188(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}


// ===================================================================
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


// ===================================================================
// FUN_08008210 @ 0x08008210  size=20  body=[[08008210, 0800821f] [0800840e, 08008411]]

uint FUN_08008210(int param_1,int param_2,uint param_3,uint param_4)

{
  int unaff_r4;
  uint *unaff_r5;
  int unaff_r6;
  int in_r12;
  bool in_ZR;
  bool in_CY;
  
  if (in_CY && !in_ZR) {
    unaff_r4 = unaff_r4 + in_r12;
    param_4 = param_1 - 2;
  }
  if (unaff_r5 != (uint *)0x0) {
    *unaff_r5 = (uint)(unaff_r4 - unaff_r6) >> (param_3 & 0xff);
    unaff_r5[1] = 0;
  }
  return param_4 | param_2 << 0x10;
}


// ===================================================================
// FUN_08008220 @ 0x08008220  size=10  body=[[08008220, 08008229]]

void FUN_08008220(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint unaff_r4;
  uint *unaff_r5;
  
  if (unaff_r5 != (uint *)0x0) {
    *unaff_r5 = unaff_r4 >> (param_3 & 0xff);
    unaff_r5[1] = 0;
  }
  return;
}


// ===================================================================
// FUN_0800822a @ 0x0800822a  size=4  body=[[0800822a, 0800822d]]

void FUN_0800822a(void)

{
  return;
}


// ===================================================================
// FUN_08008448 @ 0x08008448  size=84  body=[[08008448, 0800849b]]

undefined8 FUN_08008448(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  uint extraout_r1;
  int iVar3;
  uint extraout_r2;
  uint extraout_r3;
  undefined8 uVar4;
  
  iVar1 = DAT_20000c00;
  iVar3 = *(int *)(DAT_20000c00 + 0x30);
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 0x10) = param_1;
    *(undefined4 *)(iVar3 + 0x14) = 0;
    return CONCAT44(param_2,param_1);
  }
  puVar2 = (undefined4 *)FUN_08008970(0x18);
  *(undefined4 **)(iVar1 + 0x30) = puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    puVar2[4] = 1;
    puVar2[5] = 0;
    puVar2[2] = 0x5deec;
    *puVar2 = 0xabcd330e;
    puVar2[1] = 0xe66d1234;
    *(undefined2 *)(puVar2 + 3) = 0xb;
    puVar2[4] = param_1;
    puVar2[5] = 0;
    return 0x5deecabcd330e;
  }
  FUN_08008544("../../../../../../newlib/libc/stdlib/rand.c",0x46,0,0x801765c);
  uVar4 = FUN_08008178(0,extraout_r1,extraout_r2,extraout_r3,param_4);
  return uVar4;
}


// ===================================================================
// FUN_080084ac @ 0x080084ac  size=136  body=[[080084ac, 08008533]]

ulonglong FUN_080084ac(void)

{
  longlong lVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 extraout_r1;
  int iVar4;
  uint extraout_r2;
  uint uVar5;
  
  iVar3 = DAT_20000c00;
  iVar4 = *(int *)(DAT_20000c00 + 0x30);
  if (iVar4 != 0) {
    lVar1 = (ulonglong)*(uint *)(iVar4 + 0x10) * 0x4c957f2d;
    uVar5 = (uint)lVar1;
    iVar3 = *(int *)(iVar4 + 0x14) * 0x4c957f2d + *(uint *)(iVar4 + 0x10) * 0x5851f42d +
            (int)((ulonglong)lVar1 >> 0x20) + (uint)(0xfffffffe < uVar5);
    *(uint *)(iVar4 + 0x10) = uVar5 + 1;
    *(int *)(iVar4 + 0x14) = iVar3;
    return CONCAT44(iVar3,iVar3) & 0xffffffff7fffffff;
  }
  puVar2 = (undefined4 *)FUN_08008970(0x18);
  *(undefined4 **)(iVar3 + 0x30) = puVar2;
  if (puVar2 != (undefined4 *)0x0) {
    puVar2[2] = 0x5deec;
    *puVar2 = 0xabcd330e;
    puVar2[1] = 0xe66d1234;
    *(undefined2 *)(puVar2 + 3) = 0xb;
    *(undefined8 *)(puVar2 + 4) = 1;
    puVar2[4] = 0x4c957f2e;
    puVar2[5] = 0x5851f42d;
    return 0x5851f42d5851f42d;
  }
  iVar3 = FUN_08008544("../../../../../../newlib/libc/stdlib/rand.c",0x52,0,0x801765c);
  uVar5 = FUN_08008210(0,iVar3,extraout_r2,(uint)&stack0x0000032c);
  return CONCAT44(extraout_r1,uVar5);
}


// ===================================================================
// FUN_08008544 @ 0x08008544  size=46  body=[[08008544, 08008571]]

void FUN_08008544(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int extraout_r2;
  undefined4 extraout_r3;
  uint *puVar1;
  
  puVar1 = *(uint **)(DAT_20000c00 + 0xc);
  do {
    FUN_080089ac(puVar1,(byte *)"assertion \"%s\" failed: file \"%s\", line %d%s%s\n",param_4,
                 param_1);
    FUN_080085e8();
    param_4 = extraout_r2;
    param_1 = extraout_r3;
  } while( true );
}


// ===================================================================
// FUN_08008584 @ 0x08008584  size=56  body=[[08008584, 080085bb]]

undefined1 * FUN_08008584(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint extraout_r2;
  undefined8 uVar4;
  
  uVar4 = FUN_08008544(param_1,param_2,0,param_3);
  puVar2 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
  uVar1 = (uint)uVar4;
  while (0x22 < extraout_r2 - 2) {
    *puVar2 = 0;
    uVar1 = 0;
  }
  puVar3 = puVar2;
  if ((extraout_r2 == 10) && ((int)uVar1 < 0)) {
    puVar3 = puVar2 + 1;
    *puVar2 = 0x2d;
    uVar1 = -uVar1;
  }
  FUN_080085f8(uVar1,puVar3,extraout_r2);
  return puVar2;
}


// ===================================================================
// itoa @ 0x080085bc  size=44  body=[[080085bc, 080085e7]]

// VERIFIED use: kc_raw_hid_rx case 0xA1 calls (1,&data[2],16),(0,&data[4],16),(0,&data[6],16) =
// get_firmware_version() itoa(...,16) for DEVICE_VER 0x0100

undefined1 * itoa(uint param_1,undefined1 *param_2,uint param_3)

{
  undefined1 *puVar1;
  
  if (param_3 - 2 < 0x23) {
    puVar1 = param_2;
    if ((param_3 == 10) && ((int)param_1 < 0)) {
      puVar1 = param_2 + 1;
      *param_2 = 0x2d;
      param_1 = -param_1;
    }
    FUN_080085f8(param_1,puVar1,param_3);
    return param_2;
  }
  *param_2 = 0;
  return (undefined1 *)0x0;
}


// ===================================================================
// FUN_080085e8 @ 0x080085e8  size=16  body=[[080085e8, 080085f7]]

undefined1 * FUN_080085e8(void)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  undefined1 *puVar4;
  uint extraout_r2;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  undefined8 uVar11;
  char acStack_48 [44];
  
  FUN_0800920c(6);
  uVar11 = FUN_080166dc();
  puVar4 = (undefined1 *)((ulonglong)uVar11 >> 0x20);
  builtin_strncpy(acStack_48,"0123456789abcdefghijklmnopqrstuvwxyz",0x25);
  if (extraout_r2 - 2 < 0x23) {
    pcVar9 = puVar4 + -1;
    uVar6 = (uint)uVar11;
    iVar8 = 0;
    do {
      iVar7 = iVar8;
      pcVar9 = pcVar9 + 1;
      *pcVar9 = acStack_48[uVar6 - extraout_r2 * (uVar6 / extraout_r2)];
      iVar8 = iVar7 + 1;
      bVar1 = extraout_r2 <= uVar6;
      uVar6 = uVar6 / extraout_r2;
    } while (bVar1);
    puVar4[iVar8] = 0;
    if (iVar7 != 0) {
      pcVar9 = puVar4 + iVar8;
      pcVar10 = puVar4 + -1;
      do {
        pcVar2 = pcVar10 + 1;
        cVar3 = *pcVar2;
        pcVar9 = pcVar9 + -1;
        *pcVar2 = *pcVar9;
        pcVar5 = pcVar10 + (2 - (int)puVar4);
        *pcVar9 = cVar3;
        pcVar10 = pcVar2;
      } while ((int)pcVar5 < (int)(puVar4 + iVar7 + (-1 - (int)pcVar2)));
    }
    return puVar4;
  }
  *puVar4 = 0;
  return (undefined1 *)0x0;
}


// ===================================================================
// FUN_080085f8 @ 0x080085f8  size=152  body=[[080085f8, 0800868f]]

undefined1 * FUN_080085f8(uint param_1,undefined1 *param_2,uint param_3)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char local_40 [44];
  
  builtin_strncpy(local_40,"0123456789abcdefghijklmnopqrstuvwxyz",0x25);
  if (param_3 - 2 < 0x23) {
    pcVar7 = param_2 + -1;
    iVar6 = 0;
    do {
      iVar5 = iVar6;
      pcVar7 = pcVar7 + 1;
      *pcVar7 = local_40[param_1 - param_3 * (param_1 / param_3)];
      iVar6 = iVar5 + 1;
      bVar1 = param_3 <= param_1;
      param_1 = param_1 / param_3;
    } while (bVar1);
    param_2[iVar6] = 0;
    if (iVar5 != 0) {
      pcVar7 = param_2 + iVar6;
      pcVar8 = param_2 + -1;
      do {
        pcVar2 = pcVar8 + 1;
        cVar3 = *pcVar2;
        pcVar7 = pcVar7 + -1;
        *pcVar2 = *pcVar7;
        pcVar4 = pcVar8 + (2 - (int)param_2);
        *pcVar7 = cVar3;
        pcVar8 = pcVar2;
      } while ((int)pcVar4 < (int)(param_2 + iVar5 + (-1 - (int)pcVar2)));
    }
    return param_2;
  }
  *param_2 = 0;
  return (undefined1 *)0x0;
}


// ===================================================================
// thunk_FUN_080085f8 @ 0x08008694  size=4  body=[[08008694, 08008697]]

undefined1 * thunk_FUN_080085f8(uint param_1,undefined1 *param_2,uint param_3)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char acStack_40 [44];
  
  builtin_strncpy(acStack_40,"0123456789abcdefghijklmnopqrstuvwxyz",0x25);
  if (param_3 - 2 < 0x23) {
    pcVar7 = param_2 + -1;
    iVar6 = 0;
    do {
      iVar5 = iVar6;
      pcVar7 = pcVar7 + 1;
      *pcVar7 = acStack_40[param_1 - param_3 * (param_1 / param_3)];
      iVar6 = iVar5 + 1;
      bVar1 = param_3 <= param_1;
      param_1 = param_1 / param_3;
    } while (bVar1);
    param_2[iVar6] = 0;
    if (iVar5 != 0) {
      pcVar7 = param_2 + iVar6;
      pcVar8 = param_2 + -1;
      do {
        pcVar2 = pcVar8 + 1;
        cVar3 = *pcVar2;
        pcVar7 = pcVar7 + -1;
        *pcVar2 = *pcVar7;
        pcVar4 = pcVar8 + (2 - (int)param_2);
        *pcVar7 = cVar3;
        pcVar8 = pcVar2;
      } while ((int)pcVar4 < (int)(param_2 + iVar5 + (-1 - (int)pcVar2)));
    }
    return param_2;
  }
  *param_2 = 0;
  return (undefined1 *)0x0;
}


// ===================================================================
// FUN_080086c0 @ 0x080086c0  size=216  body=[[080086c0, 08008797]]

int FUN_080086c0(uint param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  
  HintPreloadData(param_1);
  puVar7 = (uint *)(param_1 & 0xfffffff8);
  HintPreloadData(puVar7 + 8);
  if ((param_1 & 7) != 0) {
    uVar9 = puVar7[1];
    iVar6 = -(param_1 & 7);
    HintPreloadData(puVar7 + 0x10);
    uVar10 = -1 << ((param_1 & 3) << 3);
    uVar8 = *puVar7 | ~uVar10;
    if ((param_1 & 4) == 0) goto LAB_080086ee;
    uVar9 = uVar9 | ~uVar10;
    uVar8 = 0xffffffff;
    goto LAB_080086ee;
  }
  iVar5 = -8;
  do {
    uVar9 = puVar7[1];
    HintPreloadData(puVar7 + 0x10);
    iVar6 = iVar5 + 8;
    uVar8 = *puVar7;
LAB_080086ee:
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    iVar5 = iVar6;
    if (uVar9 != 0) break;
    uVar8 = puVar7[2];
    uVar9 = puVar7[3];
    iVar5 = iVar6 + 8;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    if (uVar9 != 0) break;
    uVar8 = puVar7[4];
    uVar9 = puVar7[5];
    iVar5 = iVar6 + 0x10;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    if (uVar9 != 0) break;
    uVar8 = puVar7[6];
    uVar9 = puVar7[7];
    puVar7 = puVar7 + 8;
    iVar5 = iVar6 + 0x18;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
  } while (uVar9 == 0);
  if (uVar8 == 0) {
    iVar5 = iVar5 + 4;
    uVar8 = uVar9;
  }
  return iVar5 + ((uint)LZCOUNT(uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 |
                                (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18) >> 3);
}


// ===================================================================
// FUN_08008798 @ 0x08008798  size=162  body=[[08008798, 08008839]]

void FUN_08008798(byte *param_1,byte param_2,uint param_3)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  
  for (; ((uint)param_1 & 3) != 0; param_1 = param_1 + 1) {
    if (param_3 == 0) {
      return;
    }
    param_3 = param_3 - 1;
    *param_1 = param_2;
  }
  if (3 < param_3) {
    iVar1 = (uint)param_2 * 0x1010101;
    if (0xf < param_3) {
      pbVar2 = param_1;
      do {
        *(int *)pbVar2 = iVar1;
        *(int *)(pbVar2 + 4) = iVar1;
        *(int *)(pbVar2 + 8) = iVar1;
        *(int *)(pbVar2 + 0xc) = iVar1;
        pbVar2 = pbVar2 + 0x10;
      } while (pbVar2 != param_1 + (param_3 - 0x10 & 0xfffffff0) + 0x10);
      uVar4 = param_3 & 0xc;
      param_1 = param_1 + ((param_3 - 0x10 >> 4) + 1) * 0x10;
      param_3 = param_3 & 0xf;
      if (uVar4 == 0) goto joined_r0x08008814;
    }
    uVar4 = param_3 - 4;
    pbVar2 = param_1;
    do {
      pbVar3 = pbVar2 + 4;
      *(int *)pbVar2 = iVar1;
      pbVar2 = pbVar3;
    } while (param_1 + (uVar4 & 0xfffffffc) + 4 != pbVar3);
    param_3 = param_3 & 3;
    param_1 = param_1 + (uVar4 & 0xfffffffc) + 4;
  }
joined_r0x08008814:
  if (param_3 != 0) {
    pbVar2 = param_1;
    do {
      pbVar3 = pbVar2 + 1;
      *pbVar2 = param_2;
      pbVar2 = pbVar3;
    } while (pbVar3 != param_1 + param_3);
  }
  return;
}


// ===================================================================
// memcpy @ 0x0800883c  size=306  body=[[0800883c, 08008921] [08008924, 0800896f]]

// INFERRED: 40 callers, (dst,src,n) with n=20 copying the build-date string in
// get_firmware_version; 306-byte newlib-style body

undefined4 * memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  puVar2 = param_1;
  if ((((uint)param_2 | (uint)param_1) & 3) != 0) {
    if (param_3 < 8) {
      uVar5 = param_3 - 4;
      if (3 < param_3) {
        do {
          puVar1 = param_2;
          puVar3 = puVar2;
          bVar6 = uVar5 != 0;
          uVar5 = uVar5 - 1;
          *(undefined1 *)puVar3 = *(undefined1 *)puVar1;
          puVar2 = (undefined4 *)((int)puVar3 + 1);
          param_2 = (undefined4 *)((int)puVar1 + 1);
        } while (bVar6);
        *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)puVar1 + 1);
        *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)puVar1 + 2);
        *(undefined1 *)((int)puVar3 + 3) = *(undefined1 *)((int)puVar1 + 3);
        return param_1;
      }
      goto LAB_08008908;
    }
    if ((((uint)param_2 & 3) != 0) && (((uint)param_1 & 3) != 0)) {
      uVar5 = 4 - ((uint)param_1 & 3);
      param_3 = param_3 - uVar5;
      puVar1 = param_1;
      puVar3 = param_2;
      if (((uint)param_1 & 1) != 0) {
        puVar3 = (undefined4 *)((int)param_2 + 1);
        puVar1 = (undefined4 *)((int)param_1 + 1);
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
      }
      puVar2 = puVar1;
      param_2 = puVar3;
      if ((uVar5 & 2) != 0) {
        param_2 = (undefined4 *)((int)puVar3 + 2);
        puVar2 = (undefined4 *)((int)puVar1 + 2);
        *(undefined2 *)puVar1 = *(undefined2 *)puVar3;
      }
    }
  }
  while (0x3f < param_3) {
    *puVar2 = *param_2;
    puVar2[1] = param_2[1];
    puVar2[2] = param_2[2];
    puVar2[3] = param_2[3];
    puVar2[4] = param_2[4];
    puVar2[5] = param_2[5];
    puVar2[6] = param_2[6];
    puVar2[7] = param_2[7];
    puVar2[8] = param_2[8];
    puVar2[9] = param_2[9];
    puVar2[10] = param_2[10];
    puVar2[0xb] = param_2[0xb];
    puVar2[0xc] = param_2[0xc];
    puVar2[0xd] = param_2[0xd];
    puVar2[0xe] = param_2[0xe];
    puVar2[0xf] = param_2[0xf];
    puVar2 = puVar2 + 0x10;
    param_2 = param_2 + 0x10;
    param_3 = param_3 - 0x40;
  }
  uVar4 = param_3 - 0x10;
  if (0xffffffcf < param_3 - 0x40) {
    do {
      *puVar2 = *param_2;
      puVar2[1] = param_2[1];
      puVar1 = param_2 + 3;
      puVar3 = puVar2 + 3;
      puVar2[2] = param_2[2];
      param_2 = param_2 + 4;
      puVar2 = puVar2 + 4;
      *puVar3 = *puVar1;
      bVar6 = 0xf < uVar4;
      uVar4 = uVar4 - 0x10;
    } while (bVar6);
  }
  uVar5 = uVar4 + 0xc;
  puVar3 = puVar2;
  puVar1 = param_2;
  if (0xfffffff3 < uVar4) {
    do {
      param_2 = puVar1 + 1;
      *puVar3 = *puVar1;
      bVar6 = 3 < uVar5;
      uVar5 = uVar5 - 4;
      puVar2 = puVar3 + 1;
      puVar3 = puVar3 + 1;
      puVar1 = param_2;
    } while (bVar6);
  }
LAB_08008908:
  if (uVar5 + 4 != 0) {
    puVar1 = puVar2;
    puVar3 = param_2;
    if ((uVar5 & 1) != 0) {
      puVar3 = (undefined4 *)((int)param_2 + 1);
      puVar1 = (undefined4 *)((int)puVar2 + 1);
      *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    }
    if ((uVar5 + 4 & 2) != 0) {
      *(undefined2 *)puVar1 = *(undefined2 *)puVar3;
    }
  }
  return param_1;
}


// ===================================================================
// FUN_08008970 @ 0x08008970  size=10  body=[[08008970, 08008979]]

void FUN_08008970(uint param_1)

{
  FUN_08009758(DAT_20000c00,param_1);
  return;
}


// ===================================================================
// FUN_08008980 @ 0x08008980  size=10  body=[[08008980, 08008989]]

void FUN_08008980(int param_1)

{
  FUN_08009858(DAT_20000c00,param_1);
  return;
}


// ===================================================================
// FUN_08008990 @ 0x08008990  size=28  body=[[08008990, 080089ab]]

void FUN_08008990(uint *param_1,uint *param_2,byte *param_3,int param_4)

{
  int iStack_4;
  
  iStack_4 = param_4;
  FUN_08008abc(param_1,param_2,param_3,&iStack_4);
  return;
}


// ===================================================================
// FUN_080089ac @ 0x080089ac  size=34  body=[[080089ac, 080089cd]]

void FUN_080089ac(uint *param_1,byte *param_2,int param_3,undefined4 param_4)

{
  int iStack_8;
  undefined4 uStack_4;
  
  iStack_8 = param_3;
  uStack_4 = param_4;
  FUN_08008abc(DAT_20000c00,param_1,param_2,&iStack_8);
  return;
}


// ===================================================================
// FUN_080089d4 @ 0x080089d4  size=92  body=[[080089d4, 08008a2f]]

int FUN_080089d4(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if (3 < param_3) {
    piVar1 = param_1;
    piVar2 = param_2;
    if ((((uint)param_2 | (uint)param_1) & 3) != 0) goto LAB_08008a0a;
    do {
      param_2 = piVar2 + 1;
      param_1 = piVar1 + 1;
      if (*piVar1 != *piVar2) goto LAB_08008a0a;
      param_3 = param_3 - 4;
      piVar2 = param_2;
      piVar1 = param_1;
    } while (3 < param_3);
  }
  piVar1 = param_1;
  piVar2 = param_2;
  if (param_3 == 0) {
    return 0;
  }
LAB_08008a0a:
  pbVar4 = (byte *)((int)piVar1 + -1);
  pbVar3 = (byte *)((int)piVar2 + -1);
  do {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if ((uint)*pbVar4 != (uint)*pbVar3) {
      return (uint)*pbVar4 - (uint)*pbVar3;
    }
  } while ((byte *)((int)piVar1 + (param_3 - 1)) != pbVar4);
  return 0;
}


// ===================================================================
// FUN_08008a30 @ 0x08008a30  size=58  body=[[08008a30, 08008a69]]

uint FUN_08008a30(uint *param_1,uint param_2,uint *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  uVar2 = param_3[2] - 1;
  param_3[2] = uVar2;
  bVar1 = (byte)param_2;
  if (-1 < (int)uVar2) {
    pbVar3 = (byte *)*param_3;
    *param_3 = (uint)(pbVar3 + 1);
    *pbVar3 = bVar1;
    return param_2;
  }
  if (((int)param_3[6] <= (int)uVar2) && (param_2 != 10)) {
    pbVar3 = (byte *)*param_3;
    *param_3 = (uint)(pbVar3 + 1);
    *pbVar3 = bVar1;
    return param_2;
  }
  uVar2 = FUN_08008d44(param_1,bVar1,param_3);
  return uVar2;
}


// ===================================================================
// FUN_08008a6c @ 0x08008a6c  size=46  body=[[08008a6c, 08008a99]]

undefined4 FUN_08008a6c(uint *param_1,uint *param_2,int param_3,int param_4)

{
  uint uVar1;
  byte *pbVar2;
  
  if (param_4 == 0) {
    return 0;
  }
  pbVar2 = (byte *)(param_3 + -1);
  do {
    pbVar2 = pbVar2 + 1;
    uVar1 = FUN_08008a30(param_1,(uint)*pbVar2,param_2);
    if (uVar1 == 0xffffffff) {
      return 0xffffffff;
    }
  } while (pbVar2 != (byte *)(param_4 + param_3 + -1));
  return 0;
}


// ===================================================================
// FUN_08008a9c @ 0x08008a9c  size=30  body=[[08008a9c, 08008ab9]]

undefined4 FUN_08008a9c(uint *param_1,uint *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_3[2] == 0) {
    param_3[1] = 0;
    return 0;
  }
  uVar1 = FUN_08008de4(param_1,param_2,param_3);
  param_3[2] = 0;
  param_3[1] = 0;
  return uVar1;
}


// ===================================================================
// FUN_08008abc @ 0x08008abc  size=598  body=[[08008abc, 08008d11]]

// WARNING: Removing unreachable block (ram,0x08008bd0)
// WARNING: Type propagation algorithm not settling

int FUN_08008abc(uint *param_1,uint *param_2,byte *param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint local_9c;
  int *local_8c;
  uint local_88;
  int local_84;
  undefined4 uStack_80;
  int local_7c;
  int local_74;
  byte local_70;
  undefined2 local_6f;
  undefined1 local_45;
  undefined4 local_30;
  
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  if ((((int)((uint)(ushort)param_2[3] << 0x1c) < 0) && (param_2[4] != 0)) ||
     (iVar1 = FUN_08009b00(param_1,param_2), iVar1 == 0)) {
    local_74 = 0;
    local_6f = 0x3020;
    bVar4 = *param_3;
    local_8c = param_4;
    while (pbVar8 = param_3, bVar4 != 0) {
      do {
        if (bVar4 == 0x25) {
          pbVar7 = pbVar8 + -(int)param_3;
          if (pbVar7 != (byte *)0x0) goto LAB_08008c22;
          bVar4 = *pbVar8;
          goto LAB_08008b22;
        }
        pbVar8 = pbVar8 + 1;
        bVar4 = *pbVar8;
      } while (bVar4 != 0);
      pbVar7 = pbVar8 + -(int)param_3;
      if (pbVar7 == (byte *)0x0) break;
LAB_08008c22:
      pbVar5 = param_3 + -1;
      do {
        uVar2 = FUN_08008a30(param_1,(uint)pbVar5[1],param_2);
        pbVar6 = pbVar5 + (2 - (int)param_3);
        if (uVar2 == 0xffffffff) goto LAB_08008bf8;
        pbVar5 = pbVar5 + 1;
      } while (pbVar6 < pbVar7);
      local_74 = local_74 + (int)pbVar7;
      bVar4 = *pbVar8;
LAB_08008b22:
      if (bVar4 == 0) break;
      local_84 = -1;
      uStack_80 = 0;
      local_88 = 0;
      local_7c = 0;
      local_45 = 0;
      local_30 = 0;
      pbVar8 = pbVar8 + 1;
      while( true ) {
        pbVar5 = pbVar8 + 1;
        pbVar7 = FUN_08009a60((uint *)"#-0+ ",(uint)*pbVar8,5);
        if (pbVar7 == (byte *)0x0) break;
        local_88 = local_88 | 1 << ((uint)(pbVar7 + -0x8017708) & 0xff);
        pbVar8 = pbVar5;
      }
      if ((int)(local_88 << 0x1b) < 0) {
        local_45 = 0x20;
      }
      uVar2 = (uint)*pbVar8;
      if ((int)(local_88 << 0x1c) < 0) {
        local_45 = 0x2b;
      }
      if (uVar2 == 0x2a) {
        local_7c = *local_8c;
        local_8c = local_8c + 1;
        if (local_7c < 0) {
          local_7c = -local_7c;
          local_88 = local_88 | 2;
        }
        uVar2 = (uint)pbVar8[1];
        pbVar8 = pbVar5;
      }
      else {
        uVar3 = uVar2 - 0x30;
        if (uVar3 < 10) {
          while( true ) {
            uVar2 = (uint)*pbVar5;
            local_7c = uVar3 + local_7c * 10;
            uVar3 = uVar2 - 0x30;
            pbVar8 = pbVar5;
            if (9 < uVar3) break;
            pbVar5 = pbVar5 + 1;
          }
        }
      }
      if (uVar2 == 0x2e) {
        uVar2 = (uint)pbVar8[1];
        if (uVar2 == 0x2a) {
          uVar2 = (uint)pbVar8[2];
          local_84 = *local_8c;
          local_8c = local_8c + 1;
          pbVar8 = pbVar8 + 2;
          if (local_84 < 0) {
            local_84 = -1;
          }
        }
        else {
          local_84 = 0;
          pbVar8 = pbVar8 + 1;
          while (uVar2 - 0x30 < 10) {
            pbVar8 = pbVar8 + 1;
            local_84 = (uVar2 - 0x30) + local_84 * 10;
            uVar2 = (uint)*pbVar8;
          }
        }
      }
      pbVar7 = FUN_08009a60((uint *)&DAT_08017710,uVar2,3);
      if (pbVar7 != (byte *)0x0) {
        local_88 = local_88 | 0x40 << ((uint)(pbVar7 + -0x8017710) & 0xff);
        pbVar8 = pbVar8 + 1;
      }
      param_3 = pbVar8 + 1;
      local_70 = *pbVar8;
      pbVar8 = FUN_08009a60((uint *)"efgEFG",(uint)local_70,6);
      if (pbVar8 == (byte *)0x0) {
        local_9c = FUN_08009d4c(param_1,&local_88,param_2,(undefined *)0x8008a6d,(int *)&local_8c);
        if (local_9c == 0xffffffff) break;
      }
      else {
        local_8c = (int *)(((int)local_8c + 7U & 0xfffffff8) + 8);
      }
      local_74 = local_74 + local_9c;
      bVar4 = *param_3;
    }
LAB_08008bf8:
    if (-1 < (int)((uint)(ushort)param_2[3] << 0x19)) {
      return local_74;
    }
  }
  return -1;
}


// ===================================================================
// FUN_08008d28 @ 0x08008d28  size=22  body=[[08008d28, 08008d3d]]

void FUN_08008d28(uint *param_1,byte *param_2,int *param_3)

{
  FUN_08008abc(DAT_20000c00,param_1,param_2,param_3);
  return;
}


// ===================================================================
// FUN_08008d44 @ 0x08008d44  size=134  body=[[08008d44, 08008dc9]]

uint FUN_08008d44(uint *param_1,byte param_2,uint *param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  param_3[2] = param_3[6];
  if ((-1 < (int)((uint)(ushort)param_3[3] << 0x1c)) || (uVar3 = param_3[4], uVar3 == 0)) {
    iVar1 = FUN_08009b00(param_1,param_3);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    uVar3 = param_3[4];
  }
  pbVar2 = (byte *)*param_3;
  uVar4 = (uint)param_2;
  if ((int)((int)pbVar2 - uVar3) < (int)param_3[5]) {
    uVar3 = ((int)pbVar2 - uVar3) + 1;
  }
  else {
    iVar1 = FUN_0800968c(param_1,(int *)param_3);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    pbVar2 = (byte *)*param_3;
    uVar3 = 1;
  }
  param_3[2] = param_3[2] - 1;
  *param_3 = (uint)(pbVar2 + 1);
  *pbVar2 = param_2;
  if (param_3[5] != uVar3) {
    if (-1 < (int)((uint)(ushort)param_3[3] << 0x1f)) {
      return uVar4;
    }
    if (uVar4 != 10) {
      return uVar4;
    }
  }
  iVar1 = FUN_0800968c(param_1,(int *)param_3);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  return uVar4;
}


// ===================================================================
// FUN_08008dcc @ 0x08008dcc  size=20  body=[[08008dcc, 08008ddf]]

void FUN_08008dcc(byte param_1,uint *param_2)

{
  FUN_08008d44(DAT_20000c00,param_1,param_2);
  return;
}


// ===================================================================
// FUN_08008de4 @ 0x08008de4  size=762  body=[[08008de4, 080090dd]]

undefined4 FUN_08008de4(uint *param_1,uint *param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  byte *pbVar5;
  ushort uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  int *piVar13;
  int *piVar14;
  int iVar15;
  undefined4 *puVar16;
  byte *pbVar17;
  code *pcVar18;
  uint *puVar19;
  byte *local_30;
  
  if (param_3[2] == 0) {
    return 0;
  }
  uVar6 = (ushort)param_2[3];
  if (((uVar6 & 8) == 0) || (param_2[4] == 0)) {
    iVar15 = FUN_08009b00(param_1,param_2);
    if (iVar15 != 0) {
      return 0xffffffff;
    }
    uVar6 = (ushort)param_2[3];
    piVar13 = (int *)*param_3;
  }
  else {
    piVar13 = (int *)*param_3;
  }
  if ((uVar6 & 2) != 0) {
    iVar15 = 0;
    pcVar18 = (code *)param_2[10];
    uVar4 = param_2[8];
    uVar10 = 0;
    do {
      uVar8 = uVar10;
      if (0x7ffffbff < uVar10) {
        uVar8 = 0x7ffffc00;
      }
      while (uVar10 != 0) {
        iVar2 = (*pcVar18)(param_1,uVar4,iVar15,uVar8);
        if (iVar2 < 1) goto LAB_08008fc8;
        iVar7 = param_3[2];
        iVar15 = iVar15 + iVar2;
        uVar10 = uVar10 - iVar2;
        param_3[2] = iVar7 - iVar2;
        if (iVar7 - iVar2 == 0) {
          return 0;
        }
        pcVar18 = (code *)param_2[10];
        uVar4 = param_2[8];
        uVar8 = uVar10;
        if (0x7ffffbff < uVar10) {
          uVar8 = 0x7ffffc00;
        }
      }
      iVar15 = *piVar13;
      uVar10 = piVar13[1];
      piVar13 = piVar13 + 2;
    } while( true );
  }
  if ((uVar6 & 1) == 0) {
    puVar9 = (undefined4 *)*param_2;
    uVar4 = param_2[2];
    uVar10 = 0;
    puVar16 = (undefined4 *)0x0;
    while( true ) {
      while (uVar10 == 0) {
        puVar16 = (undefined4 *)*piVar13;
        puVar19 = (uint *)(piVar13 + 1);
        piVar13 = piVar13 + 2;
        uVar10 = *puVar19;
      }
      if ((uVar6 & 0x200) == 0) {
        if (((undefined4 *)param_2[4] < puVar9) || (uVar8 = param_2[5], uVar10 < uVar8)) {
          if (uVar10 <= uVar4) {
            uVar4 = uVar10;
          }
          FUN_08009914(puVar9,puVar16,uVar4);
          uVar8 = param_2[2];
          param_2[2] = uVar8 - uVar4;
          *param_2 = *param_2 + uVar4;
          if ((uVar8 - uVar4 == 0) && (iVar15 = FUN_0800968c(param_1,(int *)param_2), iVar15 != 0))
          goto LAB_08008fc8;
        }
        else {
          uVar4 = 0x7fffffff;
          if (uVar10 < 0x80000000) {
            uVar4 = uVar10;
          }
          uVar4 = (*(code *)param_2[10])
                            (param_1,param_2[8],puVar16,uVar8 * ((int)uVar4 / (int)uVar8));
          if ((int)uVar4 < 1) goto LAB_08008fc8;
        }
        uVar8 = uVar10 - uVar4;
      }
      else {
        uVar8 = uVar10;
        if ((uVar4 <= uVar10) && (uVar8 = uVar4, (uVar6 & 0x480) != 0)) {
          uVar11 = (int)puVar9 - (int)param_2[4];
          uVar4 = (int)(param_2[5] * 3) / 2;
          uVar8 = uVar11 + 1 + uVar10;
          if (uVar4 < uVar8) {
            uVar4 = uVar8;
          }
          if ((uVar6 & 0x400) == 0) {
            puVar3 = FUN_08009bc4(param_1,(undefined4 *)param_2[4],uVar4);
            if (puVar3 == (undefined4 *)0x0) {
              FUN_08009858(param_1,param_2[4]);
              uVar4 = param_2[3];
              *param_1 = 0xc;
              uVar6 = (ushort)uVar4 & 0xff7f;
              goto LAB_08008fcc;
            }
          }
          else {
            puVar3 = (undefined4 *)FUN_08009758(param_1,uVar4);
            if (puVar3 == (undefined4 *)0x0) {
              uVar6 = (ushort)param_2[3];
              *param_1 = 0xc;
              goto LAB_08008fcc;
            }
            memcpy(puVar3,(undefined4 *)param_2[4],uVar11);
            *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfb7f | 0x80;
          }
          puVar9 = (undefined4 *)((int)puVar3 + uVar11);
          param_2[5] = uVar4;
          param_2[4] = (uint)puVar3;
          param_2[2] = uVar4 - uVar11;
          *param_2 = (uint)puVar9;
          uVar8 = uVar10;
        }
        FUN_08009914(puVar9,puVar16,uVar8);
        param_2[2] = param_2[2] - uVar8;
        *param_2 = uVar8 + *param_2;
        uVar8 = 0;
        uVar4 = uVar10;
      }
      iVar15 = param_3[2];
      puVar16 = (undefined4 *)((int)puVar16 + uVar4);
      param_3[2] = iVar15 - uVar4;
      if (iVar15 - uVar4 == 0) break;
      puVar9 = (undefined4 *)*param_2;
      uVar4 = param_2[2];
      uVar6 = (ushort)param_2[3];
      uVar10 = uVar8;
    }
  }
  else {
    bVar1 = false;
    pbVar12 = (byte *)0x0;
    puVar19 = (uint *)0x0;
    local_30 = (byte *)0x0;
    do {
      if (pbVar12 == (byte *)0x0) {
        do {
          piVar14 = piVar13;
          pbVar12 = (byte *)piVar14[1];
          piVar13 = piVar14 + 2;
        } while (pbVar12 == (byte *)0x0);
        puVar19 = (uint *)*piVar14;
LAB_08008fee:
        local_30 = FUN_08009a60(puVar19,10,(uint)pbVar12);
        if (local_30 == (byte *)0x0) {
          local_30 = pbVar12 + 1;
        }
        else {
          local_30 = local_30 + (1 - (int)puVar19);
        }
      }
      else if (!bVar1) goto LAB_08008fee;
      puVar9 = (undefined4 *)*param_2;
      pbVar5 = local_30;
      if (pbVar12 <= local_30) {
        pbVar5 = pbVar12;
      }
      if (((undefined4 *)param_2[4] < puVar9) &&
         (pbVar17 = (byte *)(param_2[2] + param_2[5]), (int)pbVar17 < (int)pbVar5)) {
        FUN_08009914(puVar9,puVar19,(uint)pbVar17);
        *param_2 = (uint)(pbVar17 + *param_2);
        iVar15 = FUN_0800968c(param_1,(int *)param_2);
        if (iVar15 != 0) {
LAB_08008fc8:
          uVar6 = (ushort)param_2[3];
LAB_08008fcc:
          *(ushort *)(param_2 + 3) = uVar6 | 0x40;
          return 0xffffffff;
        }
      }
      else if ((int)pbVar5 < (int)param_2[5]) {
        FUN_08009914(puVar9,puVar19,(uint)pbVar5);
        param_2[2] = param_2[2] - (int)pbVar5;
        *param_2 = (uint)(pbVar5 + *param_2);
        pbVar17 = pbVar5;
      }
      else {
        pbVar17 = (byte *)(*(code *)param_2[10])(param_1,param_2[8],puVar19);
        if ((int)pbVar17 < 1) goto LAB_08008fc8;
      }
      local_30 = local_30 + -(int)pbVar17;
      if (local_30 == (byte *)0x0) {
        iVar15 = FUN_0800968c(param_1,(int *)param_2);
        bVar1 = false;
        if (iVar15 != 0) goto LAB_08008fc8;
      }
      else {
        bVar1 = true;
      }
      iVar15 = param_3[2];
      puVar19 = (uint *)((int)puVar19 + (int)pbVar17);
      pbVar12 = pbVar12 + -(int)pbVar17;
      param_3[2] = iVar15 - (int)pbVar17;
    } while (iVar15 - (int)pbVar17 != 0);
  }
  return 0;
}


// ===================================================================
// FUN_080090e4 @ 0x080090e4  size=44  body=[[080090e4, 0800910f]]

undefined4 FUN_080090e4(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1[0xf] == 0) {
    uVar1 = FUN_08009758(param_1,0x80);
    param_1[0xf] = uVar1;
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar1 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar1 + 0x7c));
  }
  return 0;
}


// ===================================================================
// FUN_08009110 @ 0x08009110  size=74  body=[[08009110, 08009159]]

undefined4 FUN_08009110(undefined4 *param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (param_2 < 0x20) {
    uVar3 = param_1[0xf];
    if (uVar3 == 0) {
      uVar3 = FUN_08009758(param_1,0x80);
      param_1[0xf] = uVar3;
      if (uVar3 == 0) goto LAB_08009130;
      puVar2 = (undefined4 *)(uVar3 - 4);
      do {
        puVar2 = puVar2 + 1;
        *puVar2 = 0;
      } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
    }
    uVar1 = *(undefined4 *)(uVar3 + param_2 * 4);
    *(undefined4 *)(uVar3 + param_2 * 4) = param_3;
  }
  else {
    *param_1 = 0x16;
LAB_08009130:
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ===================================================================
// FUN_0800915e @ 0x0800915e  size=78  body=[[0800915e, 080091ab]]

undefined4 FUN_0800915e(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  code *pcVar3;
  bool in_ZR;
  bool in_CY;
  
  if (in_CY && !in_ZR) {
    *param_1 = 0x16;
    return 0xffffffff;
  }
  iVar2 = param_1[0xf];
  if ((iVar2 != 0) && (pcVar3 = *(code **)(iVar2 + param_2 * 4), pcVar3 != (code *)0x0)) {
    if (pcVar3 != (code *)0x1) {
      if (pcVar3 == (code *)0xffffffff) {
        *param_1 = 0x16;
        return 1;
      }
      *(undefined4 *)(iVar2 + param_2 * 4) = 0;
      (*pcVar3)(param_2);
    }
    return 0;
  }
  thunk_FUN_080166fc();
  uVar1 = FUN_0800a190(param_1);
  return uVar1;
}


// ===================================================================
// FUN_080091ac @ 0x080091ac  size=96  body=[[080091ac, 0800920b]]

undefined4 FUN_080091ac(undefined4 *param_1,uint param_2)

{
  code *pcVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (0x1f < param_2) {
    return 0xffffffff;
  }
  uVar3 = param_1[0xf];
  if (uVar3 == 0) {
    uVar3 = FUN_08009758(param_1,0x80);
    param_1[0xf] = uVar3;
    if (uVar3 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar3 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
  }
  pcVar1 = *(code **)(uVar3 + param_2 * 4);
  if (pcVar1 == (code *)0x0) {
    return 1;
  }
  if (pcVar1 == (code *)0xffffffff) {
    return 2;
  }
  if (pcVar1 == (code *)0x1) {
    return 3;
  }
  *(undefined4 *)(uVar3 + param_2 * 4) = 0;
  (*pcVar1)(param_2);
  return 0;
}


// ===================================================================
// FUN_0800920c @ 0x0800920c  size=80  body=[[0800920c, 0800925b]]

undefined4 FUN_0800920c(uint param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  
  piVar1 = DAT_20000c00;
  if (0x1f < param_1) {
    *DAT_20000c00 = 0x16;
    return 0xffffffff;
  }
  iVar3 = DAT_20000c00[0xf];
  if ((iVar3 != 0) && (pcVar4 = *(code **)(iVar3 + param_1 * 4), pcVar4 != (code *)0x0)) {
    if (pcVar4 != (code *)0x1) {
      if (pcVar4 == (code *)0xffffffff) {
        *DAT_20000c00 = 0x16;
        return 1;
      }
      *(undefined4 *)(iVar3 + param_1 * 4) = 0;
      (*pcVar4)();
    }
    return 0;
  }
  thunk_FUN_080166fc();
  uVar2 = FUN_0800a190(piVar1);
  return uVar2;
}


// ===================================================================
// FUN_08009260 @ 0x08009260  size=70  body=[[08009260, 080092a5]]

undefined4 FUN_08009260(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  puVar2 = DAT_20000c00;
  if (0x1f < param_1) {
    *DAT_20000c00 = 0x16;
    return 0xffffffff;
  }
  uVar3 = DAT_20000c00[0xf];
  if (uVar3 == 0) {
    uVar3 = FUN_08009758(DAT_20000c00,0x80);
    puVar2[0xf] = uVar3;
    if (uVar3 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar3 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar3 + 0x7c));
  }
  uVar1 = *(undefined4 *)(uVar3 + param_1 * 4);
  *(undefined4 *)(uVar3 + param_1 * 4) = param_2;
  return uVar1;
}


// ===================================================================
// FUN_080092ac @ 0x080092ac  size=48  body=[[080092ac, 080092db]]

undefined4 FUN_080092ac(void)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = DAT_20000c00;
  if (DAT_20000c00[0xf] == 0) {
    uVar1 = FUN_08009758(DAT_20000c00,0x80);
    puVar2[0xf] = uVar1;
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    puVar2 = (undefined4 *)(uVar1 - 4);
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
    } while (puVar2 != (undefined4 *)(uVar1 + 0x7c));
  }
  return 0;
}


// ===================================================================
// FUN_080092e0 @ 0x080092e0  size=94  body=[[080092e0, 0800933d]]

undefined4 FUN_080092e0(uint param_1)

{
  uint uVar1;
  code *pcVar2;
  undefined4 *puVar3;
  
  puVar3 = DAT_20000c00;
  if (0x1f < param_1) {
    return 0xffffffff;
  }
  uVar1 = DAT_20000c00[0xf];
  if (uVar1 == 0) {
    uVar1 = FUN_08009758(DAT_20000c00,0x80);
    puVar3[0xf] = uVar1;
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    puVar3 = (undefined4 *)(uVar1 - 4);
    do {
      puVar3 = puVar3 + 1;
      *puVar3 = 0;
    } while (puVar3 != (undefined4 *)(uVar1 + 0x7c));
  }
  pcVar2 = *(code **)(uVar1 + param_1 * 4);
  if (pcVar2 == (code *)0x0) {
    return 1;
  }
  if (pcVar2 == (code *)0xffffffff) {
    return 2;
  }
  if (pcVar2 != (code *)0x1) {
    *(undefined4 *)(uVar1 + param_1 * 4) = 0;
    (*pcVar2)(param_1);
    return 0;
  }
  return 3;
}


// ===================================================================
// FUN_08009344 @ 0x08009344  size=4  body=[[08009344, 08009347]]

undefined4 FUN_08009344(void)

{
  return 0;
}


// ===================================================================
// FUN_08009348 @ 0x08009348  size=10  body=[[08009348, 08009351]]

void FUN_08009348(void)

{
  FUN_08009a14(&DAT_20000c04,(undefined *)0x800968d,&DAT_20000c50);
  return;
}


// ===================================================================
// FUN_08009360 @ 0x08009360  size=50  body=[[08009360, 08009391]]

void FUN_08009360(uint *param_1)

{
  if ((int *)param_1[1] != &DAT_200013b8) {
    FUN_0800968c(param_1,(int *)param_1[1]);
  }
  if ((int *)param_1[2] != &DAT_20001420) {
    FUN_0800968c(param_1,(int *)param_1[2]);
  }
  if ((int *)param_1[3] != &DAT_20001488) {
    FUN_0800968c(param_1,(int *)param_1[3]);
    return;
  }
  return;
}


// ===================================================================
// FUN_080093a0 @ 0x080093a0  size=4  body=[[080093a0, 080093a3]]

undefined4 FUN_080093a0(void)

{
  return 0;
}


// ===================================================================
// FUN_080093a4 @ 0x080093a4  size=174  body=[[080093a4, 08009451]]

void FUN_080093a4(void)

{
  DAT_200014f0 = 0x8009349;
  DAT_200013c4 = 4;
  DAT_200013b8 = 0;
  DAT_200013bc = 0;
  DAT_200013c8 = 0;
  DAT_200013cc = 0;
  DAT_200013c0 = 0;
  DAT_2000141c = 0;
  DAT_200013d0 = 0;
  FUN_08008798(&DAT_20001414,0,8);
  DAT_2000142c = 0x10009;
  DAT_200013d8 = &DAT_200013b8;
  DAT_200013dc = 0x800a0ed;
  DAT_200013e0 = 0x800a115;
  DAT_200013e4 = 0x800a155;
  DAT_20001420 = 0;
  DAT_20001424 = 0;
  DAT_20001430 = 0;
  DAT_20001434 = 0;
  DAT_20001428 = 0;
  DAT_20001484 = 0;
  DAT_20001438 = 0;
  DAT_200013e8 = 0x800a179;
  FUN_08008798(&DAT_2000147c,0,8);
  DAT_20001494 = 0x20012;
  DAT_20001440 = &DAT_20001420;
  DAT_20001444 = 0x800a0ed;
  DAT_20001448 = 0x800a115;
  DAT_2000144c = 0x800a155;
  DAT_20001450 = 0x800a179;
  DAT_20001488 = 0;
  DAT_2000148c = 0;
  DAT_20001498 = 0;
  DAT_2000149c = 0;
  DAT_20001490 = 0;
  DAT_200014ec = 0;
  DAT_200014a0 = 0;
  FUN_08008798(&DAT_200014e4,0,8);
  DAT_200014ac = 0x800a0ed;
  DAT_200014b0 = 0x800a115;
  DAT_200014b4 = 0x800a155;
  DAT_200014b8 = 0x800a179;
  DAT_200014a8 = &DAT_20001488;
  return;
}


// ===================================================================
// FUN_08009474 @ 0x08009474  size=150  body=[[08009474, 08009509]]

undefined4 * FUN_08009474(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_200014f0 == 0) {
    FUN_080093a4();
  }
  puVar2 = &DAT_20000c50;
  while( true ) {
    do {
      puVar3 = puVar2;
      puVar2 = (undefined4 *)puVar3[2];
      iVar1 = puVar3[1] + -1;
      if (-1 < iVar1) {
        do {
          iVar1 = iVar1 + -1;
          if (*(short *)(puVar2 + 3) == 0) {
            puVar2[3] = 0xffff0001;
            puVar2[1] = 0;
            puVar2[2] = 0;
            puVar2[4] = 0;
            puVar2[5] = 0;
            puVar2[0x19] = 0;
            *puVar2 = 0;
            puVar2[6] = 0;
            FUN_08008798((byte *)(puVar2 + 0x17),0,8);
            puVar2[0xd] = 0;
            puVar2[0xe] = 0;
            puVar2[0x12] = 0;
            puVar2[0x13] = 0;
            return puVar2;
          }
          puVar2 = puVar2 + 0x1a;
        } while (iVar1 != -1);
      }
      puVar2 = (undefined4 *)*puVar3;
    } while ((undefined4 *)*puVar3 != (undefined4 *)0x0);
    puVar2 = (undefined4 *)FUN_08009758(param_1,0x1ac);
    if (puVar2 == (undefined4 *)0x0) break;
    *puVar2 = 0;
    puVar2[1] = 4;
    puVar2[2] = puVar2 + 3;
    FUN_08008798((byte *)(puVar2 + 3),0,0x1a0);
    *puVar3 = puVar2;
  }
  *puVar3 = 0;
  *param_1 = 0xc;
  return (undefined4 *)0x0;
}


// ===================================================================
// FUN_08009518 @ 0x08009518  size=22  body=[[08009518, 0800952d]]

void FUN_08009518(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_200014f0;
  if ((*(int *)(param_1 + 0x20) == 0) && (*(undefined4 *)(param_1 + 0x20) = 0x8009361, iVar1 == 0))
  {
    FUN_080093a4();
    return;
  }
  return;
}


// ===================================================================
// FUN_08009538 @ 0x08009538  size=2  body=[[08009538, 08009539]]

void FUN_08009538(void)

{
  return;
}


// ===================================================================
// FUN_0800953c @ 0x0800953c  size=2  body=[[0800953c, 0800953d]]

void FUN_0800953c(void)

{
  return;
}


// ===================================================================
// FUN_08009540 @ 0x08009540  size=10  body=[[08009540, 08009549]]

void FUN_08009540(void)

{
  FUN_08009a14(0,(undefined *)0x8009345,&DAT_20000c50);
  return;
}


// ===================================================================
// FUN_08009554 @ 0x08009554  size=10  body=[[08009554, 0800955d]]

void FUN_08009554(void)

{
  FUN_08009a14(0,(undefined *)0x80093a1,&DAT_20000c50);
  return;
}


// ===================================================================
// FUN_08009568 @ 0x08009568  size=286  body=[[08009568, 08009685]]

undefined4 FUN_08009568(uint *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  ushort uVar4;
  uint uVar5;
  code *pcVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  
  uVar5 = (uint)(short)param_2[3];
  if ((int)(uVar5 << 0x1c) < 0) {
    iVar2 = param_2[4];
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = uVar5 << 0x1e;
    bVar9 = iVar1 == 0;
    iVar7 = *param_2;
    if (bVar9) {
      iVar1 = param_2[5];
    }
    *param_2 = iVar2;
    if (!bVar9) {
      iVar1 = 0;
    }
    iVar7 = iVar7 - iVar2;
    param_2[2] = iVar1;
    do {
      if (iVar7 < 1) {
        return 0;
      }
      iVar1 = (*(code *)param_2[10])(param_1,param_2[8],iVar2,iVar7);
      iVar7 = iVar7 - iVar1;
      iVar2 = iVar2 + iVar1;
    } while (0 < iVar1);
LAB_08009634:
    uVar4 = *(ushort *)(param_2 + 3);
LAB_08009638:
    *(ushort *)(param_2 + 3) = uVar4 | 0x40;
    return 0xffffffff;
  }
  if ((param_2[1] < 1) && (param_2[0x10] < 1)) {
    return 0;
  }
  pcVar6 = (code *)param_2[0xb];
  if (pcVar6 == (code *)0x0) {
    return 0;
  }
  uVar8 = *param_1;
  *param_1 = 0;
  iVar2 = param_2[8];
  if ((uVar5 & 0x1000) == 0) {
    iVar1 = (*pcVar6)(param_1,iVar2,0,1);
    if ((iVar1 == -1) && (uVar5 = *param_1, uVar5 != 0)) {
      if ((uVar5 == 0x1d) || (uVar5 == 0x16)) {
        *param_1 = uVar8;
        return 0;
      }
      goto LAB_08009634;
    }
    uVar5 = (uint)(short)param_2[3];
    pcVar6 = (code *)param_2[0xb];
    iVar2 = param_2[8];
  }
  else {
    iVar1 = param_2[0x15];
  }
  if (((int)(uVar5 << 0x1d) < 0) && (iVar1 = iVar1 - param_2[1], param_2[0xd] != 0)) {
    iVar1 = iVar1 - param_2[0x10];
  }
  iVar2 = (*pcVar6)(param_1,iVar2,iVar1,0);
  if (iVar2 == -1) {
    uVar5 = *param_1;
    uVar4 = *(ushort *)(param_2 + 3);
    if ((0x1d < uVar5) || (-1 < (int)((0x20400001U >> (uVar5 & 0xff)) << 0x1f))) goto LAB_08009638;
    *param_2 = param_2[4];
    param_2[1] = 0;
    if ((-1 < (int)(short)uVar4 << 0x13) || (uVar5 != 0)) goto LAB_080095d4;
  }
  else {
    param_2[1] = 0;
    *param_2 = param_2[4];
    if (-1 < (int)((uint)*(ushort *)(param_2 + 3) << 0x13)) goto LAB_080095d4;
  }
  param_2[0x15] = iVar2;
LAB_080095d4:
  piVar3 = (int *)param_2[0xd];
  *param_1 = uVar8;
  if (piVar3 != (int *)0x0) {
    if (piVar3 != param_2 + 0x11) {
      FUN_08009858(param_1,(int)piVar3);
    }
    param_2[0xd] = 0;
  }
  return 0;
}


// ===================================================================
// FUN_0800968c @ 0x0800968c  size=54  body=[[0800968c, 080096c1]]

undefined4 FUN_0800968c(uint *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (param_2[4] == 0) {
    return 0;
  }
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  if ((short)param_2[3] == 0) {
    return 0;
  }
  uVar1 = FUN_08009568(param_1,param_2);
  return uVar1;
}


// ===================================================================
// FUN_080096c4 @ 0x080096c4  size=60  body=[[080096c4, 080096ff]]

uint FUN_080096c4(int *param_1)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = DAT_20000c00;
  if (param_1 == (int *)0x0) {
    uVar2 = FUN_08009a14(&DAT_20000c04,(undefined *)0x800968d,&DAT_20000c50);
    return uVar2;
  }
  if (param_1[4] != 0) {
    if ((DAT_20000c00 != (uint *)0x0) && (DAT_20000c00[8] == 0)) {
      FUN_08009518((int)DAT_20000c00);
    }
    if ((short)param_1[3] != 0) {
      uVar2 = FUN_08009568(puVar1,param_1);
      return uVar2;
    }
  }
  return 0;
}


// ===================================================================
// FUN_08009710 @ 0x08009710  size=68  body=[[08009710, 08009753]]

uint FUN_08009710(undefined4 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_200014f4 == 0) {
    DAT_200014f4 = FUN_080166a4(param_1,0);
  }
  uVar1 = FUN_080166a4(param_1,param_2);
  if ((uVar1 != 0xffffffff) &&
     ((uVar3 = uVar1 + 3 & 0xfffffffc, uVar1 == uVar3 ||
      (iVar2 = FUN_080166a4(param_1,uVar3 - uVar1), iVar2 != -1)))) {
    return uVar3;
  }
  return 0xffffffff;
}


// ===================================================================
// FUN_08009758 @ 0x08009758  size=252  body=[[08009758, 08009853]]

uint FUN_08009758(undefined4 *param_1,uint param_2)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar8 = (param_2 + 3 & 0xfffffffc) + 8;
  if (uVar8 < 0xc) {
    uVar8 = 0xc;
  }
  if (((int)uVar8 < 0) || (uVar8 < param_2)) {
    *param_1 = 0xc;
  }
  else {
    FUN_08009fd0();
    puVar5 = DAT_200014f8;
    puVar6 = DAT_200014f8;
    while (puVar1 = puVar5, puVar1 != (uint *)0x0) {
      uVar4 = *puVar1 - uVar8;
      if (-1 < (int)uVar4) {
        if (uVar4 < 0xc) {
          puVar5 = (uint *)puVar1[1];
          if (puVar1 == puVar6) goto LAB_080097bc;
          goto LAB_0800979e;
        }
        puVar2 = (uint *)((int)puVar1 + uVar8);
        *puVar1 = uVar8;
        puVar5 = puVar2;
        if (puVar1 != puVar6) {
          puVar6[1] = (uint)puVar2;
          puVar5 = DAT_200014f8;
        }
        DAT_200014f8 = puVar5;
        *(uint *)((int)puVar1 + uVar8) = uVar4;
        puVar2[1] = puVar1[1];
        puVar5 = DAT_200014f8;
        goto LAB_080097bc;
      }
      puVar6 = puVar1;
      puVar5 = (uint *)puVar1[1];
    }
    puVar1 = (uint *)FUN_08009710(param_1,uVar8);
    if (puVar1 != (uint *)0xffffffff) {
      *puVar1 = uVar8;
      puVar5 = DAT_200014f8;
LAB_080097bc:
      DAT_200014f8 = puVar5;
      FUN_08009fd4();
      puVar6 = puVar1 + 1;
      uVar8 = (int)puVar1 + 0xbU & 0xfffffff8;
      iVar3 = uVar8 - (int)puVar6;
      if (iVar3 != 0) {
        puVar6 = (uint *)((int)puVar6 - uVar8);
      }
      if (iVar3 != 0) {
        *(uint **)((int)puVar1 + iVar3) = puVar6;
      }
      return uVar8;
    }
    puVar6 = DAT_200014f8;
    if (DAT_200014f8 != (uint *)0x0) {
      do {
        puVar1 = puVar6;
        puVar6 = (uint *)puVar1[1];
      } while ((uint *)puVar1[1] != (uint *)0x0);
      uVar4 = *puVar1;
      iVar3 = FUN_080166a4(param_1,0);
      if ((int)puVar1 + uVar4 == iVar3) {
        uVar7 = *puVar1;
        uVar4 = FUN_08009710(param_1,uVar8 - uVar7);
        puVar6 = DAT_200014f8;
        if (uVar4 != 0xffffffff) {
          *puVar1 = *puVar1 + (uVar8 - uVar7);
          puVar5 = (uint *)puVar6[1];
          if ((uint *)puVar6[1] == (uint *)0x0) {
            puVar5 = (uint *)0x0;
          }
          else {
            while (puVar2 = puVar5, puVar2 != puVar1) {
              puVar6 = puVar2;
              puVar5 = (uint *)puVar2[1];
            }
            puVar5 = (uint *)0x0;
LAB_0800979e:
            puVar6[1] = (uint)puVar5;
            puVar5 = DAT_200014f8;
          }
          goto LAB_080097bc;
        }
      }
    }
    *param_1 = 0xc;
    FUN_08009fd4();
  }
  return 0;
}


// ===================================================================
// FUN_08009858 @ 0x08009858  size=182  body=[[08009858, 0800990d]]

void FUN_08009858(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  if (param_2 == 0) {
    return;
  }
  piVar5 = (int *)(param_2 + -4);
  if (*(int *)(param_2 + -4) < 0) {
    piVar5 = (int *)((int)piVar5 + *(int *)(param_2 + -4));
  }
  FUN_08009fd0();
  if (DAT_200014f8 != (int *)0x0) {
    piVar4 = DAT_200014f8;
    if (DAT_200014f8 <= piVar5) {
      do {
        piVar3 = piVar4;
        piVar4 = (int *)piVar3[1];
        if (piVar4 == (int *)0x0) {
          piVar1 = (int *)((int)piVar3 + *piVar3);
          if (piVar5 != piVar1) {
            if (piVar1 <= piVar5) goto LAB_080098a6;
            goto LAB_08009900;
          }
          *piVar3 = *piVar5 + *piVar3;
          goto LAB_080098aa;
        }
      } while (piVar4 <= piVar5);
      piVar1 = (int *)((int)piVar3 + *piVar3);
      if (piVar1 == piVar5) {
        iVar2 = *piVar3 + *piVar5;
        *piVar3 = iVar2;
        if (piVar4 == (int *)((int)piVar3 + iVar2)) {
          iVar6 = piVar4[1];
          *piVar3 = iVar2 + *piVar4;
          piVar3[1] = iVar6;
        }
      }
      else {
        if (piVar5 <= piVar1) {
LAB_08009900:
          *param_1 = 0xc;
          FUN_08009fd4();
          return;
        }
        if (piVar4 == (int *)((int)piVar5 + *piVar5)) {
          iVar2 = piVar4[1];
          *piVar5 = *piVar4 + *piVar5;
          piVar5[1] = iVar2;
          piVar3[1] = (int)piVar5;
        }
        else {
LAB_080098a6:
          piVar5[1] = (int)piVar4;
          piVar3[1] = (int)piVar5;
        }
      }
LAB_080098aa:
      FUN_08009fd4();
      return;
    }
    if (DAT_200014f8 == (int *)((int)piVar5 + *piVar5)) {
      iVar2 = *DAT_200014f8;
      DAT_200014f8 = (int *)DAT_200014f8[1];
      *piVar5 = iVar2 + *piVar5;
    }
  }
  piVar5[1] = (int)DAT_200014f8;
  DAT_200014f8 = piVar5;
  FUN_08009fd4();
  return;
}


// ===================================================================
// FUN_08009914 @ 0x08009914  size=254  body=[[08009914, 08009a11]]

void FUN_08009914(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  
  if ((param_2 < param_1) && (puVar3 = (undefined4 *)((int)param_2 + param_3), param_1 < puVar3)) {
    puVar6 = (undefined1 *)((int)param_1 + param_3);
    if (param_3 == 0) {
      return;
    }
    do {
      puVar3 = (undefined4 *)((int)puVar3 + -1);
      puVar6 = puVar6 + -1;
      *puVar6 = *(undefined1 *)puVar3;
    } while (param_2 != puVar3);
    return;
  }
  if (param_3 < 0x10) {
    if (param_3 == 0) {
      return;
    }
  }
  else if ((((uint)param_1 | (uint)param_2) & 3) == 0) {
    puVar1 = param_2 + 4;
    puVar3 = param_1;
    do {
      *puVar3 = puVar1[-4];
      puVar3[1] = puVar1[-3];
      puVar3[2] = puVar1[-2];
      puVar3[3] = puVar1[-1];
      puVar1 = puVar1 + 4;
      puVar3 = puVar3 + 4;
    } while (puVar1 != (undefined4 *)((int)param_2 + (param_3 - 0x10 & 0xfffffff0) + 0x20));
    iVar4 = (param_3 - 0x10 >> 4) + 1;
    puVar3 = param_2 + iVar4 * 4;
    uVar5 = param_3 & 0xf;
    puVar1 = param_1 + iVar4 * 4;
    if ((param_3 & 0xc) != 0) {
      puVar2 = puVar1 + -1;
      puVar7 = puVar3;
      do {
        puVar2 = puVar2 + 1;
        *puVar2 = *puVar7;
        puVar7 = puVar7 + 1;
      } while (puVar2 != (undefined4 *)((uVar5 - 4 & 0xfffffffc) + (int)puVar1));
      iVar4 = (uVar5 - 4 >> 2) + 1;
      uVar5 = param_3 & 3;
      puVar1 = puVar1 + iVar4;
      puVar3 = puVar3 + iVar4;
    }
    if (uVar5 != 0) {
      puVar6 = (undefined1 *)((int)puVar1 + -1);
      puVar1 = puVar3;
      do {
        puVar2 = (undefined4 *)((int)puVar1 + 1);
        puVar6 = puVar6 + 1;
        *puVar6 = *(undefined1 *)puVar1;
        puVar1 = puVar2;
      } while (puVar2 != (undefined4 *)(uVar5 + (int)puVar3));
    }
    return;
  }
  puVar6 = (undefined1 *)((int)param_1 + -1);
  puVar3 = param_2;
  do {
    puVar1 = (undefined4 *)((int)puVar3 + 1);
    puVar6 = puVar6 + 1;
    *puVar6 = *(undefined1 *)puVar3;
    puVar3 = puVar1;
  } while (puVar1 != (undefined4 *)(param_3 + (int)param_2));
  return;
}


// ===================================================================
// FUN_08009a14 @ 0x08009a14  size=68  body=[[08009a14, 08009a57]]

uint FUN_08009a14(undefined4 param_1,undefined *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  do {
    iVar2 = param_3[2];
    iVar3 = param_3[1] + -1;
    if (-1 < iVar3) {
      do {
        if ((1 < *(ushort *)(iVar2 + 0xc)) && (*(short *)(iVar2 + 0xe) != -1)) {
          uVar1 = (*(code *)param_2)(param_1,iVar2);
          uVar4 = uVar4 | uVar1;
        }
        iVar3 = iVar3 + -1;
        iVar2 = iVar2 + 0x68;
      } while (iVar3 != -1);
    }
    param_3 = (int *)*param_3;
  } while (param_3 != (int *)0x0);
  return uVar4;
}


// ===================================================================
// FUN_08009a60 @ 0x08009a60  size=158  body=[[08009a60, 08009afd]]

byte * FUN_08009a60(uint *param_1,uint param_2,uint param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  byte *pbVar5;
  uint *puVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  
  uVar8 = param_2 & 0xff;
  if ((int)param_3 < 0x10) {
joined_r0x08009ac0:
    do {
      if (param_3 == 0) {
        return (byte *)0x0;
      }
      puVar6 = (uint *)((int)param_1 + 1);
      uVar9 = *param_1;
      param_3 = param_3 - 1;
      param_1 = puVar6;
    } while ((byte)uVar9 != uVar8);
  }
  else {
    while( true ) {
      if (((uint)param_1 & 7) == 0) {
        uVar9 = uVar8 | uVar8 << 8;
        uVar9 = uVar9 | uVar9 << 0x10;
        uVar10 = param_3 & 0xfffffff8;
        do {
          puVar6 = param_1 + 2;
          uVar10 = uVar10 - 8;
          uVar11 = *param_1 ^ uVar9;
          uVar12 = param_1[1] ^ uVar9;
          cVar1 = -((char)uVar11 == '\0');
          cVar2 = -((char)(uVar11 >> 8) == '\0');
          cVar3 = -((char)(uVar11 >> 0x10) == '\0');
          cVar4 = -((char)(uVar11 >> 0x18) == '\0');
          uVar11 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
          bVar13 = (char)uVar12 != '\0';
          bVar14 = (char)(uVar12 >> 8) != '\0';
          bVar15 = (char)(uVar12 >> 0x10) != '\0';
          bVar16 = (char)(uVar12 >> 0x18) != '\0';
          uVar12 = CONCAT13(bVar16 * cVar4 - !bVar16,
                            CONCAT12(bVar15 * cVar3 - !bVar15,
                                     CONCAT11(bVar14 * cVar2 - !bVar14,bVar13 * cVar1 - !bVar13)));
          if (uVar12 != 0) {
            if (uVar11 == 0) {
              pbVar7 = (byte *)((int)param_1 + 5);
              uVar11 = uVar12;
            }
            else {
              pbVar7 = (byte *)((int)param_1 + 1);
            }
            if ((uVar11 & 1) == 0) {
              bVar13 = (uVar11 & 0x100) == 0;
              pbVar5 = pbVar7 + 1;
              if (bVar13) {
                pbVar5 = pbVar7 + 2;
              }
              pbVar7 = pbVar5;
              if (bVar13 && (uVar11 & 0x18000) == 0) {
                pbVar7 = pbVar7 + 1;
              }
            }
            return pbVar7 + -1;
          }
          param_1 = puVar6;
        } while (uVar10 != 0);
        param_3 = param_3 & 7;
        goto joined_r0x08009ac0;
      }
      puVar6 = (uint *)((int)param_1 + 1);
      param_3 = param_3 - 1;
      if ((byte)*param_1 == uVar8) break;
      param_1 = puVar6;
      if (param_3 == 0) {
        return (byte *)0x0;
      }
    }
  }
  return (byte *)((int)puVar6 + -1);
}


// ===================================================================
// FUN_08009b00 @ 0x08009b00  size=190  body=[[08009b00, 08009bbd]]

undefined4 FUN_08009b00(undefined4 *param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  
  if ((DAT_20000c00 != 0) && (*(int *)(DAT_20000c00 + 0x20) == 0)) {
    FUN_08009518(DAT_20000c00);
  }
  uVar3 = param_2[3];
  uVar4 = (uint)(short)(ushort)uVar3;
  if ((int)(uVar4 << 0x1c) < 0) {
    uVar3 = param_2[4];
  }
  else {
    if (-1 < (int)(uVar4 << 0x1b)) {
      *param_1 = 9;
      *(ushort *)(param_2 + 3) = (ushort)uVar3 | 0x40;
      return 0xffffffff;
    }
    if ((int)(uVar4 << 0x1d) < 0) {
      puVar2 = (uint *)param_2[0xd];
      if (puVar2 != (uint *)0x0) {
        if (puVar2 != param_2 + 0x11) {
          FUN_08009858(param_1,(int)puVar2);
          uVar4 = (uint)(short)param_2[3];
        }
        param_2[0xd] = 0;
      }
      uVar3 = param_2[4];
      *param_2 = uVar3;
      param_2[1] = 0;
      uVar4 = uVar4 & 0xffffffdb;
    }
    else {
      uVar3 = param_2[4];
    }
    uVar4 = uVar4 | 8;
    *(short *)(param_2 + 3) = (short)uVar4;
  }
  if ((uVar3 == 0) && ((uVar4 & 0x280) != 0x200)) {
    FUN_08009fd8(param_1,param_2);
    uVar4 = (uint)(short)param_2[3];
    uVar3 = param_2[4];
  }
  if ((uVar4 & 1) == 0) {
    uVar1 = 0;
    if (-1 < (int)(uVar4 << 0x1e)) {
      uVar1 = param_2[5];
    }
    param_2[2] = uVar1;
  }
  else {
    param_2[2] = 0;
    param_2[6] = -param_2[5];
  }
  if ((uVar3 == 0) && ((int)(uVar4 << 0x18) < 0)) {
    *(ushort *)(param_2 + 3) = (ushort)uVar4 | 0x40;
    return 0xffffffff;
  }
  return 0;
}


// ===================================================================
// FUN_08009bc4 @ 0x08009bc4  size=100  body=[[08009bc4, 08009c27]]

undefined4 * FUN_08009bc4(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_08009758(param_1,param_3);
    return puVar2;
  }
  if (param_3 != 0) {
    uVar1 = FUN_0800a180(param_1,(int)param_2);
    if ((param_3 <= uVar1) && (uVar1 >> 1 < param_3)) {
      return param_2;
    }
    puVar2 = (undefined4 *)FUN_08009758(param_1,param_3);
    if (puVar2 != (undefined4 *)0x0) {
      if (uVar1 <= param_3) {
        param_3 = uVar1;
      }
      memcpy(puVar2,param_2,param_3);
      FUN_08009858(param_1,(int)param_2);
    }
    return puVar2;
  }
  FUN_08009858(param_1,(int)param_2);
  return (undefined4 *)0x0;
}


// ===================================================================
// FUN_08009c28 @ 0x08009c28  size=290  body=[[08009c28, 08009d49]]

undefined4
FUN_08009c28(undefined4 param_1,uint *param_2,uint *param_3,undefined4 param_4,undefined *param_5)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  uVar4 = param_2[4];
  if ((int)param_2[4] < (int)param_2[2]) {
    uVar4 = param_2[2];
  }
  *param_3 = uVar4;
  cVar1 = *(char *)((int)param_2 + 0x43);
  if (cVar1 != '\0') {
    *param_3 = uVar4 + 1;
  }
  uVar4 = *param_2;
  uVar8 = param_4;
  if ((int)(uVar4 << 0x1a) < 0) {
    uVar5 = *param_3;
    *param_3 = uVar5 + 2;
    uVar4 = *param_2;
    if (((uVar4 & 6) == 0) && ((int)(uVar5 + 2) < (int)param_2[3])) {
LAB_08009c76:
      iVar6 = 0;
      do {
        iVar2 = (*(code *)param_5)(param_1,param_4,(int)param_2 + 0x19,1,uVar8);
        iVar6 = iVar6 + 1;
        if (iVar2 == -1) {
          return 0xffffffff;
        }
      } while (iVar6 < (int)(param_2[3] - *param_3));
      uVar4 = *param_2;
    }
LAB_08009ca8:
    uVar5 = (uint)(*(char *)((int)param_2 + 0x43) != '\0');
    if ((int)(uVar4 << 0x1a) < 0) {
      *(undefined1 *)((int)param_2 + uVar5 + 0x43) = 0x30;
      *(undefined1 *)((int)param_2 + uVar5 + 0x44) = *(undefined1 *)((int)param_2 + 0x45);
      uVar5 = uVar5 + 2;
    }
  }
  else {
    if ((uVar4 & 6) == 0) {
      if ((int)*param_3 < (int)param_2[3]) goto LAB_08009c76;
      goto LAB_08009ca8;
    }
    uVar5 = (uint)(cVar1 != '\0');
  }
  iVar6 = (*(code *)param_5)(param_1,param_4,(int)param_2 + 0x43,uVar5,uVar8);
  if (iVar6 == -1) {
    return 0xffffffff;
  }
  uVar4 = param_2[4];
  uVar5 = param_2[2];
  if ((*param_2 & 6) == 4) {
    uVar3 = param_2[3] - *param_3;
    uVar7 = uVar3 & ~((int)uVar3 >> 0x1f);
    if ((int)uVar5 <= (int)uVar4) {
      if ((int)uVar3 < 1) {
        return 0;
      }
      goto LAB_08009cfa;
    }
  }
  else {
    if ((int)uVar5 <= (int)uVar4) {
      return 0;
    }
    uVar7 = 0;
  }
  uVar7 = uVar7 + (uVar5 - uVar4);
LAB_08009cfa:
  iVar6 = 0;
  do {
    iVar2 = (*(code *)param_5)(param_1,param_4,(int)param_2 + 0x1a,1,uVar8);
    iVar6 = iVar6 + 1;
    if (iVar2 == -1) {
      return 0xffffffff;
    }
  } while (iVar6 < (int)uVar7);
  return 0;
}


// ===================================================================
// FUN_08009d4c @ 0x08009d4c  size=570  body=[[08009d4c, 08009d77] [08009dba, 08009fc7]]

uint FUN_08009d4c(undefined4 param_1,uint *param_2,undefined4 param_3,undefined *param_4,
                 int *param_5)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  uint *puVar11;
  uint *puVar12;
  bool bVar13;
  uint local_24;
  
  uVar6 = (uint)(byte)param_2[6];
  puVar12 = (uint *)((int)param_2 + 0x43);
  puVar11 = puVar12;
  if (uVar6 == 0) {
LAB_08009dd2:
    param_2[4] = 0;
    goto LAB_08009dd8;
  }
  if (0x20 < (uVar6 - 0x58 & 0xff)) {
switchD_08009d74_caseD_1:
    *(byte *)((int)param_2 + 0x42) = (byte)param_2[6];
    uVar6 = 1;
    puVar11 = (uint *)((int)param_2 + 0x42);
    goto LAB_08009e4e;
  }
  switch(uVar6 - 0x58) {
  case 0:
    *(undefined1 *)((int)param_2 + 0x45) = 0x58;
    pcVar4 = "0123456789ABCDEF";
    uVar6 = *param_2;
    goto LAB_08009f14;
  default:
    goto switchD_08009d74_caseD_1;
  case 0xb:
    uVar9 = *(undefined4 *)*param_5;
    *param_5 = (int)((undefined4 *)*param_5 + 1);
    puVar11 = (uint *)((int)param_2 + 0x42);
    *(char *)((int)param_2 + 0x42) = (char)uVar9;
    uVar6 = 1;
    break;
  case 0xc:
  case 0x11:
    puVar7 = (uint *)*param_5;
    uVar6 = *param_2;
    *param_5 = (int)(puVar7 + 1);
    if (((int)(uVar6 << 0x18) < 0) || (-1 < (int)(uVar6 << 0x19))) {
      uVar5 = *puVar7;
    }
    else {
      uVar5 = (uint)(short)*puVar7;
    }
    uVar8 = param_2[1];
    if (-1 < (int)uVar5) {
      pcVar4 = "0123456789ABCDEF";
      uVar6 = 10;
      goto LAB_08009eaa;
    }
    param_2[2] = uVar8;
    *(undefined1 *)((int)param_2 + 0x43) = 0x2d;
    if (-1 < (int)uVar8) {
      *param_2 = uVar6 & 0xfffffffb;
    }
    uVar6 = 10;
    pcVar4 = "0123456789ABCDEF";
    uVar5 = -uVar5;
    goto LAB_08009f58;
  case 0x16:
    puVar10 = (undefined4 *)*param_5;
    uVar5 = *param_2;
    uVar6 = param_2[5];
    *param_5 = (int)(puVar10 + 1);
    puVar12 = (uint *)*puVar10;
    if (((int)(uVar5 << 0x18) < 0) || (-1 < (int)(uVar5 << 0x19))) {
      *puVar12 = uVar6;
    }
    else {
      *(short *)puVar12 = (short)uVar6;
    }
    goto LAB_08009dd2;
  case 0x17:
  case 0x1d:
    uVar5 = *(uint *)*param_5;
    if (((*param_2 & 0x80) == 0) && ((int)(*param_2 << 0x19) < 0)) {
      uVar5 = uVar5 & 0xffff;
    }
    pcVar4 = "0123456789ABCDEF";
    *param_5 = (int)((uint *)*param_5 + 1);
    if (uVar6 == 0x6f) {
      uVar6 = 8;
    }
    else {
      uVar6 = 10;
    }
    goto LAB_08009ea2;
  case 0x18:
    uVar6 = *param_2 | 0x20;
    *param_2 = uVar6;
    goto LAB_08009f0c;
  case 0x1b:
    puVar10 = (undefined4 *)*param_5;
    uVar6 = param_2[1];
    *param_5 = (int)(puVar10 + 1);
    puVar11 = (uint *)*puVar10;
    pbVar3 = FUN_08009a60(puVar11,0,uVar6);
    if (pbVar3 == (byte *)0x0) {
      uVar6 = param_2[1];
    }
    else {
      uVar6 = (int)pbVar3 - (int)puVar11;
      param_2[1] = uVar6;
    }
    break;
  case 0x20:
    uVar6 = *param_2;
LAB_08009f0c:
    pcVar4 = "0123456789abcdef";
    *(undefined1 *)((int)param_2 + 0x45) = 0x78;
LAB_08009f14:
    uVar5 = *(uint *)*param_5;
    if (((uVar6 & 0x80) == 0) && ((uVar6 & 0x40) != 0)) {
      uVar5 = uVar5 & 0xffff;
    }
    *param_5 = (int)((uint *)*param_5 + 1);
    if ((int)(uVar6 << 0x1f) < 0) {
      *param_2 = uVar6 | 0x20;
    }
    if (uVar5 == 0) {
      *param_2 = *param_2 & 0xffffffdf;
    }
    uVar6 = 0x10;
LAB_08009ea2:
    uVar8 = param_2[1];
    *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_08009eaa:
    param_2[2] = uVar8;
    if (((int)uVar8 < 0) || (*param_2 = *param_2 & 0xfffffffb, uVar5 != 0)) {
LAB_08009f58:
      do {
        bVar13 = uVar6 <= uVar5;
        puVar11 = (uint *)((int)puVar11 + -1);
        *(char *)puVar11 = pcVar4[uVar5 - uVar6 * (uVar5 / uVar6)];
        uVar5 = uVar5 / uVar6;
      } while (bVar13);
    }
    else if (uVar8 != 0) {
      *(char *)((int)param_2 + 0x42) = *pcVar4;
      puVar11 = (uint *)((int)param_2 + 0x42);
    }
    if (((uVar6 == 8) && ((int)(*param_2 << 0x1f) < 0)) && ((int)param_2[1] <= (int)param_2[4])) {
      *(char *)((int)puVar11 + -1) = '0';
      puVar11 = (uint *)((int)puVar11 + -1);
    }
    param_2[4] = (int)puVar12 - (int)puVar11;
    goto LAB_08009dd8;
  }
LAB_08009e4e:
  param_2[4] = uVar6;
  *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_08009dd8:
  iVar1 = FUN_08009c28(param_1,param_2,&local_24,param_3,param_4);
  if ((iVar1 != -1) && (iVar1 = (*(code *)param_4)(param_1,param_3,puVar11,param_2[4]), iVar1 != -1)
     ) {
    uVar6 = param_2[3];
    if (((int)(*param_2 << 0x1e) < 0) && ((int)local_24 < (int)uVar6)) {
      iVar1 = 0;
      do {
        iVar2 = (*(code *)param_4)(param_1,param_3,(int)param_2 + 0x19,1);
        iVar1 = iVar1 + 1;
        if (iVar2 == -1) {
          return 0xffffffff;
        }
        uVar6 = param_2[3];
      } while (iVar1 < (int)(uVar6 - local_24));
    }
    if ((int)uVar6 < (int)local_24) {
      uVar6 = local_24;
    }
    return uVar6;
  }
  return 0xffffffff;
}


// ===================================================================
// FUN_08009fd0 @ 0x08009fd0  size=2  body=[[08009fd0, 08009fd1]]

void FUN_08009fd0(void)

{
  return;
}


// ===================================================================
// FUN_08009fd4 @ 0x08009fd4  size=2  body=[[08009fd4, 08009fd5]]

void FUN_08009fd4(void)

{
  return;
}


// ===================================================================
// FUN_08009fd8 @ 0x08009fd8  size=196  body=[[08009fd8, 0800a09b]]

void FUN_08009fd8(undefined4 *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte abStack_68 [4];
  uint local_64;
  
  uVar3 = (uint)(short)param_2[3];
  if ((int)(uVar3 << 0x1e) < 0) {
    param_2[4] = (int)param_2 + 0x47U;
    param_2[5] = 1;
    *param_2 = (int)param_2 + 0x47U;
    return;
  }
  if (-1 < *(short *)((int)param_2 + 0xe)) {
    iVar1 = FUN_080166be(param_1,(int)*(short *)((int)param_2 + 0xe),abStack_68);
    if (-1 < iVar1) {
      uVar3 = FUN_08009758(param_1,0x400);
      if (uVar3 != 0) {
        *param_2 = uVar3;
        *(ushort *)(param_2 + 3) = (ushort)param_2[3] | 0x80;
        param_2[4] = uVar3;
        param_2[5] = 0x400;
        if ((local_64 & 0xf000) != 0x2000) {
          return;
        }
        iVar1 = FUN_080166d6();
        if (iVar1 == 0) {
          return;
        }
        *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfffc | 1;
        return;
      }
      goto LAB_0800a07c;
    }
    uVar3 = (uint)(short)param_2[3];
  }
  if ((uVar3 & 0x80) == 0) {
    uVar3 = 0x400;
  }
  else {
    uVar3 = 0x40;
  }
  uVar2 = FUN_08009758(param_1,uVar3);
  if (uVar2 != 0) {
    *param_2 = uVar2;
    param_2[4] = uVar2;
    param_2[5] = uVar3;
    *(ushort *)(param_2 + 3) = (ushort)param_2[3] | 0x80;
    return;
  }
LAB_0800a07c:
  if (-1 < (int)(short)(ushort)param_2[3] << 0x16) {
    param_2[4] = (int)param_2 + 0x47U;
    param_2[5] = 1;
    *(ushort *)(param_2 + 3) = (ushort)param_2[3] & 0xfffc | 2;
    *param_2 = (int)param_2 + 0x47U;
  }
  return;
}


// ===================================================================
// FUN_0800a09c @ 0x0800a09c  size=78  body=[[0800a09c, 0800a0e9]]

undefined4 FUN_0800a09c(undefined4 param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  byte abStack_68 [4];
  uint local_64;
  
  if ((*(short *)(param_2 + 0xe) < 0) ||
     (iVar1 = FUN_080166be(param_1,(int)*(short *)(param_2 + 0xe),abStack_68), iVar1 < 0)) {
    uVar3 = 0;
    if ((*(ushort *)(param_2 + 0xc) & 0x80) == 0) {
      uVar2 = 0x400;
    }
    else {
      uVar2 = 0x40;
    }
  }
  else {
    uVar2 = 0x400;
    uVar3 = (uint)((local_64 & 0xf000) == 0x2000);
  }
  *param_4 = uVar3;
  *param_3 = uVar2;
  return 0;
}


// ===================================================================
// FUN_0800a0ec @ 0x0800a0ec  size=34  body=[[0800a0ec, 0800a10d]]

void FUN_0800a0ec(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0801668e(param_1);
  if (-1 < iVar1) {
    *(int *)(param_2 + 0x54) = *(int *)(param_2 + 0x54) + iVar1;
    return;
  }
  *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  return;
}


// ===================================================================
// FUN_0800a110 @ 0x0800a110  size=4  body=[[0800a110, 0800a113]]

undefined4 FUN_0800a110(void)

{
  return 0;
}


// ===================================================================
// FUN_0800a114 @ 0x0800a114  size=66  body=[[0800a114, 0800a151] [0801669c, 0801669f]]

undefined8 FUN_0800a114(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_2 + 0xc);
  if ((int)(short)uVar1 << 0x17 < 0) {
    FUN_08016698();
    uVar1 = *(ushort *)(param_2 + 0xc);
  }
  *(ushort *)(param_2 + 0xc) = uVar1 & 0xefff;
  return CONCAT44((int)*(short *)(param_2 + 0xe),param_4);
}


// ===================================================================
// FUN_0800a154 @ 0x0800a154  size=34  body=[[0800a154, 0800a175]]

void FUN_0800a154(undefined4 param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  
  iVar1 = FUN_08016698();
  if (iVar1 == -1) {
    uVar2 = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    uVar2 = *(ushort *)(param_2 + 0xc) | 0x1000;
    *(int *)(param_2 + 0x54) = iVar1;
  }
  *(ushort *)(param_2 + 0xc) = uVar2;
  return;
}


// ===================================================================
// FUN_0800a178 @ 0x0800a178  size=12  body=[[0800a178, 0800a17f] [080166a0, 080166a3]]

longlong FUN_0800a178(undefined4 param_1,int param_2)

{
  return (ulonglong)(uint)(int)*(short *)(param_2 + 0xe) << 0x20;
}


// ===================================================================
// FUN_0800a180 @ 0x0800a180  size=16  body=[[0800a180, 0800a18f]]

int FUN_0800a180(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + -4) + -4;
  if (*(int *)(param_2 + -4) < 0) {
    iVar1 = iVar1 + *(int *)(param_2 + iVar1);
  }
  return iVar1;
}


// ===================================================================
// FUN_0800a190 @ 0x0800a190  size=38  body=[[0800a190, 0800a1b5]]

void FUN_0800a190(int *param_1)

{
  undefined8 uVar1;
  
  DAT_200014fc = 0;
  uVar1 = FUN_080166ec();
  if (((int)uVar1 == -1) && (DAT_200014fc != 0)) {
    *param_1 = DAT_200014fc;
    return;
  }
  return;
}


// ===================================================================
// thunk_FUN_080166fc @ 0x0800a1bc  size=4  body=[[0800a1bc, 0800a1bf]]

undefined4 thunk_FUN_080166fc(void)

{
  return 1;
}


// ===================================================================
// FUN_0800a1c0 @ 0x0800a1c0  size=16  body=[[0800a1c0, 0800a1cf]]

undefined1 FUN_0800a1c0(void)

{
  undefined1 uVar1;
  
  uVar1 = DAT_20001502;
  if (DAT_20001501 != '\x03') {
    uVar1 = 0;
  }
  return uVar1;
}


// ===================================================================
// FUN_0800a1d8 @ 0x0800a1d8  size=24  body=[[0800a1d8, 0800a1ef]]

void FUN_0800a1d8(void)

{
  FUN_08008798(&DAT_20002570,0,0x20);
  DAT_20002590 = 0;
  DAT_20002591 = 0;
  return;
}


// ===================================================================
// FUN_0800a1fc @ 0x0800a1fc  size=56  body=[[0800a1fc, 0800a233]]

undefined4 FUN_0800a1fc(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined2 local_14;
  undefined2 uStack_12;
  undefined4 uStack_10;
  
  _local_14 = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar2 = DAT_20002590 + 1 & 0xf;
  cVar1 = (char)uVar2;
  if (DAT_20002591 == uVar2) {
    DAT_20002591 = cVar1 + 1U & 0xf;
  }
  uStack_10 = param_3;
  memcpy((undefined4 *)(&DAT_20002570 + (uint)DAT_20002590 * 2),(undefined4 *)&local_14,2);
  DAT_20002590 = cVar1;
  return 1;
}


// ===================================================================
// FUN_0800a240 @ 0x0800a240  size=40  body=[[0800a240, 0800a263] [0800c488, 0800c48b]]

void FUN_0800a240(void)

{
  undefined4 extraout_r2;
  undefined8 uVar1;
  
  DAT_20001501 = 1;
  FUN_0800a1d8();
  FUN_0800a7cc();
  FUN_0800b328();
  FUN_0800c058();
  uVar1 = FUN_0800bc8c();
  FUN_0800c46c((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),extraout_r2);
  return;
}


// ===================================================================
// FUN_0800a268 @ 0x0800a268  size=36  body=[[0800a268, 0800a28b]]

void FUN_0800a268(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20000c7c != (code *)0x0) {
      (*DAT_20000c7c)(param_1,param_2);
    }
    DAT_20001501 = 4;
    DAT_20001503 = (undefined1)param_1;
  }
  return;
}


// ===================================================================
// FUN_0800a298 @ 0x0800a298  size=54  body=[[0800a298, 0800a2cd]]

void FUN_0800a298(void)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = FUN_0800c158();
  if ((!bVar1) && (iVar2 = FUN_08012508(), iVar2 != 0)) {
    if ((DAT_20001501 == 5) && (bVar1 = FUN_0800b39c(), !bVar1)) {
      FUN_0800b6ac((uint)DAT_20001501,(uint)DAT_20001503);
    }
    (*DAT_20000c78)(0);
    DAT_20001501 = 5;
  }
  return;
}


// ===================================================================
// FUN_0800a2dc @ 0x0800a2dc  size=82  body=[[0800a2dc, 0800a32d]]

uint FUN_0800a2dc(undefined4 *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_2c [2];
  undefined4 auStack_2a [8];
  
  bVar1 = FUN_0800c158();
  uVar2 = (uint)bVar1;
  if (uVar2 == 0) {
    if (DAT_20001501 == '\x04') {
      if (DAT_20001500 == '\0') {
        return 0;
      }
    }
    else if (DAT_20001501 != '\x03') {
      if (DAT_20001501 == '\0') {
        return 0;
      }
      uVar2 = FUN_0800a298();
      return uVar2;
    }
    if (DAT_20000c84 != 0) {
      local_2c[0] = 1;
      memcpy(auStack_2a,param_1,8);
      bVar1 = FUN_0800a808((undefined4 *)local_2c);
      uVar2 = (uint)bVar1;
    }
  }
  return uVar2;
}


// ===================================================================
// FUN_0800a33c @ 0x0800a33c  size=88  body=[[0800a33c, 0800a393]]

void FUN_0800a33c(undefined4 *param_1)

{
  bool bVar1;
  undefined1 local_34 [2];
  undefined4 auStack_32 [9];
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20001501 == '\x04') {
      if (DAT_20001500 == '\0') {
        return;
      }
    }
    else if (DAT_20001501 != '\x03') {
      if (DAT_20001501 == '\0') {
        return;
      }
      FUN_0800a298();
      return;
    }
    if (DAT_20000c88 != (code *)0x0) {
      local_34[0] = 2;
      memcpy(auStack_32,param_1,0x20);
      FUN_0800a808((undefined4 *)local_34);
      (*DAT_20000c88)((int)param_1 + 1);
    }
  }
  return;
}


// ===================================================================
// FUN_0800a3a0 @ 0x0800a3a0  size=44  body=[[0800a3a0, 0800a3cb]]

void FUN_0800a3a0(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20001501 == '\x03') {
      if (DAT_20000c94 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a3be. Too many branches
                    // WARNING: Treating indirect jump as call
        (*DAT_20000c94)(param_1);
        return;
      }
    }
    else if (DAT_20001501 != '\0') {
      FUN_0800a298();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_0800a3d4 @ 0x0800a3d4  size=54  body=[[0800a3d4, 0800a409]]

void FUN_0800a3d4(uint param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (param_1 != 0) {
      if ((DAT_20001503 == param_1) && (DAT_20001501 == '\x03')) {
        return;
      }
      DAT_20001503 = (byte)param_1;
      DAT_20001502 = 0;
    }
    (*DAT_20000c78)(param_1,param_2);
    DAT_20001501 = '\x05';
  }
  return;
}


// ===================================================================
// FUN_0800a41c @ 0x0800a41c  size=10  body=[[0800a41c, 0800a425]]

void FUN_0800a41c(void)

{
  if (DAT_20000c80 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a422. Too many branches
                    // WARNING: Treating indirect jump as call
    (*DAT_20000c80)();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800a42c @ 0x0800a42c  size=2  body=[[0800a42c, 0800a42d]]

void FUN_0800a42c(void)

{
  return;
}


// ===================================================================
// FUN_0800a42e @ 0x0800a42e  size=2  body=[[0800a42e, 0800a42f]]

void FUN_0800a42e(void)

{
  return;
}


// ===================================================================
// FUN_0800a430 @ 0x0800a430  size=2  body=[[0800a430, 0800a431]]

void FUN_0800a430(void)

{
  return;
}


// ===================================================================
// FUN_0800a432 @ 0x0800a432  size=2  body=[[0800a432, 0800a433]]

void FUN_0800a432(void)

{
  return;
}


// ===================================================================
// FUN_0800a434 @ 0x0800a434  size=2  body=[[0800a434, 0800a435]]

void FUN_0800a434(void)

{
  return;
}


// ===================================================================
// FUN_0800a436 @ 0x0800a436  size=2  body=[[0800a436, 0800a437]]

void FUN_0800a436(void)

{
  return;
}


// ===================================================================
// FUN_0800a458 @ 0x0800a458  size=80  body=[[0800a458, 0800a4a7]]

uint FUN_0800a458(uint param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_2c [2];
  undefined2 local_2a;
  
  if (DAT_20001501 == '\x03') {
    bVar1 = FUN_0800a874();
    if ((bVar1) && (bVar1 = FUN_0800a89c(), bVar1)) {
      if (DAT_20000c8c != (code *)0x0) {
        (*DAT_20000c8c)(param_1);
      }
      uVar2 = FUN_0800a88c();
      return uVar2;
    }
    local_2c[0] = 3;
    local_2a = (undefined2)param_1;
    bVar1 = FUN_0800a808((undefined4 *)local_2c);
    param_1 = (uint)bVar1;
  }
  else if (DAT_20001501 != '\0') {
    uVar2 = FUN_0800a298();
    return uVar2;
  }
  return param_1;
}


// ===================================================================
// FUN_0800a4b0 @ 0x0800a4b0  size=78  body=[[0800a438, 0800a44f] [0800a4b0, 0800a4e5]]

uint FUN_0800a4b0(char *param_1)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = FUN_0800c158();
  if (bVar1 == 0) {
    if (*param_1 == '\x03') {
      if (DAT_20001501 == '\x03') {
        if (DAT_20000c90 != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x0800a446. Too many branches
                    // WARNING: Treating indirect jump as call
          uVar2 = (*DAT_20000c90)();
          return uVar2;
        }
      }
      else if (DAT_20001501 != '\0') {
        uVar2 = FUN_0800a298();
        return uVar2;
      }
      return (uint)*(ushort *)(param_1 + 1);
    }
    if (*param_1 == '\x04') {
      uVar2 = FUN_0800a458((uint)*(ushort *)(param_1 + 1));
      return uVar2;
    }
  }
  return (uint)bVar1;
}


// ===================================================================
// FUN_0800a4e8 @ 0x0800a4e8  size=126  body=[[0800a4e8, 0800a565]]

void FUN_0800a4e8(void)

{
  byte *pbVar1;
  uint extraout_r1;
  undefined4 extraout_r2;
  code *pcVar2;
  byte local_28 [4];
  uint local_24;
  
  pbVar1 = local_28;
  FUN_0800b3ec(0);
  FUN_0800b420(0,extraout_r1,extraout_r2);
  FUN_0800a7cc();
  FUN_0800db44();
  FUN_08013a7a(5000);
  if ((char)DAT_200047d4 < '\0') {
    FUN_08008798(local_28,0,0x20);
    pbVar1 = local_28 + 1;
    pcVar2 = DAT_20000c88;
  }
  else {
    local_28[0] = 0;
    local_28[1] = 0;
    local_28[2] = 0;
    local_28[3] = 0;
    local_24 = 0;
    pcVar2 = DAT_20000c84;
  }
  (*pcVar2)(pbVar1);
  FUN_08013a7a(1000);
  (*DAT_20000c8c)(0);
  FUN_08013a7a(1000);
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_24 = local_24 & 0xffff0000;
  (*DAT_20000c94)(local_28);
  FUN_08013a7a(30000);
  FUN_0800a41c();
  return;
}


// ===================================================================
// FUN_0800a570 @ 0x0800a570  size=396  body=[[0800a570, 0800a6fb]]

void FUN_0800a570(void)

{
  int iVar1;
  byte bVar2;
  code *pcVar3;
  byte bVar4;
  bool bVar5;
  char cVar6;
  byte bVar7;
  uint extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 uVar8;
  undefined4 extraout_r2_00;
  uint uVar9;
  uint uVar10;
  
LAB_0800a578:
  bVar4 = DAT_20001501;
  uVar9 = (uint)DAT_20002591;
  bVar5 = false;
switchD_0800a6f8_default:
  if (DAT_20002590 == uVar9) {
    if (bVar5) {
      DAT_20002591 = DAT_20002590;
    }
    return;
  }
  iVar1 = uVar9 * 2;
  bVar7 = (&DAT_20002571)[uVar9 * 2];
  uVar10 = (uint)bVar7;
  uVar9 = uVar9 + 1 & 0xf;
  bVar5 = true;
  bVar2 = (byte)uVar9;
  switch((byte)(&DAT_20002570)[iVar1] - 1) {
  case 0:
    goto switchD_0800a6f8_caseD_0;
  case 1:
    DAT_20001501 = 4;
    DAT_20001503 = bVar7;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(4,uVar10);
    FUN_0800a42c();
    goto LAB_0800a578;
  case 2:
    DAT_20001501 = 5;
    DAT_20001503 = bVar7;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(5,uVar10);
    FUN_0800a42e();
    goto LAB_0800a578;
  case 3:
    DAT_20001501 = 3;
    DAT_20002591 = bVar2;
    FUN_0800b6ac(3,uVar10);
    DAT_20001503 = bVar7;
    FUN_0800db44();
    FUN_0800a430();
    bVar5 = FUN_0800c144();
    if (bVar5) {
      FUN_0800b3ec(1);
    }
    pcVar3 = DAT_20000c98;
    if (DAT_20000c98 != (code *)0x0) {
      cVar6 = FUN_0800c0ec();
      (*pcVar3)((int)cVar6);
    }
    goto LAB_0800a578;
  case 4:
    DAT_20001502 = 0;
    DAT_20002591 = bVar2;
    bVar7 = FUN_0800bbb4();
    if ((bVar7 & 6) != 0) {
      FUN_0800b91c();
    }
    uVar9 = 2;
    DAT_20001501 = 2;
    if (bVar4 == 3) {
      FUN_0800bc70();
      uVar9 = 6;
    }
    FUN_0800b6ac(uVar9,uVar10);
    FUN_0800a7cc();
    DAT_20001504 = 0;
    FUN_0800c598();
    FUN_0800b3ec(0);
    uVar9 = extraout_r1;
    uVar8 = extraout_r2;
    break;
  case 5:
    DAT_200047d4 = DAT_200047d4 & 0xff7f;
    DAT_20001500 = 1;
    DAT_20002591 = bVar2;
    FUN_0800a432();
    goto LAB_0800a578;
  case 6:
    DAT_20002591 = bVar2;
    DAT_200047d4 = FUN_0800e600((uint)DAT_20002590,1,(byte)(&DAT_20002570)[iVar1] - 1);
    DAT_20001500 = 0;
    FUN_0800a434();
    goto LAB_0800a578;
  case 7:
    DAT_20001502 = 0;
    DAT_20002591 = bVar2;
    if (DAT_20001501 != 4) goto LAB_0800a578;
    DAT_20001501 = 6;
    FUN_0800a436();
    FUN_0800b6ac((uint)DAT_20001501,0);
    FUN_0800b3ec(0);
    uVar9 = extraout_r1_00;
    uVar8 = extraout_r2_00;
    break;
  case 8:
    DAT_20000c70 = 0;
    DAT_20002591 = bVar2;
    goto LAB_0800a578;
  case 9:
    DAT_20001502 = bVar7;
    DAT_20002591 = bVar2;
    goto LAB_0800a578;
  case 10:
    DAT_20002591 = bVar2;
    FUN_0800a8bc(bVar7);
    goto LAB_0800a578;
  default:
    goto switchD_0800a6f8_default;
  }
  FUN_0800b420(0,uVar9,uVar8);
  goto LAB_0800a578;
switchD_0800a6f8_caseD_0:
  DAT_20001501 = 0;
  DAT_20002591 = bVar2;
  thunk_FUN_0800c54c(uVar10,1,0,&DAT_20001501);
  goto LAB_0800a578;
}


// ===================================================================
// FUN_0800a754 @ 0x0800a754  size=36  body=[[0800a754, 0800a777]]

void FUN_0800a754(void)

{
  undefined4 extraout_r2;
  undefined8 uVar1;
  
  (*DAT_20000c9c)();
  FUN_0800a570();
  FUN_0800a8d4();
  FUN_0800b8dc();
  uVar1 = FUN_0800c5c4();
  FUN_0800c1e0((int)uVar1,(uint)((ulonglong)uVar1 >> 0x20),extraout_r2);
  FUN_0800bdcc();
  return;
}


// ===================================================================
// FUN_0800a77c @ 0x0800a77c  size=6  body=[[0800a77c, 0800a781]]

undefined1 FUN_0800a77c(void)

{
  return DAT_20001501;
}


// ===================================================================
// process_record_wireless @ 0x0800a788  size=62  body=[[0800a788, 0800a7c5]]

// INFERRED: 2nd callee of process_record_kb (process_record_keychron order in keychron_task.c);
// body tests 0x7E0B 0x7E0E 0x7E0F (BT_HST*/P2P4G/BAT_LVL range)

undefined4 process_record_wireless(uint param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 uVar3;
  uint extraout_r1;
  undefined4 extraout_r2;
  
  bVar1 = FUN_0800bbb4();
  if ((bVar1 & 6) != 0) {
    FUN_0800bc70();
    bVar2 = FUN_0800c144();
    if (((bVar2) && (DAT_20001501 == '\x03')) && (*(char *)(param_2 + 5) != '\0')) {
      FUN_0800b3ec(1);
      FUN_0800b420(1,extraout_r1,extraout_r2);
    }
  }
  uVar3 = FUN_0800c4b4(param_1,param_2);
  return uVar3;
}


// ===================================================================
// FUN_0800a7cc @ 0x0800a7cc  size=38  body=[[0800a7cc, 0800a7f1]]

void FUN_0800a7cc(void)

{
  FUN_08008798(&DAT_200025b8,0,0x2200);
  DAT_200025b6 = 0;
  DAT_20002592 = 0;
  DAT_20001504 = 0;
  DAT_2000150c = FUN_08012508();
  return;
}


// ===================================================================
// FUN_0800a808 @ 0x0800a808  size=42  body=[[0800a808, 0800a831]]

bool FUN_0800a808(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)DAT_20002592;
  uVar2 = DAT_200025b6 + 1 & 0xff;
  if (uVar1 != uVar2) {
    memcpy((undefined4 *)(&DAT_200025b8 + (uint)DAT_200025b6 * 0x22),param_1,0x22);
    DAT_200025b6 = (ushort)uVar2;
  }
  return uVar1 != uVar2;
}


// ===================================================================
// FUN_0800a840 @ 0x0800a840  size=40  body=[[0800a840, 0800a867]]

bool FUN_0800a840(undefined4 *param_1)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = (uint)DAT_20002592;
  uVar2 = (uint)DAT_200025b6;
  if (uVar2 != uVar3) {
    uVar1 = DAT_20002592 + 1;
    memcpy(param_1,(undefined4 *)(&DAT_200025b8 + uVar3 * 0x22),0x22);
    DAT_20002592 = uVar1 & 0xff;
  }
  return uVar2 != uVar3;
}


// ===================================================================
// FUN_0800a874 @ 0x0800a874  size=16  body=[[0800a874, 0800a883]]

bool FUN_0800a874(void)

{
  return DAT_200025b6 == DAT_20002592;
}


// ===================================================================
// FUN_0800a88c @ 0x0800a88c  size=12  body=[[0800a88c, 0800a897]]

void FUN_0800a88c(void)

{
  DAT_2000150c = FUN_08012508();
  return;
}


// ===================================================================
// FUN_0800a89c @ 0x0800a89c  size=24  body=[[0800a89c, 0800a8b3]]

bool FUN_0800a89c(void)

{
  uint uVar1;
  
  uVar1 = FUN_0801258c(DAT_2000150c);
  return DAT_20000c71 < uVar1;
}


// ===================================================================
// FUN_0800a8bc @ 0x0800a8bc  size=6  body=[[0800a8bc, 0800a8c1]]

void FUN_0800a8bc(undefined1 param_1)

{
  DAT_20000c71 = param_1;
  return;
}


// ===================================================================
// FUN_0800a8c8 @ 0x0800a8c8  size=6  body=[[0800a8c8, 0800a8cd]]

void FUN_0800a8c8(undefined1 param_1)

{
  DAT_20001504 = param_1;
  return;
}


// ===================================================================
// FUN_0800a8d4 @ 0x0800a8d4  size=162  body=[[0800a8d4, 0800a975]]

void FUN_0800a8d4(void)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  undefined2 *puVar4;
  code *pcVar5;
  
  cVar1 = FUN_0800a77c();
  if ((cVar1 != '\x03') ||
     (((bVar2 = FUN_0800a874(), bVar2 && (DAT_20001504 == '\0')) || (bVar2 = FUN_0800a89c(), !bVar2)
      ))) {
    return;
  }
  if (DAT_20001504 == '\0') {
    bVar2 = FUN_0800a840((undefined4 *)&DAT_20002594);
    if (!bVar2) {
      return;
    }
    if (DAT_20002594 == '\0') {
      return;
    }
    uVar3 = FUN_08012508();
    if (uVar3 < 3) {
      return;
    }
    DAT_20001504 = '\x1e';
  }
  else {
    uVar3 = FUN_0801258c(DAT_20001508);
    if (uVar3 < 3) {
      return;
    }
    DAT_20001504 = DAT_20001504 + -1;
  }
  DAT_20001508 = FUN_08012508();
  if (DAT_20002594 == '\x02') {
    if (DAT_20000c88 == (code *)0x0) goto LAB_0800a942;
    puVar4 = (undefined2 *)0x20002597;
    pcVar5 = DAT_20000c88;
LAB_0800a930:
    (*pcVar5)(puVar4);
  }
  else if (DAT_20002594 == '\x01') {
    if (DAT_20000c84 == (code *)0x0) goto LAB_0800a942;
    puVar4 = &DAT_20002596;
    pcVar5 = DAT_20000c84;
    goto LAB_0800a930;
  }
  if ((DAT_20002594 == '\x03') && (DAT_20000c8c != (code *)0x0)) {
    (*DAT_20000c8c)(DAT_20002596);
  }
LAB_0800a942:
  DAT_2000150c = FUN_08012508();
  FUN_0800bc70();
  return;
}


// ===================================================================
// FUN_0800a98c @ 0x0800a98c  size=130  body=[[0800a98c, 0800aa0d]]

void FUN_0800a98c(int param_1)

{
  if (param_1 == 0) {
    FUN_08015338((uint *)&DAT_40020800,0x10,1);
    DAT_4002081a = 0x10;
    FUN_08013a7a(100);
    DAT_40020818 = 0x10;
  }
  if (DAT_20004b50 == '\0') {
    FUN_08015338((uint *)&DAT_40020000,0x20,1);
    DAT_40020018._0_2_ = 0x20;
    FUN_08015338((uint *)&DAT_40020000,0x20,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x282);
    if (param_1 != 0) {
      thunk_FUN_080163c8();
      return;
    }
    thunk_FUN_080163c8();
  }
  FUN_08015338((uint *)&DAT_40020000,0x10,1);
  DAT_40020018._0_2_ = 0x10;
  FUN_08015338((uint *)&DAT_40020400,2,0x20);
  return;
}


// ===================================================================
// FUN_0800aa20 @ 0x0800aa20  size=58  body=[[0800aa20, 0800aa59]]

void FUN_0800aa20(void)

{
  uint uVar1;
  
  uVar1 = FUN_0801258c(DAT_20001514);
  if (3000 < uVar1) {
    DAT_20001514 = FUN_08012508();
    DAT_40020018 = 0x100000;
    FUN_08013a7a(1000);
    DAT_40020018 = 0x10;
    FUN_08013a7a(30000);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800aa64 @ 0x0800aa64  size=200  body=[[0800aa64, 0800ab2b]]

void FUN_0800aa64(byte *param_1,uint param_2,char param_3,int param_4)

{
  byte *pbVar1;
  uint uVar2;
  byte local_58 [4];
  undefined1 local_54;
  char local_53;
  char local_52;
  char local_51;
  char local_50;
  undefined4 auStack_4f [14];
  
  FUN_08008798(local_58,0,0x40);
  if (param_4 == 0) {
    DAT_20001512 = DAT_20001512 + '\x01';
  }
  if (DAT_20001512 == '\0') {
    DAT_20001512 = '\x01';
  }
  uVar2 = 0;
  for (pbVar1 = param_1; pbVar1 != param_1 + param_2; pbVar1 = pbVar1 + 1) {
    uVar2 = *pbVar1 + uVar2 & 0xffff;
  }
  local_58[0] = 0x84;
  local_58[1] = 0x7e;
  local_54 = 0xaa;
  local_52 = (char)param_2 + '\x02';
  local_51 = -3 - (char)param_2;
  local_50 = DAT_20001512;
  local_53 = param_3 + 'U';
  memcpy(auStack_4f,(undefined4 *)param_1,param_2);
  local_58[param_2 + 9 & 0xff] = (byte)uVar2;
  local_58[param_2 + 10 & 0xff] = (byte)(uVar2 >> 8);
  DAT_20000ca2 = 0x40;
  FUN_08014120(&DAT_20004b50,&DAT_08016714);
  FUN_0801415e(0x20004b50);
  FUN_080141de(&DAT_20004b50,param_2 + 0xb & 0xff,(uint)local_58);
  *(short *)(*(int *)(DAT_20004b54 + 0xc) + 0x18) =
       (short)(1 << (*(uint *)(DAT_20004b54 + 0x10) & 0xff));
  FUN_08014142(&DAT_20004b50);
  return;
}


// ===================================================================
// FUN_0800ab3c @ 0x0800ab3c  size=48  body=[[0800ab3c, 0800ab6b]]

void FUN_0800ab3c(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x11;
  memcpy(puVar1,param_1,8);
  FUN_0800aa64((byte *)((int)puVar1 + -1),9,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800ab70 @ 0x0800ab70  size=48  body=[[0800ab70, 0800ab9f]]

void FUN_0800ab70(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x12;
  memcpy(puVar1,param_1,0x14);
  FUN_0800aa64((byte *)((int)puVar1 + -1),0x15,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800aba4 @ 0x0800aba4  size=50  body=[[0800aba4, 0800abd5]]

void FUN_0800aba4(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151b,0,0x3d);
  *(char *)(iVar1 + -2) = (char)param_1;
  *(undefined1 *)(iVar1 + -3) = 0x13;
  *(char *)(iVar1 + -1) = (char)((uint)param_1 >> 8);
  FUN_0800aa64((byte *)(iVar1 + -3),7,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800abdc @ 0x0800abdc  size=60  body=[[0800abdc, 0800ac17]]

void FUN_0800abdc(char param_1)

{
  int iVar1;
  
  if ((byte)(param_1 + 0x7fU) < 3) {
    iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
    *(undefined1 *)(iVar1 + -2) = 0x14;
    *(char *)(iVar1 + -1) = (char)(1 << (uint)(byte)(param_1 + 0x7f));
    FUN_0800aa64((byte *)(iVar1 + -2),2,'\x01',0);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800ac1c @ 0x0800ac1c  size=70  body=[[0800ac1c, 0800ac61]]

void FUN_0800ac1c(int param_1)

{
  char cVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)FUN_08008798(&DAT_20001519,0,0x3f);
  puVar2[-1] = 0x16;
  *puVar2 = *(undefined1 *)(param_1 + 1);
  cVar1 = *(char *)(param_1 + 2);
  puVar2[1] = cVar1;
  puVar2[2] = cVar1 >> 7;
  cVar1 = *(char *)(param_1 + 3);
  puVar2[3] = cVar1;
  puVar2[4] = cVar1 >> 7;
  puVar2[5] = *(undefined1 *)(param_1 + 4);
  puVar2[6] = *(undefined1 *)(param_1 + 5);
  FUN_0800aa64(puVar2 + -1,8,'\0',0);
  return;
}


// ===================================================================
// FUN_0800ac68 @ 0x0800ac68  size=118  body=[[0800ac68, 0800acdd]]

void FUN_0800ac68(undefined1 param_1,undefined4 ***param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 ***pppuVar3;
  undefined4 ***local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  FUN_08008798(&DAT_2000151a,0,0x3e);
  local_1c = (undefined4 ***)0x0;
  local_18 = 0x103;
  local_14 = 0;
  if (param_2 == (undefined4 ***)0x0) {
    param_2 = &local_1c;
  }
  DAT_20001518 = 0x21;
  DAT_2000151a = (undefined1)*(undefined2 *)((int)param_2 + 2);
  pppuVar3 = (undefined4 ***)param_2[2];
  DAT_2000151b = (undefined1)((ushort)*(undefined2 *)((int)param_2 + 2) >> 8);
  DAT_2000151c = *(undefined1 *)(param_2 + 1);
  DAT_2000151d = *(undefined1 *)((int)param_2 + 5);
  DAT_2000151e = *(undefined1 *)((int)param_2 + 6);
  DAT_20001519 = param_1;
  if (pppuVar3 == (undefined4 ***)0x0) {
    uVar1 = 7;
  }
  else {
    uVar1 = FUN_080086c0((uint)pppuVar3);
    memcpy((undefined4 *)&DAT_2000151f,pppuVar3,uVar1);
    iVar2 = FUN_080086c0((uint)param_2[2]);
    uVar1 = iVar2 + 7U & 0xff;
  }
  FUN_0800aa20();
  FUN_0800aa64(&DAT_20001518,uVar1,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800acec @ 0x0800acec  size=60  body=[[0800acec, 0800ad27]]

void FUN_0800acec(undefined1 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151c,0,0x3c);
  *(char *)(iVar1 + -2) = (char)param_2;
  *(undefined1 *)(iVar1 + -4) = 0x22;
  *(undefined1 *)(iVar1 + -3) = param_1;
  *(char *)(iVar1 + -1) = (char)((uint)param_2 >> 8);
  FUN_0800aa20();
  FUN_0800aa64((byte *)(iVar1 + -4),4,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800ad2c @ 0x0800ad2c  size=60  body=[[0800ad2c, 0800ad67]]

void FUN_0800ad2c(void)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)(iVar1 + -1) = 0x23;
  FUN_0801415e(0x20004b50);
  FUN_08013a7a(3000);
  FUN_08013a7a(7000);
  FUN_0800aa64((byte *)(iVar1 + -1),2,'\x01',0);
  return;
}


// ===================================================================
// FUN_0800ad70 @ 0x0800ad70  size=44  body=[[0800ad70, 0800ad9b]]

void FUN_0800ad70(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
  *(undefined1 *)(iVar1 + -2) = 0x32;
  *(undefined1 *)(iVar1 + -1) = param_1;
  FUN_0800aa64((byte *)(iVar1 + -2),2,'\0',0);
  return;
}


// ===================================================================
// FUN_0800ada0 @ 0x0800ada0  size=78  body=[[0800ada0, 0800aded]]

void FUN_0800ada0(uint param_1,char param_2)

{
  byte local_50 [3];
  undefined1 local_4d;
  
  FUN_08008798(local_50,0,0x40);
  local_50[0] = 0x84;
  local_50[1] = 0x7f;
  local_4d = 0x80;
  FUN_08014120(&DAT_20004b50,&DAT_08016714);
  FUN_0801415e(0x20004b50);
  FUN_080141bc(&DAT_20004b50,(uint)(byte)(param_2 + 4),(uint)local_50,param_1);
  FUN_0801417a(0x20004b50);
  FUN_08014142(&DAT_20004b50);
  return;
}


// ===================================================================
// FUN_0800adf8 @ 0x0800adf8  size=36  body=[[0800adf8, 0800ae1b]]

void FUN_0800adf8(void)

{
  FUN_08008798(&DAT_20001519,0,0x3f);
  DAT_20001518 = 0xa4;
  FUN_0800aa64(&DAT_20001518,1,'\0',0);
  return;
}


// ===================================================================
// FUN_0800ae58 @ 0x0800ae58  size=44  body=[[0800ae58, 0800ae83]]

void FUN_0800ae58(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
  *(undefined1 *)(iVar1 + -2) = 0x33;
  *(undefined1 *)(iVar1 + -1) = param_1;
  FUN_0800aa64((byte *)(iVar1 + -2),2,'\0',0);
  return;
}


// ===================================================================
// FUN_0800ae88 @ 0x0800ae88  size=48  body=[[0800ae88, 0800aeb7]]

void FUN_0800ae88(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x41;
  memcpy(puVar1,param_1,0x16);
  FUN_0800aa64((byte *)((int)puVar1 + -1),0x17,'\0',0);
  return;
}


// ===================================================================
// FUN_0800aebc @ 0x0800aebc  size=56  body=[[0800aebc, 0800aef3]]

void FUN_0800aebc(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_080086c0((uint)param_1);
  puVar2 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar2 + -1) = 0x45;
  memcpy(puVar2,param_1,uVar1 & 0xff);
  FUN_0800aa64((byte *)((int)puVar2 + -1),uVar1 + 1 & 0xff,'\0',0);
  return;
}


// ===================================================================
// FUN_0800aef8 @ 0x0800aef8  size=48  body=[[0800aef8, 0800af27]]

void FUN_0800aef8(byte param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
  *(undefined1 *)(iVar1 + -2) = 0x71;
  *(byte *)(iVar1 + -1) = param_1;
  FUN_0800aa20();
  FUN_0800aa64((byte *)(iVar1 + -2),2,'\0',0);
  return;
}


// ===================================================================
// FUN_0800af8c @ 0x0800af8c  size=124  body=[[0800af8c, 0800b007]]

// WARNING: Type propagation algorithm not settling

void FUN_0800af8c(undefined1 param_1,undefined4 *param_2,uint param_3,undefined1 param_4)

{
  byte local_38 [4];
  byte local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined4 auStack_31 [7];
  
  FUN_08008798(local_38,0,0x20);
  local_38[0] = 3;
  local_38[1] = 0xaa;
  local_38[2] = 0x57;
  local_38[3] = (byte)param_3;
  local_34 = ~local_38[3];
  local_33 = param_4;
  local_32 = param_1;
  memcpy(auStack_31,param_2,param_3);
  raw_hid_send((undefined4 *)local_38,0x20);
  if (0x19 < param_3) {
    FUN_08008798((byte *)((int)local_38 + 1),0,0x1f);
    local_38[0] = 3;
    memcpy((undefined4 *)((int)local_38 + 1),(undefined4 *)((int)param_2 + 0x19),param_3 - 0x19);
    raw_hid_send((undefined4 *)local_38,0x20);
  }
  return;
}


// ===================================================================
// FUN_0800b008 @ 0x0800b008  size=616  body=[[0800b008, 0800b083] [0800b08c, 0800b277]]

void FUN_0800b008(void)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar2;
  int extraout_r1_01;
  char cVar3;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 uVar4;
  uint uVar5;
  undefined1 uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  byte *pbVar10;
  byte bVar11;
  char cVar12;
  undefined4 local_64;
  byte abStack_60 [4];
  char local_5c;
  byte local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  char local_58;
  undefined2 local_57;
  char local_55 [57];
  
  iVar2 = DAT_40020410;
  bVar11 = 0;
  cVar12 = '\0';
  if (-1 < iVar2 << 0x1e) {
    FUN_08008798(abStack_60,0,0x40);
    FUN_0800ada0((uint)abStack_60,DAT_20000ca2);
    if ((local_5c == -0x56) &&
       (((uVar9 = (uint)local_5b, uVar9 != 0x54 || (local_58 != -0x55)) || ((char)local_57 != 'U')))
       ) {
      local_64._0_2_ = 0;
      uVar4 = extraout_r2;
      if ((int)(uVar9 << 0x1c) < 0) {
        local_64._0_2_ = CONCAT11(local_5a,1);
        FUN_0800a1fc((undefined2)local_64,extraout_r1,extraout_r2);
        uVar4 = extraout_r2_00;
      }
      if ((int)(uVar9 << 0x1f) < 0) {
        FUN_0800adf8();
        switch(local_5a) {
        case 0x20:
          local_64._0_1_ = 4;
          break;
        case 0x21:
          local_64._0_1_ = 2;
          break;
        case 0x22:
          local_64._0_1_ = 3;
          break;
        case 0x23:
          local_64._0_1_ = 5;
          break;
        case 0x24:
          local_64._0_1_ = 6;
          break;
        case 0x25:
          local_64._0_1_ = 7;
          break;
        case 0x26:
          local_64._0_1_ = 8;
        }
        local_64._0_2_ = CONCAT11(local_59,(undefined1)local_64);
        FUN_0800a1fc((undefined2)local_64,extraout_r1_00,extraout_r2_01);
        uVar4 = extraout_r2_02;
      }
      iVar2 = uVar9 << 0x1e;
      if (iVar2 < 0) {
        local_64._0_2_ = CONCAT11(local_58,10);
        FUN_0800a1fc((undefined2)local_64,iVar2,uVar4);
        iVar2 = extraout_r1_01;
      }
      if ((int)(uVar9 << 0x1b) < 0) {
        if (local_55[1] < '\0') {
          uVar7 = ((byte)local_55[1] & 0x7f) * 0x4e2;
        }
        else {
          uVar7 = (uint)(byte)local_55[1] * 0x7d;
        }
        uVar5 = uVar7 / 1000;
        if (7999 < uVar7) {
          uVar5 = uVar5 / 3;
        }
        DAT_20000ca0 = (undefined2)uVar5;
        local_64 = CONCAT31((uint3)(byte)uVar5,0xb);
        FUN_0800a1fc((short)local_64,iVar2,uVar5);
      }
      if ((int)(uVar9 << 0x1d) < 0) {
        FUN_0800c074(1,(uint)local_57);
      }
    }
    if (DAT_20000c73 == '\0') {
      pbVar10 = abStack_60;
    }
    else {
      cVar3 = '1';
      cVar1 = '\0';
      pbVar10 = abStack_60;
      pcVar8 = (char *)((int)&local_57 + 1);
      do {
        if (((*pcVar8 == -0x56) && (pcVar8[1] == 'W')) && (pcVar8[3] == ~pcVar8[2])) {
          cVar12 = pcVar8[4];
          pbVar10 = (byte *)(pcVar8 + 5);
          bVar11 = pcVar8[2];
          cVar1 = DAT_20000c73;
        }
        cVar3 = cVar3 + -1;
        pcVar8 = pcVar8 + 1;
      } while (cVar3 != '\0');
      if (cVar1 == '\0') {
        return;
      }
      DAT_20000c73 = '\0';
      DAT_20000c72 = bVar11;
      DAT_20001510 = cVar12;
    }
    uVar9 = (uint)DAT_20000c72;
    if (uVar9 < 0x3c) {
      DAT_20000c73 = '\x01';
      uVar7 = 0;
      for (iVar2 = 0; iVar2 < (int)(uVar9 - 2); iVar2 = iVar2 + 1) {
        uVar7 = uVar7 + pbVar10[iVar2] & 0xffff;
      }
      if (((uint)pbVar10[uVar9 - 2] == (uVar7 & 0xff)) && ((uint)pbVar10[uVar9 - 1] == uVar7 >> 8))
      {
        bVar11 = *pbVar10;
        uVar9 = uVar9 - 3 & 0xff;
        if (bVar11 == 0xa3) {
          FUN_0800af8c(0xa3,(undefined4 *)(pbVar10 + 1),uVar9,DAT_20001510);
        }
        else if (bVar11 < 0xa4) {
          if (bVar11 == 0xa1) {
            bVar11 = pbVar10[2];
            if (bVar11 < 0x15) {
              if (bVar11 < 0x11) {
                DAT_20000c73 = 1;
                return;
              }
            }
            else if (bVar11 != 0x16) {
              DAT_20000c73 = 1;
              return;
            }
            bVar11 = pbVar10[3];
            if (bVar11 == 2) {
              FUN_0800a8c8(0);
              cVar12 = (char)DAT_20000ca0 + '\x05';
            }
            else if (bVar11 == 3) {
              cVar12 = (char)DAT_20000ca0 + '\n';
            }
            else {
              if (bVar11 != 0) {
                DAT_20000c73 = 1;
                return;
              }
              FUN_0800a8c8(0);
              cVar12 = (char)DAT_20000ca0;
            }
            FUN_0800a8bc(cVar12);
          }
          else if (((bVar11 == 0xa2) && (pbVar10[3] == 0)) && (pbVar10[2] == 0x72)) {
            FUN_0800cb44((undefined4 *)(pbVar10 + 1),uVar9);
          }
        }
        else {
          if (bVar11 == 0xb0) {
            bVar11 = pbVar10[1];
            uVar6 = 1;
          }
          else {
            if (bVar11 != 0xb4) {
              DAT_20000c73 = 1;
              return;
            }
            bVar11 = pbVar10[1];
            uVar6 = 10;
          }
          FUN_0800a1fc(CONCAT11(bVar11,uVar6),uVar9,0);
        }
      }
    }
  }
  return;
}


// ===================================================================
// lkbt51_dfu_rx @ 0x0800b290  size=148  body=[[0800b290, 0800b323]]

// INFERRED: 0xAA case target of kc_raw_hid_rx

void lkbt51_dfu_rx(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  
  if ((((*param_1 == -0x56) && ((byte)param_1[1] - 0x55 < 2)) &&
      (uVar3 = (uint)(byte)param_1[2], uVar3 == (byte)~param_1[3])) && (uVar3 < 0x1c)) {
    pbVar5 = (byte *)(param_1 + 5);
    pbVar4 = (byte *)(param_1 + 4);
    uVar2 = 0;
    while ((int)(pbVar4 + (-4 - (int)param_1)) < (int)(uVar3 - 2)) {
      pbVar4 = pbVar4 + 1;
      uVar2 = uVar2 + *pbVar4 & 0xffff;
    }
    if (((uint)pbVar5[uVar3 - 2] == (uVar2 & 0xff)) && ((uint)pbVar5[uVar3 - 1] == uVar2 >> 8)) {
      cVar1 = param_1[4];
      bVar6 = DAT_20001511 != cVar1;
      if (bVar6) {
        DAT_20001511 = cVar1;
      }
      if ((param_1[5] & 0xf0U) == 0x60) {
        FUN_0800aa20();
        FUN_0800aa64(pbVar5,uVar3 - 2 & 0xff,param_1[1] == 'V',(uint)!bVar6);
        return;
      }
    }
  }
  return;
}


// ===================================================================
// FUN_0800b328 @ 0x0800b328  size=34  body=[[0800b328, 0800b349]]

void FUN_0800b328(void)

{
  FUN_08008798((byte *)&DAT_200047bc,0,0x18);
  FUN_08015338((uint *)&DAT_40020400,0x1000,1);
  DAT_4002041a = 0x1000;
  return;
}


// ===================================================================
// FUN_0800b354 @ 0x0800b354  size=18  body=[[0800b354, 0800b365]]

void FUN_0800b354(void)

{
  byte bVar1;
  
  bVar1 = FUN_08010cf4();
  if (bVar1 == 0) {
    FUN_08010ebc();
    return;
  }
  return;
}


// ===================================================================
// thunk_FUN_08010cd4 @ 0x0800b366  size=4  body=[[0800b366, 0800b369]]

void thunk_FUN_08010cd4(void)

{
  if ((DAT_20004808 & 3) != 0) {
    DAT_20000eb0 = 0;
  }
  DAT_20004808 = DAT_20004808 & 0xfc;
  return;
}


// ===================================================================
// FUN_0800b36a @ 0x0800b36a  size=14  body=[[0800b36a, 0800b377]]

bool FUN_0800b36a(void)

{
  byte bVar1;
  
  bVar1 = FUN_08010cf4();
  return bVar1 != 0;
}


// ===================================================================
// FUN_0800b378 @ 0x0800b378  size=30  body=[[0800b378, 0800b395]]

uint FUN_0800b378(void)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = FUN_0800f1cc((undefined4 *)&DAT_20004808,0x18,8);
  if (DAT_20004808 < 4) {
    uVar2 = FUN_0800fe14();
    return uVar2;
  }
  return (uint)bVar1;
}


// ===================================================================
// FUN_0800b39c @ 0x0800b39c  size=28  body=[[0800b39c, 0800b3b7]]

bool FUN_0800b39c(void)

{
  if (DAT_20001568 != 0) {
    return true;
  }
  return DAT_20001560 != '\0' || DAT_200047cd != '\0';
}


// ===================================================================
// FUN_0800b3c4 @ 0x0800b3c4  size=34  body=[[0800b3c4, 0800b3e5]]

void FUN_0800b3c4(void)

{
  bool bVar1;
  
  DAT_200047cd = 0;
  FUN_0800b378();
  bVar1 = FUN_0800b36a();
  if (bVar1) {
    FUN_0800b354();
    return;
  }
  FUN_08010cd4();
  return;
}


// ===================================================================
// FUN_0800b3ec @ 0x0800b3ec  size=38  body=[[0800b3ec, 0800b411]]

void FUN_0800b3ec(int param_1)

{
  if (param_1 == 0) {
    DAT_4002041a = 0x1000;
  }
  else if (DAT_20001568 == 0) {
    DAT_20001568 = FUN_08012508();
    DAT_2000156c = DAT_20001568;
  }
  else {
    DAT_20001568 = FUN_08012508();
  }
  return;
}


// ===================================================================
// FUN_0800b420 @ 0x0800b420  size=102  body=[[0800b420, 0800b485]]

void FUN_0800b420(uint param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint extraout_r1;
  undefined4 extraout_r2;
  
  if (param_1 == 0) {
    DAT_20001560 = '\0';
    DAT_2000155c = param_1;
    FUN_0800b378();
    bVar2 = FUN_08010cf4();
    if (bVar2 == 0) {
      FUN_08010cd4();
      return;
    }
  }
  else {
    uVar3 = FUN_0800c48c(param_1,param_2,param_3);
    uVar1 = DAT_2000155c;
    if ((uVar3 < DAT_2000155c) && (uVar1 = uVar3, DAT_20001560 != '\0')) {
      uVar1 = DAT_2000155c + uVar3;
    }
    DAT_2000155c = uVar1;
    if (((DAT_2000155c == 0) || (30000 < uVar3 - DAT_2000155c)) && (DAT_20001560 == '\0')) {
      DAT_20001564 = FUN_08012508();
      DAT_2000155c = FUN_0800c48c(DAT_20001564,extraout_r1,extraout_r2);
      DAT_20001560 = 1;
      FUN_0800b354();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_0800b494 @ 0x0800b494  size=44  body=[[0800b494, 0800b4bf]]

void FUN_0800b494(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_0800bbb4();
  if (((cVar1 != '\x01') || (DAT_20004ae4 != '\x05')) && (iVar2 = FUN_08012148(), iVar2 << 0x1e < 0)
     ) {
    FUN_0800fe78(0x30,0xff,0xff,0xff);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800b4c4 @ 0x0800b4c4  size=250  body=[[0800b4c4, 0800b5bd]]

undefined4 FUN_0800b4c4(void)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined4 extraout_r1;
  byte bVar6;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  uint uVar7;
  
  bVar1 = FUN_0800bbb4();
  if ((bVar1 & 6) != 0) {
    bVar2 = FUN_0800c158();
    if (bVar2) {
      thunk_FUN_08011378(0,0,0);
      return 1;
    }
    bVar2 = FUN_0800c144();
    if (bVar2) {
      thunk_FUN_08011378(0,0,0);
    }
    if ((DAT_20001560 != 0) && (bVar1 = DAT_20001560 & 0xc, (DAT_20001560 & 0xc) == 0)) {
      bVar4 = bVar1;
      if ((DAT_20001560 & 0x80) != 0) {
        bVar4 = 0xff;
      }
      FUN_0800fe78(0x51,bVar4,bVar1,bVar1);
      if ((char)DAT_20001560 < '\0') {
        uVar5 = 0xff;
      }
      else {
        uVar5 = 0;
      }
      FUN_0800fe78(0x53,uVar5,0,0);
    }
    bVar2 = FUN_0800c304();
    if (bVar2 != 0) {
      FUN_0800c314((uint)bVar2,extraout_r1,extraout_r2,extraout_r3);
    }
    if (DAT_200047cd != 0) {
      uVar7 = DAT_200047cd & 0xf;
      if (DAT_200047cc == '\0') {
        if (DAT_20000ca3 != uVar7) {
          bVar1 = DAT_200047cd & 0x10;
          if ((DAT_200047cd & 0x10) == 0) {
            uVar3 = (uint)(byte)(&DAT_0801672b)[uVar7];
          }
          else {
            uVar3 = 0x14;
            bVar1 = 0;
          }
          FUN_0800fe78(uVar3,bVar1,bVar1,bVar1);
          DAT_20000ca3 = (byte)uVar7;
        }
      }
      else {
        thunk_FUN_08011378(0,0,0);
      }
      bVar1 = DAT_200047cd & 0x10;
      if ((int)((uint)DAT_200047cd << 0x18) < 0) {
        if ((DAT_200047cd & 0x10) == 0) {
          bVar4 = 0xff;
          goto LAB_0800b598;
        }
        bVar6 = 0xff;
LAB_0800b560:
        bVar4 = 0;
        bVar1 = 0;
        uVar7 = 0x14;
      }
      else {
        bVar4 = bVar1;
        if ((DAT_200047cd & 0x10) != 0) {
          bVar6 = 0;
          goto LAB_0800b560;
        }
LAB_0800b598:
        uVar7 = (uint)(byte)(&DAT_0801672b)[uVar7];
        bVar6 = bVar1;
      }
      FUN_0800fe78(uVar7,bVar1,bVar6,bVar4);
      goto LAB_0800b5a0;
    }
  }
  FUN_0800b494();
LAB_0800b5a0:
  FUN_0801017a();
  return 1;
}


// ===================================================================
// FUN_0800b5d0 @ 0x0800b5d0  size=200  body=[[0800b5d0, 0800b5e9] [0800b5f0, 0800b69d]]

void FUN_0800b5d0(char *param_1)

{
  byte bVar1;
  uint uVar2;
  
  if (*param_1 != '\x05') {
    DAT_20001574 = *param_1;
  }
  switch(DAT_20001574) {
  case '\0':
    goto switchD_0800b5e6_caseD_0;
  default:
    DAT_20001576 = 0;
    break;
  case '\x02':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    if (DAT_200047d0 == 0) {
      DAT_200047cd = DAT_200047cd | 0x80;
      if (DAT_200047c8 != 0) {
        DAT_200047d0 = DAT_200047c8;
      }
      goto switchD_0800b5e6_caseD_0;
    }
    break;
  case '\x03':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    uVar2 = (uint)(ushort)DAT_200047c0;
    if (DAT_200047d0 == 0) {
      DAT_200047cd = DAT_200047cd | 0x80;
    }
    else {
      DAT_200047cd = DAT_200047cd & 0x1f;
      uVar2 = DAT_200047c8 - uVar2 & 0xffff;
    }
    DAT_20001576 = (ushort)uVar2;
    goto joined_r0x0800b68a;
  case '\x04':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    if ((int)((uint)DAT_200047cd << 0x18) < 0) {
      DAT_200047cd = DAT_200047cd & 0x1f;
      DAT_20001576 = (ushort)DAT_200047c4;
    }
    else {
      DAT_200047cd = DAT_200047cd | 0x80;
      DAT_20001576 = (ushort)DAT_200047c0;
    }
    uVar2 = (uint)DAT_20001576;
joined_r0x0800b68a:
    if (((DAT_200047c8 == 0) || (DAT_200047d0 <= DAT_200047c8)) && (uVar2 != 0)) {
      DAT_200047d0 = DAT_200047d0 + uVar2;
      goto switchD_0800b5e6_caseD_0;
    }
  }
  DAT_200047cd = DAT_200047cd & 0x1f;
  FUN_0800b4c4();
  DAT_200047cd = 0;
  FUN_0800bc70();
switchD_0800b5e6_caseD_0:
  if (DAT_200047cd == 0) {
    FUN_0800b378();
    bVar1 = FUN_08010cf4();
    if (bVar1 == 0) {
      FUN_08010cd4();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_0800b6ac @ 0x0800b6ac  size=292  body=[[0800b6ac, 0800b6ff] [0800b706, 0800b7d5]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0800b6ac(uint param_1,uint param_2)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  cVar2 = FUN_0800bbb4();
  if (cVar2 == '\x01') {
    return;
  }
  if (param_2 == 0x18) {
    param_2 = 0x11;
  }
  bVar1 = (byte)param_2;
  if ((DAT_20001559 == param_2) || (param_1 == 2)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
    DAT_20001559 = bVar1;
  }
  if (((DAT_20001558 == param_1) && (!bVar3)) && (param_1 != 5)) {
    return;
  }
  DAT_20001558 = (char)param_1;
  DAT_20001570 = FUN_08012508();
  FUN_0800b354();
  FUN_08010fa4();
  switch(param_1) {
  case 2:
    DAT_200047bc = 0;
    DAT_200047c0 = 100;
    DAT_200047c4 = 100;
    DAT_200047c8 = 600;
    _DAT_200047cc = 0;
    DAT_200047d0 = 0;
    FUN_0800b5d0((char *)&DAT_200047bc);
    bVar3 = FUN_0800c158();
    if (bVar3) {
LAB_0800b728:
      uVar4 = 1000;
      goto LAB_0800b72c;
    }
    goto LAB_0800b73a;
  case 3:
    if (DAT_20001578 != '\x03') {
      DAT_200047bc = 3;
      DAT_200047c0 = 2000;
      DAT_200047c4 = 0xfa;
      DAT_200047c8 = 2000;
      DAT_200047d0 = 0;
      _DAT_200047cc = (uint)CONCAT11(bVar1,1);
      FUN_0800b5d0((char *)&DAT_200047bc);
    }
    if (DAT_200047c8 == 0) goto LAB_0800b7aa;
    uVar5 = 600000;
    uVar4 = DAT_200047c8;
    goto LAB_0800b770;
  case 4:
    puVar6 = &DAT_08016778;
    break;
  case 5:
    puVar6 = &DAT_08016748;
    break;
  case 6:
    DAT_200047bc = 0;
    DAT_200047c0 = 100;
    DAT_200047c4 = 100;
    DAT_200047c8 = 600;
    _DAT_200047cc = 0;
    DAT_200047d0 = 0;
    FUN_0800b5d0((char *)&DAT_200047bc);
    bVar3 = FUN_0800ca74();
    if (!bVar3) goto LAB_0800b728;
    uVar4 = 3000;
    goto LAB_0800b72c;
  default:
    goto switchD_0800b6fc_default;
  }
  DAT_200047bc = *puVar6;
  DAT_200047c0 = puVar6[1];
  DAT_200047c4 = puVar6[2];
  DAT_200047c8 = puVar6[3];
  DAT_200047d0 = puVar6[5];
  DAT_200047cc_2 = (undefined2)((uint)puVar6[4] >> 0x10);
  DAT_200047cc = (undefined1)puVar6[4];
  _DAT_200047cc = CONCAT22(DAT_200047cc_2,CONCAT11(bVar1,DAT_200047cc)) | 0x8000;
  FUN_0800b5d0((char *)&DAT_200047bc);
LAB_0800b73a:
  if (DAT_200047c8 == 0) {
LAB_0800b7aa:
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = 40000;
    uVar5 = DAT_200047c8;
LAB_0800b770:
    if (uVar4 < uVar5) {
      uVar4 = uVar5;
    }
  }
LAB_0800b72c:
  FUN_08010f98(uVar4);
switchD_0800b6fc_default:
  DAT_20001578 = (char)param_1;
  return;
}


// ===================================================================
// FUN_0800b800 @ 0x0800b800  size=24  body=[[0800b800, 0800b817]]

void FUN_0800b800(void)

{
  char cVar1;
  
  cVar1 = FUN_0800bbb4();
  if ((cVar1 != '\x01') || (DAT_20004ae4 != '\x05')) {
    FUN_0800b494();
  }
  return;
}


// ===================================================================
// FUN_0800b81c @ 0x0800b81c  size=16  body=[[0800b81c, 0800b82b]]

uint FUN_0800b81c(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012148();
  return ((uVar1 ^ 2) & 3) >> 1;
}


// ===================================================================
// FUN_0800b82c @ 0x0800b82c  size=154  body=[[0800b82c, 0800b8c5]]

void FUN_0800b82c(void)

{
  uint uVar1;
  
  if ((DAT_2000156c != 0) && (uVar1 = FUN_0801258c(DAT_2000156c), 1000 < uVar1)) {
    uVar1 = DAT_40020414;
    DAT_40020414 = uVar1 ^ 0x1000;
    DAT_2000156c = FUN_08012508();
    uVar1 = FUN_0801258c(DAT_20001568);
    if (10000 < uVar1) {
      uVar1 = DAT_40020410;
      if ((uVar1 & 0x1000) == 0) {
        DAT_20001568 = 0;
        DAT_2000156c = 0;
      }
    }
  }
  if (DAT_20001560 != 0) {
    if ((DAT_20001560 & 0xc) != 0) {
LAB_0800b876:
      DAT_20001560 = 0;
      FUN_0800bc70();
      return;
    }
    uVar1 = FUN_0801258c(DAT_20001564);
    if (uVar1 < 0x3e9) {
      if ((DAT_20001560 & 0xc) != 0) goto LAB_0800b876;
    }
    else {
      if ((int)((uint)DAT_20001560 << 0x18) < 0) {
        DAT_20001560 = (DAT_20001560 & 0x7f) + 1;
      }
      else {
        DAT_20001560 = DAT_20001560 | 0x80;
      }
      DAT_20001564 = FUN_08012508();
      if (((DAT_20001560 & 0xc) != 0) && (uVar1 = FUN_0800b81c(), uVar1 != 0)) {
        FUN_08010cd4();
        return;
      }
    }
  }
  return;
}


// ===================================================================
// FUN_0800b8dc @ 0x0800b8dc  size=48  body=[[0800b8dc, 0800b90b]]

void FUN_0800b8dc(void)

{
  uint uVar1;
  
  FUN_0800c43c();
  if ((DAT_200047cd != '\0') && (uVar1 = FUN_0801258c(DAT_20001570), DAT_20001576 <= uVar1)) {
    FUN_0800b5d0(&DAT_20001574);
    DAT_20001570 = FUN_08012508();
  }
  FUN_0800b82c();
  return;
}


// ===================================================================
// FUN_0800b91c @ 0x0800b91c  size=78  body=[[0800b91c, 0800b969]]

int FUN_0800b91c(void)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_0800d4b2();
  if (iVar3 != 0) {
    FUN_0800d4b6();
    bVar1 = FUN_08010cf4();
    if ((bVar1 == 0) || ((bVar1 = FUN_08010cf4(), bVar1 != 0 && (bVar2 = FUN_08010fb0(), bVar2)))) {
      FUN_08010fe4();
      thunk_FUN_08011378(0,0,0);
      FUN_0800b494();
      FUN_080114fc();
      uVar4 = FUN_0800b81c();
      if (uVar4 != 0) {
        FUN_08010fcc();
      }
    }
  }
  return iVar3;
}


// ===================================================================
// FUN_0800b970 @ 0x0800b970  size=2  body=[[0800b970, 0800b971]]

void FUN_0800b970(void)

{
  return;
}


// ===================================================================
// FUN_0800b972 @ 0x0800b972  size=30  body=[[0800b972, 0800b98f]]

undefined4 FUN_0800b972(void)

{
  char cVar1;
  
  FUN_0800c5ec();
  FUN_0800a754();
  FUN_0800b970();
  cVar1 = FUN_0800bbb4();
  if (cVar1 == '\x01') {
    FUN_0800bbc0();
  }
  return 1;
}


// ===================================================================
// FUN_0800b990 @ 0x0800b990  size=90  body=[[0800b990, 0800b9e9]]

void FUN_0800b990(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int local_18;
  int iStack_14;
  undefined4 uStack_10;
  
  local_18 = param_1;
  iStack_14 = param_2;
  uStack_10 = param_3;
  if (param_1 != 0) {
    FUN_08012120(&DAT_20000c5c);
    FUN_0800a41c();
    iVar2 = FUN_08012508();
    while (uVar3 = FUN_0801258c(iVar2), uVar3 < 0x32) {
      (*DAT_20000c9c)();
    }
    FUN_0800a3d4(0x1e,0);
    return;
  }
  FUN_0800b3c4();
  cVar1 = FUN_0800a77c();
  if ((cVar1 == '\x03') && (DAT_2000157a == '\x02')) {
    local_18 = param_1;
    iStack_14 = param_1;
    (*DAT_20000c60)(&local_18);
  }
  return;
}


// ===================================================================
// FUN_0800b9f8 @ 0x0800b9f8  size=90  body=[[0800b9f8, 0800ba51]]

void FUN_0800b9f8(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int local_18;
  int iStack_14;
  undefined4 uStack_10;
  
  local_18 = param_1;
  iStack_14 = param_2;
  uStack_10 = param_3;
  if (param_1 != 0) {
    FUN_08012120(&DAT_20000c5c);
    FUN_0800a41c();
    iVar2 = FUN_08012508();
    while (uVar3 = FUN_0801258c(iVar2), uVar3 < 0x32) {
      (*DAT_20000c9c)();
    }
    FUN_0800a3d4(0x18,0);
    return;
  }
  FUN_0800b3c4();
  cVar1 = FUN_0800a77c();
  if ((cVar1 == '\x03') && (DAT_2000157a == '\x04')) {
    local_18 = param_1;
    iStack_14 = param_1;
    (*DAT_20000c60)(&local_18);
  }
  return;
}


// ===================================================================
// FUN_0800ba60 @ 0x0800ba60  size=52  body=[[0800ba60, 0800ba93]]

void FUN_0800ba60(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  int local_10;
  int iStack_c;
  undefined4 uStack_8;
  
  local_10 = param_1;
  uStack_8 = param_3;
  if (param_1 == 0) {
    if (DAT_20004ae4 == '\x04') {
      iStack_c = param_1;
      (*DAT_20000ecc)(&local_10);
    }
  }
  else {
    iStack_c = param_2;
    puVar1 = (undefined *)FUN_0801212c();
    if (puVar1 != &DAT_20000ec8) {
      FUN_08012120(&DAT_20000ec8);
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_0800ba9c @ 0x0800ba9c  size=258  body=[[0800ba9c, 0800bb9d]]

void FUN_0800ba9c(uint param_1)

{
  bool bVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  undefined4 uVar6;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  uint uVar7;
  undefined4 extraout_r2_02;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  undefined4 uVar8;
  undefined4 extraout_r2_05;
  undefined4 extraout_r2_06;
  undefined8 uVar9;
  
  if (DAT_2000157a == param_1) {
    return;
  }
  if ((DAT_2000157a == 1) ||
     (cVar3 = FUN_0800a77c(), uVar6 = extraout_r1_02, uVar8 = extraout_r2_02, cVar3 == '\x03')) {
    FUN_0800db44();
    uVar6 = extraout_r1;
    uVar8 = extraout_r2;
  }
  DAT_2000157a = (byte)param_1;
  if (param_1 == 2) {
    FUN_0800b9f8(0,uVar6,uVar8);
    FUN_08013a7a(100);
    FUN_0800b990(1,extraout_r1_03,extraout_r2_03);
    uVar6 = extraout_r1_04;
    uVar8 = extraout_r2_04;
LAB_0800bb66:
    FUN_0800ba60(0,uVar6,uVar8);
    FUN_0800bc70();
    uVar7 = (uint)DAT_20001579;
    DAT_20001579 = DAT_20001579 & 0xfe | (byte)DAT_200047d4 >> 7;
    uVar7 = (uVar7 & 2) >> 1;
  }
  else {
    if (param_1 == 4) {
      FUN_0800b990(0,uVar6,uVar8);
      FUN_08013a7a(100);
      FUN_0800b9f8(1,extraout_r1_05,extraout_r2_05);
      uVar6 = extraout_r1_06;
      uVar8 = extraout_r2_06;
      goto LAB_0800bb66;
    }
    if (param_1 != 1) goto LAB_0800baf8;
    FUN_0800ba60(1,uVar6,uVar8);
    FUN_0800b990(0,extraout_r1_00,extraout_r2_00);
    FUN_08013a7a(500);
    FUN_0800b9f8(0,extraout_r1_01,extraout_r2_01);
    FUN_0800a41c();
    FUN_0800bca4();
    uVar7 = DAT_20001579 & 0xfffffffd | (uint)((byte)DAT_200047d4 >> 7) << 1;
    DAT_20001579 = (byte)uVar7;
  }
  DAT_200047d4._0_1_ = (byte)DAT_200047d4 & 0x7f | (byte)((uVar7 & 1) << 7);
LAB_0800baf8:
  FUN_0800b328();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar4 = FUN_08013cfa();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  do {
    iVar5 = FUN_08013cfa();
    lVar2 = (ulonglong)(uint)(iVar5 - iVar4) * 1000 + 99999;
    uVar9 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
  } while ((uint)uVar9 < 100);
  FUN_08010c70();
  FUN_08010f98(0xffffffff);
  FUN_08010fa4();
  return;
}


// ===================================================================
// FUN_0800bbb4 @ 0x0800bbb4  size=6  body=[[0800bbb4, 0800bbb9]]

undefined1 FUN_0800bbb4(void)

{
  return DAT_2000157a;
}


// ===================================================================
// FUN_0800bbc0 @ 0x0800bbc0  size=108  body=[[0800bbc0, 0800bc2b]]

void FUN_0800bbc0(void)

{
  int iVar1;
  
  if (DAT_20004ae4 == '\x05') {
    while (DAT_20004ae4 == '\x05') {
      FUN_0801249e();
      iVar1 = FUN_0801246c();
      if (iVar1 != 0) {
        FUN_08014358(&DAT_20004ae4);
        FUN_08013a7a(30000);
        FUN_08011b84(0xcf);
        FUN_08011d68();
        FUN_08013a7a(1000);
        FUN_08011b84(0xd0);
        FUN_08011d68();
        FUN_08013a7a(1000);
        FUN_08011c48(0xd0);
        FUN_08011d68();
      }
    }
    FUN_0800e4dc();
    FUN_08011d68();
    FUN_08012a98();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800bc30 @ 0x0800bc30  size=58  body=[[0800bc30, 0800bc69]]

void FUN_0800bc30(void)

{
  char cVar1;
  uint *puVar2;
  
  cVar1 = '\0';
  puVar2 = &DAT_20000ca4;
  do {
    FUN_08015338((uint *)(*puVar2 & 0xfffffff0),1 << (*puVar2 & 0xf),1);
    cVar1 = cVar1 + '\x01';
    *(short *)((*puVar2 & 0xfffffff0) + 0x1a) = (short)(1 << (*puVar2 & 0xf));
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\x12');
  return;
}


// ===================================================================
// FUN_0800bc70 @ 0x0800bc70  size=18  body=[[0800bc70, 0800bc81]]

void FUN_0800bc70(void)

{
  DAT_20001594 = 0;
  DAT_20001598 = FUN_08012508();
  return;
}


// ===================================================================
// FUN_0800bc8c @ 0x0800bc8c  size=20  body=[[0800bc8c, 0800bc9f]]

void FUN_0800bc8c(void)

{
  FUN_08015338((uint *)&DAT_40020400,1,0x20);
  FUN_0800bc70();
  return;
}


// ===================================================================
// FUN_0800bca4 @ 0x0800bca4  size=12  body=[[0800bca4, 0800bcaf]]

void FUN_0800bca4(void)

{
  DAT_20001594 = 0;
  DAT_20001598 = 0;
  return;
}


// ===================================================================
// FUN_0800bcb8 @ 0x0800bcb8  size=12  body=[[0800bcb8, 0800bcc3]]

uint FUN_0800bcb8(void)

{
  uint uVar1;
  
  uVar1 = DAT_40020410;
  return ~uVar1 & 1;
}


// ===================================================================
// FUN_0800bcc8 @ 0x0800bcc8  size=242  body=[[0800bcc8, 0800bdb9]]

int FUN_0800bcc8(uint param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  uint *puVar5;
  
  if (((param_1 < 2) || (uVar3 = FUN_0800bcb8(), uVar3 == 0)) &&
     (iVar2 = FUN_0800bf94(param_1), iVar2 != 0)) {
    FUN_08014242(&DAT_20004ae4);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020400,1,2);
    cVar4 = '\0';
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020400,0,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020000,10,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08015410(0x40020000,9,3);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    puVar5 = &DAT_20000cec;
    do {
      if (*puVar5 != 0xffffffff) {
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        FUN_08015410(*puVar5 & 0xfffffff0,*puVar5 & 0xf,3);
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0);
        }
      }
      cVar4 = cVar4 + '\x01';
      puVar5 = puVar5 + 1;
    } while (cVar4 != '\x06');
    FUN_0800bc30();
    FUN_08015338((uint *)&DAT_40020000,0x20,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x1000,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x800,0x40);
    FUN_08015338((uint *)&DAT_40020000,0x100,0x40);
    FUN_0800c068();
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}


// ===================================================================
// FUN_0800bdcc @ 0x0800bdcc  size=418  body=[[0800bdcc, 0800bf6d]]

void FUN_0800bdcc(void)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  uint *puVar6;
  
  if ((DAT_20001594 == '\0') && (uVar4 = FUN_0801258c(DAT_20001598), 1000 < uVar4)) {
    DAT_20001594 = '\x01';
    DAT_20001598 = 0;
  }
  uVar4 = FUN_0800bcb8();
  if ((uVar4 != 0) && (DAT_20004ae4 == '\x01')) {
    FUN_08012a74();
    FUN_08012b50(&DAT_20004ae4);
  }
  cVar1 = FUN_0800bbb4();
  if ((((((cVar1 == '\x02') || (cVar1 = FUN_0800bbb4(), cVar1 == '\x04')) && (DAT_20001594 != '\0'))
       && ((bVar2 = FUN_0800b39c(), !bVar2 && (bVar2 = FUN_0800cdb8(), bVar2)))) &&
      ((bVar3 = FUN_08010cf4(), bVar3 == 0 ||
       ((bVar3 = FUN_08010cf4(), bVar3 != 0 && (cVar1 = FUN_08010ffc(), cVar1 != '\0')))))) &&
     ((iVar5 = FUN_080089d4((int *)&DAT_200047f0,(int *)&DAT_2000157c,0x18), iVar5 == 0 &&
      (iVar5 = FUN_0800bcc8(2), iVar5 != 0)))) {
    FUN_0800bff4();
    FUN_08015338((uint *)&DAT_40020000,0x800,0x51a);
    FUN_08015338((uint *)&DAT_40020000,0x1000,0x51a);
    FUN_08015338((uint *)&DAT_40020000,0x20,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x282);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x282);
    FUN_08013cd0();
    FUN_0800c810();
    if (DAT_20000c74 != (code *)0x0) {
      (*DAT_20000c74)(1);
    }
    FUN_0800c058();
    cVar1 = '\0';
    puVar6 = &DAT_20000cec;
    do {
      if (*puVar6 != 0xffffffff) {
        bVar2 = (bool)isCurrentModePrivileged();
        if (bVar2) {
          setBasePriority(0x30);
        }
        FUN_08015474(*puVar6 & 0xfffffff0,*puVar6 & 0xf);
        bVar2 = (bool)isCurrentModePrivileged();
        if (bVar2) {
          setBasePriority(0);
        }
      }
      cVar1 = cVar1 + '\x01';
      puVar6 = puVar6 + 1;
    } while (cVar1 != '\x06');
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020400,1);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020000,10);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020000,9);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08015474(&DAT_40020400,0);
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
    uVar4 = FUN_0800bcb8();
    if (uVar4 != 0) {
      FUN_08012a74();
      FUN_08012b50(&DAT_20004ae4);
    }
    FUN_080118d8();
    FUN_0801189c(1,extraout_r1,extraout_r2);
    FUN_0800ef1c();
    FUN_0800ee58();
    FUN_0800bc70();
    FUN_0800a7cc();
    FUN_0800bf94(0);
  }
  return;
}


// ===================================================================
// FUN_0800bf94 @ 0x0800bf94  size=84  body=[[0800bf94, 0800bfe7]]

undefined4 FUN_0800bf94(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_1 == 2) {
    if (DAT_2000159c != '\0') {
LAB_0800bfe4:
      uVar1 = 0;
      goto LAB_0800bfd2;
    }
    uVar2 = DAT_e000ed10;
    DAT_e000ed10 = uVar2 | 4;
    uVar2 = DAT_40007000;
    DAT_40007000 = uVar2 | 0xe01;
  }
  else {
    if (param_1 == 3) {
      if (DAT_2000159c != '\0') goto LAB_0800bfe4;
      uVar2 = DAT_e000ed10;
      uVar2 = uVar2 | 4;
    }
    else {
      if (param_1 != 1) goto LAB_0800bfd0;
      if (DAT_2000159c != '\0') goto LAB_0800bfe4;
      uVar2 = DAT_e000ed10;
      uVar2 = uVar2 & 0xfffffffb;
    }
    DAT_e000ed10 = uVar2;
  }
LAB_0800bfd0:
  uVar1 = 1;
LAB_0800bfd2:
  DAT_2000159c = (char)param_1;
  return uVar1;
}


// ===================================================================
// FUN_0800bff4 @ 0x0800bff4  size=82  body=[[0800bff4, 0800c045]]

void FUN_0800bff4(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = DAT_40023808;
  DAT_40023808 = uVar1 & 0xfffffffc;
  do {
    uVar1 = DAT_40023808;
  } while ((uVar1 & 0xc) != 0);
  uVar1 = DAT_40023800;
  DAT_40023800 = uVar1 & 0xfffeffff;
  do {
    iVar2 = DAT_40023800;
  } while (iVar2 << 0xe < 0);
  FUN_08015338((uint *)&DAT_40021c00,1,0x40);
  FUN_08015338((uint *)&DAT_40021c00,2,0x40);
  WaitForInterrupt();
  uVar1 = DAT_e000ed10;
  DAT_e000ed10 = uVar1 & 0xfffffffb;
  DAT_40020018._2_2_ = 0x10;
  FUN_08014b5c();
  DAT_40020018._0_2_ = 0x10;
  return;
}


// ===================================================================
// FUN_0800c058 @ 0x0800c058  size=12  body=[[0800c058, 0800c063]]

void FUN_0800c058(void)

{
  FUN_08015338((uint *)&DAT_40020800,0x4000,0x20);
  return;
}


// ===================================================================
// FUN_0800c068 @ 0x0800c068  size=2  body=[[0800c068, 0800c069]]

void FUN_0800c068(void)

{
  return;
}


// ===================================================================
// FUN_0800c06a @ 0x0800c06a  size=58  body=[[0800ae20, 0800ae51] [0800c06a, 0800c071]]

void FUN_0800c06a(void)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151b,0,0x3d);
  *(undefined1 *)(iVar1 + -3) = 0x25;
  *(undefined1 *)(iVar1 + -2) = 5;
  *(undefined1 *)(iVar1 + -1) = 2;
  FUN_0800aa64((byte *)(iVar1 + -3),3,'\0',0);
  return;
}


// ===================================================================
// FUN_0800c074 @ 0x0800c074  size=104  body=[[0800c074, 0800c0db]]

void FUN_0800c074(int param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  uint uVar7;
  
  if (param_1 == 0) {
    uVar7 = ((uint)(param_2 * 0xce4) >> 10) * 0x14;
    uVar4 = 10;
  }
  else {
    uVar7 = param_2 * 0x423;
    uVar4 = 499;
  }
  sVar6 = (short)(uVar7 / uVar4);
  bVar1 = FUN_08010cf4();
  if (bVar1 != 0) {
    cVar3 = '\0';
    iVar5 = 0;
    pbVar2 = &DAT_2000483d;
    do {
      cVar3 = cVar3 + '\x01';
      iVar5 = iVar5 + (uint)*pbVar2;
      pbVar2 = pbVar2 + 1;
    } while (cVar3 != -0x40);
    pbVar2 = (byte *)0x200048fc;
    cVar3 = '\0';
    do {
      cVar3 = cVar3 + '\x01';
      pbVar2 = pbVar2 + 1;
      iVar5 = iVar5 + (uint)*pbVar2;
    } while (cVar3 != -0x40);
    sVar6 = (short)((uint)(iVar5 * 0x3c) / 0x106f8) + sVar6;
  }
  DAT_20000d04 = sVar6;
  return;
}


// ===================================================================
// FUN_0800c0ec @ 0x0800c0ec  size=84  body=[[0800c0ec, 0800c13f]]

char FUN_0800c0ec(void)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = (uint)DAT_20000d04;
  if (0x1004 < uVar2) {
    return 'd';
  }
  if (uVar2 < 0xdad) {
    if (uVar2 < 0xce5) {
      return '\0';
    }
    cVar1 = (char)((uVar2 * 0x14 - 66000) / 200);
  }
  else {
    cVar1 = (char)((uVar2 * 0x50 - 280000) / 600) + '\x14';
  }
  return cVar1;
}


// ===================================================================
// FUN_0800c144 @ 0x0800c144  size=14  body=[[0800c144, 0800c151]]

bool FUN_0800c144(void)

{
  return 10 < DAT_2000159f;
}


// ===================================================================
// FUN_0800c158 @ 0x0800c158  size=14  body=[[0800c158, 0800c165]]

bool FUN_0800c158(void)

{
  return 0x14 < DAT_2000159e;
}


// ===================================================================
// FUN_0800c16c @ 0x0800c16c  size=52  body=[[0800c16c, 0800c19f]]

void FUN_0800c16c(void)

{
  uint extraout_r1;
  undefined4 extraout_r2;
  byte bVar1;
  bool bVar2;
  
  if (((DAT_20000d04 < 0xdac) && (DAT_2000159f < 0xb)) &&
     (bVar1 = DAT_2000159f + 1, bVar2 = DAT_2000159f == 10, DAT_2000159f = bVar1, bVar2)) {
    FUN_0800b3ec(1);
    FUN_0800b420(1,extraout_r1,extraout_r2);
    DAT_2000159d = 0xf;
  }
  return;
}


// ===================================================================
// FUN_0800c1ac @ 0x0800c1ac  size=44  body=[[0800c1ac, 0800c1d7]]

void FUN_0800c1ac(void)

{
  byte bVar1;
  bool bVar2;
  
  if (DAT_20000d04 < 0xce4) {
    if ((DAT_2000159e < 0x15) &&
       (bVar1 = DAT_2000159e + 1, bVar2 = DAT_2000159e == 0x14, DAT_2000159e = bVar1, bVar2)) {
      FUN_0800a4e8();
      return;
    }
  }
  else if (DAT_2000159e < 0x15) {
    DAT_2000159e = 0;
  }
  return;
}


// ===================================================================
// FUN_0800c1e0 @ 0x0800c1e0  size=178  body=[[0800c1e0, 0800c291]]

void FUN_0800c1e0(undefined4 param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  undefined4 extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  bool bVar8;
  undefined8 uVar9;
  
  uVar6 = FUN_0800c4a8(DAT_200015a0,param_2,param_3);
  bVar2 = FUN_0800bbb4();
  if (((bVar2 & 6) != 0) && ((cVar3 = FUN_0800a77c(), cVar3 == '\x03' || (DAT_2000159d < 0xf)))) {
    uVar7 = FUN_0800bcb8();
    if ((uVar7 != 0) && (3000 < uVar6)) {
      iVar1 = DAT_40020810;
      if (iVar1 << 0x11 < 0) {
        uVar4 = 2;
      }
      else {
        uVar4 = 1;
      }
      FUN_0800ae58(uVar4);
    }
    if ((0xe < DAT_2000159d) || (bVar5 = FUN_0800b36a(), bVar5)) {
      bVar8 = 2999 < uVar6;
      bVar5 = uVar6 == 3000;
    }
    else {
      bVar8 = 199 < uVar6;
      bVar5 = uVar6 == 200;
    }
    if (bVar8 && !bVar5) {
      FUN_0800c16c();
      uVar9 = FUN_0800c1ac();
      uVar6 = FUN_0800c48c((uint)uVar9,(uint)((ulonglong)uVar9 >> 0x20),extraout_r2);
      DAT_200015a0 = uVar6;
      if (86400000 < uVar6) {
        DAT_200015a0 = 0;
        FUN_0800c46c(uVar6,extraout_r1,extraout_r2_00);
      }
      FUN_0800c06a();
      if (DAT_2000159d < 0xf) {
        DAT_2000159d = DAT_2000159d + 1;
      }
    }
  }
  if ((DAT_2000159f != '\0' || DAT_2000159e != '\0') && (uVar6 = FUN_0800bcb8(), uVar6 != 0)) {
    DAT_2000159f = 0;
    DAT_2000159e = 0;
    FUN_0800b3ec(0);
    FUN_0800b420(0,extraout_r1_00,extraout_r2_01);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800c2ac @ 0x0800c2ac  size=54  body=[[0800c2ac, 0800c2e1]]

void FUN_0800c2ac(undefined1 param_1)

{
  FUN_0800b354();
  DAT_200015b4 = 1;
  DAT_200015ad = param_1;
  DAT_200015b0 = FUN_08012508();
  DAT_200015ac = 0;
  DAT_200015a8 = 0x96;
  DAT_200015a4 = 0xff;
  DAT_200015a5 = 0xff;
  DAT_200015a6 = 0xff;
  return;
}


// ===================================================================
// FUN_0800c304 @ 0x0800c304  size=12  body=[[0800c304, 0800c30f]]

bool FUN_0800c304(void)

{
  return DAT_200015b4 != '\0';
}


// ===================================================================
// FUN_0800c314 @ 0x0800c314  size=100  body=[[0800c314, 0800c377]]

void FUN_0800c314(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uStack_24 = param_2;
  uStack_20 = param_3;
  uStack_1c = param_4;
  memcpy(&uStack_24,(undefined4 *)&DAT_08016790,10);
  uVar1 = 0;
  do {
    uVar2 = uVar1 + 1;
    FUN_0800fe78(uVar1,0,0,0);
    uVar1 = uVar2;
  } while (uVar2 != 0x59);
  if ((DAT_200015b4 & 0xfd) == 1) {
    pbVar3 = (byte *)&uStack_24;
    for (bVar4 = 0; (uint)bVar4 < DAT_200015ac / 10; bVar4 = bVar4 + 1) {
      FUN_0800fe78((uint)*pbVar3,DAT_200015a6,DAT_200015a5,DAT_200015a4);
      pbVar3 = pbVar3 + 1;
    }
  }
  return;
}


// ===================================================================
// FUN_0800c390 @ 0x0800c390  size=134  body=[[0800c390, 0800c415]]

void FUN_0800c390(void)

{
  byte bVar1;
  
  if (DAT_200015b4 == '\x02') {
    if (DAT_200015ad < 0x1e) {
      DAT_200015a6 = 0xff;
      DAT_200015a5 = 0;
    }
    else {
      DAT_200015a6 = 0;
      DAT_200015a5 = 0xff;
    }
    DAT_200015a4 = 0;
    DAT_200015a8 = 3000;
    DAT_200015b4 = '\x03';
  }
  else if (DAT_200015b4 == '\x03') {
    DAT_200015b4 = '\0';
    FUN_0800b378();
    if ((DAT_200047cd == '\0') && (bVar1 = FUN_08010cf4(), bVar1 == 0)) {
      thunk_FUN_08010cd4();
    }
    FUN_0800bc70();
  }
  else if (DAT_200015b4 == '\x01') {
    if (DAT_200015ac < DAT_200015ad) {
      DAT_200015ac = DAT_200015ac + 10;
    }
    else {
      if (DAT_200015ac == 0) {
        DAT_200015ac = 10;
      }
      DAT_200015b4 = '\x02';
    }
  }
  DAT_200015b0 = FUN_08012508();
  return;
}


// ===================================================================
// FUN_0800c43c @ 0x0800c43c  size=34  body=[[0800c43c, 0800c45d]]

void FUN_0800c43c(void)

{
  uint uVar1;
  
  if ((DAT_200015b4 != '\0') && (uVar1 = FUN_0801258c(DAT_200015b0), DAT_200015a8 < uVar1)) {
    FUN_0800c390();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800c46c @ 0x0800c46c  size=22  body=[[0800c46c, 0800c481]]

void FUN_0800c46c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  byte local_10 [8];
  undefined4 uStack_8;
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  local_10[5] = 0;
  local_10[6] = 0;
  local_10[7] = 0;
  uStack_8 = param_3;
  thunk_FUN_08016058(0x20004b44,local_10);
  return;
}


// ===================================================================
// FUN_0800c48c @ 0x0800c48c  size=22  body=[[0800c48c, 0800c4a1]]

uint FUN_0800c48c(uint param_1,uint param_2,undefined4 param_3)

{
  uint uStack_10;
  uint local_c;
  undefined4 uStack_8;
  
  uStack_10 = param_1;
  local_c = param_2;
  uStack_8 = param_3;
  thunk_FUN_08016130(0x20004b44,&uStack_10);
  return local_c & 0x7ffffff;
}


// ===================================================================
// FUN_0800c4a8 @ 0x0800c4a8  size=12  body=[[0800c4a8, 0800c4b3]]

int FUN_0800c4a8(uint param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0800c48c(param_1,param_2,param_3);
  return uVar1 - param_1;
}


// ===================================================================
// FUN_0800c4b4 @ 0x0800c4b4  size=144  body=[[0800c4b4, 0800c543]]

undefined4 FUN_0800c4b4(uint param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  
  if (param_1 == 0x7e0e) {
    cVar2 = FUN_0800bbb4();
    if (cVar2 != '\x04') {
      return 1;
    }
    if (*(char *)(param_2 + 5) != '\0') {
      DAT_200015bc = 0x18;
      DAT_200015c0 = FUN_08012508();
      return 1;
    }
  }
  else {
    if (0x7e0e < param_1) {
      if (param_1 != 0x7e0f) {
        return 1;
      }
      bVar1 = FUN_0800bbb4();
      if ((bVar1 & 6) == 0) {
        return 1;
      }
      uVar3 = FUN_0800bcb8();
      if (uVar3 != 0) {
        return 1;
      }
      cVar2 = FUN_0800c0ec();
      FUN_0800c2ac(cVar2);
      return 1;
    }
    if (2 < param_1 - 0x7e0b) {
      return 1;
    }
    cVar2 = FUN_0800bbb4();
    if (cVar2 != '\x02') {
      return 1;
    }
    if (*(char *)(param_2 + 5) != '\0') {
      DAT_200015bc = (char)param_1 - 10;
      DAT_200015c0 = FUN_08012508();
      FUN_0800a3d4((uint)DAT_200015bc,0);
      return 1;
    }
  }
  DAT_200015c0 = 0;
  DAT_200015bc = 0;
  return 1;
}


// ===================================================================
// FUN_0800c54c @ 0x0800c54c  size=54  body=[[0800c54c, 0800c581]]

void FUN_0800c54c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  local_20 = param_1;
  uStack_1c = param_2;
  local_18 = param_3;
  uStack_14 = param_4;
  FUN_0800aebc((undefined4 *)"Keychron V10 Max");
  FUN_08013a7a(300);
  local_20 = 0xb41c2002;
  uStack_1c = 0x50000;
  local_18 = 0x100005a;
  uStack_14 = 0x9a03434;
  FUN_0800ae88(&local_20);
  return;
}


// ===================================================================
// thunk_FUN_0800c54c @ 0x0800c594  size=4  body=[[0800c594, 0800c597]]

void thunk_FUN_0800c54c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_20 = param_1;
  uStack_1c = param_2;
  uStack_18 = param_3;
  uStack_14 = param_4;
  FUN_0800aebc((undefined4 *)"Keychron V10 Max");
  FUN_08013a7a(300);
  uStack_20 = 0xb41c2002;
  uStack_1c = 0x50000;
  uStack_18 = 0x100005a;
  uStack_14 = 0x9a03434;
  FUN_0800ae88(&uStack_20);
  return;
}


// ===================================================================
// FUN_0800c598 @ 0x0800c598  size=40  body=[[0800c598, 0800c5bf]]

void FUN_0800c598(void)

{
  char cVar1;
  uint uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  
  if ((DAT_20000d06 != '\0') && (uVar2 = FUN_08012508(), uVar2 < 1000)) {
    FUN_0800c54c(uVar2,extraout_r1,extraout_r2,extraout_r3);
    cVar1 = FUN_0800bbb4();
    if (cVar1 == '\x02') {
      FUN_0800a298();
    }
    DAT_20000d06 = '\0';
  }
  return;
}


// ===================================================================
// FUN_0800c5c4 @ 0x0800c5c4  size=34  body=[[0800c5c4, 0800c5e5]]

void FUN_0800c5c4(void)

{
  uint uVar1;
  
  if ((DAT_200015c0 != 0) && (uVar1 = FUN_0801258c(DAT_200015c0), 2000 < uVar1)) {
    DAT_200015c0 = 0;
    FUN_0800a268(0,0);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800c5ec @ 0x0800c5ec  size=164  body=[[0800c5ec, 0800c68f]]

void FUN_0800c5ec(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  
  if (DAT_200015b8 == 0) {
    uVar5 = DAT_40020010;
    uVar1 = DAT_40020010;
    if ((uVar5 >> 8 & 2 | (uVar1 & 0x7ff) >> 10) != (uint)DAT_200015b5) {
      uVar2 = DAT_40020010;
      iVar3 = DAT_40020010;
      DAT_200015b5 = (byte)((uint)uVar2 >> 8) & 2 | (byte)((uint)(iVar3 << 0x15) >> 0x1f);
      DAT_200015b8 = FUN_08012508();
    }
  }
  if (((DAT_200015b8 != 0) && (uVar5 = FUN_0801258c(DAT_200015b8), 100 < uVar5)) ||
     (cVar4 = FUN_0800bbb4(), cVar4 == '\0')) {
    uVar5 = DAT_40020010;
    uVar1 = DAT_40020010;
    uVar5 = uVar5 >> 8 & 2 | (uVar1 & 0x7ff) >> 10;
    if (uVar5 == DAT_200015b5) {
      DAT_200015b8 = 0;
      if (uVar5 == 2) {
        uVar5 = 4;
      }
      else if (uVar5 == 3) {
        uVar5 = 1;
      }
      else {
        if (uVar5 != 1) {
          DAT_200015b8 = 0;
          return;
        }
        uVar5 = 2;
      }
      FUN_0800ba9c(uVar5);
      return;
    }
    uVar2 = DAT_40020010;
    iVar3 = DAT_40020010;
    DAT_200015b5 = (byte)((uint)uVar2 >> 8) & 2 | (byte)((uint)(iVar3 << 0x15) >> 0x1f);
    DAT_200015b8 = FUN_08012508();
  }
  return;
}


// ===================================================================
// FUN_0800c69c @ 0x0800c69c  size=4  body=[[0800c69c, 0800c69f]]

undefined4 FUN_0800c69c(void)

{
  return 1;
}


// ===================================================================
// FUN_0800c6a0 @ 0x0800c6a0  size=38  body=[[0800c6a0, 0800c6c5]]

undefined4 FUN_0800c6a0(uint param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = process_record_wireless(param_1,param_2);
  if ((iVar2 == 0) || (bVar1 = process_record_factory_test(param_1,param_2), bVar1 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0800c69c();
  }
  return uVar3;
}


// ===================================================================
// FUN_0800c6c6 @ 0x0800c6c6  size=14  body=[[0800c6c6, 0800c6d3]]

undefined4 FUN_0800c6c6(void)

{
  FUN_0800b4c4();
  FUN_0800ca18();
  return 1;
}


// ===================================================================
// FUN_0800c6d4 @ 0x0800c6d4  size=20  body=[[0800c6d4, 0800c6e7]]

void FUN_0800c6d4(void)

{
  FUN_0800b972();
  FUN_0800ca84();
  FUN_0800c7dc();
  FUN_0800cd88();
  return;
}


// ===================================================================
// process_record_kb @ 0x0800c6e8  size=26  body=[[0800c6e8, 0800c701]]

// VERIFIED shape of keychron_task.c:111 with process_record_keychron inlined: 0x0800D104
// (process_record_user) && 0x0800A788 (wireless) && 0x0800C928 (factory test) && 0x0800C69C

undefined4 process_record_kb(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = process_record_user(param_1,param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_0800c6a0(param_1,param_2);
    return uVar2;
  }
  return 0;
}


// ===================================================================
// FUN_0800c702 @ 0x0800c702  size=18  body=[[0800c702, 0800c713]]

int FUN_0800c702(void)

{
  int iVar1;
  
  iVar1 = FUN_0801017a();
  if (iVar1 != 0) {
    FUN_0800c6c6();
  }
  return iVar1;
}


// ===================================================================
// thunk_FUN_0800c6d4 @ 0x0800c714  size=4  body=[[0800c714, 0800c717]]

void thunk_FUN_0800c6d4(void)

{
  FUN_0800b972();
  FUN_0800ca84();
  FUN_0800c7dc();
  FUN_0800cd88();
  return;
}


// ===================================================================
// FUN_0800c718 @ 0x0800c718  size=60  body=[[0800c718, 0800c71d] [08011844, 08011879]]

void FUN_0800c718(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_40020410;
  uVar2 = DAT_40020410;
  uVar2 = uVar2 >> 0xd & 2 | (uVar1 & 0xffff) >> 0xf;
  uVar1 = (uint)DAT_20001ff7;
  DAT_20001ff7 = (byte)uVar2 | (byte)(uVar1 << 2);
  DAT_20001ff6 = (&DAT_080170b4)[uVar2 | uVar1 << 2 & 0xf] + DAT_20001ff6;
  DAT_20001ff8 = 1;
  return;
}


// ===================================================================
// process_record_keychron_common @ 0x0800c720  size=158  body=[[0800c720, 0800c72d] [0800c73a, 0800c7c9]]

// VERIFIED: switch 0x7E00-0x7E03 (KC_LOPTN..KC_RCMMD via mac_keycode table @0x0800EA3C) 0x7E04
// KC_MCTRL->0xC1 0x7E05 KC_LNPAD->0xC2 0x7E06-0x7E09 KC_TASK..KC_CTANA via key_comb_list
// @0x0801682C stride 4 (keychron_common.c:87)

undefined4 process_record_keychron_common(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int extraout_r1;
  char cVar4;
  byte bVar5;
  
  switch(param_1) {
  case 0x7e00:
  case 0x7e01:
  case 0x7e02:
  case 0x7e03:
    uVar2 = (uint)*(byte *)(param_1 + 0x800ea3c);
    cVar4 = *(char *)(param_2 + 5);
    break;
  case 0x7e04:
    cVar4 = *(char *)(param_2 + 5);
    uVar2 = 0xc1;
    break;
  case 0x7e05:
    cVar4 = *(char *)(param_2 + 5);
    uVar2 = 0xc2;
    break;
  case 0x7e06:
  case 0x7e07:
  case 0x7e08:
  case 0x7e09:
    iVar3 = param_1 + -0x7e06;
    if (*(char *)(param_2 + 5) == '\0') {
      bVar1 = (&key_comb_list)[iVar3 * 4];
      for (bVar5 = 0; (uint)bVar5 < (uint)bVar1; bVar5 = bVar5 + 1) {
        unregister_code((uint)(byte)(&DAT_0801682d)[(uint)bVar5 + iVar3 * 4],param_2);
        param_2 = extraout_r1;
      }
      return 0;
    }
    bVar1 = (&key_comb_list)[iVar3 * 4];
    for (bVar5 = 0; (uint)bVar5 < (uint)bVar1; bVar5 = bVar5 + 1) {
      register_code((uint)(byte)(&DAT_0801682d)[(uint)bVar5 + iVar3 * 4]);
    }
    return 0;
  case 0x7e0a:
    if (*(char *)(param_2 + 5) == '\0') {
      return 0;
    }
    if (DAT_200015c8 == '\0') {
      DAT_200015c8 = '\x01';
      register_code(0xe3);
      register_code(0x2c);
    }
    DAT_200015c4 = FUN_08012508();
    return 0;
  default:
    return 1;
  }
  if (cVar4 == '\0') {
    unregister_code(uVar2,param_2);
  }
  else {
    register_code(uVar2);
  }
  return 0;
}


// ===================================================================
// FUN_0800c7dc @ 0x0800c7dc  size=42  body=[[0800c7dc, 0800c805]]

void FUN_0800c7dc(void)

{
  uint uVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  
  if ((DAT_200015c8 != '\0') && (uVar1 = FUN_0801258c(DAT_200015c4), 500 < uVar1)) {
    unregister_code(0xe3,extraout_r1);
    unregister_code(0x2c,extraout_r1_00);
    DAT_200015c8 = '\0';
    DAT_200015c4 = 0;
  }
  return;
}


// ===================================================================
// FUN_0800c810 @ 0x0800c810  size=84  body=[[0800c810, 0800c863]]

void FUN_0800c810(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015410(0x40020400,0xf,3);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015410(0x40020400,0xe,3);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080140dc(0x4002040f,0x800c719,0);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080140dc(0x4002040e,0x800c719,0);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// kc_raw_hid_rx @ 0x0800c874  size=104  body=[[0800c874, 0800c885] [0800c896, 0800c8a1] [0800c8ae, 0800c8db] [0800c8e2, 0800c8fd]]

// WARNING: Possible PIC construction at 0x0800c8fc: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8f8: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8f2: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8ec: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8da: Changing call to branch
// WARNING: Removing unreachable block (ram,0x0800c8ec)
// WARNING: Removing unreachable block (ram,0x0800c8f2)
// WARNING: Removing unreachable block (ram,0x0800c8f8)
// WARNING: Removing unreachable block (ram,0x0800c8fc)
// WARNING: Removing unreachable block (ram,0x0800c8da)
// VERIFIED vs keychron_raw_hid.c kc_raw_hid_rx: ldrb data[0]; subs #0xA0; cmp #0xB; tbb @0x0800C882
// (12 cases 0xA0..0xAB); case 0xA1 copies build-date string 0x080167AC (get_firmware_version); 0xAA
// -> 0x0800B290 (lkbt51_dfu_rx); 0xAB -> 0x0800CB90 (factory_test_rx)

undefined4 kc_raw_hid_rx(byte *param_1,int param_2)

{
  int iVar1;
  
  switch(*param_1) {
  case 0xa0:
    param_1[1] = 2;
    break;
  case 0xa1:
    param_1[1] = 0x76;
    itoa(1,param_1 + 2,0x10);
    param_1[3] = 0x2e;
    itoa(0,param_1 + 4,0x10);
    param_1[5] = 0x2e;
    itoa(0,param_1 + 6,0x10);
    param_1[7] = 0x20;
    memcpy((undefined4 *)(param_1 + 8),(undefined4 *)"2024-07-09-13:57:36",0x14);
    break;
  case 0xa2:
    param_1[2] = 7;
    break;
  case 0xa3:
    iVar1 = get_highest_layer((uint)default_layer_state);
    param_1[1] = (byte)iVar1;
    break;
  default:
    return 0;
  case 0xaa:
    lkbt51_dfu_rx((char *)param_1);
    return 1;
  case 0xab:
    factory_test_rx(param_1);
    return 1;
  }
  raw_hid_send((undefined4 *)param_1,param_2);
  return 1;
}


// ===================================================================
// FUN_0800c908 @ 0x0800c908  size=14  body=[[0800c908, 0800c915]]

byte * FUN_0800c908(byte *param_1,int param_2)

{
  byte *pbVar1;
  
  if (*param_1 - 0xaa < 2) {
    pbVar1 = (byte *)kc_raw_hid_rx(param_1,param_2);
    return pbVar1;
  }
  return param_1;
}


// ===================================================================
// FUN_0800c918 @ 0x0800c918  size=12  body=[[0800c918, 0800c923]]

void FUN_0800c918(void)

{
  DAT_200015d4 = FUN_08012508();
  return;
}


// ===================================================================
// process_record_factory_test @ 0x0800c928  size=226  body=[[0800c928, 0800ca09]]

// VERIFIED vs factory_test.c:171: keycodes 0x0D KC_J 0x1D KC_Z 0x4A KC_HOME (BL_TRIG_KEY) 0x4D
// KC_END 0x4F KC_RIGHT (BL_CYCLE_KEY) 0x5221/0x5223 MO(1)/MO(3) FN keys; state byte @0x200015D1;
// timer start 0x0800C918 when state==7 or 0x19

byte process_record_factory_test(uint param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  
  if (param_1 != 0x4d) {
    if (0x4d < param_1) {
      if ((param_1 & 0xfffffffd) == 0x5221) {
        pbVar1 = &factory_reset_state;
        if (*(char *)(param_2 + 5) == '\0') {
          factory_reset_state = factory_reset_state & 0xfe;
          DAT_200015d4 = 0;
          return 1;
        }
        bVar2 = factory_reset_state | 1;
LAB_0800c976:
        *pbVar1 = bVar2;
        return 1;
      }
      if (param_1 != 0x4f) {
        return 1;
      }
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xf7;
        DAT_200015d4 = 0;
        return 1;
      }
      pbVar1 = (byte *)&DAT_200015d0;
      if (DAT_200015d0 != '\0') {
        bVar2 = DAT_200015d0 + 1;
        if (4 < bVar2) {
          bVar2 = 1;
        }
        goto LAB_0800c976;
      }
      factory_reset_state = factory_reset_state | 8;
      goto LAB_0800c9ce;
    }
    if (param_1 == 0x1d) {
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xfb;
        DAT_200015d4 = 0;
        return 1;
      }
      factory_reset_state = factory_reset_state | 4;
LAB_0800c992:
      if (factory_reset_state == 7) {
        FUN_0800c918();
      }
      return ~factory_reset_state & 1;
    }
    if (param_1 != 0x4a) {
      if (param_1 != 0xd) {
        return 1;
      }
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xfd;
        DAT_200015d4 = 0;
        return 1;
      }
      factory_reset_state = factory_reset_state | 2;
      goto LAB_0800c992;
    }
  }
  if (*(char *)(param_2 + 5) == '\0') {
    factory_reset_state = factory_reset_state & 0xef;
    DAT_200015d4 = 0;
    return 1;
  }
  if (DAT_200015d0 != '\0') {
    DAT_200015d0 = 0;
    return 1;
  }
  factory_reset_state = factory_reset_state | 0x10;
LAB_0800c9ce:
  if (factory_reset_state == 0x19) {
    FUN_0800c918();
  }
  return 1;
}


// ===================================================================
// FUN_0800ca18 @ 0x0800ca18  size=80  body=[[0800ca18, 0800ca45] [0800ca4a, 0800ca6b]]

undefined4 FUN_0800ca18(void)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  
  if (DAT_200015ca != 0) {
    cVar3 = '\0';
    DAT_200015d0 = '\0';
    uVar2 = 0;
    cVar1 = (DAT_200015ca & 1) - 1;
    goto LAB_0800ca30;
  }
  if (DAT_200015d0 == '\0') {
    return 1;
  }
  switch(DAT_200015d0) {
  case '\x01':
    cVar3 = -1;
    goto LAB_0800ca4e;
  case '\x02':
    cVar3 = '\0';
    uVar2 = 0;
    cVar1 = -1;
    break;
  case '\x03':
    cVar3 = '\0';
LAB_0800ca4e:
    uVar2 = 0xff;
    cVar1 = cVar3;
    break;
  case '\x04':
    uVar2 = 0;
    cVar3 = -1;
    cVar1 = '\0';
    break;
  default:
    goto switchD_0800ca42_default;
  }
LAB_0800ca30:
  thunk_FUN_08011378(cVar1,uVar2,cVar3);
switchD_0800ca42_default:
  return 0;
}


// ===================================================================
// FUN_0800ca74 @ 0x0800ca74  size=12  body=[[0800ca74, 0800ca7f]]

bool FUN_0800ca74(void)

{
  return DAT_200015cc != 0;
}


// ===================================================================
// FUN_0800ca84 @ 0x0800ca84  size=162  body=[[0800ca84, 0800cb25]]

undefined4 FUN_0800ca84(void)

{
  byte bVar1;
  uint uVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined8 uVar3;
  undefined6 uVar4;
  
  if ((DAT_200015d4 != 0) && (uVar2 = FUN_0801258c(DAT_200015d4), 3000 < uVar2)) {
    DAT_200015d4 = 0;
    if (factory_reset_state == '\a') {
      DAT_200015cc = FUN_08012508();
      DAT_200015ca = DAT_200015ca + 1;
      uVar3 = FUN_0800db44();
      uVar4 = thunk_FUN_0800e634((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),extraout_r2);
      DAT_200047d4 = FUN_0800e600((int)uVar4,(ushort)((uint6)uVar4 >> 0x20),extraout_r2_00);
      thunk_FUN_0800dbd0();
      bVar1 = FUN_08010cf4();
      if (bVar1 == 0) {
        FUN_08010ef0();
      }
      FUN_08010c70();
      FUN_0800aef8(0);
    }
    else if (factory_reset_state == '\x19') {
      bVar1 = FUN_08010cf4();
      if (bVar1 == 0) {
        FUN_08010ef0();
      }
      DAT_200015d0 = 1;
    }
    factory_reset_state = '\0';
  }
  if ((DAT_200015cc != 0) && (uVar2 = FUN_0801258c(DAT_200015cc), 0xfa < uVar2)) {
    if (DAT_200015ca < 7) {
      DAT_200015ca = DAT_200015ca + 1;
      DAT_200015cc = FUN_08012508();
    }
    else {
      DAT_200015ca = 0;
      DAT_200015cc = 0;
    }
  }
  return 1;
}


// ===================================================================
// FUN_0800cb44 @ 0x0800cb44  size=74  body=[[0800cb44, 0800cb8d]]

void FUN_0800cb44(undefined4 *param_1,uint param_2)

{
  byte *pbVar1;
  char cVar2;
  byte local_30;
  byte local_2f [29];
  short local_12;
  
  pbVar1 = &local_30;
  FUN_08008798(&local_30,0,0x20);
  local_30 = 0xab;
  memcpy((undefined4 *)local_2f,param_1,param_2);
  cVar2 = '\x01';
  local_12 = 0;
  do {
    pbVar1 = pbVar1 + 1;
    cVar2 = cVar2 + '\x01';
    local_12 = local_12 + (ushort)*pbVar1;
  } while (cVar2 != '\x1d');
  raw_hid_send((undefined4 *)&local_30,0x20);
  return;
}


// ===================================================================
// factory_test_rx @ 0x0800cb90  size=392  body=[[0800af2c, 0800af57] [0800af5c, 0800af87] [0800cb90, 0800cbc9] [0800cbd4, 0800ccc9]]

// INFERRED: 0xAB case target of kc_raw_hid_rx; 392 bytes; references build-date string 0x080167AC

void factory_test_rx(byte *param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  undefined2 local_28;
  byte local_26 [3];
  undefined1 local_23;
  undefined1 auStack_22 [4];
  undefined4 auStack_1e [5];
  
  if (*param_1 != 0xab) {
    return;
  }
  uVar6 = 0;
  pbVar5 = param_1;
  do {
    pbVar5 = pbVar5 + 1;
    uVar7 = uVar6 + *pbVar5;
    uVar6 = uVar7 & 0xffff;
  } while (pbVar5 != param_1 + 0x1c);
  if ((uint)param_1[0x1e] != (uVar7 & 0xff)) {
    return;
  }
  if ((uint)param_1[0x1f] != uVar6 >> 8) {
    return;
  }
  switch(param_1[1]) {
  case 1:
    DAT_200015d0 = param_1[2];
    DAT_200015d4 = 0;
    break;
  case 2:
    DAT_200015c9 = param_1[2] != 0;
    break;
  case 4:
    if (param_1[2] == 0xa1) {
      bVar1 = param_1[3];
      iVar4 = FUN_08008798(&DAT_2000151a,0,0x3e);
      *(undefined1 *)(iVar4 + -2) = 0x72;
      *(bool *)(iVar4 + -1) = bVar1 != 0;
      FUN_0800aa64((byte *)(iVar4 + -2),2,'\0',0);
      return;
    }
    if (param_1[2] == 0xa2) {
      if (param_1[3] == 0) {
        DAT_40020018._2_2_ = 0x10;
      }
      else {
        DAT_40020018._0_2_ = 0x10;
      }
    }
    break;
  case 5:
    local_28 = CONCAT11(local_28._1_1_,5);
    uVar3 = FUN_0800bbb4();
    local_28 = CONCAT11(uVar3,(undefined1)local_28);
    uVar2 = DAT_40020410;
    local_26[0] = (byte)uVar2 & 1;
    uVar6 = 3;
    goto LAB_0800cc3a;
  case 7:
    bVar1 = param_1[2];
    if (bVar1 < 0x4f) {
      iVar4 = FUN_08008798(&DAT_2000151a,0,0x3e);
      *(undefined1 *)(iVar4 + -2) = 0x73;
      *(byte *)(iVar4 + -1) = bVar1;
      FUN_0800aa64((byte *)(iVar4 + -2),3,'\0',0);
      return;
    }
    break;
  case 8:
    local_28 = 0x7608;
    itoa(1,local_26,0x10);
    local_26[1] = 0x2e;
    itoa(0,local_26 + 2,0x10);
    local_23 = 0x2e;
    itoa(0,auStack_22,0x10);
    auStack_22[1] = 0x20;
    memcpy((undefined4 *)(auStack_22 + 2),(undefined4 *)"2024-07-09-13:57:36",0x14);
    uVar6 = 0x1c;
    goto LAB_0800cc3a;
  case 9:
    local_28 = 0xc09;
    memcpy((undefined4 *)local_26,(undefined4 *)0x1fff7a10,4);
    memcpy((undefined4 *)auStack_22,(undefined4 *)0x1fff7a20,4);
    memcpy(auStack_1e,(undefined4 *)0x1fff7a30,4);
    uVar6 = 0xe;
LAB_0800cc3a:
    FUN_0800cb44((undefined4 *)&local_28,uVar6);
  }
  return;
}


// ===================================================================
// FUN_0800ccf0 @ 0x0800ccf0  size=36  body=[[0800ccf0, 0800cd13]]

undefined4 FUN_0800ccf0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 local_c;
  undefined2 local_a;
  undefined4 uStack_8;
  
  if (DAT_200015c9 != '\0') {
    local_a._1_1_ = (undefined1)((uint)param_2 >> 0x18);
    _local_c = CONCAT22(CONCAT11(local_a._1_1_,(char)param_2),0x102);
    uStack_8 = param_3;
    FUN_0800cb44((undefined4 *)&local_c,3);
  }
  return 1;
}


// ===================================================================
// FUN_0800cd18 @ 0x0800cd18  size=32  body=[[0800cd18, 0800cd37]]

undefined4 FUN_0800cd18(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_r2;
  
  if (param_1 == 0) {
    thunk_FUN_0800dbd0();
    param_3 = extraout_r2;
  }
  FUN_0800ccf0(param_1,param_2,param_3);
  return 1;
}


// ===================================================================
// FUN_0800cd38 @ 0x0800cd38  size=66  body=[[0800cd38, 0800cd79]]

void FUN_0800cd38(void)

{
  FUN_08015338((uint *)&DAT_40020000,0x400,0);
  FUN_08015338((uint *)&DAT_40020000,0x200,0);
  DAT_40020418 = 0x1000;
  FUN_0800a98c(0);
  FUN_0800a240();
  DAT_200015d8 = FUN_08012508();
  FUN_0800c810();
  FUN_0800cf60();
  return;
}


// ===================================================================
// FUN_0800cd88 @ 0x0800cd88  size=38  body=[[0800cd88, 0800cdad]]

undefined4 FUN_0800cd88(void)

{
  uint uVar1;
  
  if (DAT_200015d8 != 0) {
    uVar1 = FUN_0801258c(DAT_200015d8);
    if (uVar1 < 0xbb9) {
      DAT_40020418 = 0x1000;
    }
    else {
      DAT_200015d8 = 0;
      DAT_4002041a = 0x1000;
    }
  }
  return 1;
}


// ===================================================================
// FUN_0800cdb8 @ 0x0800cdb8  size=28  body=[[0800cdb8, 0800cdd3]]

bool FUN_0800cdb8(void)

{
  bool bVar1;
  
  if (DAT_200015d8 == 0) {
    bVar1 = FUN_0800ca74();
    bVar1 = !bVar1;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ===================================================================
// FUN_0800cdd8 @ 0x0800cdd8  size=2  body=[[0800cdd8, 0800cdd9]]

void FUN_0800cdd8(void)

{
  return;
}


// ===================================================================
// FUN_0800cdda @ 0x0800cdda  size=26  body=[[0800cdda, 0800cdf3]]

void FUN_0800cdda(void)

{
  FUN_0800dc64();
  FUN_0800e504('\x01',3);
  FUN_0800e548(1);
  return;
}


// ===================================================================
// FUN_0800cdf4 @ 0x0800cdf4  size=10  body=[[0800cdf4, 0800cdfd]]

void FUN_0800cdf4(void)

{
  thunk_FUN_08011378(0xff,0,0xff);
  return;
}


// ===================================================================
// FUN_0800cdfe @ 0x0800cdfe  size=354  body=[[0800cdfe, 0800cf5f]]

void FUN_0800cdfe(void)

{
  bool bVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  undefined4 extraout_r1_10;
  undefined4 extraout_r1_11;
  undefined4 extraout_r1_12;
  undefined4 extraout_r1_13;
  undefined4 extraout_r1_14;
  undefined4 extraout_r1_15;
  undefined4 extraout_r1_16;
  undefined4 extraout_r1_17;
  undefined4 extraout_r1_18;
  undefined4 extraout_r1_19;
  undefined4 extraout_r1_20;
  undefined4 extraout_r1_21;
  
  thunk_FUN_08011378(0,0,0);
  bVar1 = FUN_08011a3c(9);
  if (bVar1) {
    register_code(0xe3);
    register_code(0x13);
    unregister_code(0xe3,extraout_r1);
    unregister_code(0x13,extraout_r1_00);
    register_code(0xe3);
    register_code(0xe);
    unregister_code(0xe3,extraout_r1_01);
    unregister_code(0xe,extraout_r1_02);
  }
  bVar1 = FUN_08011a50(4,0x14);
  if (bVar1) {
    register_code(0xe0);
    register_code(4);
    unregister_code(0xe0,extraout_r1_03);
    unregister_code(4,extraout_r1_04);
    register_code(0x1d);
    unregister_code(0x1d,extraout_r1_05);
    register_code(0x14);
    unregister_code(0x14,extraout_r1_06);
    register_code(0x28);
    unregister_code(0x28,extraout_r1_07);
  }
  bVar1 = FUN_08011a3c(0x1c);
  if (bVar1) {
    register_code(0xe0);
    register_code(0x1b);
    unregister_code(0xe0,extraout_r1_08);
    unregister_code(0x1b,extraout_r1_09);
    register_code(0x1c);
    unregister_code(0x1c,extraout_r1_10);
    register_code(0x28);
    unregister_code(0x28,extraout_r1_11);
  }
  bVar1 = FUN_08011a50(0xe0,0xc);
  if (bVar1) {
    register_code(0xe0);
    register_code(0xe2);
    register_code(0xc);
    unregister_code(0xe0,extraout_r1_12);
    unregister_code(0xe2,extraout_r1_13);
    unregister_code(0xc,extraout_r1_14);
  }
  bVar1 = FUN_08011a3c(0xd);
  if (bVar1) {
    register_code(0xe3);
    register_code(0x13);
    unregister_code(0xe3,extraout_r1_15);
    unregister_code(0x13,extraout_r1_16);
  }
  bVar1 = FUN_08011a3c(9);
  if (bVar1) {
    register_code(0xe3);
    register_code(0x34);
    unregister_code(0xe3,extraout_r1_17);
    unregister_code(0x34,extraout_r1_18);
  }
  bVar1 = FUN_08011a3c(0x4c);
  if (bVar1) {
    register_code(0xe3);
    register_code(0x52);
    register_code(0x50);
    unregister_code(0xe3,extraout_r1_19);
    unregister_code(0x52,extraout_r1_20);
    unregister_code(0x50,extraout_r1_21);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800cf60 @ 0x0800cf60  size=18  body=[[0800cf60, 0800cf71]]

void FUN_0800cf60(void)

{
  thunk_FUN_0800dbd0();
  FUN_08010d40(0x10);
  return;
}


// ===================================================================
// FUN_0800cf74 @ 0x0800cf74  size=130  body=[[0800cf74, 0800cfa5] [0800cfac, 0800cffb]]

undefined4 FUN_0800cf74(uint param_1,uint param_2)

{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  do {
    if (param_2 <= (param_1 & 0xff)) {
      return 0;
    }
    iVar1 = get_highest_layer((uint)(layer_state | default_layer_state));
    switch(iVar1) {
    case 1:
      uVar3 = 0;
      uVar4 = 0xff;
      break;
    case 2:
      uVar3 = 0xff;
      uVar4 = 0;
      break;
    case 3:
      uVar4 = 0x80;
      goto LAB_0800cfd2;
    case 4:
      uVar4 = 0x80;
      uVar3 = uVar4;
      break;
    case 5:
      uVar4 = 0;
LAB_0800cfd2:
      uVar3 = 0;
      uVar2 = 0xff;
      goto LAB_0800cfb2;
    default:
      goto switchD_0800cfa2_default;
    }
    uVar2 = 0;
LAB_0800cfb2:
    FUN_0800fe78(param_1,uVar2,uVar4,uVar3);
switchD_0800cfa2_default:
    if (DAT_200015dd == '\0') {
      if (DAT_200015de != '\0' || user_capslock_flag != '\0') {
        uVar4 = 0xff;
        goto LAB_0800cfc4;
      }
    }
    else {
      uVar4 = 0;
LAB_0800cfc4:
      FUN_0800fe78(param_1,0xff,0xff,uVar4);
    }
    param_1 = param_1 + 1;
  } while( true );
}


// ===================================================================
// FUN_0800d010 @ 0x0800d010  size=110  body=[[0800d010, 0800d07d]]

void FUN_0800d010(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x22;
  if ((uVar1 == 0) && (DAT_200015de != '\0')) {
    thunk_FUN_08011378(0,0,0);
    DAT_200015de = '\0';
  }
  else {
    if ((param_1 & 0xffffff88) == 0) {
      if (DAT_200015dd != '\0') {
        thunk_FUN_08011378(0,0,0);
        DAT_200015dd = '\0';
      }
      if (uVar1 == 0) {
        return;
      }
    }
    else if (uVar1 == 0) goto LAB_0800d030;
    if (DAT_200015de == '\0') {
      thunk_FUN_08011378(0xff,0xff,0xff);
      DAT_200015de = '\x01';
    }
  }
  if ((param_1 & 0xffffff88) == 0) {
    return;
  }
LAB_0800d030:
  if (DAT_200015dd == '\0') {
    thunk_FUN_08011378(0xff,0xff,0);
    DAT_200015dd = '\x01';
  }
  return;
}


// ===================================================================
// thunk_FUN_0800d010 @ 0x0800d088  size=4  body=[[0800d088, 0800d08b]]

void thunk_FUN_0800d010(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x22;
  if ((uVar1 == 0) && (DAT_200015de != '\0')) {
    thunk_FUN_08011378(0,0,0);
    DAT_200015de = '\0';
  }
  else {
    if ((param_1 & 0xffffff88) == 0) {
      if (DAT_200015dd != '\0') {
        thunk_FUN_08011378(0,0,0);
        DAT_200015dd = '\0';
      }
      if (uVar1 == 0) {
        return;
      }
    }
    else if (uVar1 == 0) goto LAB_0800d030;
    if (DAT_200015de == '\0') {
      thunk_FUN_08011378(0xff,0xff,0xff);
      DAT_200015de = '\x01';
    }
  }
  if ((param_1 & 0xffffff88) == 0) {
    return;
  }
LAB_0800d030:
  if (DAT_200015dd == '\0') {
    thunk_FUN_08011378(0xff,0xff,0);
    DAT_200015dd = '\x01';
  }
  return;
}


// ===================================================================
// thunk_FUN_0800d010 @ 0x0800d08c  size=4  body=[[0800d08c, 0800d08f]]

void thunk_FUN_0800d010(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x22;
  if ((uVar1 == 0) && (DAT_200015de != '\0')) {
    thunk_FUN_08011378(0,0,0);
    DAT_200015de = '\0';
  }
  else {
    if ((param_1 & 0xffffff88) == 0) {
      if (DAT_200015dd != '\0') {
        thunk_FUN_08011378(0,0,0);
        DAT_200015dd = '\0';
      }
      if (uVar1 == 0) {
        return;
      }
    }
    else if (uVar1 == 0) goto LAB_0800d030;
    if (DAT_200015de == '\0') {
      thunk_FUN_08011378(0xff,0xff,0xff);
      DAT_200015de = '\x01';
    }
  }
  if ((param_1 & 0xffffff88) == 0) {
    return;
  }
LAB_0800d030:
  if (DAT_200015dd == '\0') {
    thunk_FUN_08011378(0xff,0xff,0);
    DAT_200015dd = '\x01';
  }
  return;
}


// ===================================================================
// FUN_0800d090 @ 0x0800d090  size=32  body=[[0800d090, 0800d0af]]

ushort * FUN_0800d090(uint param_1)

{
  ushort *puVar1;
  
  if (DAT_200015e0 == (ushort *)0x0) {
    puVar1 = (ushort *)&Reset;
  }
  else {
    if (*DAT_200015e0 == param_1) {
      return DAT_200015e0;
    }
    puVar1 = DAT_200015e0 + 2;
  }
  if (DAT_200015e0[2] != param_1) {
    puVar1 = (ushort *)0x0;
  }
  return puVar1;
}


// ===================================================================
// FUN_0800d0b4 @ 0x0800d0b4  size=66  body=[[0800d0b4, 0800d0f5]]

undefined4 FUN_0800d0b4(uint param_1)

{
  char cVar1;
  byte bVar2;
  ushort *puVar3;
  undefined4 uVar4;
  
  puVar3 = FUN_0800d090(param_1);
  if (puVar3 == (ushort *)0x0) {
    uVar4 = 1;
  }
  else {
    cVar1 = FUN_0800e310();
    if ((cVar1 != '\0') && (*puVar3 != param_1)) {
      FUN_0800e424();
      FUN_0800e3b0();
      bVar2 = FUN_0800e380();
      FUN_0800d684((uint)bVar2);
      DAT_200015e0 = 0;
      DAT_200015e4 = 0;
      DAT_200015de = 0;
      DAT_200015dd = 0;
    }
    uVar4 = 0;
  }
  return uVar4;
}


// ===================================================================
// process_record_user @ 0x0800d104  size=180  body=[[0800d104, 0800d1b7]]

// CUSTOM KEYMAP CODE. INFERRED name: first callee of process_record_kb and begins with
// process_record_keychron_common (0x0800C720) exactly like the default keymap template. VERIFIED
// body: flag@0x200015E8 cleared unless keycode==0x5700 TD(0); flag@0x200015E9 cleared when
// 0x0800DC3C(1)==0; only when pressed: 0x39 KC_CAPS -> flag@0x200015DC from 0x08012148() bit1;
// (kc-0x52A2)<0x17 with mask 0x410041 = OSM(MOD_LSFT) 0x52A2 / OSM(MOD_LGUI) 0x52A8 / OSM(MOD_RSFT)
// 0x52B2 / OSM(MOD_RGUI) 0x52B8 -> custom one-shot handling via
// 0x0800D090/0x0800E310/0x0800E424/0x0800E3B0/0x0800E380/0x0800D684; 0x7E40 QK_USER_0 ->
// register/unregister_code 0x37 KC_DOT then 0x38 KC_SLASH ('./'); 0x7E41 QK_USER_1 -> DOT then
// falls into USER_0 path ('../'); returns false after handling

int process_record_user(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  
  iVar1 = process_record_keychron_common(param_1,param_2);
  if (iVar1 != 0) {
    if ((user_td0_flag != '\0') && (param_1 != 0x5700)) {
      user_td0_flag = '\0';
    }
    if ((DAT_200015e9 != '\0') && (uVar2 = FUN_0800dc3c(1), uVar2 == 0)) {
      DAT_200015e9 = '\0';
    }
    if (*(char *)(param_2 + 5) == '\0') {
      return iVar1;
    }
    if (param_1 == 0x39) {
      iVar3 = FUN_08012148();
      if (-1 < iVar3 << 0x1e) {
        user_capslock_flag = 1;
        return iVar1;
      }
      iVar3 = FUN_08012148();
      if (-1 < iVar3 << 0x1e) {
        return iVar1;
      }
      user_capslock_flag = 0;
      return iVar1;
    }
    if ((param_1 - 0x52a2 & 0xffff) < 0x17) {
      if (-1 < (int)((0x410041U >> (param_1 - 0x52a2 & 0xff)) << 0x1f)) {
        return iVar1;
      }
      iVar1 = FUN_0800d0b4(param_1);
      return iVar1;
    }
    if (param_1 != 0x7e40) {
      if (param_1 != 0x7e41) {
        return iVar1;
      }
      register_code(0x37);
      unregister_code(0x37,extraout_r1_01);
    }
    register_code(0x37);
    unregister_code(0x37,extraout_r1);
    register_code(0x38);
    unregister_code(0x38,extraout_r1_00);
  }
  return 0;
}


// ===================================================================
// FUN_0800d1c4 @ 0x0800d1c4  size=38  body=[[0800d1c4, 0800d1e9]]

undefined4 FUN_0800d1c4(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 2) != '\x01') {
    if (*(char *)(param_1 + 2) == '\x02') {
      uVar1 = 4;
    }
    else {
      uVar1 = 1;
    }
    return uVar1;
  }
  if (-1 < (int)((uint)*(byte *)(param_1 + 5) << 0x1f)) {
    return 2;
  }
  if ((*(byte *)(param_1 + 5) & 4) == 0) {
    uVar1 = 3;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


// ===================================================================
// FUN_0800d1ec @ 0x0800d1ec  size=104  body=[[0800d1ec, 0800d253]]

void FUN_0800d1ec(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0800d1c4(param_1);
  if (iVar1 == 3) {
    FUN_0800dc34();
LAB_0800d244:
    FUN_0800dc58();
    return;
  }
  if (iVar1 == 4) {
    FUN_0800dc34();
    goto LAB_0800d244;
  }
  if (iVar1 != 2) {
    return;
  }
  uVar2 = FUN_0800dc3c(4);
  if (uVar2 == 0) {
    if (user_td0_flag != '\0') {
      FUN_0800dc34();
      FUN_0800dc58();
      user_td0_flag = 0;
      return;
    }
    uVar2 = FUN_0800dc3c(1);
    if (uVar2 == 0) {
      user_td0_flag = '\x01';
      goto LAB_0800d212;
    }
  }
  else {
    DAT_200015e9 = 1;
  }
  FUN_0800dc34();
LAB_0800d212:
  FUN_0800cdda();
  return;
}


// ===================================================================
// FUN_0800d25c @ 0x0800d25c  size=26  body=[[0800d25c, 0800d275]]

void FUN_0800d25c(int param_1)

{
  if ((param_1 == 0) && (DAT_200015e9 != '\0')) {
    FUN_0800dc34();
    FUN_0800dc58();
    DAT_200015e9 = '\0';
  }
  return;
}


// ===================================================================
// keycode_at_keymap_location_raw @ 0x0800d27c  size=36  body=[[0800d27c, 0800d29f]]

// VERIFIED: cmp r0#5/r1#5/r2#17 bhi -> movs r0#1 (KC_TRNS); idx = layer*0x6C + row*18 + col; ldr
// r3=[0x0800D2A0]=0x080169B8 keymaps; ldrh.w r0=[r3 + idx*2]; bx lr  (0x0800D27C-0x0800D29F)

ushort keycode_at_keymap_location_raw(uint param_1,uint param_2,uint param_3)

{
  if (((param_1 < 6) && (param_2 < 6)) && (param_3 < 0x12)) {
    return keymaps[param_1][param_2][param_3];
  }
  return 1;
}


// ===================================================================
// keycode_at_keymap_location @ 0x0800d2a4  size=4  body=[[0800d2a4, 0800d2a7]]

// VERIFIED: 4-byte ICF thunk 'b.w 0x0800D27C' (f7ff bfea); tail-jumped from keymap_key_to_keycode
// @0x0800EA78

ushort keycode_at_keymap_location(uint param_1,uint param_2,uint param_3)

{
  if (((param_1 < 6) && (param_2 < 6)) && (param_3 < 0x12)) {
    return keymaps[param_1][param_2][param_3];
  }
  return 1;
}


// ===================================================================
// keycode_at_encodermap_location_raw @ 0x0800d2a8  size=26  body=[[0800d2a8, 0800d2c1]]

// VERIFIED: layer<6 && encoder_idx==0; idx = layer*2 + (clockwise^1); ldr
// r3=[0x0800D2C4]=0x080169A0 encoder_map; ldrh.w [r3 + idx*2]; else movs r0#1

undefined2 keycode_at_encodermap_location_raw(uint param_1,int param_2,uint param_3)

{
  if ((param_1 < 6) && (param_2 == 0)) {
    return *(undefined2 *)(&encoder_map + ((param_3 ^ 1) + param_1 * 2) * 2);
  }
  return 1;
}


// ===================================================================
// keycode_at_encodermap_location @ 0x0800d2c8  size=4  body=[[0800d2c8, 0800d2cb]]

// VERIFIED: ICF thunk 'b.w 0x0800D2A8'; tail-jumped from keymap_key_to_keycode @0x0800EA88

undefined2 keycode_at_encodermap_location(uint param_1,int param_2,uint param_3)

{
  if ((param_1 < 6) && (param_2 == 0)) {
    return *(undefined2 *)(&encoder_map + ((param_3 ^ 1) + param_1 * 2) * 2);
  }
  return 1;
}


// ===================================================================
// FUN_0800d2cc @ 0x0800d2cc  size=4  body=[[0800d2cc, 0800d2cf]]

undefined4 FUN_0800d2cc(void)

{
  return 1;
}


// ===================================================================
// FUN_0800d2d0 @ 0x0800d2d0  size=8  body=[[0800d2d0, 0800d2d7]]

void FUN_0800d2d0(void)

{
  FUN_0800d2cc();
  return;
}


// ===================================================================
// process_action_kb @ 0x0800d2d8  size=4  body=[[0800d2d8, 0800d2db]]

// INFERRED: 'movs r0,#1; bx lr' weak default returned at the end of process_record_quantum

undefined4 process_action_kb(void)

{
  return 1;
}


// ===================================================================
// FUN_0800d2dc @ 0x0800d2dc  size=2  body=[[0800d2dc, 0800d2dd]]

void FUN_0800d2dc(void)

{
  return;
}


// ===================================================================
// FUN_0800d2de @ 0x0800d2de  size=8  body=[[0800d2de, 0800d2e5]]

void FUN_0800d2de(void)

{
  FUN_0800d2dc();
  return;
}


// ===================================================================
// get_event_keycode @ 0x0800d2e8  size=70  body=[[0800d2e8, 0800d32d]]

// VERIFIED shape of action.c get_event_keycode(): if !disable_action_cache(@0x200015F0) { if
// pressed && update_layer_cache: layer_switch_get_layer + update_source_layers_cache else
// read_source_layers_cache } else layer_switch_get_layer; tail b.w keymap_key_to_keycode 0x0800EA64

ushort get_event_keycode(uint param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined1 local_b;
  
  if (disable_action_cache == '\0') {
    local_b = (char)((uint)param_2 >> 8);
    if ((local_b == '\0') || (param_3 == 0)) {
      uVar2 = read_source_layers_cache(param_1);
    }
    else {
      uVar2 = layer_switch_get_layer((short)param_1,param_2);
      update_source_layers_cache(param_1,uVar2);
    }
  }
  else {
    uVar2 = layer_switch_get_layer((short)param_1,param_2);
  }
  uVar1 = keymap_key_to_keycode(uVar2,param_1);
  return uVar1;
}


// ===================================================================
// get_record_keycode @ 0x0800d334  size=24  body=[[0800d334, 0800d34b]]

// VERIFIED: loads record->event (ldrh [r0] [r0+2] [r0+4]) and tail-jumps b.w 0x0800D2E8
// get_event_keycode

ushort get_record_keycode(uint *param_1,int param_2)

{
  ushort uVar1;
  
  uVar1 = get_event_keycode(*param_1,(uint)(ushort)param_1[1],param_2);
  return uVar1;
}


// ===================================================================
// FUN_0800d34c @ 0x0800d34c  size=18  body=[[0800d34c, 0800d35d]]

void FUN_0800d34c(uint *param_1)

{
  get_record_keycode(param_1,1);
  FUN_0800d2d0();
  return;
}


// ===================================================================
// FUN_0800d35e @ 0x0800d35e  size=18  body=[[0800d35e, 0800d36f]]

void FUN_0800d35e(uint *param_1)

{
  get_record_keycode(param_1,0);
  FUN_0800d2de();
  return;
}


// ===================================================================
// FUN_0800d370 @ 0x0800d370  size=4  body=[[0800d370, 0800d373]]

undefined4 FUN_0800d370(void)

{
  return 1;
}


// ===================================================================
// FUN_0800d374 @ 0x0800d374  size=8  body=[[0800d374, 0800d37b]]

void FUN_0800d374(void)

{
  FUN_0800d370();
  return;
}


// ===================================================================
// FUN_0800d37c @ 0x0800d37c  size=26  body=[[0800d37c, 0800d395]]

void FUN_0800d37c(void)

{
  FUN_0800db44();
  FUN_0800d374();
  FUN_08013a7a(25000);
  return;
}


// ===================================================================
// reset_keyboard @ 0x0800d396  size=16  body=[[0800d396, 0800d3a5]]

// INFERRED: target of the QK_BOOT (0x7C00) case in process_record_quantum

void reset_keyboard(void)

{
  FUN_0800d37c();
  FUN_080125f0();
  return;
}


// ===================================================================
// soft_reset_keyboard @ 0x0800d3a6  size=16  body=[[0800d3a6, 0800d3b5]]

// INFERRED: target of the QK_REBOOT (0x7C01) case in process_record_quantum

void soft_reset_keyboard(void)

{
  FUN_0800d37c();
  FUN_080125fa();
  return;
}


// ===================================================================
// process_record_quantum @ 0x0800d3b6  size=166  body=[[0800d3b6, 0800d45b]]

// VERIFIED shape: keycode=get_record_keycode(record,1); if preprocess_tap_dance(kc,rec) re-read;
// chain process_record_kb 0x0800C6E8 && process_tap_dance 0x08012040 && process_leader 0x080118F4
// && process_rgb_matrix 0x08011530; if pressed: 0x7C00 QK_BOOT->0x0800D396 0x7C01
// QK_REBOOT->0x0800D3A6 0x7C03 QK_CLEAR_EEPROM->0x0800E5CC+0x0800D3A6 0x7C5A/5B/5C
// OS_ON/OFF/TOGG->0x0800E5C0/E5C6/E5A8; return process_action_kb 0x0800D2D8

undefined4 process_record_quantum(uint *param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar4;
  undefined4 uVar5;
  uint uVar3;
  
  uVar2 = get_record_keycode(param_1,1);
  uVar3 = (uint)uVar2;
  cVar1 = preprocess_tap_dance(uVar3,(int)param_1);
  if (cVar1 != '\0') {
    uVar2 = get_record_keycode(param_1,1);
    uVar3 = (uint)uVar2;
  }
  iVar4 = process_record_kb(uVar3,(int)param_1);
  if ((((iVar4 == 0) || (iVar4 = process_tap_dance(uVar3,(int)param_1), iVar4 == 0)) ||
      (cVar1 = process_leader(uVar3,(int)param_1), cVar1 == '\0')) ||
     (cVar1 = process_rgb_matrix(uVar3,(int)param_1), cVar1 == '\0')) {
LAB_0800d442:
    uVar5 = 0;
  }
  else {
    if (*(char *)((int)param_1 + 5) != '\0') {
      if (uVar3 == 0x7c5a) {
        FUN_0800e5c0();
      }
      else {
        if (uVar3 < 0x7c5b) {
          if (uVar3 != 0x7c01) {
            if (uVar3 != 0x7c03) {
              if (uVar3 == 0x7c00) {
                reset_keyboard();
                goto LAB_0800d442;
              }
              goto LAB_0800d420;
            }
            FUN_0800e5cc();
          }
          soft_reset_keyboard();
          goto LAB_0800d442;
        }
        if (uVar3 == 0x7c5b) {
          FUN_0800e5c6();
        }
        else if (uVar3 == 0x7c5c) {
          FUN_0800e5a8();
        }
      }
    }
LAB_0800d420:
    uVar5 = process_action_kb();
  }
  return uVar5;
}


// ===================================================================
// FUN_0800d45c @ 0x0800d45c  size=24  body=[[0800d45c, 0800d473]]

void FUN_0800d45c(void)

{
  undefined4 extraout_r1;
  uint extraout_r2;
  
  FUN_0801245a();
  FUN_08011058();
  FUN_0800d4ca();
  FUN_08011180(1,extraout_r1,extraout_r2);
  return;
}


// ===================================================================
// FUN_0800d474 @ 0x0800d474  size=20  body=[[0800d474, 0800d487]]

void FUN_0800d474(void)

{
  undefined4 extraout_r1;
  uint extraout_r2;
  
  FUN_0800d4d4();
  FUN_08011180(0,extraout_r1,extraout_r2);
  FUN_08012464();
  return;
}


// ===================================================================
// get_highest_layer @ 0x0800d488  size=40  body=[[0800d488, 0800d4af]]

// VERIFIED use: kc_raw_hid_rx case 0xA3 calls it on default_layer_state and stores the byte result
// (keychron_raw_hid.c: data[1] = get_highest_layer(default_layer_state))

int get_highest_layer(uint param_1)

{
  int iVar1;
  
  if (param_1 >> 8 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 8;
    param_1 = param_1 >> 8;
  }
  if (param_1 >> 4 != 0) {
    iVar1 = iVar1 + 4;
    param_1 = param_1 >> 4;
  }
  if (param_1 >> 2 != 0) {
    iVar1 = iVar1 + 2;
    param_1 = param_1 >> 2;
  }
  if (param_1 >> 1 != 0) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}


// ===================================================================
// FUN_0800d4b0 @ 0x0800d4b0  size=2  body=[[0800d4b0, 0800d4b1]]

void FUN_0800d4b0(void)

{
  return;
}


// ===================================================================
// FUN_0800d4b2 @ 0x0800d4b2  size=4  body=[[0800d4b2, 0800d4b5]]

undefined4 FUN_0800d4b2(void)

{
  return 1;
}


// ===================================================================
// FUN_0800d4b6 @ 0x0800d4b6  size=2  body=[[0800d4b6, 0800d4b7]]

void FUN_0800d4b6(void)

{
  return;
}


// ===================================================================
// FUN_0800d4b8 @ 0x0800d4b8  size=2  body=[[0800d4b8, 0800d4b9]]

void FUN_0800d4b8(void)

{
  return;
}


// ===================================================================
// FUN_0800d4ba @ 0x0800d4ba  size=16  body=[[0800d4ba, 0800d4c9]]

void FUN_0800d4ba(void)

{
  FUN_0800d4b0();
  FUN_0800b91c();
  return;
}


// ===================================================================
// FUN_0800d4ca @ 0x0800d4ca  size=10  body=[[0800d4ca, 0800d4d3]]

void FUN_0800d4ca(void)

{
  FUN_0800d4ba();
  return;
}


// ===================================================================
// FUN_0800d4d4 @ 0x0800d4d4  size=12  body=[[0800d4d4, 0800d4df]]

void FUN_0800d4d4(void)

{
  FUN_08012138();
  FUN_0800d4ba();
  return;
}


// ===================================================================
// FUN_0800d4e0 @ 0x0800d4e0  size=34  body=[[0800d4e0, 0800d501]]

void FUN_0800d4e0(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012138();
  if (DAT_200015ea != uVar1) {
    DAT_200015ea = (byte)uVar1;
    DAT_200015ec = FUN_08012508();
    FUN_0800d4ba();
  }
  return;
}


// ===================================================================
// FUN_0800d50c @ 0x0800d50c  size=64  body=[[0800d50c, 0800d54b]]

void FUN_0800d50c(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  char local_13;
  uint local_10;
  uint local_c;
  
  local_13 = (char)(param_2 >> 8);
  if (local_13 != '\0') {
    local_10 = param_3;
    local_c = param_4;
    FUN_0800e374();
  }
  local_c = param_2 & 0xffff;
  local_10 = param_1;
  if (((param_2 & 0xff) == 0) || (iVar1 = FUN_0800d34c(&local_10), iVar1 != 0)) {
    FUN_0800e21c(local_10,local_c);
  }
  return;
}


// ===================================================================
// FUN_0800d54c @ 0x0800d54c  size=14  body=[[0800d54c, 0800d559]]

void FUN_0800d54c(undefined2 *param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 2) == '\x01') {
    FUN_0800ddf8(*param_1,param_2);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800d55a @ 0x0800d55a  size=22  body=[[0800d55a, 0800d56f]]

void FUN_0800d55a(int param_1,int param_2)

{
  if (param_2 == 0) {
    FUN_08011c48(param_1);
  }
  else {
    FUN_08011b84(param_1);
  }
  FUN_08011d68();
  return;
}


// ===================================================================
// register_code @ 0x0800d570  size=140  body=[[0800d570, 0800d5fb]]

// VERIFIED shape of register_code(): 0->return; (kc-4)&0xff<0xA1 basic -> add_key path
// 0x08012238/0x08012350/0x0801231C; (kc+0x20)&0xff<8 mods 0xE0-0xE7 -> 0x0800E31C(1<<(kc&7));
// 0xA5-0xA7 system -> 0x08012188(kc-0x24); 0xA8-0xC2 consumer -> 0x080121B8(u16 table @0x08016EC8);
// 0xCD-0xDF mouse -> 0x08011B84+0x08011D68; then send 0x0800E4DC

void register_code(uint param_1)

{
  bool bVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    return;
  }
  if ((param_1 - 4 & 0xff) < 0xa1) {
    bVar1 = FUN_08012238(param_1);
    if (bVar1) {
      FUN_08012350(param_1);
      FUN_0800e4dc();
    }
    FUN_0801231c(param_1);
  }
  else {
    if (7 < (param_1 + 0x20 & 0xff)) {
      if ((param_1 + 0x5b & 0xff) < 3) {
        FUN_08012188(param_1 - 0x24 & 0xffff);
        return;
      }
      uVar2 = param_1 + 0x58 & 0xff;
      if (0x1a < uVar2) {
        if (0x12 < (param_1 + 0x33 & 0xff)) {
          return;
        }
        FUN_08011b84(param_1);
        FUN_08011d68();
        return;
      }
      FUN_080121b8((uint)*(ushort *)(&consumer_usage_table + uVar2 * 2));
      return;
    }
    FUN_0800e31c((byte)(1 << (param_1 & 7)));
  }
  FUN_0800e4dc();
  return;
}


// ===================================================================
// unregister_code @ 0x0800d600  size=114  body=[[0800d600, 0800d671]]

// VERIFIED mirror of register_code: 0x08012350 del_key, 0x0800E32C del_mods, 0x08012188(0),
// 0x080121B8(0), 0x08011C48 mousekey_off

void unregister_code(uint param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return;
  }
  if ((param_1 - 4 & 0xff) < 0xa1) {
    FUN_08012350(param_1);
  }
  else {
    if (7 < (param_1 + 0x20 & 0xff)) {
      if ((param_1 + 0x5b & 0xff) < 3) {
        FUN_08012188(0);
        return;
      }
      if (0x1a < (param_1 + 0x58 & 0xff)) {
        if (0x12 < (param_1 + 0x33 & 0xff)) {
          return;
        }
        FUN_08011c48(param_1);
        FUN_08011d68();
        return;
      }
      FUN_080121b8(0);
      return;
    }
    FUN_0800e32c((byte)(1 << (param_1 & 7)));
  }
  FUN_0800e4dc();
  return;
}


// ===================================================================
// FUN_0800d672 @ 0x0800d672  size=18  body=[[0800d672, 0800d683]]

void FUN_0800d672(int param_1)

{
  if (param_1 != 0) {
    FUN_0800e31c((byte)param_1);
    FUN_0800e4dc();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800d684 @ 0x0800d684  size=18  body=[[0800d684, 0800d695]]

void FUN_0800d684(int param_1)

{
  if (param_1 != 0) {
    FUN_0800e32c((byte)param_1);
    FUN_0800e4dc();
    return;
  }
  return;
}


// ===================================================================
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


// ===================================================================
// FUN_0800dab4 @ 0x0800dab4  size=34  body=[[0800dab4, 0800dad5]]

void FUN_0800dab4(uint *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0800de10((uint)*(byte *)((int)param_1 + 5),(uint)(ushort)*param_1);
  FUN_0800dcd8();
  FUN_0800dbe0();
  FUN_0800d698(param_1,uVar1);
  return;
}


// ===================================================================
// FUN_0800dad8 @ 0x0800dad8  size=56  body=[[0800dad8, 0800db0f]]

void FUN_0800dad8(uint *param_1)

{
  byte bVar1;
  int iVar2;
  
  if ((char)param_1[1] != '\0') {
    iVar2 = process_record_quantum(param_1);
    if (iVar2 == 0) {
      bVar1 = FUN_0800e2fc();
      if (((bVar1 != 0) && (*(char *)((int)param_1 + 5) != '\0')) &&
         ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0)) {
        FUN_0800e548(2);
        return;
      }
    }
    else {
      FUN_0800dab4(param_1);
      FUN_0800d35e(param_1);
    }
  }
  return;
}


// ===================================================================
// FUN_0800db14 @ 0x0800db14  size=34  body=[[0800db14, 0800db35]]

void FUN_0800db14(void)

{
  FUN_08012188(0);
  FUN_080121b8(0);
  FUN_0800e374();
  FUN_0800e4dc();
  FUN_08011da0();
  FUN_08011d68();
  return;
}


// ===================================================================
// FUN_0800db36 @ 0x0800db36  size=14  body=[[0800db36, 0800db43]]

void FUN_0800db36(void)

{
  FUN_08012384();
  FUN_0800db14();
  return;
}


// ===================================================================
// FUN_0800db44 @ 0x0800db44  size=14  body=[[0800db44, 0800db51]]

void FUN_0800db44(void)

{
  FUN_0800e33c();
  FUN_0800db36();
  return;
}


// ===================================================================
// FUN_0800db94 @ 0x0800db94  size=90  body=[[0800db52, 0800dbab]]

bool FUN_0800db94(undefined2 *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  if (*(char *)(param_1 + 2) == '\0') {
    return false;
  }
  uVar1 = FUN_0800ddf8(*param_1,param_2);
  uVar2 = (uVar1 & 0xffff) >> 0xc;
  uVar1 = uVar1 & 0xff;
  if (uVar2 == 6) {
    if (uVar1 < 0xe8) {
      return true;
    }
    bVar3 = uVar1 == 0xf1;
  }
  else {
    if (uVar2 < 7) {
      uVar2 = uVar2 + 0xe;
    }
    else {
      uVar2 = uVar2 + 6;
    }
    if (1 < (uVar2 & 0xf)) {
      return false;
    }
    if (uVar1 == 0xf0) {
      return true;
    }
    if (uVar1 < 0xf1) {
      return uVar1 < 0xe8;
    }
    bVar3 = uVar1 == 0xf4;
  }
  return bVar3;
}


// ===================================================================
// FUN_0800dbac @ 0x0800dbac  size=12  body=[[0800dbac, 0800dbb7]]

void FUN_0800dbac(void)

{
  return;
}


// ===================================================================
// FUN_0800dbb8 @ 0x0800dbb8  size=12  body=[[0800dbb8, 0800dbc3]]

void FUN_0800dbb8(void)

{
  return;
}


// ===================================================================
// FUN_0800dbc4 @ 0x0800dbc4  size=2  body=[[0800dbc4, 0800dbc5]]

void FUN_0800dbc4(void)

{
  return;
}


// ===================================================================
// FUN_0800dbc6 @ 0x0800dbc6  size=8  body=[[0800dbc6, 0800dbcd]]

void FUN_0800dbc6(void)

{
  FUN_0800dbc4();
  return;
}


// ===================================================================
// FUN_0800dbd0 @ 0x0800dbd0  size=12  body=[[0800dbd0, 0800dbdb]]

void FUN_0800dbd0(void)

{
  default_layer_state = FUN_0800dbc6();
  return;
}


// ===================================================================
// FUN_0800dbe0 @ 0x0800dbe0  size=2  body=[[0800dbe0, 0800dbe1]]

void FUN_0800dbe0(void)

{
  return;
}


// ===================================================================
// thunk_FUN_0800dbd0 @ 0x0800dbe2  size=4  body=[[0800dbe2, 0800dbe5]]

void thunk_FUN_0800dbd0(void)

{
  default_layer_state = FUN_0800dbc6();
  return;
}


// ===================================================================
// FUN_0800dbe8 @ 0x0800dbe8  size=10  body=[[0800dbe8, 0800dbf1]]

void FUN_0800dbe8(void)

{
  FUN_0800dbd0();
  return;
}


// ===================================================================
// FUN_0800dbf8 @ 0x0800dbf8  size=10  body=[[0800dbf8, 0800dc01]]

void FUN_0800dbf8(void)

{
  FUN_0800dbd0();
  return;
}


// ===================================================================
// FUN_0800dc08 @ 0x0800dc08  size=10  body=[[0800dc08, 0800dc11]]

void FUN_0800dc08(void)

{
  FUN_0800dbd0();
  return;
}


// ===================================================================
// FUN_0800dc18 @ 0x0800dc18  size=2  body=[[0800dc18, 0800dc19]]

void FUN_0800dc18(void)

{
  return;
}


// ===================================================================
// FUN_0800dc1a @ 0x0800dc1a  size=8  body=[[0800dc1a, 0800dc21]]

void FUN_0800dc1a(void)

{
  FUN_0800dc18();
  return;
}


// ===================================================================
// FUN_0800dc24 @ 0x0800dc24  size=12  body=[[0800dc24, 0800dc2f]]

void FUN_0800dc24(void)

{
  layer_state = FUN_0800dc1a();
  return;
}


// ===================================================================
// FUN_0800dc34 @ 0x0800dc34  size=6  body=[[0800dc34, 0800dc39]]

void FUN_0800dc34(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dc3c @ 0x0800dc3c  size=24  body=[[0800dc3c, 0800dc53]]

uint FUN_0800dc3c(uint param_1)

{
  if (layer_state == 0) {
    return (uint)(param_1 == 0);
  }
  return (int)(uint)layer_state >> (param_1 & 0xff) & 1;
}


// ===================================================================
// FUN_0800dc58 @ 0x0800dc58  size=12  body=[[0800dc58, 0800dc63]]

void FUN_0800dc58(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dc64 @ 0x0800dc64  size=18  body=[[0800dc64, 0800dc75]]

void FUN_0800dc64(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dc7c @ 0x0800dc7c  size=16  body=[[0800dc7c, 0800dc8b]]

void FUN_0800dc7c(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dc90 @ 0x0800dc90  size=18  body=[[0800dc90, 0800dca1]]

void FUN_0800dc90(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dca8 @ 0x0800dca8  size=10  body=[[0800dca8, 0800dcb1]]

void FUN_0800dca8(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dcb8 @ 0x0800dcb8  size=10  body=[[0800dcb8, 0800dcc1]]

void FUN_0800dcb8(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dcc8 @ 0x0800dcc8  size=10  body=[[0800dcc8, 0800dcd1]]

void FUN_0800dcc8(void)

{
  FUN_0800dc24();
  return;
}


// ===================================================================
// FUN_0800dcd8 @ 0x0800dcd8  size=2  body=[[0800dcd8, 0800dcd9]]

void FUN_0800dcd8(void)

{
  return;
}


// ===================================================================
// FUN_0800dd0c @ 0x0800dd0c  size=38  body=[[0800dd0c, 0800dd31]]

uint FUN_0800dd0c(uint param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  uVar3 = 0;
  do {
    pbVar1 = (byte *)(param_2 + (param_1 >> 3) * 4 + uVar4);
    uVar2 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    uVar3 = uVar3 | (*pbVar1 >> (param_1 & 7) & 1) << uVar2 & 0xff;
  } while (uVar4 != 4);
  return uVar3;
}


// ===================================================================
// update_source_layers_cache @ 0x0800dd34  size=110  body=[[0800dcda, 0800dd0b] [0800dd34, 0800dd6f]]

// INFERRED: second callee (key,layer) in the pressed&&update_layer_cache branch of
// get_event_keycode (QMK 0.23 action.c order)

void update_source_layers_cache(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  undefined *puVar5;
  
  uVar3 = param_1 & 0xff;
  uVar2 = (param_1 & 0xffff) >> 8;
  if (uVar2 < 6) {
    if (0x11 < uVar3) {
      return;
    }
    puVar5 = &DAT_200015f5;
    uVar3 = uVar3 + uVar2 * 0x12;
  }
  else {
    if (1 < (uVar2 + 4 & 0xff)) {
      return;
    }
    puVar5 = &DAT_200015f1;
  }
  pbVar4 = puVar5 + (uVar3 >> 3) * 4 + -1;
  uVar2 = 0;
  do {
    pbVar4 = pbVar4 + 1;
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    *pbVar4 = *pbVar4 ^ ((byte)((int)((param_2 >> uVar1) << 0x1f) >> 0x1f) ^ *pbVar4) &
                        (byte)(1 << (uVar3 & 7));
  } while (uVar2 != 4);
  return;
}


// ===================================================================
// read_source_layers_cache @ 0x0800dd78  size=52  body=[[0800dd78, 0800ddab]]

// INFERRED: callee in the else-branch of get_event_keycode

uint read_source_layers_cache(uint param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  
  uVar3 = param_1 & 0xff;
  uVar1 = (param_1 & 0xffff) >> 8;
  if (uVar1 < 6) {
    if (0x11 < uVar3) {
      return 0;
    }
    puVar2 = &DAT_200015f5;
    uVar3 = uVar3 + uVar1 * 0x12;
  }
  else {
    if (1 < (uVar1 + 4 & 0xff)) {
      return 0;
    }
    puVar2 = &DAT_200015f1;
  }
  uVar1 = FUN_0800dd0c(uVar3,(int)puVar2);
  return uVar1;
}


// ===================================================================
// layer_switch_get_layer @ 0x0800ddb4  size=58  body=[[0800ddb4, 0800dded]]

// VERIFIED: loops layer 15..0 over bits of (u16@0x2000162E | u16@0x20001630); calls
// 0x0800EA9E(layer,key) and returns first layer whose keycode != 1 (KC_TRNS); else 0

uint layer_switch_get_layer(undefined2 param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  bool bVar4;
  undefined4 local_14;
  
  local_14 = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar3 = layer_state | default_layer_state;
  uVar2 = 0xf;
  do {
    if (((int)(uint)uVar3 >> (uVar2 & 0xff)) << 0x1f < 0) {
      uVar1 = FUN_0800ea9e(uVar2 & 0xff,local_14);
      if ((uVar1 & 0xffff) != 1) {
        return uVar2 & 0xff;
      }
    }
    bVar4 = uVar2 != 0;
    uVar2 = uVar2 - 1;
  } while (bVar4);
  return 0;
}


// ===================================================================
// FUN_0800ddf8 @ 0x0800ddf8  size=24  body=[[0800ddf8, 0800de0f]]

void FUN_0800ddf8(undefined2 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 local_c;
  
  local_c = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar1 = layer_switch_get_layer(param_1,param_2);
  FUN_0800ea9e(uVar1,local_c);
  return;
}


// ===================================================================
// FUN_0800de10 @ 0x0800de10  size=66  body=[[0800de10, 0800de51]]

void FUN_0800de10(int param_1,uint param_2)

{
  uint uVar1;
  
  if (disable_action_cache != '\0') {
    FUN_0800ddf8((short)param_2,param_2);
    return;
  }
  if (param_1 == 0) {
    uVar1 = read_source_layers_cache(param_2);
  }
  else {
    uVar1 = layer_switch_get_layer((short)param_2,param_2);
    update_source_layers_cache(param_2,uVar1);
  }
  FUN_0800ea9e(uVar1,param_2);
  return;
}


// ===================================================================
// FUN_0800de58 @ 0x0800de58  size=52  body=[[0800de58, 0800de8b]]

void FUN_0800de58(void)

{
  byte bVar1;
  
  for (bVar1 = DAT_20001632; DAT_20001633 != bVar1; bVar1 = bVar1 + 1 & 7) {
    FUN_0800dbb8();
  }
  return;
}


// ===================================================================
// FUN_0800de98 @ 0x0800de98  size=28  body=[[0800de98, 0800deb3]]

void FUN_0800de98(void)

{
  FUN_0800dbb8();
  return;
}


// ===================================================================
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


// ===================================================================
// FUN_0800defc @ 0x0800defc  size=4  body=[[0800defc, 0800deff]]

undefined4 FUN_0800defc(void)

{
  return 0xaf;
}


// ===================================================================
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


// ===================================================================
// FUN_0800df94 @ 0x0800df94  size=644  body=[[0800df94, 0800e217]]

char FUN_0800df94(uint *param_1)

{
  byte bVar1;
  short sVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint extraout_r2;
  uint uVar10;
  ushort uVar11;
  bool bVar12;
  undefined2 local_38 [4];
  ushort local_30;
  short local_2e;
  char local_2c;
  undefined1 local_2b;
  byte local_2a;
  
  memcpy((undefined4 *)local_38,param_1,6);
  cVar5 = DAT_20001678._1_1_;
  uVar9 = *param_1;
  bVar1 = *(byte *)((int)param_1 + 1);
  cVar3 = *(char *)((int)param_1 + 5);
  sVar2 = *(short *)((int)param_1 + 2);
  cVar4 = (char)param_1[1];
  if ((char)DAT_20001678 == '\0') {
    if (cVar4 == '\0') {
      return '\x01';
    }
    if ((cVar3 == '\0') || (bVar6 = FUN_0800db94((undefined2 *)param_1,0), !bVar6))
    goto LAB_0800e206;
    memcpy((undefined4 *)&DAT_20001674,param_1,8);
    FUN_0800d54c(&DAT_20001674,extraout_r1);
  }
  else {
    uVar11 = sVar2 - DAT_20001676;
    if (DAT_20001678._1_1_ == '\0') {
      get_record_keycode((uint *)&DAT_20001674,0);
      uVar9 = FUN_0800defc();
      if (uVar9 <= uVar11) {
        FUN_0800dbac();
LAB_0800e14e:
        FUN_08008798((byte *)&DAT_20001674,0,8);
        FUN_0800de98();
        return '\0';
      }
      if (cVar4 == '\0') {
        return '\x01';
      }
      if (cVar3 == '\0') goto LAB_0800e206;
      if (DAT_20001674 == (ushort)*param_1) {
        if (((0xae < (ushort)(sVar2 - DAT_20001676)) ||
            (uVar9 = (uint)(byte)DAT_2000167a, (int)(uVar9 << 0x1f) < 0)) || (uVar9 < 0x10)) {
          memcpy((undefined4 *)&DAT_20001674,param_1,8);
          return '\x01';
        }
        *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
        if ((uVar9 & 0xf0) != 0xf0) {
          *(byte *)((int)param_1 + 6) =
               *(byte *)((int)param_1 + 6) & 0xf | ((*(byte *)((int)param_1 + 6) >> 4) + 1) * '\x10'
          ;
        }
        FUN_0800dad8(param_1);
        goto LAB_0800e0f0;
      }
      bVar6 = FUN_0800db94((undefined2 *)param_1,extraout_r1_02);
      if (!bVar6) {
        DAT_2000167a._0_1_ = (byte)DAT_2000167a | 1;
        goto LAB_0800e206;
      }
    }
    else {
      get_record_keycode((uint *)&DAT_20001674,0);
      uVar7 = FUN_0800defc();
      if (uVar11 < uVar7) {
        if (cVar4 == '\0') {
          return '\x01';
        }
        uVar7 = (uint)(ushort)*param_1;
        if ((byte)DAT_2000167a < 0x10) {
          if (DAT_20001674 == uVar7) {
            if (cVar3 == '\0') {
              DAT_2000167a._0_1_ = (byte)DAT_2000167a & 0xf | 0x10;
              FUN_0800de98();
              FUN_0800dad8((uint *)&DAT_20001674);
              *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
              return '\0';
            }
LAB_0800e0ce:
            DAT_2000167a._0_1_ = (byte)DAT_2000167a | 1;
            return '\0';
          }
          if (cVar3 != '\0') goto LAB_0800e0ce;
          FUN_0800deb8((uint)(byte)uVar9,(uint)bVar1,0);
          iVar8 = FUN_0800deb8((uint)(byte)uVar9,extraout_r1_00,extraout_r2);
          if (iVar8 != 0) {
            return '\0';
          }
          uVar9 = FUN_0800ddf8(local_38[0],extraout_r1_01);
          uVar7 = (uVar9 & 0xffff) >> 0xc;
          uVar10 = uVar9 & 0xff;
          if (uVar7 < 4) {
            if (uVar7 < 2) {
              if (((uVar9 & 0xf00) != 0) && (uVar10 == 0)) {
                return '\0';
              }
            }
            else if (((uVar9 & 0xf00) != 0) && (*(byte *)((int)param_1 + 6) < 0x10)) {
              return '\0';
            }
            uVar9 = uVar10 + 0x20 & 0xff;
            bVar12 = 6 < uVar9;
            bVar6 = uVar9 == 7;
          }
          else {
            if (1 < (uVar7 + 6 & 0xf)) goto LAB_0800e0a4;
            if (uVar10 < 0xf0) {
              return '\0';
            }
            uVar9 = uVar10 + 0xf & 0xff;
            bVar12 = 1 < uVar9;
            bVar6 = uVar9 == 2;
          }
          if (!bVar12 || bVar6) {
            return '\0';
          }
LAB_0800e0a4:
          FUN_0800dad8(param_1);
          return cVar5;
        }
        if ((DAT_20001674 == uVar7) && (cVar3 == '\0')) {
          *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
          FUN_0800dad8(param_1);
LAB_0800e0f0:
          memcpy((undefined4 *)&DAT_20001674,param_1,8);
          goto LAB_0800dff2;
        }
      }
      else {
        uVar7 = (uint)(byte)DAT_2000167a;
        if (uVar7 < 0x10) {
          FUN_0800dbac();
          FUN_0800dad8((uint *)&DAT_20001674);
          goto LAB_0800e14e;
        }
        if (cVar4 == '\0') {
          return '\x01';
        }
        if ((DAT_20001674 == (ushort)*param_1) && (cVar3 == '\0')) {
          *(byte *)((int)param_1 + 6) = (byte)DAT_2000167a;
          FUN_0800dad8(param_1);
          FUN_08008798((byte *)&DAT_20001674,0,8);
          return '\x01';
        }
      }
      bVar6 = FUN_0800db94((undefined2 *)param_1,uVar7);
      if ((!bVar6) || (cVar3 == '\0')) {
LAB_0800e206:
        FUN_0800dad8(param_1);
        return '\x01';
      }
      if (0x1f < (byte)DAT_2000167a) {
        local_30 = DAT_20001674;
        local_2c = (char)DAT_20001678;
        local_2b = 0;
        local_2a = (byte)DAT_2000167a;
        local_2e = sVar2;
        FUN_0800dad8((uint *)&local_30);
      }
    }
    memcpy((undefined4 *)&DAT_20001674,param_1,8);
  }
  FUN_0800df00();
LAB_0800dff2:
  FUN_0800de98();
  return '\x01';
}


// ===================================================================
// FUN_0800e21c @ 0x0800e21c  size=178  body=[[0800e21c, 0800e2cd]]

void FUN_0800e21c(uint param_1,undefined4 param_2)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint local_28;
  undefined4 local_24;
  uint local_20;
  undefined4 uStack_1c;
  
  local_28 = param_1;
  local_24 = param_2;
  bVar1 = FUN_0800df94(&local_28);
  if (bVar1 == 0) {
    local_20 = local_28;
    uStack_1c = local_24;
    if ((char)local_24 != '\0') {
      uVar3 = DAT_20001633 + 1 & 7;
      if (uVar3 == DAT_20001632) {
        FUN_0800db44();
        DAT_20001632 = bVar1;
        DAT_20001633 = bVar1;
        FUN_08008798((byte *)&DAT_20001674,0,8);
      }
      else {
        memcpy((undefined4 *)(&DAT_20001634 + (uint)DAT_20001633 * 8),&local_20,8);
        DAT_20001633 = (byte)uVar3;
        FUN_0800de58();
      }
    }
  }
  else if ((char)local_24 != '\0') {
    FUN_0800dbb8();
  }
  while (((uint)DAT_20001633 != (uint)DAT_20001632 &&
         (cVar2 = FUN_0800df94((uint *)(&DAT_20001634 + (uint)DAT_20001632 * 8)), cVar2 != '\0'))) {
    FUN_0800dbb8();
    DAT_20001632 = DAT_20001632 + 1 & 7;
  }
  return;
}


// ===================================================================
// FUN_0800e2e0 @ 0x0800e2e0  size=8  body=[[0800e2e0, 0800e2e7]]

byte FUN_0800e2e0(void)

{
  return DAT_200016a4 >> 3;
}


// ===================================================================
// FUN_0800e2ec @ 0x0800e2ec  size=10  body=[[0800e2ec, 0800e2f5]]

byte FUN_0800e2ec(void)

{
  return DAT_200016a4 & 7;
}


// ===================================================================
// FUN_0800e2fc @ 0x0800e2fc  size=14  body=[[0800e2fc, 0800e309]]

byte FUN_0800e2fc(void)

{
  byte bVar1;
  
  bVar1 = DAT_200016a4 & 7;
  if ((DAT_200016a4 & 7) != 0) {
    bVar1 = 1;
  }
  return bVar1;
}


// ===================================================================
// FUN_0800e310 @ 0x0800e310  size=6  body=[[0800e310, 0800e315]]

undefined1 FUN_0800e310(void)

{
  return DAT_200016d0;
}


// ===================================================================
// FUN_0800e31c @ 0x0800e31c  size=10  body=[[0800e31c, 0800e325]]

void FUN_0800e31c(byte param_1)

{
  DAT_200016d0 = param_1 | DAT_200016d0;
  return;
}


// ===================================================================
// FUN_0800e32c @ 0x0800e32c  size=12  body=[[0800e32c, 0800e337]]

void FUN_0800e32c(byte param_1)

{
  DAT_200016d0 = DAT_200016d0 & ~param_1;
  return;
}


// ===================================================================
// FUN_0800e33c @ 0x0800e33c  size=8  body=[[0800e33c, 0800e343]]

void FUN_0800e33c(void)

{
  DAT_200016d0 = 0;
  return;
}


// ===================================================================
// FUN_0800e348 @ 0x0800e348  size=6  body=[[0800e348, 0800e34d]]

undefined1 FUN_0800e348(void)

{
  return DAT_200016cf;
}


// ===================================================================
// FUN_0800e354 @ 0x0800e354  size=10  body=[[0800e354, 0800e35d]]

void FUN_0800e354(byte param_1)

{
  DAT_200016cf = param_1 | DAT_200016cf;
  return;
}


// ===================================================================
// FUN_0800e364 @ 0x0800e364  size=12  body=[[0800e364, 0800e36f]]

void FUN_0800e364(byte param_1)

{
  DAT_200016cf = DAT_200016cf & ~param_1;
  return;
}


// ===================================================================
// FUN_0800e374 @ 0x0800e374  size=8  body=[[0800e374, 0800e37b]]

void FUN_0800e374(void)

{
  DAT_200016cf = 0;
  return;
}


// ===================================================================
// FUN_0800e380 @ 0x0800e380  size=6  body=[[0800e380, 0800e385]]

undefined1 FUN_0800e380(void)

{
  return DAT_200016a6;
}


// ===================================================================
// FUN_0800e38c @ 0x0800e38c  size=8  body=[[0800e38c, 0800e393]]

void FUN_0800e38c(uint param_1)

{
  thunk_FUN_0800d010(param_1);
  return;
}


// ===================================================================
// FUN_0800e394 @ 0x0800e394  size=22  body=[[0800e394, 0800e3a9]]

void FUN_0800e394(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & ~(uint)DAT_200016a5) != 0) {
    uVar1 = param_1 | DAT_200016a5;
    DAT_200016a5 = (byte)uVar1;
    FUN_0800e38c(uVar1);
  }
  return;
}


// ===================================================================
// FUN_0800e3b0 @ 0x0800e3b0  size=18  body=[[0800e3b0, 0800e3c1]]

void FUN_0800e3b0(void)

{
  if (DAT_200016a5 != '\0') {
    DAT_200016a5 = '\0';
    FUN_0800e38c(0);
  }
  return;
}


// ===================================================================
// FUN_0800e3c8 @ 0x0800e3c8  size=22  body=[[0800e3c8, 0800e3dd]]

void FUN_0800e3c8(uint param_1)

{
  uint uVar1;
  
  if ((DAT_200016a5 & param_1) != 0) {
    uVar1 = (uint)DAT_200016a5 & ~param_1;
    DAT_200016a5 = (byte)uVar1;
    FUN_0800e38c(uVar1);
  }
  return;
}


// ===================================================================
// FUN_0800e3e4 @ 0x0800e3e4  size=8  body=[[0800e3e4, 0800e3eb]]

void FUN_0800e3e4(uint param_1)

{
  thunk_FUN_0800d010(param_1);
  return;
}


// ===================================================================
// FUN_0800e3ec @ 0x0800e3ec  size=22  body=[[0800e3ec, 0800e401]]

void FUN_0800e3ec(uint param_1)

{
  if ((param_1 & ~(uint)DAT_200016a6) != 0) {
    DAT_200016a6 = DAT_200016a6 | (byte)param_1;
    FUN_0800e3e4(param_1);
  }
  return;
}


// ===================================================================
// FUN_0800e408 @ 0x0800e408  size=22  body=[[0800e408, 0800e41d]]

void FUN_0800e408(uint param_1)

{
  uint uVar1;
  
  if ((DAT_200016a6 & param_1) != 0) {
    uVar1 = (uint)DAT_200016a6 & ~param_1;
    DAT_200016a6 = (byte)uVar1;
    FUN_0800e3e4(uVar1);
  }
  return;
}


// ===================================================================
// FUN_0800e424 @ 0x0800e424  size=18  body=[[0800e424, 0800e435]]

void FUN_0800e424(void)

{
  if (DAT_200016a6 != '\0') {
    DAT_200016a6 = '\0';
    FUN_0800e3e4(0);
  }
  return;
}


// ===================================================================
// FUN_0800e43c @ 0x0800e43c  size=34  body=[[0800e43c, 0800e45d]]

byte FUN_0800e43c(void)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = DAT_200016d0 | DAT_200016cf;
  if (DAT_200016a6 != 0) {
    bVar2 = bVar2 | DAT_200016a6;
    cVar1 = FUN_080121e8();
    if (cVar1 != '\0') {
      FUN_0800e424();
    }
  }
  return bVar2;
}


// ===================================================================
// FUN_0800e46c @ 0x0800e46c  size=48  body=[[0800e46c, 0800e49b]]

void FUN_0800e46c(void)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  
  pbVar1 = DAT_20000e9c;
  bVar2 = FUN_0800e43c();
  *pbVar1 = bVar2;
  pbVar1 = DAT_20000e9c;
  iVar3 = FUN_080089d4((int *)DAT_20000e9c,(int *)&DAT_2000169c,8);
  if (iVar3 != 0) {
    memcpy((undefined4 *)&DAT_2000169c,(undefined4 *)pbVar1,8);
    FUN_08012150();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800e4a4 @ 0x0800e4a4  size=48  body=[[0800e4a4, 0800e4d3]]

void FUN_0800e4a4(void)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  
  piVar1 = DAT_20000e98;
  bVar2 = FUN_0800e43c();
  *(byte *)((int)piVar1 + 1) = bVar2;
  piVar1 = DAT_20000e98;
  iVar3 = FUN_080089d4(DAT_20000e98,(int *)&DAT_2000167c,0x20);
  if (iVar3 != 0) {
    memcpy((undefined4 *)&DAT_2000167c,piVar1,0x20);
    FUN_08012160((undefined1 *)piVar1);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800e4dc @ 0x0800e4dc  size=24  body=[[0800e4dc, 0800e4f3]]

void FUN_0800e4dc(void)

{
  if ((DAT_20000ec6 != '\0') && ((char)DAT_200047d4 < '\0')) {
    FUN_0800e4a4();
    return;
  }
  FUN_0800e46c();
  return;
}


// ===================================================================
// FUN_0800e4fc @ 0x0800e4fc  size=8  body=[[0800e4fc, 0800e503]]

void FUN_0800e4fc(int param_1)

{
  FUN_0800d25c(param_1);
  return;
}


// ===================================================================
// FUN_0800e504 @ 0x0800e504  size=40  body=[[0800e504, 0800e52b]]

void FUN_0800e504(char param_1,byte param_2)

{
  if ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0) {
    DAT_200016a4 = param_2 | param_1 << 3;
    FUN_0800dc64();
    FUN_0800e4fc((uint)(DAT_200016a4 >> 3));
    return;
  }
  FUN_0800dc64();
  return;
}


// ===================================================================
// FUN_0800e534 @ 0x0800e534  size=14  body=[[0800e534, 0800e541]]

void FUN_0800e534(void)

{
  DAT_200016a4 = 0;
  FUN_0800e4fc(0);
  return;
}


// ===================================================================
// FUN_0800e548 @ 0x0800e548  size=44  body=[[0800e548, 0800e573]]

void FUN_0800e548(byte param_1)

{
  byte bVar1;
  
  bVar1 = DAT_200016a4;
  DAT_200016a4 = DAT_200016a4 & ~param_1;
  if ((((DAT_200016a4 & 7) == 0) && (DAT_200016a4 != bVar1)) &&
     ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0)) {
    FUN_0800dc7c();
    FUN_0800e534();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800e57c @ 0x0800e57c  size=38  body=[[0800e57c, 0800e5a1]]

void FUN_0800e57c(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (DAT_200047d4._1_1_ & 7) >> 2;
  if (uVar1 != param_1) {
    uVar2 = DAT_200047d4._1_1_ & 0xfffffffb | (param_1 & 1) << 2;
    DAT_200047d4 = CONCAT11((char)uVar2,(undefined1)DAT_200047d4);
    FUN_0800e606((uint)DAT_200047d4,uVar1,&DAT_200047d4,uVar2);
    FUN_0800e548(2);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800e5a8 @ 0x0800e5a8  size=20  body=[[0800e5a8, 0800e5bb]]

void FUN_0800e5a8(void)

{
  FUN_0800e57c((DAT_200047d4._1_1_ & 7) >> 2 ^ 1);
  return;
}


// ===================================================================
// FUN_0800e5c0 @ 0x0800e5c0  size=6  body=[[0800e5c0, 0800e5c5]]

void FUN_0800e5c0(void)

{
  FUN_0800e57c(1);
  return;
}


// ===================================================================
// FUN_0800e5c6 @ 0x0800e5c6  size=6  body=[[0800e5c6, 0800e5cb]]

void FUN_0800e5c6(void)

{
  FUN_0800e57c(0);
  return;
}


// ===================================================================
// FUN_0800e5cc @ 0x0800e5cc  size=20  body=[[0800e5cc, 0800e5df]]

void FUN_0800e5cc(void)

{
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  thunk_FUN_0800f244();
  FUN_0800f18c(0,0xffff,extraout_r2,in_r3);
  return;
}


// ===================================================================
// FUN_0800e5e0 @ 0x0800e5e0  size=20  body=[[0800e5e0, 0800e5f3]]

bool FUN_0800e5e0(undefined4 param_1,ushort param_2,undefined4 param_3)

{
  short sVar1;
  
  sVar1 = FUN_0800f0be(0,param_2,param_3);
  return sVar1 == -0x11a;
}


// ===================================================================
// FUN_0800e5f4 @ 0x0800e5f4  size=6  body=[[0800e5f4, 0800e5f9]]

undefined1 FUN_0800e5f4(undefined4 param_1,uint3 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  
  uVar1 = FUN_0800f0a0(2,param_2,param_3);
  return uVar1;
}


// ===================================================================
// FUN_0800e5fa @ 0x0800e5fa  size=6  body=[[0800e5fa, 0800e5ff]]

undefined1 FUN_0800e5fa(undefined4 param_1,uint3 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  
  uVar1 = FUN_0800f0a0(3,param_2,param_3);
  return uVar1;
}


// ===================================================================
// FUN_0800e600 @ 0x0800e600  size=6  body=[[0800e600, 0800e605]]

undefined2 FUN_0800e600(undefined4 param_1,ushort param_2,undefined4 param_3)

{
  undefined2 uVar1;
  
  uVar1 = FUN_0800f0be(4,param_2,param_3);
  return uVar1;
}


// ===================================================================
// FUN_0800e606 @ 0x0800e606  size=8  body=[[0800e606, 0800e60d]]

void FUN_0800e606(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0800f18c(4,param_1,param_3,param_4);
  return;
}


// ===================================================================
// FUN_0800e60e @ 0x0800e60e  size=8  body=[[0800e60e, 0800e615]]

void FUN_0800e60e(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0800f1a8(0xf,param_1,param_3,param_4);
  return;
}


// ===================================================================
// FUN_0800e61e @ 0x0800e61e  size=14  body=[[0800e616, 0800e623]]

void FUN_0800e61e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0800f1a8(0x13,0,param_3,param_4);
  return;
}


// ===================================================================
// FUN_0800e624 @ 0x0800e624  size=14  body=[[0800e624, 0800e631]]

void FUN_0800e624(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  undefined8 uVar1;
  
  uVar1 = FUN_0800e60e(0,param_2,param_3,param_4);
  FUN_0800e61e((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),extraout_r2,extraout_r3);
  return;
}


// ===================================================================
// FUN_0800e634 @ 0x0800e634  size=138  body=[[0800e634, 0800e6bd]]

void FUN_0800e634(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  undefined4 extraout_r2_05;
  undefined4 extraout_r2_06;
  undefined4 extraout_r2_07;
  undefined4 extraout_r2_08;
  undefined4 extraout_r2_09;
  undefined4 extraout_r2_10;
  undefined4 extraout_r2_11;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 extraout_r3_01;
  undefined4 extraout_r3_02;
  undefined4 extraout_r3_03;
  undefined8 uVar1;
  int local_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_10 = param_1;
  uStack_c = param_2;
  uStack_8 = param_3;
  thunk_FUN_0800f244();
  FUN_0800f18c(0,0xfee6,extraout_r2,extraout_r3);
  FUN_0800f170(2,0,extraout_r2_00);
  default_layer_state = 1;
  FUN_0800f170(3,1,extraout_r2_01);
  FUN_0800f18c(4,0x1400,extraout_r2_02,extraout_r3_00);
  FUN_0800f170(6,0,extraout_r2_03);
  FUN_0800f170(7,0xff,extraout_r2_04);
  FUN_0800f1a8(8,0,extraout_r2_05,extraout_r3_01);
  FUN_0800f170(0x24,0,extraout_r2_06);
  FUN_0800f170(0x17,0,extraout_r2_07);
  FUN_0800f170(0xc,0,extraout_r2_08);
  FUN_0800f170(0xd,0,extraout_r2_09);
  local_10 = 0;
  uStack_c = 0;
  FUN_0800f13c(&local_10,0x18,8,0);
  uVar1 = FUN_0800f1a8(0x20,0,extraout_r2_10,extraout_r3_02);
  FUN_0800e624((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),extraout_r2_11,extraout_r3_03);
  return;
}


// ===================================================================
// thunk_FUN_0800e634 @ 0x0800e6c4  size=4  body=[[0800e6c4, 0800e6c7]]

void thunk_FUN_0800e634(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  undefined4 extraout_r2_05;
  undefined4 extraout_r2_06;
  undefined4 extraout_r2_07;
  undefined4 extraout_r2_08;
  undefined4 extraout_r2_09;
  undefined4 extraout_r2_10;
  undefined4 extraout_r2_11;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 extraout_r3_01;
  undefined4 extraout_r3_02;
  undefined4 extraout_r3_03;
  undefined8 uVar1;
  int iStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  iStack_10 = param_1;
  uStack_c = param_2;
  uStack_8 = param_3;
  thunk_FUN_0800f244();
  FUN_0800f18c(0,0xfee6,extraout_r2,extraout_r3);
  FUN_0800f170(2,0,extraout_r2_00);
  default_layer_state = 1;
  FUN_0800f170(3,1,extraout_r2_01);
  FUN_0800f18c(4,0x1400,extraout_r2_02,extraout_r3_00);
  FUN_0800f170(6,0,extraout_r2_03);
  FUN_0800f170(7,0xff,extraout_r2_04);
  FUN_0800f1a8(8,0,extraout_r2_05,extraout_r3_01);
  FUN_0800f170(0x24,0,extraout_r2_06);
  FUN_0800f170(0x17,0,extraout_r2_07);
  FUN_0800f170(0xc,0,extraout_r2_08);
  FUN_0800f170(0xd,0,extraout_r2_09);
  iStack_10 = 0;
  uStack_c = 0;
  FUN_0800f13c(&iStack_10,0x18,8,0);
  uVar1 = FUN_0800f1a8(0x20,0,extraout_r2_10,extraout_r3_02);
  FUN_0800e624((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),extraout_r2_11,extraout_r3_03);
  return;
}


// ===================================================================
// FUN_0800e6c8 @ 0x0800e6c8  size=50  body=[[0800e6c8, 0800e6f9]]

void FUN_0800e6c8(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint extraout_r2;
  uint local_18;
  uint local_14;
  
  uVar1 = FUN_08012574();
  if (DAT_200016d2 != uVar1) {
    local_18 = FUN_08012574();
    local_14 = param_2 & 0xffff0000;
    local_18 = local_18 << 0x10;
    FUN_0800d50c(local_18,local_14,extraout_r2,&stack0xfffffff0);
    DAT_200016d2 = (ushort)uVar1;
  }
  return;
}


// ===================================================================
// FUN_0800e700 @ 0x0800e700  size=16  body=[[0800e700, 0800e70f]]

void FUN_0800e700(void)

{
  DAT_200016f4 = FUN_08012508();
  DAT_200016f0 = DAT_200016f4;
  return;
}


// ===================================================================
// FUN_0800e718 @ 0x0800e718  size=16  body=[[0800e718, 0800e727]]

void FUN_0800e718(void)

{
  DAT_200016f4 = FUN_08012508();
  DAT_200016ec = DAT_200016f4;
  return;
}


// ===================================================================
// FUN_0800e730 @ 0x0800e730  size=2  body=[[0800e730, 0800e731]]

void FUN_0800e730(void)

{
  return;
}


// ===================================================================
// FUN_0800e732 @ 0x0800e732  size=2  body=[[0800e732, 0800e733]]

void FUN_0800e732(void)

{
  return;
}


// ===================================================================
// FUN_0800e734 @ 0x0800e734  size=8  body=[[0800e734, 0800e73b]]

void FUN_0800e734(void)

{
  FUN_0800e732();
  return;
}


// ===================================================================
// FUN_0800e73c @ 0x0800e73c  size=4  body=[[0800e73c, 0800e73f]]

undefined4 FUN_0800e73c(void)

{
  return 1;
}


// ===================================================================
// FUN_0800e740 @ 0x0800e740  size=22  body=[[0800e740, 0800e755]]

void FUN_0800e740(void)

{
  uint extraout_r2;
  uint extraout_r3;
  undefined8 uVar1;
  
  uVar1 = FUN_0800ec88(0x800ec81);
  thunk_FUN_0800f460((int)uVar1,(uint)((ulonglong)uVar1 >> 0x20),extraout_r2,extraout_r3);
  FUN_0800e730();
  FUN_0800e734();
  return;
}


// ===================================================================
// FUN_0800e75c @ 0x0800e75c  size=4  body=[[0800e75c, 0800e75f]]

undefined4 FUN_0800e75c(void)

{
  return 1;
}


// ===================================================================
// FUN_0800e760 @ 0x0800e760  size=8  body=[[0800e760, 0800e767]]

void FUN_0800e760(void)

{
  FUN_0800e75c();
  return;
}


// ===================================================================
// FUN_0800e768 @ 0x0800e768  size=2  body=[[0800e768, 0800e769]]

void FUN_0800e768(void)

{
  return;
}


// ===================================================================
// FUN_0800e76a @ 0x0800e76a  size=12  body=[[0800e76a, 0800e775]]

void FUN_0800e76a(void)

{
  thunk_FUN_0800c6d4();
  FUN_0800e768();
  return;
}


// ===================================================================
// FUN_0800e776 @ 0x0800e776  size=18  body=[[0800e776, 0800e787]]

void FUN_0800e776(undefined4 param_1,ushort param_2,undefined4 param_3)

{
  FUN_0800eccc(param_1,param_2,param_3);
  FUN_0800d4b8();
  FUN_08010c70();
  return;
}


// ===================================================================
// FUN_0800e788 @ 0x0800e788  size=28  body=[[0800e788, 0800e7a3]]

void FUN_0800e788(void)

{
  undefined4 extraout_r2;
  undefined6 uVar1;
  
  thunk_FUN_080124d8();
  FUN_08011668();
  uVar1 = FUN_0800ee58();
  FUN_0800e776((int)uVar1,(ushort)((uint6)uVar1 >> 0x20),extraout_r2);
  FUN_080118d8();
  FUN_0800cd38();
  return;
}


// ===================================================================
// FUN_0800e7a4 @ 0x0800e7a4  size=20  body=[[0800e7a4, 0800e7b7]]

void FUN_0800e7a4(void)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  FUN_080120d0();
  FUN_080119dc();
  FUN_0801189c(0,extraout_r1,extraout_r2);
  return;
}


// ===================================================================
// FUN_0800e7b8 @ 0x0800e7b8  size=240  body=[[0800e7b8, 0800e8a7]]

void FUN_0800e7b8(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r2;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  uint *puVar10;
  uint uVar11;
  bool bVar12;
  longlong lVar13;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar2 = FUN_0800e73c();
  iVar3 = 0;
  uVar7 = extraout_r1;
  if (iVar2 == 0) {
LAB_0800e7c4:
    FUN_0800e6c8(iVar3,uVar7);
  }
  else {
    FUN_0800ee8c();
    uVar7 = 0;
    piVar9 = &DAT_200016d4;
    do {
      iVar2 = *piVar9;
      iVar3 = FUN_0800ed20(uVar7 & 0xff);
      if (uVar7 == 5) {
        uVar7 = extraout_r1_01;
        if (iVar2 == iVar3) goto LAB_0800e7c4;
        break;
      }
      uVar7 = uVar7 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar2 == iVar3);
    if ((int)((uint)DAT_200016f8 << 0x1e) < 0) {
      FUN_0800ed2c();
    }
    iVar3 = FUN_0800e760();
    uVar7 = 0;
    puVar10 = &DAT_200016d4;
    do {
      uVar4 = FUN_0800ed20(uVar7 & 0xff);
      uVar6 = *puVar10;
      if (uVar4 != uVar6) {
        uVar8 = 0;
        uVar11 = 1;
        do {
          if (((uVar6 ^ uVar4) & uVar11) != 0) {
            bVar12 = (uVar4 & uVar11) != 0;
            if (iVar3 != 0) {
              uVar5 = FUN_08012574();
              local_30 = CONCAT22((short)uVar5,CONCAT11((char)uVar7,(char)uVar8));
              local_2c._0_2_ = CONCAT11(bVar12,1);
              FUN_0800d50c(local_30,local_2c,extraout_r2,1);
            }
            FUN_08010060(uVar7 & 0xff,uVar8,(uint)bVar12);
          }
          uVar8 = uVar8 + 1 & 0xff;
          uVar11 = uVar11 << 1;
        } while (uVar8 != 0x12);
        *puVar10 = uVar4;
      }
      uVar7 = uVar7 + 1;
      puVar10 = puVar10 + 1;
    } while (uVar7 != 6);
    FUN_0800e700();
  }
  FUN_0800e7a4();
  FUN_08011058();
  bVar1 = FUN_080116d0();
  lVar13 = (ulonglong)extraout_r1_00 << 0x20;
  if (bVar1 != 0) {
    lVar13 = FUN_0800e718();
  }
  FUN_08011df0((int)lVar13,(int)((ulonglong)lVar13 >> 0x20));
  FUN_0800d4e0();
  return;
}


// ===================================================================
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


// ===================================================================
// keymap_key_to_keycode @ 0x0800ea64  size=58  body=[[0800ea64, 0800ea9d]]

// VERIFIED: col=key&0xff row=(key>>8)&0xff; row<6&&col<18 -> keycode_at_keymap_location; row==0xFD
// (KEYLOC_ENCODER_CW) && col==0 -> encodermap(clockwise=1); row==0xFC (KEYLOC_ENCODER_CCW) ->
// clockwise=0; else KC_NO

ushort keymap_key_to_keycode(uint param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_2 & 0xff;
  uVar2 = (param_2 & 0xffff) >> 8;
  if (uVar2 < 6) {
    if (uVar3 < 0x12) {
      uVar1 = keycode_at_keymap_location(param_1,uVar2,uVar3);
      return uVar1;
    }
  }
  else if (uVar2 == 0xfd) {
    if (uVar3 == 0) {
      uVar2 = 1;
LAB_0800ea86:
      uVar1 = keycode_at_encodermap_location(param_1,uVar3,uVar2);
      return uVar1;
    }
  }
  else if ((uVar2 == 0xfc) && (uVar3 == 0)) {
    uVar2 = 0;
    goto LAB_0800ea86;
  }
  return 0;
}


// ===================================================================
// FUN_0800ea9e @ 0x0800ea9e  size=22  body=[[0800ea9e, 0800eab3]]

uint FUN_0800ea9e(uint param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = keymap_key_to_keycode(param_1,param_2);
  uVar2 = FUN_0800e8b0((uint)uVar1);
  return uVar2;
}


// ===================================================================
// FUN_0800eab4 @ 0x0800eab4  size=250  body=[[0800eab4, 0800ead7] [0800eae0, 0800ebb5]]

uint FUN_0800eab4(uint param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if (0xe7 < param_1) {
    return param_1;
  }
  if (param_1 < 0xe0) {
    if (param_1 == 0x31) {
      uVar2 = 0x31;
      if (((byte)DAT_200047d4 & 0x40) != 0) {
        uVar2 = 0x2a;
      }
      return uVar2;
    }
    if (0x31 < param_1) {
      if ((param_1 == 0x39) || (param_1 == 0x82)) {
        if (((byte)DAT_200047d4 & 3) != 0) {
          return 0xe0;
        }
        bVar1 = DAT_200047d4._1_1_ & 8;
      }
      else {
        if (param_1 != 0x35) {
          return param_1;
        }
        bVar1 = (byte)DAT_200047d4 & 0x20;
      }
      if (bVar1 != 0) {
        param_1 = 0x29;
      }
      return param_1;
    }
    if (param_1 != 0x29) {
      if (param_1 != 0x2a) {
        return param_1;
      }
      uVar2 = 0x2a;
      if (((byte)DAT_200047d4 & 0x40) != 0) {
        uVar2 = 0x31;
      }
      return uVar2;
    }
    if ((int)((uint)(byte)DAT_200047d4 << 0x1a) < 0) {
      return 0x35;
    }
    uVar2 = 0x29;
    if ((DAT_200047d4._1_1_ & 8) != 0) {
      uVar2 = 0x39;
    }
    return uVar2;
  }
  switch(param_1) {
  case 0xe0:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1f) < 0) {
      return 0x39;
    }
    bVar1 = DAT_200047d4._1_1_ & 1;
    break;
  default:
    goto switchD_0800ead4_caseD_e1;
  case 0xe2:
    bVar1 = (byte)DAT_200047d4 & 4;
    break;
  case 0xe3:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1d) < 0) {
      return 0xe2;
    }
    if ((int)((uint)DAT_200047d4._1_1_ << 0x1f) < 0) {
      return 0xe0;
    }
    goto LAB_0800eb12;
  case 0xe4:
    iVar3 = (uint)DAT_200047d4._1_1_ << 0x1e;
    goto joined_r0x0800eb56;
  case 0xe6:
    iVar3 = (uint)(byte)DAT_200047d4 << 0x1c;
joined_r0x0800eb56:
    if (-1 < iVar3) {
      return param_1;
    }
LAB_0800eb44:
    if (((byte)DAT_200047d4 & 0x10) == 0) {
      uVar2 = 0xe7;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  case 0xe7:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1c) < 0) {
      return 0xe6;
    }
    if ((int)((uint)DAT_200047d4._1_1_ << 0x1e) < 0) {
      return 0xe4;
    }
    goto LAB_0800eb44;
  }
  if (bVar1 != 0) {
LAB_0800eb12:
    if (((byte)DAT_200047d4 & 0x10) == 0) {
      uVar2 = 0xe3;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  }
switchD_0800ead4_caseD_e1:
  return param_1;
}


// ===================================================================
// FUN_0800ebbc @ 0x0800ebbc  size=190  body=[[0800ebbc, 0800ec79]]

uint FUN_0800ebbc(uint param_1)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)DAT_200047d4;
  if (((int)(uVar1 << 0x1d) < 0) && (((param_1 & 0x14) == 4) != ((param_1 & 0x18) == 8))) {
    param_1 = param_1 ^ 0xc;
  }
  if (((int)(uVar1 << 0x1c) < 0) && (((param_1 & 0x14) == 0x14) != ((param_1 & 0x18) == 0x18))) {
    param_1 = param_1 ^ 0xc;
  }
  if (((int)((uint)DAT_200047d4._1_1_ << 0x1f) < 0) &&
     (((param_1 & 0x11) == 1) != ((param_1 & 0x18) == 8))) {
    param_1 = param_1 ^ 9;
  }
  if (((int)((uint)DAT_200047d4._1_1_ << 0x1e) < 0) &&
     (((param_1 & 0x11) == 0x11) != ((param_1 & 0x18) == 0x18))) {
    param_1 = param_1 ^ 9;
  }
  if ((int)(uVar1 << 0x1b) < 0) {
    param_1 = param_1 & 0xe7;
  }
  return param_1;
}


// ===================================================================
// FUN_0800ec80 @ 0x0800ec80  size=4  body=[[0800ec80, 0800ec83]]

undefined4 FUN_0800ec80(void)

{
  return 0;
}


// ===================================================================
// FUN_0800ec84 @ 0x0800ec84  size=4  body=[[0800ec84, 0800ec87]]

undefined4 FUN_0800ec84(void)

{
  return 0;
}


// ===================================================================
// FUN_0800ec88 @ 0x0800ec88  size=6  body=[[0800ec88, 0800ec8d]]

void FUN_0800ec88(undefined4 param_1)

{
  DAT_20000ea0 = param_1;
  return;
}


// ===================================================================
// thunk_FUN_0800e5cc @ 0x0800ec94  size=4  body=[[0800ec94, 0800ec97]]

void thunk_FUN_0800e5cc(void)

{
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  thunk_FUN_0800f244();
  FUN_0800f18c(0,0xffff,extraout_r2,in_r3);
  return;
}


// ===================================================================
// FUN_0800ec98 @ 0x0800ec98  size=42  body=[[0800ec98, 0800ecc1]]

void FUN_0800ec98(void)

{
  int iVar1;
  
  FUN_0800ee8c();
  FUN_08013a7a(4000);
  FUN_0800ee8c();
  iVar1 = FUN_0800ed20(0);
  if (iVar1 << 0x1e < 0) {
    thunk_FUN_0800e5cc();
    FUN_080125f0();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800ecc2 @ 0x0800ecc2  size=8  body=[[0800ecc2, 0800ecc9]]

void FUN_0800ecc2(void)

{
  FUN_0800ec98();
  return;
}


// ===================================================================
// FUN_0800eccc @ 0x0800eccc  size=52  body=[[0800eccc, 0800ecff]]

void FUN_0800eccc(undefined4 param_1,ushort param_2,undefined4 param_3)

{
  bool bVar1;
  ushort extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined8 uVar3;
  undefined4 uVar2;
  
  bVar1 = FUN_0800e5e0(param_1,param_2,param_3);
  uVar3 = CONCAT44(extraout_r1_00,(uint)bVar1);
  uVar2 = extraout_r2;
  if (bVar1 == 0) {
    uVar3 = thunk_FUN_0800e634(0,extraout_r1_00,extraout_r2);
    uVar2 = extraout_r2_00;
  }
  DAT_200016f8 = FUN_0800e5f4((int)uVar3,(uint3)((ulonglong)uVar3 >> 0x20),uVar2);
  DAT_200047d4 = FUN_0800e600((uint)DAT_200016f8,extraout_r1,extraout_r2_01);
  uVar3 = FUN_0800ecc2();
  FUN_0800e5fa((int)uVar3,(uint3)((ulonglong)uVar3 >> 0x20),extraout_r2_02);
  thunk_FUN_0800dbd0();
  FUN_0800dc1a();
  return;
}


// ===================================================================
// FUN_0800ed0c @ 0x0800ed0c  size=2  body=[[0800ed0c, 0800ed0d]]

void FUN_0800ed0c(void)

{
  return;
}


// ===================================================================
// FUN_0800ed0e @ 0x0800ed0e  size=8  body=[[0800ed0e, 0800ed15]]

void FUN_0800ed0e(void)

{
  FUN_0800ed0c();
  return;
}


// ===================================================================
// FUN_0800ed16 @ 0x0800ed16  size=2  body=[[0800ed16, 0800ed17]]

void FUN_0800ed16(void)

{
  return;
}


// ===================================================================
// FUN_0800ed18 @ 0x0800ed18  size=8  body=[[0800ed18, 0800ed1f]]

void FUN_0800ed18(void)

{
  FUN_0800ed16();
  return;
}


// ===================================================================
// FUN_0800ed20 @ 0x0800ed20  size=8  body=[[0800ed20, 0800ed27]]

undefined4 FUN_0800ed20(int param_1)

{
  return *(undefined4 *)(&DAT_200047f0 + param_1 * 4);
}


// ===================================================================
// FUN_0800ed2c @ 0x0800ed2c  size=2  body=[[0800ed2c, 0800ed2d]]

void FUN_0800ed2c(void)

{
  return;
}


// ===================================================================
// FUN_0800ed2e @ 0x0800ed2e  size=8  body=[[0800ed2e, 0800ed35]]

void FUN_0800ed2e(void)

{
  FUN_080135c8(0x1e0);
  return;
}


// ===================================================================
// FUN_0800ed36 @ 0x0800ed36  size=26  body=[[0800ed36, 0800ed4f]]

void FUN_0800ed36(void)

{
  return;
}


// ===================================================================
// FUN_0800ed50 @ 0x0800ed50  size=8  body=[[0800ed50, 0800ed57]]

void FUN_0800ed50(void)

{
  FUN_0800ed2e();
  return;
}


// ===================================================================
// FUN_0800ed58 @ 0x0800ed58  size=34  body=[[0800ed58, 0800ed79]]

void FUN_0800ed58(uint param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015338((uint *)(param_1 & 0xfffffff0),1 << (param_1 & 0xf),0x20);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_0800ed7c @ 0x0800ed7c  size=52  body=[[0800ed7c, 0800edaf]]

void FUN_0800ed7c(void)

{
  char cVar1;
  uint *puVar2;
  
  cVar1 = '\x12';
  puVar2 = &DAT_08016f34;
  do {
    if (*puVar2 != 0xffffffff) {
      FUN_0800ed58(*puVar2);
    }
    cVar1 = cVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\0');
  cVar1 = '\x06';
  puVar2 = &DAT_08016f7c;
  do {
    if (*puVar2 != 0xffffffff) {
      FUN_0800ed58(*puVar2);
    }
    cVar1 = cVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (cVar1 != '\0');
  return;
}


// ===================================================================
// FUN_0800edb8 @ 0x0800edb8  size=152  body=[[0800edb8, 0800ee4f]]

void FUN_0800edb8(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  uVar3 = (&DAT_08016f34)[param_2];
  if (uVar3 != 0xffffffff) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    uVar4 = 1 << (uVar3 & 0xf);
    FUN_08015338((uint *)(uVar3 & 0xfffffff0),uVar4,1);
    *(short *)((int)(uVar3 & 0xfffffff0) + 0x1a) = (short)uVar4;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    FUN_0800ed36();
    puVar2 = (uint *)(param_1 + -4);
    puVar5 = &DAT_08016f7c;
    do {
      uVar3 = *puVar5;
      puVar2 = puVar2 + 1;
      if ((uVar3 == 0xffffffff) ||
         ((int)((*(uint *)((uVar3 & 0xfffffff0) + 0x10) >> (uVar3 & 0xf)) << 0x1f) < 0)) {
        uVar3 = ~param_3 & *puVar2;
      }
      else {
        uVar3 = *puVar2 | param_3;
      }
      *puVar2 = uVar3;
      puVar5 = puVar5 + 1;
    } while ((uint *)(param_1 + 0x14) != puVar2);
    if ((&DAT_08016f34)[param_2] != 0xffffffff) {
      FUN_0800ed58((&DAT_08016f34)[param_2]);
    }
    FUN_0800ed50();
    return;
  }
  return;
}


// ===================================================================
// FUN_0800ee58 @ 0x0800ee58  size=42  body=[[0800ee58, 0800ee81]]

void FUN_0800ee58(void)

{
  FUN_0800ed7c();
  FUN_08008798(&DAT_200047f0,0,0x18);
  FUN_08008798((byte *)&DAT_200047d8,0,0x18);
  FUN_0800eef8(6);
  FUN_0800ed0e();
  return;
}


// ===================================================================
// FUN_0800ee8c @ 0x0800ee8c  size=98  body=[[0800ee8c, 0800eeed]]

undefined1 FUN_0800ee8c(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  FUN_08008798((byte *)&local_28,0,0x18);
  uVar4 = 0;
  uVar5 = 1;
  do {
    uVar3 = uVar4 & 0xff;
    uVar4 = uVar4 + 1;
    FUN_0800edb8((int)&local_28,uVar3,uVar5);
    uVar5 = uVar5 << 1;
  } while (uVar4 != 0x12);
  iVar2 = FUN_080089d4(&DAT_200047d8,&local_28,0x18);
  if (iVar2 != 0) {
    DAT_200047d8 = local_28;
    DAT_200047dc = uStack_24;
    DAT_200047e0 = uStack_20;
    DAT_200047e4 = uStack_1c;
    DAT_200047e8 = local_18;
    DAT_200047ec = uStack_14;
  }
  uVar1 = FUN_0800ef30(0x200047d8,0x200047f0,6,(uint)(iVar2 != 0));
  FUN_0800ed18();
  return uVar1;
}


// ===================================================================
// FUN_0800eef8 @ 0x0800eef8  size=30  body=[[0800eef8, 0800ef15]]

void FUN_0800eef8(int param_1)

{
  DAT_20001700 = (byte *)FUN_08008970(param_1 * 0x12);
  FUN_08008798(DAT_20001700,0,param_1 * 0x12);
  return;
}


// ===================================================================
// FUN_0800ef1c @ 0x0800ef1c  size=16  body=[[0800ef1c, 0800ef2b]]

void FUN_0800ef1c(void)

{
  FUN_08008980(DAT_20001700);
  DAT_20001700 = 0;
  return;
}


// ===================================================================
// FUN_0800ef30 @ 0x0800ef30  size=284  body=[[0800ef30, 0800f04b]]

undefined1 FUN_0800ef30(int param_1,int param_2,uint param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char cVar9;
  uint uVar10;
  int iVar11;
  char cVar12;
  uint uVar13;
  char cVar14;
  
  cVar9 = DAT_200016fb;
  DAT_200016f9 = 0;
  if (DAT_200016fb == '\0') {
    cVar9 = '\0';
    if (param_4 == 0) goto LAB_0800ef92;
  }
  else {
    iVar3 = FUN_08012508();
    uVar5 = iVar3 - DAT_200016fc;
    DAT_200016fc = iVar3;
    if (uVar5 < 0x100) {
      if (uVar5 != 0) goto LAB_0800ef5e;
    }
    else {
      uVar5 = 0xff;
LAB_0800ef5e:
      DAT_200016fb = '\0';
      DAT_200016fa = '\0';
      cVar12 = '\0';
      cVar14 = '\0';
      iVar3 = DAT_20001700;
      for (uVar6 = 0; (uVar6 & 0xff) < param_3; uVar6 = uVar6 + 1) {
        pbVar8 = (byte *)(iVar3 + -1);
        do {
          pbVar8 = pbVar8 + 1;
          bVar1 = *pbVar8;
          if (bVar1 != 0) {
            if ((uVar5 & 0xff) < (uint)bVar1) {
              *pbVar8 = bVar1 - (char)uVar5;
              cVar14 = cVar9;
            }
            else {
              *pbVar8 = 0;
              cVar12 = cVar9;
            }
          }
        } while (pbVar8 != (byte *)(iVar3 + 0x11));
        iVar3 = iVar3 + 0x12;
      }
      if (cVar12 != '\0') {
        DAT_200016fa = '\x01';
      }
      if (cVar14 != '\0') {
        DAT_200016fb = '\x01';
      }
    }
    if (param_4 != 0) goto LAB_0800efa0;
LAB_0800ef92:
    if (DAT_200016fa == '\0') {
      return DAT_200016f9;
    }
    if (cVar9 != '\0') goto LAB_0800efa0;
  }
  DAT_200016fc = FUN_08012508();
LAB_0800efa0:
  iVar3 = DAT_20001700;
  DAT_200016fa = 0;
  puVar4 = (uint *)(param_2 + -4);
  bVar2 = false;
  for (uVar5 = 0; iVar11 = uVar5 * 0x12 + iVar3, (uVar5 & 0xff) < param_3; uVar5 = uVar5 + 1) {
    uVar6 = puVar4[1];
    uVar10 = uVar6 ^ *(uint *)(param_1 + uVar5 * 4);
    uVar7 = 0;
    do {
      uVar13 = 1 << (uVar7 & 0xff);
      if (((uVar10 & uVar13) != 0) && (*(char *)(iVar11 + uVar7) == '\0')) {
        *(undefined1 *)(iVar11 + uVar7) = 0x14;
        uVar6 = uVar6 ^ uVar13;
        bVar2 = true;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 != 0x12);
    puVar4 = puVar4 + 1;
    *puVar4 = uVar6;
  }
  if (bVar2) {
    DAT_200016f9 = 1;
    DAT_200016fb = '\x01';
  }
  return DAT_200016f9;
}


// ===================================================================
// FUN_0800f060 @ 0x0800f060  size=26  body=[[0800f060, 0800f071] [08012c98, 08012c9f]]

void FUN_0800f060(void)

{
  FUN_08012c6c();
  FUN_0800e788();
  FUN_08012120(DAT_2000206c);
  return;
}


// ===================================================================
// FUN_0800f072 @ 0x0800f072  size=18  body=[[0800f072, 0800f083]]

void FUN_0800f072(void)

{
  thunk_FUN_08012a98();
  FUN_0800e7b8();
  FUN_08012ca8();
  return;
}


// ===================================================================
// FUN_0800f084 @ 0x0800f084  size=28  body=[[0800f084, 0800f09f]]

void FUN_0800f084(void)

{
  FUN_08012490();
  thunk_FUN_0801243c();
  FUN_0800e740();
  FUN_0800f060();
  do {
    FUN_0800f072();
    FUN_0800e76a();
  } while( true );
}


// ===================================================================
// FUN_0800f0a0 @ 0x0800f0a0  size=30  body=[[0800f0a0, 0800f0bd]]

undefined1 FUN_0800f0a0(int param_1,uint3 param_2,undefined4 param_3)

{
  undefined1 auStack_c [4];
  undefined4 uStack_8;
  
  auStack_c[3] = 0;
  auStack_c._0_3_ = param_2;
  uStack_8 = param_3;
  FUN_0800f1cc((undefined4 *)(auStack_c + 3),param_1,1);
  return auStack_c[3];
}


// ===================================================================
// FUN_0800f0be @ 0x0800f0be  size=30  body=[[0800f0be, 0800f0db]]

undefined2 FUN_0800f0be(int param_1,ushort param_2,undefined4 param_3)

{
  undefined1 auStack_c [4];
  undefined4 uStack_8;
  
  auStack_c._2_2_ = 0;
  auStack_c._0_2_ = param_2;
  uStack_8 = param_3;
  FUN_0800f1cc((undefined4 *)(auStack_c + 2),param_1,2);
  return auStack_c._2_2_;
}


// ===================================================================
// FUN_0800f0dc @ 0x0800f0dc  size=26  body=[[0800f0dc, 0800f0f5]]

undefined4 FUN_0800f0dc(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_c;
  undefined4 uStack_8;
  
  local_c = 0;
  uStack_8 = param_3;
  FUN_0800f1cc(&local_c,param_1,4);
  return local_c;
}


// ===================================================================
// FUN_0800f0f6 @ 0x0800f0f6  size=24  body=[[0800f0f6, 0800f10d]]

void FUN_0800f0f6(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_9 [5];
  
  local_9._1_4_ = param_3;
  FUN_0800f1d6((int *)local_9,param_1,1);
  return;
}


// ===================================================================
// FUN_0800f10e @ 0x0800f10e  size=24  body=[[0800f10e, 0800f125]]

void FUN_0800f10e(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_a [6];
  
  local_a._2_4_ = param_3;
  FUN_0800f1d6((int *)local_a,param_1,2);
  return;
}


// ===================================================================
// FUN_0800f126 @ 0x0800f126  size=22  body=[[0800f126, 0800f13b]]

void FUN_0800f126(uint param_1,int param_2,undefined4 param_3)

{
  int local_c;
  undefined4 uStack_8;
  
  local_c = param_2;
  uStack_8 = param_3;
  FUN_0800f1d6(&local_c,param_1,4);
  return;
}


// ===================================================================
// FUN_0800f13c @ 0x0800f13c  size=52  body=[[0800f13c, 0800f16f]]

void FUN_0800f13c(int *param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  int iStack_18;
  
  iVar1 = -(param_3 + 7 & 0xfffffff8);
  iStack_18 = param_4;
  FUN_0800f1cc((undefined4 *)((int)&iStack_18 + iVar1),param_2,param_3);
  iVar1 = FUN_080089d4(param_1,(int *)((int)&iStack_18 + iVar1),param_3);
  if (iVar1 != 0) {
    FUN_0800f1d6(param_1,param_2,param_3);
  }
  return;
}


// ===================================================================
// FUN_0800f170 @ 0x0800f170  size=28  body=[[0800f170, 0800f18b]]

void FUN_0800f170(uint param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  undefined4 extraout_r2;
  
  bVar1 = FUN_0800f0a0(param_1,(uint3)param_2,param_3);
  if (bVar1 != param_2) {
    FUN_0800f0f6(param_1,param_2,extraout_r2);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800f18c @ 0x0800f18c  size=28  body=[[0800f18c, 0800f1a7]]

void FUN_0800f18c(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  undefined4 extraout_r2;
  
  uVar1 = FUN_0800f0be(param_1,(ushort)param_2,param_3);
  if (uVar1 != param_2) {
    FUN_0800f10e(param_1,param_2,extraout_r2);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800f1a8 @ 0x0800f1a8  size=28  body=[[0800f1a8, 0800f1c3]]

void FUN_0800f1a8(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = FUN_0800f0dc(param_1,param_2,param_3);
  if (iVar1 != param_2) {
    FUN_0800f126(param_1,param_2,extraout_r2);
    return;
  }
  return;
}


// ===================================================================
// thunk_FUN_0800f460 @ 0x0800f1c4  size=4  body=[[0800f1c4, 0800f1c7]]

int thunk_FUN_0800f460(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char cVar1;
  int iVar2;
  uint extraout_r1;
  uint uVar3;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r2;
  uint uVar4;
  uint extraout_r2_00;
  uint extraout_r2_01;
  uint extraout_r3;
  uint uVar5;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  uint uStack_24;
  undefined1 auStack_20 [4];
  uint uStack_1c;
  
  uStack_24 = param_2;
  auStack_20 = (undefined1  [4])param_3;
  uStack_1c = param_4;
  FUN_0800f1e0();
  iVar2 = FUN_0800f5f4();
  if (iVar2 != 0) {
    cVar1 = FUN_0800f29c(0,0x20001704,0x200);
    if (cVar1 != '\0') {
      lVar10 = FUN_080115f0(0x20001704,0x800);
      FUN_0800f29c(0x800,(int)auStack_20,2);
      if (lVar10 != CONCAT44(uStack_1c,auStack_20)) {
        FUN_0800f1e0();
      }
      uVar6 = 0x808;
      do {
        cVar1 = FUN_0800f67c(uVar6,&uStack_24);
        iVar2 = 0;
        uVar3 = extraout_r1;
        uVar4 = extraout_r2;
        uVar5 = extraout_r3;
        uVar8 = uVar6;
        if (cVar1 == '\0') goto LAB_0800f524;
        uVar5 = uStack_24;
        if (uStack_24 == 0) break;
        uVar8 = uVar6 + 4;
        auStack_20 = (undefined1  [4])uStack_24;
        uVar3 = uStack_24 & 0xff;
        if ((uStack_24 & 0xc0) != 0) {
LAB_0800f54a:
          iVar2 = 0;
          goto LAB_0800f524;
        }
        uVar4 = uStack_24 & 0xff00;
        uVar7 = (uStack_24 & 7) << 0x10 | (uStack_24 & 0xffffff) >> 0x10 | uVar4;
        uVar5 = uVar7 + (uVar3 >> 3);
        uVar9 = uVar3 >> 3;
        if (0x800 < uVar5) goto LAB_0800f54a;
        if ((uStack_24 & 0x30) != 0) {
          cVar1 = FUN_0800f67c(uVar8,&uStack_1c);
          uVar3 = extraout_r1_00;
          uVar4 = extraout_r2_00;
          uVar5 = extraout_r3_00;
          if (cVar1 == '\0') goto LAB_0800f54a;
          uVar8 = uVar6 + 8;
        }
        memcpy((undefined4 *)(&DAT_20001704 + uVar7),(undefined4 *)(auStack_20 + 3),uVar9);
        uVar3 = extraout_r1_01;
        uVar4 = extraout_r2_01;
        uVar5 = extraout_r3_01;
        uVar6 = uVar8;
      } while (uVar8 < 0x1000);
      iVar2 = 1;
LAB_0800f524:
      DAT_20001f04 = uVar8;
      if (iVar2 == 0) {
        cVar1 = FUN_0800f2e8(0,uVar3,uVar4,uVar5);
        iVar2 = (int)cVar1;
      }
      else {
        iVar2 = FUN_0800f354(iVar2,uVar3,uVar4);
      }
      if (iVar2 != 0) {
        return iVar2;
      }
      FUN_0800f1e0();
      return 0;
    }
    FUN_0800f1e0();
  }
  FUN_0800f1e0();
  return 0;
}


// ===================================================================
// thunk_FUN_0800f244 @ 0x0800f1c8  size=4  body=[[0800f1c8, 0800f1cb]]

uint thunk_FUN_0800f244(void)

{
  byte bVar1;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  uint uVar2;
  
  bVar1 = FUN_0800f200();
  uVar2 = (uint)bVar1;
  if (uVar2 == 0) {
    FUN_0800f220();
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0800f574(uVar2,extraout_r1,extraout_r2,extraout_r3);
    FUN_0800f1e0();
    if (uVar2 == 1) {
      iVar4 = FUN_0800f220();
      if (iVar4 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = uVar3 & 1;
      }
    }
  }
  return uVar3;
}


// ===================================================================
// FUN_0800f1cc @ 0x0800f1cc  size=10  body=[[0800f1cc, 0800f1d5]]

bool FUN_0800f1cc(undefined4 *param_1,int param_2,uint param_3)

{
  bool bVar1;
  
  bVar1 = FUN_0800f278(param_2,param_1,param_3);
  return bVar1;
}


// ===================================================================
// FUN_0800f1d6 @ 0x0800f1d6  size=206  body=[[0800f1d6, 0800f1df] [0800f394, 0800f457]]

uint FUN_0800f1d6(int *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar4;
  undefined4 extraout_r1;
  undefined4 uVar5;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar6;
  undefined4 extraout_r2_01;
  uint uVar7;
  undefined8 uVar8;
  undefined1 local_30 [4];
  int *local_2c;
  uint uStack_28;
  uint uVar3;
  
  if (param_2 + param_3 < 0x801) {
    local_30 = (undefined1  [4])param_2;
    local_2c = param_1;
    uStack_28 = param_3;
    iVar2 = FUN_080089d4(param_1,(int *)(&DAT_20001704 + param_2),param_3);
    if (iVar2 == 0) {
      return 1;
    }
    memcpy((undefined4 *)(&DAT_20001704 + param_2),param_1,param_3);
    bVar1 = FUN_0800f200();
    uVar3 = (uint)bVar1;
    uVar7 = uVar3;
    uVar5 = extraout_r1;
    uVar6 = extraout_r2;
    if (uVar3 == 0) {
      FUN_0800f220();
    }
    else {
      while (param_3 != 0) {
        uVar7 = param_3;
        if (4 < param_3) {
          uVar7 = 5;
        }
        local_2c = (int *)0x0;
        local_30[1] = (char)(param_2 >> 8);
        local_30[0] = (byte)((param_2 << 0xd) >> 0x1d) | (byte)(uVar7 << 3);
        local_30[2] = (char)param_2;
        local_30[3] = 0;
        memcpy((undefined4 *)(local_30 + 3),param_1,uVar7);
        uVar8 = FUN_0800f36c((uint)local_30);
        uVar5 = (undefined4)((ulonglong)uVar8 >> 0x20);
        uVar4 = (uint)uVar8;
        if (uVar4 != 1) {
LAB_0800f44a:
          if ((uVar4 & 0xfd) != 0) {
            uVar4 = 0;
          }
          goto LAB_0800f3d8;
        }
        uVar6 = extraout_r2_00;
        if (param_3 != 1) {
          uVar8 = FUN_0800f36c((uint)local_2c);
          uVar5 = (undefined4)((ulonglong)uVar8 >> 0x20);
          uVar4 = (uint)uVar8;
          uVar6 = extraout_r2_01;
          if (uVar4 != 1) goto LAB_0800f44a;
        }
        param_2 = param_2 + uVar7;
        param_1 = (int *)((int)param_1 + uVar7);
        param_3 = param_3 - uVar7;
        uVar7 = 1;
      }
      uVar4 = FUN_0800f354(uVar7,uVar5,uVar6);
LAB_0800f3d8:
      if (uVar3 != 1) {
        return uVar4;
      }
      iVar2 = FUN_0800f220();
      if (iVar2 != 0) {
        return uVar4;
      }
    }
  }
  return 0;
}


// ===================================================================
// FUN_0800f1e0 @ 0x0800f1e0  size=26  body=[[0800f1e0, 0800f1f9]]

void FUN_0800f1e0(void)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_20001704,0,0x800);
  *(undefined4 *)(iVar1 + 0x800) = 0x808;
  return;
}


// ===================================================================
// FUN_0800f200 @ 0x0800f200  size=28  body=[[0800f200, 0800f21b]]

undefined1 FUN_0800f200(void)

{
  bool bVar1;
  undefined1 uVar2;
  
  if (DAT_20001f08 == '\0') {
    bVar1 = FUN_0800f55c();
    uVar2 = 0;
    if (bVar1) {
      uVar2 = 1;
      DAT_20001f08 = '\x01';
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}


// ===================================================================
// FUN_0800f220 @ 0x0800f220  size=30  body=[[0800f220, 0800f23d]]

undefined4 FUN_0800f220(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_20001f08 == '\0') {
    uVar2 = 2;
  }
  else {
    iVar1 = FUN_0800f5e4();
    uVar2 = 0;
    if (iVar1 != 0) {
      DAT_20001f08 = '\0';
      uVar2 = 1;
    }
  }
  return uVar2;
}


// ===================================================================
// FUN_0800f244 @ 0x0800f244  size=50  body=[[0800f244, 0800f275]]

uint FUN_0800f244(void)

{
  byte bVar1;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  uint uVar2;
  
  bVar1 = FUN_0800f200();
  uVar2 = (uint)bVar1;
  if (uVar2 == 0) {
    FUN_0800f220();
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0800f574(uVar2,extraout_r1,extraout_r2,extraout_r3);
    FUN_0800f1e0();
    if (uVar2 == 1) {
      iVar4 = FUN_0800f220();
      if (iVar4 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = uVar3 & 1;
      }
    }
  }
  return uVar3;
}


// ===================================================================
// FUN_0800f278 @ 0x0800f278  size=30  body=[[0800f278, 0800f295]]

bool FUN_0800f278(int param_1,undefined4 *param_2,uint param_3)

{
  bool bVar1;
  
  bVar1 = param_1 + param_3 < 0x801;
  if (bVar1) {
    memcpy(param_2,(undefined4 *)(&DAT_20001704 + param_1),param_3);
  }
  return bVar1;
}


// ===================================================================
// FUN_0800f29c @ 0x0800f29c  size=38  body=[[0800f29c, 0800f2c1]]

undefined1 FUN_0800f29c(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (iVar2 == param_3) {
      return 1;
    }
    cVar1 = FUN_0800f67c(param_1 + iVar2 * 4,(uint *)(param_2 + iVar2 * 4));
    if (cVar1 == '\0') break;
    iVar2 = iVar2 + 1;
  }
  return 0;
}


// ===================================================================
// FUN_0800f2c2 @ 0x0800f2c2  size=38  body=[[0800f2c2, 0800f2e7]]

bool FUN_0800f2c2(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (iVar2 == param_3) {
      return true;
    }
    bVar1 = FUN_0800f5b4(param_1 + iVar2 * 4,*(uint *)(param_2 + iVar2 * 4));
    if (!bVar1) break;
    iVar2 = iVar2 + 1;
  }
  return bVar1;
}


// ===================================================================
// FUN_0800f2e8 @ 0x0800f2e8  size=92  body=[[0800f2e8, 0800f343]]

char FUN_0800f2e8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  char cVar4;
  undefined8 local_18;
  
  local_18._0_4_ = param_1;
  local_18._4_4_ = param_2;
  iVar3 = FUN_0800f574(param_1,param_2,param_3,param_4);
  cVar4 = '\0';
  if (iVar3 != 0) {
    cVar1 = FUN_0800f200();
    bVar2 = FUN_0800f2c2(0,0x20001704,0x200);
    cVar4 = '\0';
    if (bVar2) {
      local_18 = FUN_080115f0(0x20001704,0x800);
      bVar2 = FUN_0800f2c2(0x800,(int)&local_18,2);
      cVar4 = bVar2 << 1;
    }
    if (cVar1 == '\x01') {
      FUN_0800f220();
    }
    DAT_20001f04 = 0x808;
  }
  return cVar4;
}


// ===================================================================
// FUN_0800f354 @ 0x0800f354  size=20  body=[[0800f354, 0800f367]]

int FUN_0800f354(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  if (0xfff < DAT_20001f04) {
    cVar1 = FUN_0800f2e8(param_1,param_2,param_3,DAT_20001f04);
    return (int)cVar1;
  }
  return 1;
}


// ===================================================================
// FUN_0800f36c @ 0x0800f36c  size=36  body=[[0800f36c, 0800f38f]]

void FUN_0800f36c(uint param_1)

{
  bool bVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  bVar1 = FUN_0800f5b4(DAT_20001f04,param_1);
  if (bVar1 != 0) {
    DAT_20001f04 = DAT_20001f04 + 4;
    FUN_0800f354((uint)bVar1,extraout_r1,extraout_r2);
    return;
  }
  return;
}


// ===================================================================
// FUN_0800f460 @ 0x0800f460  size=240  body=[[0800f460, 0800f54f]]

int FUN_0800f460(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char cVar1;
  int iVar2;
  uint extraout_r1;
  uint uVar3;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r2;
  uint uVar4;
  uint extraout_r2_00;
  uint extraout_r2_01;
  uint extraout_r3;
  uint uVar5;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  uint local_24;
  undefined1 local_20 [4];
  uint uStack_1c;
  
  local_24 = param_2;
  local_20 = (undefined1  [4])param_3;
  uStack_1c = param_4;
  FUN_0800f1e0();
  iVar2 = FUN_0800f5f4();
  if (iVar2 != 0) {
    cVar1 = FUN_0800f29c(0,0x20001704,0x200);
    if (cVar1 != '\0') {
      lVar10 = FUN_080115f0(0x20001704,0x800);
      FUN_0800f29c(0x800,(int)local_20,2);
      if (lVar10 != CONCAT44(uStack_1c,local_20)) {
        FUN_0800f1e0();
      }
      uVar6 = 0x808;
      do {
        cVar1 = FUN_0800f67c(uVar6,&local_24);
        iVar2 = 0;
        uVar3 = extraout_r1;
        uVar4 = extraout_r2;
        uVar5 = extraout_r3;
        uVar8 = uVar6;
        if (cVar1 == '\0') goto LAB_0800f524;
        uVar5 = local_24;
        if (local_24 == 0) break;
        uVar8 = uVar6 + 4;
        local_20 = (undefined1  [4])local_24;
        uVar3 = local_24 & 0xff;
        if ((local_24 & 0xc0) != 0) {
LAB_0800f54a:
          iVar2 = 0;
          goto LAB_0800f524;
        }
        uVar4 = local_24 & 0xff00;
        uVar7 = (local_24 & 7) << 0x10 | (local_24 & 0xffffff) >> 0x10 | uVar4;
        uVar5 = uVar7 + (uVar3 >> 3);
        uVar9 = uVar3 >> 3;
        if (0x800 < uVar5) goto LAB_0800f54a;
        if ((local_24 & 0x30) != 0) {
          cVar1 = FUN_0800f67c(uVar8,&uStack_1c);
          uVar3 = extraout_r1_00;
          uVar4 = extraout_r2_00;
          uVar5 = extraout_r3_00;
          if (cVar1 == '\0') goto LAB_0800f54a;
          uVar8 = uVar6 + 8;
        }
        memcpy((undefined4 *)(&DAT_20001704 + uVar7),(undefined4 *)(local_20 + 3),uVar9);
        uVar3 = extraout_r1_01;
        uVar4 = extraout_r2_01;
        uVar5 = extraout_r3_01;
        uVar6 = uVar8;
      } while (uVar8 < 0x1000);
      iVar2 = 1;
LAB_0800f524:
      DAT_20001f04 = uVar8;
      if (iVar2 == 0) {
        cVar1 = FUN_0800f2e8(0,uVar3,uVar4,uVar5);
        iVar2 = (int)cVar1;
      }
      else {
        iVar2 = FUN_0800f354(iVar2,uVar3,uVar4);
      }
      if (iVar2 != 0) {
        return iVar2;
      }
      FUN_0800f1e0();
      return 0;
    }
    FUN_0800f1e0();
  }
  FUN_0800f1e0();
  return 0;
}


// ===================================================================
// FUN_0800f55c @ 0x0800f55c  size=18  body=[[0800f55c, 0800f56d]]

bool FUN_0800f55c(void)

{
  int iVar1;
  
  iVar1 = FUN_080140a4(0x20004a40,0);
  return iVar1 == 0;
}


// ===================================================================
// FUN_0800f574 @ 0x0800f574  size=54  body=[[0800f574, 0800f5a9]]

undefined4 FUN_0800f574(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  uVar2 = 0;
  uVar3 = 1;
  while (uVar2 < DAT_20000ea4) {
    uVar2 = uVar2 + 1;
    uVar4 = (**(code **)(*DAT_20001f10 + 0x14))(DAT_20001f10,uVar2);
    if (1 < (uint)uVar4) {
      uVar3 = 0;
    }
    uVar1 = FUN_08013ff4(DAT_20001f10,(uint)((ulonglong)uVar4 >> 0x20));
    if (1 < uVar1) {
      uVar3 = 0;
    }
  }
  return uVar3;
}


// ===================================================================
// FUN_0800f5b4 @ 0x0800f5b4  size=38  body=[[0800f5b4, 0800f5d9]]

bool FUN_0800f5b4(int param_1,uint param_2)

{
  int iVar1;
  uint local_14;
  
  local_14 = ~param_2;
  iVar1 = (**(code **)(*DAT_20001f10 + 0xc))
                    (DAT_20001f10,param_1 + DAT_20000ea8,4,&local_14,param_1);
  return iVar1 == 0;
}


// ===================================================================
// FUN_0800f5e4 @ 0x0800f5e4  size=12  body=[[0800f5e4, 0800f5ef]]

undefined4 FUN_0800f5e4(void)

{
  FUN_080140c0(0x20004a40);
  return 1;
}


// ===================================================================
// FUN_0800f5f4 @ 0x0800f5f4  size=110  body=[[0800f5f4, 0800f661]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_0800f5f4(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  DAT_20001f10 = &DAT_20004a40;
  FUN_0800f5e4();
  iVar1 = (**(code **)(*DAT_20001f10 + 4))();
  uVar4 = (uint)_DAT_1fff7a22;
  uVar3 = 0;
  uVar5 = 0;
  do {
    if (*(int *)(iVar1 + 8) - 1U <= uVar3) goto LAB_0800f642;
    uVar3 = uVar3 + 1;
    iVar2 = FUN_0801404a(DAT_20001f10,uVar3);
    uVar5 = uVar5 + iVar2;
  } while (uVar5 < 0x1000);
  DAT_20000ea4 = uVar3;
  DAT_20000ea8 = FUN_08014030(DAT_20001f10,1);
LAB_0800f642:
  if ((DAT_20000ea4 == 0xffff) || (uVar4 << 10 <= DAT_20000ea8)) {
    FUN_0801357c();
  }
  return 1;
}


// ===================================================================
// FUN_0800f67c @ 0x0800f67c  size=50  body=[[0800f67c, 0800f6ad]]

// WARNING: Removing unreachable block (ram,0x0800f6a2)

undefined1 FUN_0800f67c(int param_1,uint *param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)FUN_08014064(DAT_20001f10,DAT_20000ea8 + param_1);
  DAT_20001f0d = 0;
  DAT_20001f0c = 0;
  *param_2 = ~*puVar1;
  return 1;
}


// ===================================================================
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


// ===================================================================
// FUN_0800f7aa @ 0x0800f7aa  size=76  body=[[0800f7aa, 0800f7f5]]

uint FUN_0800f7aa(uint param_1)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (1 < param_1) {
    if (param_1 < 0x1ee1) {
      uVar2 = (param_1 >> 5) + 8 & 0xff;
    }
    else {
      uVar2 = 0xff;
    }
    uVar4 = 1;
    do {
      uVar3 = uVar4 + uVar2;
      sVar1 = (short)(uVar3 * 0x8000 >> 0x10);
      if (param_1 < (ushort)(sVar1 * sVar1)) {
        uVar2 = (uVar3 >> 1) - 1 & 0xff;
      }
      else {
        if ((int)uVar3 >> 1 == 0xff) {
          return 0xff;
        }
        uVar4 = (uVar3 >> 1) + 1 & 0xff;
      }
    } while (uVar4 <= uVar2);
    param_1 = uVar4 - 1;
  }
  return param_1 & 0xff;
}


// ===================================================================
// FUN_0800f7f8 @ 0x0800f7f8  size=30  body=[[0800f7f8, 0800f815]]

ushort FUN_0800f7f8(void)

{
  DAT_20000ec0 = DAT_20000ec0 * 0x805 + 0x3619;
  return DAT_20000ec0 + (DAT_20000ec0 >> 8) & 0xff;
}


// ===================================================================
// FUN_0800f81c @ 0x0800f81c  size=62  body=[[0800f81c, 0800f859]]

uint FUN_0800f81c(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  
  uVar2 = param_1;
  if ((param_1 & 0x40) != 0) {
    uVar2 = ~param_1 & 0xff;
  }
  uVar1 = (ushort)uVar2 & 0xf;
  if ((param_1 & 0x40) != 0) {
    uVar1 = uVar1 + 1;
  }
  uVar2 = (uVar2 & 0x3f) >> 4;
  uVar2 = (uint)(byte)(&DAT_08016f94)[uVar2 * 2] +
          ((int)(short)(ushort)(byte)(&DAT_08016f95)[uVar2 * 2] * (int)(short)uVar1 >> 4) & 0xff;
  if ((int)(param_1 << 0x18) < 0) {
    uVar2 = -uVar2 & 0xff;
  }
  return uVar2 ^ 0x80;
}


// ===================================================================
// FUN_0800f860 @ 0x0800f860  size=38  body=[[0800f860, 0800f885]]

uint FUN_0800f860(undefined4 param_1,undefined4 param_2,byte param_3)

{
  undefined3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)param_3 | (uStack_b & 0xff) << 8 | (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f888 @ 0x0800f888  size=50  body=[[0800f888, 0800f8b9]]

uint FUN_0800f888(undefined4 param_1,int param_2,char param_3)

{
  uint3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((&DAT_20000d73)[param_2 * 2] - param_3) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f8c0 @ 0x0800f8c0  size=50  body=[[0800f8c0, 0800f8f1]]

uint FUN_0800f8c0(undefined4 param_1,int param_2,char param_3)

{
  uint3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((&DAT_20000d74)[param_2 * 2] - param_3) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f8f8 @ 0x0800f8f8  size=80  body=[[0800f8f8, 0800f947]]

uint FUN_0800f8f8(undefined4 param_1,int param_2,char param_3)

{
  char cVar1;
  uint3 uStack_1b;
  
  cVar1 = (&DAT_20000d0c)[(param_2 + 0x34) * 2] + -0x20;
  if (cVar1 < '\0') {
    cVar1 = ' ' - (&DAT_20000d0c)[(param_2 + 0x34) * 2];
  }
  uStack_1b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((char)param_1 + ((&DAT_20000d0b)[(param_2 + 0x34) * 2] - param_3) + cVar1) |
         (uStack_1b & 0xff) << 8 | (uStack_1b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f94c @ 0x0800f94c  size=50  body=[[0800f94c, 0800f97d]]

uint FUN_0800f94c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,char param_5)

{
  undefined3 uStack_b;
  
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(param_5 + (char)((uint)(param_4 * 3) >> 1)) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f97e @ 0x0800f97e  size=72  body=[[0800f97e, 0800f9c5]]

uint FUN_0800f97e(undefined4 param_1,char param_2,int param_3,char param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined3 uStack_13;
  
  iVar2 = (int)param_2;
  if (iVar2 < 0) {
    iVar2 = (int)-param_2;
  }
  sVar1 = 0x38 - (short)iVar2;
  uVar3 = FUN_0800f7aa((int)sVar1 * (int)sVar1 + param_3 * param_3 & 0xffff);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(param_4 + (char)uVar3 + (char)(uVar3 << 1)) | (uStack_13 & 0xff) << 8 |
         (uStack_13 & 0xff00) << 8;
}


// ===================================================================
// FUN_0800f9c8 @ 0x0800f9c8  size=76  body=[[0800f9c8, 0800fa13]]

uint FUN_0800f9c8(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  char local_c;
  uint3 uStack_b;
  
  iVar1 = (param_4 + 0x34) * 2;
  iVar1 = param_3 * ((byte)(&DAT_20000d0c)[iVar1] - 0x20) +
          param_2 * ((byte)(&DAT_20000d0b)[iVar1] - 0x70);
  local_c = (char)param_1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x7f;
  }
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(local_c + (char)(iVar1 >> 7)) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800fa18 @ 0x0800fa18  size=76  body=[[0800fa18, 0800fa63]]

uint FUN_0800fa18(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  char local_c;
  uint3 uStack_b;
  
  iVar1 = (param_4 + 0x34) * 2;
  iVar1 = param_3 * ((byte)(&DAT_20000d0c)[iVar1] - 0x20) +
          param_2 * ((byte)(&DAT_20000d0b)[iVar1] - 0x70);
  local_c = (char)param_1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x3f;
  }
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(local_c + (char)(iVar1 >> 6)) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}


// ===================================================================
// FUN_0800fa68 @ 0x0800fa68  size=52  body=[[0800fa68, 0800fa9b]]

uint FUN_0800fa68(undefined4 param_1,byte param_2)

{
  byte bVar1;
  undefined4 local_c;
  
  bVar1 = (byte)((uint)((int)(short)(ushort)(byte)~param_2 *
                       (int)(short)(ushort)(byte)((uint)param_1 >> 0x10)) >> 8);
  local_c = (uint)CONCAT12(bVar1,(short)param_1);
  return local_c & 0xffff | (uint)bVar1 << 0x10;
}


// ===================================================================
// FUN_0800fa9c @ 0x0800fa9c  size=72  body=[[0800fa9c, 0800fae3]]

uint FUN_0800fa9c(uint param_1,undefined4 param_2,undefined4 param_3,short param_4,short param_5)

{
  uint uVar1;
  undefined4 local_c;
  
  uVar1 = (uint)(ushort)(param_5 + param_4 * 5);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~uVar1 & 0xff);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_c = param_1 & 0xffff;
  return local_c | (uVar1 & 0xff) << 0x10;
}


// ===================================================================
// FUN_0800fae4 @ 0x0800fae4  size=114  body=[[0800fae4, 0800fb55]]

uint FUN_0800fae4(uint param_1,short param_2,int param_3,uint param_4,ushort param_5)

{
  uint uVar1;
  undefined4 local_14;
  
  if (param_4 < 0x49) {
    uVar1 = param_5 - param_4 & 0xffff;
    if (0xfe < uVar1) {
      uVar1 = 0xff;
    }
  }
  else {
    uVar1 = 0xff;
  }
  if ((0x10 < (ushort)(param_2 + 8U)) && (0x10 < (param_3 + 8U & 0xffff))) {
    uVar1 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~uVar1 & 0xff);
  if (param_3 < 0) {
    param_3 = param_3 + 3;
  }
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_14 = CONCAT31((int3)(param_1 >> 8),DAT_20004809 + (char)(param_3 >> 2));
  local_14 = local_14 & 0xffff;
  return local_14 | (uVar1 & 0xff) << 0x10;
}


// ===================================================================
// FUN_0800fb5c @ 0x0800fb5c  size=78  body=[[0800fb5c, 0800fba9]]

uint FUN_0800fb5c(uint param_1,undefined4 param_2,undefined4 param_3,int param_4,ushort param_5)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_c;
  
  uVar2 = (uint)param_5 - param_4 & 0xffff;
  if (0xfe < uVar2) {
    uVar2 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~(uVar2 & 0xff) & 0xff);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_c = CONCAT31((int3)(param_1 >> 8),(char)uVar2 + (char)param_1);
  local_c = local_c & 0xffff;
  return local_c | (uVar1 & 0xff) << 0x10;
}


// ===================================================================
// FUN_0800fbaa @ 0x0800fbaa  size=68  body=[[0800fbaa, 0800fbed]]

uint FUN_0800fbaa(uint param_1,undefined4 param_2,undefined4 param_3,int param_4,ushort param_5)

{
  uint uVar1;
  undefined4 local_c;
  
  uVar1 = (uint)param_5 - param_4 & 0xffff;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  uVar1 = ((param_1 & 0xffffff) >> 0x10) + (~uVar1 & 0xff);
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  local_c = param_1 & 0xffff;
  return local_c | (uVar1 & 0xff) << 0x10;
}


// ===================================================================
// FUN_0800fbf0 @ 0x0800fbf0  size=10  body=[[0800fbf0, 0800fbf9]]

void FUN_0800fbf0(byte param_1)

{
  DAT_20001f1a = param_1 | DAT_20001f1a;
  return;
}


// ===================================================================
// FUN_0800fc00 @ 0x0800fc00  size=24  body=[[0800fc00, 0800fc17]]

bool FUN_0800fc00(void)

{
  bool bVar1;
  
  DAT_20001f1a = 1;
  bVar1 = FUN_0800f1cc((undefined4 *)&DAT_20004808,0x18,8);
  DAT_20001f1a = 0;
  return bVar1;
}


// ===================================================================
// FUN_0800fc20 @ 0x0800fc20  size=70  body=[[0800fc20, 0800fc65]]

uint FUN_0800fc20(int param_1,uint param_2)

{
  short sVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  
  if (param_1 != 0) {
    uVar2 = (ushort)(param_1 >> 0x1f);
    sVar1 = ((ushort)param_1 ^ uVar2) - uVar2;
    if ((int)param_2 < 0) {
      bVar4 = 0x60 - (char)((int)(((int)sVar1 + param_2) * 0x20) / (int)((int)sVar1 - param_2));
    }
    else {
      bVar4 = 0x20 - (char)((int)((param_2 - (int)sVar1) * 0x20) / (int)((int)sVar1 + param_2));
    }
    uVar3 = (uint)bVar4;
    if (param_1 < 0) {
      uVar3 = -uVar3 & 0xff;
    }
    return uVar3;
  }
  return (param_2 >> 0x1f) << 7;
}


// ===================================================================
// FUN_0800fc66 @ 0x0800fc66  size=70  body=[[0800fc66, 0800fcab]]

uint FUN_0800fc66(undefined4 param_1,uint param_2,int param_3,short param_4,byte param_5)

{
  byte bVar1;
  uint uVar2;
  undefined4 local_1c;
  
  uVar2 = FUN_0800fc20(param_3,param_2);
  bVar1 = (byte)((uint)param_1 >> 0x10);
  bVar1 = (byte)((uint)((int)(short)(((param_4 - (ushort)param_5) + (ushort)bVar1 & 0xff) -
                                     (short)uVar2 & 0xff) * (int)(short)(ushort)bVar1) >> 8);
  local_1c = (uint)CONCAT12(bVar1,(short)param_1);
  return local_1c & 0xffff | (uint)bVar1 << 0x10;
}


// ===================================================================
// FUN_0800fcac @ 0x0800fcac  size=48  body=[[0800fcac, 0800fcdb]]

uint FUN_0800fcac(undefined4 param_1,uint param_2,int param_3,char param_4)

{
  uint uVar1;
  undefined3 uStack_13;
  
  uVar1 = FUN_0800fc20(param_3,param_2);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((char)uVar1 + param_4) | (uStack_13 & 0xff) << 8 | (uStack_13 & 0xff00) << 8;
}


// ===================================================================
// FUN_0800fcdc @ 0x0800fcdc  size=54  body=[[0800fcdc, 0800fd11]]

uint FUN_0800fcdc(undefined4 param_1,uint param_2,int param_3,char param_4,char param_5)

{
  uint uVar1;
  undefined3 uStack_13;
  
  uVar1 = FUN_0800fc20(param_3,param_2);
  uStack_13 = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)((param_4 - param_5) - (char)uVar1) | (uStack_13 & 0xff) << 8 |
         (uStack_13 & 0xff00) << 8;
}


// ===================================================================
// FUN_0800fd14 @ 0x0800fd14  size=20  body=[[0800fd14, 0800fd27]]

void FUN_0800fd14(void)

{
  int in_r3;
  
  FUN_0800f13c((int *)&DAT_20004808,0x18,8,in_r3);
  DAT_20001f1a = 0;
  return;
}


// ===================================================================
// FUN_0800fd30 @ 0x0800fd30  size=18  body=[[0800f7a0, 0800f7a9] [0800fd30, 0800fd37]]

uint FUN_0800fd30(uint param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0800f6c0(param_1,1);
  return uVar1;
}


// ===================================================================
// FUN_0800fd38 @ 0x0800fd38  size=212  body=[[0800fd38, 0800fe0b]]

void FUN_0800fd38(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  
  bVar3 = (&DAT_20000d07)[param_2 + param_1 * 0x12];
  if (bVar3 != 0xff) {
    uVar7 = 0;
    do {
      uVar8 = 0;
      pbVar6 = &DAT_20001f4e + uVar7 * 0x12;
      iVar1 = (bVar3 + 0x34) * 2;
      pbVar5 = &DAT_20000d07 + uVar7 * 0x12;
      do {
        if (*pbVar5 != 0xff) {
          if ((param_1 == (uVar7 & 0xff)) && (param_2 == (uVar8 & 0xff))) {
            uVar4 = (byte)(&DAT_20001f4e)[param_2 + param_1 * 0x12] + 0x20;
            if (0xfe < uVar4) {
              uVar4 = 0xff;
            }
            (&DAT_20001f4e)[param_2 + param_1 * 0x12] = (char)uVar4;
          }
          else {
            iVar2 = (*pbVar5 + 0x34) * 2;
            uVar4 = FUN_0800f7aa(((uint)(byte)(&DAT_20000d0b)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0b)[iVar2]) *
                                 ((uint)(byte)(&DAT_20000d0b)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0b)[iVar2]) +
                                 ((uint)(byte)(&DAT_20000d0c)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0c)[iVar2]) *
                                 ((uint)(byte)(&DAT_20000d0c)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0c)[iVar2]) & 0xffff);
            if (uVar4 < 0x29) {
              uVar4 = 0x28 - uVar4 & 0xffff;
              if (0xf < uVar4) {
                uVar4 = 0x10;
              }
              uVar4 = (uint)*pbVar6 + (uVar4 & 0xff);
              if (0xfe < uVar4) {
                uVar4 = 0xff;
              }
              *pbVar6 = (byte)uVar4;
            }
          }
        }
        uVar8 = uVar8 + 1;
        pbVar6 = pbVar6 + 1;
        pbVar5 = pbVar5 + 1;
      } while (uVar8 != 0x12);
      uVar7 = uVar7 + 1;
    } while (uVar7 != 6);
  }
  return;
}


// ===================================================================
// FUN_0800fe14 @ 0x0800fe14  size=34  body=[[0800fe14, 0800fe35]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0800fe14(void)

{
  DAT_20004808 = 0x41;
  memcpy((undefined4 *)&DAT_20004809,(undefined4 *)&DAT_08016710,3);
  _DAT_2000480c = 0xff7f;
  FUN_0800fd14();
  return;
}


// ===================================================================
// FUN_0800fe40 @ 0x0800fe40  size=4  body=[[0800fe40, 0800fe43]]

undefined4 FUN_0800fe40(void)

{
  return 0;
}


// ===================================================================
// FUN_0800fe44 @ 0x0800fe44  size=34  body=[[0800fe44, 0800fe65]]

uint FUN_0800fe44(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0800fe40();
  if ((&DAT_20000d07)[param_2 + param_1 * 0x12] != -1) {
    *(undefined1 *)(param_3 + uVar1) = (&DAT_20000d07)[param_2 + param_1 * 0x12];
    uVar1 = uVar1 + 1 & 0xff;
  }
  return uVar1;
}


// ===================================================================
// thunk_FUN_080114fc @ 0x0800fe6c  size=6  body=[[0800fe6c, 0800fe71]]

void thunk_FUN_080114fc(void)

{
  FUN_080114fc();
  return;
}


// ===================================================================
// FUN_0800fe78 @ 0x0800fe78  size=14  body=[[0800fe78, 0800fe85]]

void FUN_0800fe78(uint param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  FUN_08011338(param_1,param_2,param_3,param_4);
  return;
}


// ===================================================================
// FUN_0800fe8c @ 0x0800fe8c  size=78  body=[[0800fe8c, 0800fed9]]

void FUN_0800fe8c(uint param_1,byte param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 local_10;
  
  if ((param_2 & (&DAT_20000e23)[param_1]) != 0) {
    uVar1 = FUN_0800f7f8();
    uVar2 = FUN_0800f7f8();
    local_10._3_1_ = (undefined1)(param_1 >> 0x18);
    local_10._0_3_ =
         CONCAT12(DAT_2000480b,
                  CONCAT11((char)((int)((uint)uVar2 << 0x10) >> 0x11) + '\x7f',(char)uVar1));
    uVar3 = FUN_0800fd30(local_10);
    FUN_0800fe78(param_1,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    return;
  }
  return;
}


// ===================================================================
// thunk_FUN_08011378 @ 0x0800fee4  size=6  body=[[0800fee4, 0800fee9]]

void thunk_FUN_08011378(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  FUN_08011378(param_1,param_2,param_3);
  return;
}


// ===================================================================
// FUN_0800fef0 @ 0x0800fef0  size=342  body=[[0800fef0, 08010045]]

undefined4 FUN_0800fef0(int param_1)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  byte *pbVar4;
  char cVar5;
  byte bVar6;
  undefined1 uVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  ulonglong uVar14;
  byte local_30 [12];
  
  bVar2 = DAT_2000480b;
  uVar9 = (uint)DAT_2000480b;
  uVar1 = (int)(uVar9 * 3) >> 2;
  if (*(char *)(param_1 + 2) != '\0') {
    thunk_FUN_08011378(0,0,0);
    FUN_08008798(&DAT_20001f4e,0,0x6c);
    DAT_20001f19 = '\0';
  }
  pbVar13 = &DAT_20001f4e;
  DAT_20001f18 = DAT_20001f18 + 1;
  uVar10 = 0;
  do {
    uVar12 = 0;
    pbVar11 = pbVar13;
    do {
      if ((DAT_20001f19 == '\0' && (uVar12 & 0xff) == 0) &&
         (uVar14 = FUN_080084ac(), (int)uVar14 < 0x5555555)) {
        *pbVar13 = bVar2;
      }
      else {
        bVar6 = *pbVar11;
        if ((bVar6 != 0) && ((bVar6 < uVar9 && ((uint)DAT_20001f18 == 0xff / uVar9)))) {
          *pbVar11 = bVar6 - 1;
        }
      }
      uVar3 = FUN_0800fe44(uVar12 & 0xff,uVar10,(int)local_30);
      if (uVar3 != 0) {
        bVar6 = *pbVar11;
        if (uVar9 * 3 >> 2 < (uint)bVar6) {
          uVar7 = (undefined1)((int)(uVar1 * (bVar6 - uVar1)) / (int)(uVar9 - uVar1));
          bVar6 = bVar2;
        }
        else {
          uVar7 = 0;
          bVar6 = (byte)((uint)((int)(short)(ushort)bVar2 * (int)(short)(ushort)bVar6) / uVar1);
        }
        FUN_0800fe78((uint)local_30[0],uVar7,bVar6,uVar7);
      }
      uVar12 = uVar12 + 1;
      pbVar11 = pbVar11 + 0x12;
    } while (uVar12 != 6);
    uVar10 = uVar10 + 1 & 0xff;
    pbVar13 = pbVar13 + 1;
  } while (uVar10 != 0x12);
  if ((uint)DAT_20001f18 == 0xff / uVar9) {
    DAT_20001f18 = 0;
  }
  DAT_20001f19 = DAT_20001f19 + 1;
  if (0x1c < DAT_20001f19) {
    DAT_20001f19 = 0;
    cVar8 = '\x05';
    pbVar13 = &DAT_20001fa8;
    do {
      pbVar4 = &DAT_20001fa8;
      cVar5 = '\x12';
      pbVar11 = pbVar13;
      do {
        if ((cVar8 == '\x05') && (uVar9 == *pbVar4)) {
          *pbVar4 = bVar2 - 1;
        }
        cVar5 = cVar5 + -1;
        if (uVar9 <= pbVar11[-0x12]) {
          pbVar11[-0x12] = bVar2 - 1;
          *pbVar11 = bVar2;
        }
        pbVar11 = pbVar11 + 1;
        pbVar4 = pbVar4 + 1;
      } while (cVar5 != '\0');
      cVar8 = cVar8 + -1;
      pbVar13 = pbVar13 + -0x12;
    } while (cVar8 != '\0');
  }
  return 0;
}


// ===================================================================
// FUN_08010060 @ 0x08010060  size=250  body=[[08010060, 08010159]]

void FUN_08010060(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte *local_34;
  byte abStack_30 [12];
  
  iVar5 = FUN_0800e75c();
  if (iVar5 != 0) {
    DAT_20001f48 = 0;
    if (param_3 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = FUN_0800fe44(param_1,param_2,(int)abStack_30);
    }
    if (8 < (int)(DAT_20001f1b + uVar6)) {
      uVar9 = 8 - uVar6;
      memcpy((undefined4 *)&DAT_20001f1c,(undefined4 *)(&DAT_20001f1c + uVar6),uVar9);
      memcpy((undefined4 *)&DAT_20001f24,(undefined4 *)(&DAT_20001f24 + uVar6),uVar9);
      memcpy((undefined4 *)&DAT_20001f34,(undefined4 *)(&DAT_20001f34 + (short)uVar6 * 2),uVar9 * 2)
      ;
      memcpy((undefined4 *)&DAT_20001f2c,(undefined4 *)(&DAT_20001f2c + uVar6),uVar9);
      DAT_20001f1b = (byte)uVar9;
    }
    bVar4 = DAT_20001f1b;
    uVar10 = (uint)DAT_20001f1b;
    iVar7 = 0;
    local_34 = abStack_30;
    for (uVar9 = 0; uVar8 = uVar10 + (uVar9 & 0xff) & 0xff, (uVar9 & 0xff) < uVar6;
        uVar9 = uVar9 + 1) {
      bVar3 = *local_34;
      iVar7 = (bVar3 + 0x34) * 2;
      iVar1 = (uVar8 + 0xc) * 2;
      uVar2 = (&DAT_20000d0c)[iVar7];
      (&DAT_20001f1c)[uVar8] = (&DAT_20000d0b)[iVar7];
      (&DAT_20001f24)[uVar8] = uVar2;
      (&DAT_20001f2c)[uVar8] = bVar3;
      (&DAT_20001f1c)[iVar1] = 0;
      (&DAT_20001f1d)[iVar1] = 0;
      iVar7 = iVar5;
      local_34 = local_34 + 1;
    }
    if (iVar7 != 0) {
      DAT_20001f1b = (char)uVar6 + bVar4;
    }
    if ((param_3 != 0) && ((DAT_20004808 & 0xfc) == 0x40)) {
      FUN_0800fd38(param_1,param_2);
    }
  }
  return;
}


// ===================================================================
// FUN_0801016c @ 0x0801016c  size=2  body=[[0801016c, 0801016d]]

void FUN_0801016c(void)

{
  return;
}


// ===================================================================
// FUN_0801016e @ 0x0801016e  size=12  body=[[0801016e, 08010179]]

void FUN_0801016e(void)

{
  FUN_0800b800();
  FUN_0801016c();
  return;
}


// ===================================================================
// FUN_0801017a @ 0x0801017a  size=4  body=[[0801017a, 0801017d]]

undefined4 FUN_0801017a(void)

{
  return 1;
}


// ===================================================================
// FUN_0801017e @ 0x0801017e  size=40  body=[[0801017e, 080101a5]]

uint FUN_0801017e(char param_1)

{
  uint uVar1;
  
  uVar1 = (byte)(param_1 * '\x12') + 0x12 & 0xff;
  if (0x57 < uVar1) {
    uVar1 = 0x58;
  }
  return (uint)(byte)(param_1 * '\x12') | uVar1 << 8;
}


// ===================================================================
// FUN_080101a8 @ 0x080101a8  size=206  body=[[080101a8, 08010275]]

bool FUN_080101a8(char *param_1,undefined *param_2)

{
  byte bVar1;
  short sVar2;
  undefined3 uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  uint local_2c;
  
  uVar4 = FUN_0801017e(*param_1);
  uVar9 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 1;
  uVar8 = uVar4 & 0xff;
  uVar4 = (uVar4 & 0xffff) >> 8;
  puVar7 = &DAT_20000d07 + uVar8 * 2;
  for (; (uVar8 & 0xff) < uVar4; uVar8 = uVar8 + 1) {
    if (((&DAT_20000e23)[uVar8] & param_1[1]) != 0) {
      sVar6 = (byte)puVar7[0x6c] - 0x70;
      sVar2 = (byte)puVar7[0x6d] - 0x20;
      uVar5 = FUN_0800f7aa((uint)(ushort)(sVar2 * sVar2 + sVar6 * sVar6));
      uVar3 = (*(code *)param_2)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                                 (int)sVar6,(int)sVar2,uVar5,(bVar1 * uVar9 & 0xffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar3);
      uVar5 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar8,(char)(uVar5 >> 8),(char)uVar5,(char)(uVar5 >> 0x10));
    }
    puVar7 = puVar7 + 2;
  }
  return uVar4 < 0x58;
}


// ===================================================================
// FUN_08010284 @ 0x08010284  size=6  body=[[08010284, 08010289]]

bool FUN_08010284(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_080101a8(param_1,(undefined *)0x800fc67);
  return bVar1;
}


// ===================================================================
// FUN_08010290 @ 0x08010290  size=6  body=[[08010290, 08010295]]

bool FUN_08010290(undefined1 *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_080101a8(param_1,(undefined *)0x800f94d);
  return bVar1;
}


// ===================================================================
// FUN_0801029c @ 0x0801029c  size=6  body=[[0801029c, 080102a1]]

bool FUN_0801029c(undefined1 *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_080101a8(param_1,(undefined *)0x800fcdd);
  return bVar1;
}


// ===================================================================
// FUN_080102a8 @ 0x080102a8  size=170  body=[[080102a8, 08010351]]

bool FUN_080102a8(char *param_1)

{
  byte bVar1;
  undefined3 uVar2;
  uint uVar3;
  uint uVar4;
  code *extraout_r1;
  uint uVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint local_2c;
  
  uVar3 = FUN_0801017e(*param_1);
  uVar5 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 1;
  uVar7 = uVar3 & 0xff;
  uVar3 = (uVar3 & 0xffff) >> 8;
  puVar6 = &DAT_20000d07 + uVar7 * 2;
  for (; (uVar7 & 0xff) < uVar3; uVar7 = uVar7 + 1) {
    if (((&DAT_20000e23)[uVar7] & param_1[1]) != 0) {
      uVar2 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (byte)puVar6[0x6c] - 0x70,(byte)puVar6[0x6d] - 0x20,
                             (uVar5 * bVar1 & 0xffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar2);
      uVar4 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar7,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
    }
    puVar6 = puVar6 + 2;
  }
  return uVar3 < 0x58;
}


// ===================================================================
// FUN_08010360 @ 0x08010360  size=6  body=[[08010360, 08010365]]

bool FUN_08010360(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_080102a8(param_1);
  return bVar1;
}


// ===================================================================
// FUN_0801036c @ 0x0801036c  size=6  body=[[0801036c, 08010371]]

bool FUN_0801036c(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_080102a8(param_1);
  return bVar1;
}


// ===================================================================
// FUN_08010378 @ 0x08010378  size=138  body=[[08010378, 08010401]]

bool FUN_08010378(char *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  undefined3 uVar2;
  uint uVar3;
  uint uVar4;
  code *extraout_r1;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar7 = param_1;
  uVar3 = FUN_0801017e(*param_1);
  uVar5 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 2;
  uVar6 = (uVar3 & 0xffff) >> 8;
  for (uVar3 = uVar3 & 0xff; (uVar3 & 0xff) < uVar6; uVar3 = uVar3 + 1) {
    if (((&DAT_20000e23)[uVar3] & param_1[1]) != 0) {
      uVar2 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             uVar3 & 0xff,(bVar1 * uVar5 + uVar5 & 0xffff) >> 8,
                             CONCAT11(DAT_2000480a,DAT_20004809),pcVar7,param_2,param_3,param_4);
      param_4 = CONCAT13((char)(param_4 >> 0x18),uVar2);
      uVar4 = FUN_0800fd30(param_4);
      FUN_0800fe78(uVar3,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
    }
  }
  return uVar6 < 0x58;
}


// ===================================================================
// FUN_08010410 @ 0x08010410  size=6  body=[[08010410, 08010415]]

bool FUN_08010410(char *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = FUN_08010378(param_1,0x800f861,param_3,param_4);
  return bVar1;
}


// ===================================================================
// FUN_0801041c @ 0x0801041c  size=6  body=[[0801041c, 08010421]]

bool FUN_0801041c(undefined1 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = FUN_08010378(param_1,0x800f889,param_3,param_4);
  return bVar1;
}


// ===================================================================
// FUN_08010428 @ 0x08010428  size=6  body=[[08010428, 0801042d]]

bool FUN_08010428(undefined1 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = FUN_08010378(param_1,0x800f8c1,param_3,param_4);
  return bVar1;
}


// ===================================================================
// FUN_08010434 @ 0x08010434  size=6  body=[[08010434, 08010439]]

bool FUN_08010434(undefined1 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = FUN_08010378(param_1,0x800f8f9,param_3,param_4);
  return bVar1;
}


// ===================================================================
// FUN_08010440 @ 0x08010440  size=180  body=[[08010440, 080104f3]]

bool FUN_08010440(char *param_1)

{
  undefined3 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  code *extraout_r1;
  uint uVar6;
  uint uVar7;
  uint local_2c;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar6 = ((uint)(ushort)DAT_20004810 * (uint)(DAT_2000480c >> 2) & 0xffff) >> 8;
  uVar7 = (uVar2 & 0xffff) >> 8;
  uVar3 = FUN_0800f81c(uVar6 + 0x40 & 0xff);
  uVar4 = FUN_0800f81c(uVar6);
  for (uVar2 = uVar2 & 0xff; (uVar2 & 0xff) < uVar7; uVar2 = uVar2 + 1) {
    if (((&DAT_20000e23)[uVar2] & param_1[1]) != 0) {
      uVar1 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (int)(char)((char)uVar3 + -0x80),(int)(char)((char)uVar4 + -0x80),
                             uVar2 & 0xff,uVar6);
      local_2c = CONCAT13(local_2c._3_1_,uVar1);
      uVar5 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar2,(char)(uVar5 >> 8),(char)uVar5,(char)(uVar5 >> 0x10));
    }
  }
  return uVar7 < 0x58;
}


// ===================================================================
// FUN_08010500 @ 0x08010500  size=6  body=[[08010500, 08010505]]

bool FUN_08010500(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010440(param_1);
  return bVar1;
}


// ===================================================================
// FUN_0801050c @ 0x0801050c  size=6  body=[[0801050c, 08010511]]

bool FUN_0801050c(undefined1 *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010440(param_1);
  return bVar1;
}


// ===================================================================
// FUN_08010518 @ 0x08010518  size=208  body=[[08010518, 080105e7]]

bool FUN_08010518(char *param_1)

{
  undefined3 uVar1;
  uint uVar2;
  uint uVar3;
  code *extraout_r1;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint local_2c;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar5 = DAT_2000480c + 1;
  uVar7 = (uVar2 & 0xffff) >> 8;
  uVar2 = uVar2 & 0xff;
  if (0xfe < uVar5) {
    uVar5 = 0xff;
  }
  for (; (uVar2 & 0xff) < uVar7; uVar2 = uVar2 + 1) {
    if (((&DAT_20000e23)[uVar2] & param_1[1]) != 0) {
      iVar6 = (int)(char)(DAT_20004814 + -1);
      while ((uVar3 = 0xffff / uVar5, -1 < iVar6 << 0x18 &&
             (((uint)(byte)(&DAT_20004825)[iVar6] != (uVar2 & 0xff) ||
              (uVar3 = (uint)*(ushort *)(&DAT_20004815 + (iVar6 + 0xc) * 2),
              0xffff / uVar5 <= (uint)*(ushort *)(&DAT_20004815 + (iVar6 + 0xc) * 2)))))) {
        iVar6 = iVar6 + -1;
      }
      uVar4 = DAT_2000480c + 1;
      if (0xfe < uVar4) {
        uVar4 = 0xff;
      }
      uVar1 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (uVar3 * uVar4 & 0xffffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar1);
      uVar3 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar2,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    }
  }
  return uVar7 < 0x58;
}


// ===================================================================
// FUN_080105f8 @ 0x080105f8  size=6  body=[[080105f8, 080105fd]]

bool FUN_080105f8(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010518(param_1);
  return bVar1;
}


// ===================================================================
// FUN_08010604 @ 0x08010604  size=284  body=[[08010604, 0801071f]]

bool FUN_08010604(uint param_1,char *param_2,undefined *param_3)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  undefined1 *puVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  undefined4 local_30;
  
  uVar2 = FUN_0801017e(*param_2);
  uVar7 = (uint)DAT_20004814;
  uVar9 = uVar2 & 0xff;
  puVar8 = &DAT_20000d07 + uVar9 * 2;
  uVar2 = (uVar2 & 0xffff) >> 8;
  for (; (uVar9 & 0xff) < uVar2; uVar9 = uVar9 + 1) {
    if (((&DAT_20000e23)[uVar9] & param_2[1]) != 0) {
      memcpy(&local_30,(undefined4 *)&DAT_20004809,3);
      uVar5 = 0;
      pbVar10 = &DAT_20004814 + param_1;
      for (uVar3 = param_1; (uVar3 & 0xff) < uVar7; uVar3 = uVar3 + 1) {
        sVar1 = (ushort)(byte)puVar8[0x6c] - (ushort)pbVar10[1];
        sVar6 = (ushort)(byte)puVar8[0x6d] - (ushort)pbVar10[9];
        uVar4 = FUN_0800f7aa((uint)(ushort)(sVar1 * sVar1 + sVar6 * sVar6));
        uVar11 = DAT_2000480c + 1;
        local_30._0_3_ = CONCAT12((char)uVar5,(undefined2)local_30);
        if (0xfe < uVar11) {
          uVar11 = 0xff;
        }
        uVar5 = (*(code *)param_3)(local_30,(int)sVar1,(int)sVar6,uVar4,
                                   (*(ushort *)(&DAT_20004815 + (uVar3 + 0xc) * 2) * uVar11 &
                                   0xffffff) >> 8);
        local_30._0_2_ = (undefined2)uVar5;
        uVar5 = (uVar5 & 0xffffff) >> 0x10;
        pbVar10 = pbVar10 + 1;
      }
      local_30._0_3_ =
           CONCAT12((char)((uint)((int)(short)(ushort)DAT_2000480b * (int)(short)uVar5) >> 8),
                    (undefined2)local_30);
      uVar3 = FUN_0800fd30(local_30);
      FUN_0800fe78(uVar9,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    }
    puVar8 = puVar8 + 2;
  }
  return uVar2 < 0x58;
}


// ===================================================================
// FUN_08010730 @ 0x08010730  size=10  body=[[08010730, 08010739]]

bool FUN_08010730(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010604(0,param_1,(undefined *)0x800fa9d);
  return bVar1;
}


// ===================================================================
// FUN_08010740 @ 0x08010740  size=10  body=[[08010740, 08010749]]

bool FUN_08010740(undefined1 *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010604(0,param_1,(undefined *)0x800fae5);
  return bVar1;
}


// ===================================================================
// FUN_08010750 @ 0x08010750  size=20  body=[[08010750, 08010763]]

bool FUN_08010750(undefined1 *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010604(DAT_20004814 - 1 & ~((int)(DAT_20004814 - 1) >> 0x1f) & 0xff,param_1,
                       (undefined *)0x800fb5d);
  return bVar1;
}


// ===================================================================
// FUN_0801076c @ 0x0801076c  size=20  body=[[0801076c, 0801077f]]

bool FUN_0801076c(char *param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08010604(DAT_20004814 - 1 & ~((int)(DAT_20004814 - 1) >> 0x1f) & 0xff,param_1,
                       (undefined *)0x800fbab);
  return bVar1;
}


// ===================================================================
// FUN_08010788 @ 0x08010788  size=106  body=[[08010788, 080107f1]]

bool FUN_08010788(char *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = FUN_0801017e(*param_1);
  uVar3 = (uVar1 & 0xffff) >> 8;
  uVar2 = FUN_0800fd30((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)));
  for (uVar1 = uVar1 & 0xff; (uVar1 & 0xff) < uVar3; uVar1 = uVar1 + 1) {
    if (((&DAT_20000e23)[uVar1] & param_1[1]) != 0) {
      FUN_0800fe78(uVar1,(char)(uVar2 >> 8),(char)uVar2,(char)(uVar2 >> 0x10));
    }
  }
  return uVar3 < 0x58;
}


// ===================================================================
// FUN_080107fc @ 0x080107fc  size=166  body=[[080107fc, 080108a1]]

bool FUN_080107fc(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  uVar2 = FUN_0801017e(*param_1);
  uVar5 = uVar2 & 0xff;
  uVar4 = (uVar2 & 0xffff) >> 8;
  memcpy(&local_20,(undefined4 *)&DAT_20004809,3);
  bVar1 = DAT_2000480b;
  uVar2 = FUN_0800f81c(((uint)(DAT_2000480c >> 3) * (uint)(ushort)DAT_20004810 & 0xffff) >> 8);
  iVar3 = (int)(char)((char)uVar2 + -0x80);
  if (iVar3 < 0) {
    iVar3 = (int)(char)(-0x80 - (char)uVar2);
  }
  local_20._0_3_ =
       CONCAT12((char)((uint)((int)(short)((ushort)(iVar3 << 1) & 0xff) * (int)(short)(ushort)bVar1)
                      >> 8),(undefined2)local_20);
  uVar2 = FUN_0800fd30(local_20);
  local_1c._0_3_ = (undefined3)uVar2;
  for (; (uVar5 & 0xff) < uVar4; uVar5 = uVar5 + 1) {
    if (((&DAT_20000e23)[uVar5] & param_1[1]) != 0) {
      FUN_0800fe78(uVar5,local_1c._1_1_,(undefined1)local_1c,local_1c._2_1_);
    }
  }
  return uVar4 < 0x58;
}


// ===================================================================
// FUN_080108b0 @ 0x080108b0  size=104  body=[[080108b0, 08010917]]

bool FUN_080108b0(char *param_1)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar3 = uVar2 & 0xff;
  uVar2 = (uVar2 & 0xffff) >> 8;
  if (param_1[2] == '\0') {
    uVar3 = DAT_2000480c + 0x10;
    if (0xfe < uVar3) {
      uVar3 = 0xff;
    }
    if ((((ushort)DAT_20004810 * uVar3 & 0xffffff) >> 8) % 5 == 0) {
      uVar1 = FUN_0800f7f8();
      FUN_0800fe8c((short)uVar1 * 0x58 >> 8,param_1[1]);
    }
  }
  else {
    for (; (int)uVar3 < (int)uVar2; uVar3 = uVar3 + 1) {
      FUN_0800fe8c(uVar3,param_1[1]);
    }
  }
  return uVar2 < 0x58;
}


// ===================================================================
// FUN_08010920 @ 0x08010920  size=280  body=[[08010920, 08010a37]]

bool FUN_08010920(char *param_1)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  short sVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined4 local_30;
  
  uVar1 = FUN_0801017e(*param_1);
  uVar6 = (uVar1 & 0xffff) >> 8;
  if (param_1[2] != '\0') {
    thunk_FUN_08011378(0,0,0);
    FUN_08008798(&DAT_20001f4e,0,0x6c);
  }
  if (*param_1 == '\0') {
    uVar2 = FUN_0801257e((uint)DAT_20001fbc);
    DAT_20001fba = 0x18 < uVar2;
    if ((bool)DAT_20001fba) {
      uVar2 = FUN_08012574();
      DAT_20001fbc = (ushort)uVar2;
    }
  }
  iVar7 = 0;
  bVar8 = 0;
  do {
    cVar3 = '\x12';
    pbVar9 = &DAT_20001f4e + iVar7;
    pbVar10 = &DAT_20000d07 + iVar7;
    do {
      uVar2 = local_30;
      uVar5 = (uint)*pbVar10;
      if (((uVar1 & 0xff) <= uVar5) && (uVar5 < uVar6)) {
        if (((&DAT_20000e23)[uVar5] & param_1[1]) != 0) {
          uVar5 = (uint)*pbVar9;
          sVar4 = (short)(uVar5 + 0xaa);
          if (0xfe < uVar5 + 0xaa) {
            sVar4 = 0xff;
          }
          local_30._3_1_ = SUB41(uVar2,3);
          local_30._0_3_ =
               CONCAT12((char)((uint)((int)(short)(sVar4 * 3 + 2U & 0xff) *
                                     (int)(short)(ushort)DAT_2000480b) >> 8),
                        CONCAT11(DAT_2000480a,
                                 -0x56 - ((byte)(uVar5 - 0x55) &
                                         ~(byte)((int)(uVar5 - 0x55) >> 0x1f))));
          uVar2 = FUN_0800fd30(local_30);
          FUN_0800fe78((uint)*pbVar10,(char)(uVar2 >> 8),(char)uVar2,(char)(uVar2 >> 0x10));
          if (DAT_20001fba != '\0') {
            *pbVar9 = (byte)(uVar5 - 1) & ~(byte)((int)(uVar5 - 1) >> 0x1f);
          }
        }
        bVar8 = bVar8 + 1;
      }
      cVar3 = cVar3 + -1;
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
    } while (cVar3 != '\0');
  } while ((iVar7 != 0x5a) && (iVar7 = iVar7 + 0x12, bVar8 < 0x12));
  return uVar6 < 0x58;
}


// ===================================================================
// FUN_08010a4c @ 0x08010a4c  size=456  body=[[08010a4c, 08010a91] [08010aaa, 08010c2b]]

void FUN_08010a4c(uint param_1,undefined4 param_2,uint param_3)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 extraout_r1;
  uint uVar5;
  uint extraout_r2;
  undefined1 uVar6;
  uint uVar7;
  uint extraout_r3;
  undefined4 local_28;
  
  if (DAT_20000eb4 == param_1) {
    DAT_20000eb3 = '\0';
    if ((DAT_20004808 & 3) != DAT_20000eb5) {
      DAT_20000eb3 = '\x01';
    }
  }
  else {
    DAT_20000eb3 = '\x01';
  }
  uVar5 = (uint)DAT_20000eb2;
  uVar7 = (uint)DAT_2000480d;
  if (uVar5 != uVar7) {
    DAT_20000eb2 = DAT_2000480d;
    thunk_FUN_08011378(0,0,0);
    param_2 = extraout_r1;
    uVar5 = extraout_r2;
    uVar7 = extraout_r3;
  }
  switch(param_1) {
  case 0:
    if (DAT_20000eb3 != '\0') {
      thunk_FUN_08011378(0,0,0);
      FUN_0801016e();
    }
  default:
    uVar5 = 0;
    break;
  case 1:
    bVar1 = FUN_08010788(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 2:
    bVar1 = FUN_080107fc(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 3:
    bVar1 = FUN_08010284(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 4:
    bVar1 = FUN_08010410(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 5:
    bVar1 = FUN_0801041c(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 6:
    bVar1 = FUN_08010428(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 7:
    bVar1 = FUN_08010434(&DAT_20000eb1,param_2,uVar5,uVar7);
    uVar5 = (uint)bVar1;
    break;
  case 8:
    bVar1 = FUN_08010290(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 9:
    bVar1 = FUN_08010360(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 10:
    bVar1 = FUN_0801036c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xb:
    bVar1 = FUN_0801029c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xc:
    bVar1 = FUN_08010500(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xd:
    bVar1 = FUN_0801050c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xe:
    bVar1 = FUN_080108b0(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0xf:
    uVar5 = FUN_0801017e(DAT_20000eb1);
    if (DAT_20001f14 < DAT_20004810) {
      uVar2 = FUN_0800f7f8();
      uVar7 = (short)uVar2 * 0x58 >> 8;
      if (((&DAT_20000e23)[uVar7] & DAT_20000eb2) != 0) {
        uVar2 = FUN_0800f7f8();
        if ((int)((uint)uVar2 << 0x1e) < 0) {
          local_28 = param_3 & 0xffff0000;
          uVar6 = 0;
        }
        else {
          uVar2 = FUN_0800f7f8();
          uVar3 = FUN_0800f7f8();
          local_28._2_2_ = (undefined2)(param_3 >> 0x10);
          local_28._0_2_ = CONCAT11((char)((int)((uint)uVar3 << 0x10) >> 0x11) + '\x7f',(char)uVar2)
          ;
          uVar6 = DAT_2000480b;
        }
        local_28._0_3_ = CONCAT12(uVar6,(undefined2)local_28);
        uVar4 = FUN_0800fd30(local_28);
        FUN_0800fe78(uVar7,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
        uVar7 = DAT_2000480c + 0x10;
        if (0xfe < uVar7) {
          uVar7 = 0xff;
        }
        DAT_20001f14 = 500 / (uVar7 >> 4) + DAT_20004810;
      }
    }
    uVar5 = (uint)((uVar5 & 0xffff) >> 8 < 0x58);
    break;
  case 0x10:
    bVar1 = FUN_08010920(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x11:
    uVar5 = FUN_0800fef0(0x20000eb1);
    break;
  case 0x12:
    bVar1 = FUN_080105f8(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x13:
    bVar1 = FUN_08010730(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x14:
    bVar1 = FUN_08010740(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x15:
    bVar1 = FUN_08010750(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
    break;
  case 0x16:
    bVar1 = FUN_0801076c(&DAT_20000eb1);
    uVar5 = (uint)bVar1;
  }
  DAT_20000eb1 = DAT_20000eb1 + '\x01';
  if (((uVar5 == 0) && (DAT_20000eb0 = 2, DAT_20000eb3 == '\0')) && (param_1 == 0)) {
    DAT_20000eb0 = 3;
  }
  return;
}


// ===================================================================
// FUN_08010c4c @ 0x08010c4c  size=8  body=[[08010c4c, 08010c53]]

void FUN_08010c4c(uint param_1,uint param_2)

{
  FUN_0800cf74(param_1,param_2);
  return;
}


// ===================================================================
// FUN_08010c54 @ 0x08010c54  size=28  body=[[08010c54, 08010c6f]]

void FUN_08010c54(char *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0801017e(*param_1 + -1);
  FUN_08010c4c(uVar1 & 0xff,(uVar1 & 0xffff) >> 8);
  return;
}


// ===================================================================
// FUN_08010c70 @ 0x08010c70  size=78  body=[[08010c70, 08010cbd]]

uint FUN_08010c70(void)

{
  bool bVar1;
  uint uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined6 uVar3;
  
  FUN_080114b0();
  DAT_20004814 = 0;
  DAT_20001f4d = 0;
  FUN_08008798(&DAT_2000482d,0xff,0x10);
  DAT_20001f1b = 0;
  uVar3 = FUN_08008798(&DAT_20001f34,0xff,0x10);
  bVar1 = FUN_0800e5e0((int)uVar3,(ushort)((uint6)uVar3 >> 0x20),extraout_r2);
  if (!bVar1) {
    thunk_FUN_0800e634(0,extraout_r1,extraout_r2_00);
    FUN_0800fe14();
  }
  bVar1 = FUN_0800fc00();
  if (DAT_20004808 < 4) {
    uVar2 = FUN_0800fe14();
    return uVar2;
  }
  return (uint)bVar1;
}


// ===================================================================
// FUN_08010cd4 @ 0x08010cd4  size=24  body=[[08010cd4, 08010ceb]]

void FUN_08010cd4(void)

{
  if ((DAT_20004808 & 3) != 0) {
    DAT_20000eb0 = 0;
  }
  DAT_20004808 = DAT_20004808 & 0xfc;
  return;
}


// ===================================================================
// FUN_08010cf4 @ 0x08010cf4  size=10  body=[[08010cf4, 08010cfd]]

byte FUN_08010cf4(void)

{
  return DAT_20004808 & 3;
}


// ===================================================================
// FUN_08010d04 @ 0x08010d04  size=50  body=[[08010d04, 08010d35]]

void FUN_08010d04(uint param_1,byte param_2)

{
  uint uVar1;
  
  if ((DAT_20004808 & 3) != 0) {
    if (param_1 == 0) {
      uVar1 = 1;
    }
    else if (param_1 < 0x17) {
      uVar1 = param_1 & 0x3f;
    }
    else {
      uVar1 = 0x16;
    }
    DAT_20004808 = DAT_20004808 & 3 | (byte)(uVar1 << 2);
    DAT_20000eb0 = 0;
    FUN_0800fbf0(param_2);
    return;
  }
  return;
}


// ===================================================================
// FUN_08010d40 @ 0x08010d40  size=6  body=[[08010d40, 08010d45]]

void FUN_08010d40(uint param_1)

{
  FUN_08010d04(param_1,1);
  return;
}


// ===================================================================
// FUN_08010d64 @ 0x08010d64  size=28  body=[[08010d48, 08010d5d] [08010d64, 08010d69]]

void FUN_08010d64(void)

{
  uint uVar1;
  
  uVar1 = (DAT_20004808 >> 2) + 1;
  if (0x16 < uVar1) {
    uVar1 = 1;
  }
  FUN_08010d04(uVar1,1);
  return;
}


// ===================================================================
// FUN_08010d8c @ 0x08010d8c  size=32  body=[[08010d6c, 08010d85] [08010d8c, 08010d91]]

void FUN_08010d8c(void)

{
  uint uVar1;
  
  uVar1 = (DAT_20004808 >> 2) - 1 & 0xff;
  if (uVar1 == 0) {
    uVar1 = 0x16;
  }
  FUN_08010d04(uVar1,1);
  return;
}


// ===================================================================
// FUN_08010d94 @ 0x08010d94  size=30  body=[[08010d94, 08010db1]]

void FUN_08010d94(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4)

{
  if ((DAT_20004808 & 3) != 0) {
    DAT_20004809 = param_1;
    DAT_2000480a = param_2;
    DAT_2000480b = param_3;
    FUN_0800fbf0(param_4);
    return;
  }
  return;
}


// ===================================================================
// FUN_08010dcc @ 0x08010dcc  size=22  body=[[08010db8, 08010dc7] [08010dcc, 08010dd1]]

void FUN_08010dcc(void)

{
  FUN_08010d94(DAT_20004809 + '\b',DAT_2000480a,DAT_2000480b,1);
  return;
}


// ===================================================================
// FUN_08010df0 @ 0x08010df0  size=30  body=[[08010dd4, 08010deb] [08010df0, 08010df5]]

void FUN_08010df0(void)

{
  FUN_08010d94(DAT_20004809 + -8,DAT_2000480a,DAT_2000480b,1);
  return;
}


// ===================================================================
// FUN_08010e1c @ 0x08010e1c  size=36  body=[[08010df8, 08010e15] [08010e1c, 08010e21]]

void FUN_08010e1c(void)

{
  uint uVar1;
  
  uVar1 = DAT_2000480a + 0x10;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  FUN_08010d94(DAT_20004809,(char)uVar1,DAT_2000480b,1);
  return;
}


// ===================================================================
// FUN_08010e44 @ 0x08010e44  size=34  body=[[08010e24, 08010e3f] [08010e44, 08010e49]]

void FUN_08010e44(void)

{
  FUN_08010d94(DAT_20004809,
               (byte)(DAT_2000480a - 0x10) & ~(byte)((int)(DAT_2000480a - 0x10) >> 0x1f),
               DAT_2000480b,1);
  return;
}


// ===================================================================
// FUN_08010e4c @ 0x08010e4c  size=44  body=[[08010e4c, 08010e77]]

void FUN_08010e4c(undefined4 param_1)

{
  uint uVar1;
  
  if ((DAT_20004808 & 3) == 0) {
    FUN_08010e7c(param_1);
    return;
  }
  uVar1 = DAT_2000480b + 0x10;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  FUN_08010d94(DAT_20004809,DAT_2000480a,(char)uVar1,(byte)param_1);
  return;
}


// ===================================================================
// FUN_08010e7c @ 0x08010e7c  size=46  body=[[08010e7c, 08010ea9]]

void FUN_08010e7c(undefined4 param_1)

{
  DAT_20004808 = DAT_20004808 ^ 1;
  DAT_20000eb0 = 0;
  FUN_0800fbf0((byte)param_1);
  while (((DAT_20004808 & 3) != 0 && (DAT_2000480b < 0x20))) {
    FUN_08010e4c(param_1);
  }
  return;
}


// ===================================================================
// FUN_08010eb4 @ 0x08010eb4  size=6  body=[[08010eb4, 08010eb9]]

void FUN_08010eb4(void)

{
  FUN_08010e7c(1);
  return;
}


// ===================================================================
// FUN_08010ebc @ 0x08010ebc  size=42  body=[[08010ebc, 08010ee5]]

void FUN_08010ebc(void)

{
  if ((DAT_20004808 & 3) == 0) {
    DAT_20000eb0 = DAT_20004808 & 3;
  }
  DAT_20004808 = DAT_20004808 & 0xfc | 1;
  while (DAT_2000480b < 0x20) {
    FUN_08010e4c(0);
  }
  return;
}


// ===================================================================
// FUN_08010ef0 @ 0x08010ef0  size=30  body=[[08010ef0, 08010f0d]]

void FUN_08010ef0(void)

{
  FUN_08010ebc();
  FUN_0800fbf0(1);
  while (DAT_2000480b < 0x20) {
    FUN_08010e4c(1);
  }
  return;
}


// ===================================================================
// FUN_08010f14 @ 0x08010f14  size=6  body=[[08010f14, 08010f19]]

void FUN_08010f14(void)

{
  FUN_08010e4c(1);
  return;
}


// ===================================================================
// FUN_08010f1c @ 0x08010f1c  size=50  body=[[08010f1c, 08010f4d]]

void FUN_08010f1c(undefined4 param_1)

{
  FUN_08010d94(DAT_20004809,DAT_2000480a,
               (byte)(DAT_2000480b - 0x10) & ~(byte)((int)(DAT_2000480b - 0x10) >> 0x1f),
               (byte)param_1);
  if (((DAT_20004808 & 3) != 0) && (DAT_2000480b < 0x21)) {
    FUN_08010e7c(param_1);
    return;
  }
  return;
}


// ===================================================================
// FUN_08010f54 @ 0x08010f54  size=6  body=[[08010f54, 08010f59]]

void FUN_08010f54(void)

{
  FUN_08010f1c(1);
  return;
}


// ===================================================================
// FUN_08010f74 @ 0x08010f74  size=24  body=[[08010f5c, 08010f6d] [08010f74, 08010f79]]

void FUN_08010f74(void)

{
  uint uVar1;
  
  uVar1 = DAT_2000480c + 0x10;
  if (0xfe < uVar1) {
    uVar1 = 0xff;
  }
  DAT_2000480c = (byte)uVar1;
  FUN_0800fbf0(1);
  return;
}


// ===================================================================
// FUN_08010f90 @ 0x08010f90  size=22  body=[[08010f7c, 08010f8b] [08010f90, 08010f95]]

void FUN_08010f90(void)

{
  DAT_2000480c = (byte)(DAT_2000480c - 0x10) & ~(byte)((int)(DAT_2000480c - 0x10) >> 0x1f);
  FUN_0800fbf0(1);
  return;
}


// ===================================================================
// FUN_08010f98 @ 0x08010f98  size=6  body=[[08010f98, 08010f9d]]

void FUN_08010f98(undefined4 param_1)

{
  DAT_20000eac = param_1;
  return;
}


// ===================================================================
// FUN_08010fa4 @ 0x08010fa4  size=8  body=[[08010fa4, 08010fab]]

void FUN_08010fa4(void)

{
  DAT_20001f48 = 0;
  return;
}


// ===================================================================
// FUN_08010fb0 @ 0x08010fb0  size=18  body=[[08010fb0, 08010fc1]]

bool FUN_08010fb0(void)

{
  return DAT_20000eac < DAT_20001f48;
}


// ===================================================================
// FUN_08010fcc @ 0x08010fcc  size=16  body=[[08010fcc, 08010fdb]]

void FUN_08010fcc(void)

{
  FUN_08011510();
  DAT_20001f4d = 1;
  return;
}


// ===================================================================
// FUN_08010fe4 @ 0x08010fe4  size=16  body=[[08010fe4, 08010ff3]]

void FUN_08010fe4(void)

{
  FUN_0801151c();
  DAT_20001f4d = 0;
  return;
}


// ===================================================================
// FUN_08010ffc @ 0x08010ffc  size=6  body=[[08010ffc, 08011001]]

undefined1 FUN_08010ffc(void)

{
  return DAT_20001f4d;
}


// ===================================================================
// FUN_08011008 @ 0x08011008  size=58  body=[[08011008, 08011041]]

void FUN_08011008(int param_1)

{
  uint uVar1;
  
  DAT_20000eb4 = (undefined1)param_1;
  DAT_20000eb5 = (byte)(((uint)DAT_20004808 << 0x1e) >> 0x1e);
  if (DAT_20001f4d != '\0') {
    FUN_08010fe4();
  }
  thunk_FUN_080114fc();
  if (((param_1 == 0) && (DAT_20001f4d == '\0')) && (uVar1 = FUN_0800b81c(), uVar1 != 0)) {
    FUN_08010fcc();
  }
  DAT_20000eb0 = 3;
  return;
}


// ===================================================================
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


// ===================================================================
// FUN_08011180 @ 0x08011180  size=28  body=[[08011180, 0801119b]]

void FUN_08011180(int param_1,undefined4 param_2,uint param_3)

{
  if ((param_1 != 0) && (DAT_20001f4c == '\0')) {
    FUN_08010a4c(0,param_2,param_3);
    FUN_08011008(0);
  }
  DAT_20001f4c = (char)param_1;
  return;
}


// ===================================================================
// FUN_080111a0 @ 0x080111a0  size=86  body=[[080111a0, 080111f5]]

char FUN_080111a0(uint param_1,byte param_2,undefined1 param_3,uint param_4,byte param_5)

{
  char cVar1;
  int iVar2;
  
  if (param_1 < 2) {
    cVar1 = FUN_080126e8(*(uint *)(&DAT_20000eb8 + param_1 * 4),0,0,0x10);
    if (cVar1 != '\0') {
      DAT_20001fbe = param_2 & 0xf | 0x20;
      DAT_20001fbf = param_3;
      iVar2 = FUN_080127c4(0x20001fbe,2);
      if ((iVar2 == 0) && (iVar2 = FUN_080127c4(param_4,(uint)param_5), iVar2 == 0)) {
        FUN_080127d8();
        return cVar1;
      }
    }
    FUN_080127d8();
  }
  return '\0';
}


// ===================================================================
// FUN_08011200 @ 0x08011200  size=24  body=[[08011200, 08011217]]

int FUN_08011200(uint param_1,byte param_2,undefined1 param_3)

{
  char cVar1;
  undefined1 local_9;
  
  cVar1 = FUN_080111a0(param_1,param_2,param_3,(uint)&local_9,1);
  return (int)cVar1;
}


// ===================================================================
// FUN_08011218 @ 0x08011218  size=42  body=[[08011218, 08011241]]

undefined4 FUN_08011218(uint param_1)

{
  if ((&DAT_20001ff2)[param_1] != '\0') {
    FUN_080111a0(param_1,1,0,(uint)(&DAT_2000483d + param_1 * 0xc0),0xc0);
  }
  (&DAT_20001ff2)[param_1] = 0;
  return 1;
}


// ===================================================================
// FUN_0801124c @ 0x0801124c  size=226  body=[[0801124c, 0801132d]]

void FUN_0801124c(uint param_1)

{
  undefined4 auStack_f4 [3];
  byte abStack_e8 [24];
  byte abStack_d0 [192];
  
  FUN_08015338((uint *)(*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xfffffff0),
               1 << (*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xf),1);
  *(short *)((*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xfffffff0) + 0x18) =
       (short)(1 << (*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xf));
  FUN_08011200(param_1,3,0);
  FUN_08011200(param_1,3,0x13);
  FUN_08011200(param_1,3,0x14);
  FUN_08011200(param_1,3,0x15);
  FUN_08011200(param_1,3,0x16);
  FUN_08011200(param_1,3,0x1a);
  FUN_08008798(abStack_e8,0,0x18);
  FUN_080111a0(param_1,0,0,(uint)abStack_e8,0x18);
  FUN_08008798(abStack_d0,0,0xc0);
  FUN_080111a0(param_1,1,0,(uint)abStack_d0,0xc0);
  memcpy(auStack_f4,(undefined4 *)"            ",0xc);
  FUN_080111a0(param_1,4,0,(uint)auStack_f4,0xc);
  FUN_08011200(param_1,3,0);
  return;
}


// ===================================================================
// FUN_08011338 @ 0x08011338  size=50  body=[[08011338, 08011369]]

void FUN_08011338(uint param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  
  if (param_1 < 0x58) {
    iVar1 = param_1 * 4;
    bVar2 = (&DAT_08016842)[iVar1];
    bVar3 = (&DAT_08016843)[iVar1];
    uVar4 = (byte)(&DAT_08016840)[param_1 * 4] & 3;
    (&DAT_2000483d)[(uint)(byte)(&DAT_08016841)[iVar1] + uVar4 * 0xc0] = param_2;
    (&DAT_2000483d)[(uint)bVar2 + uVar4 * 0xc0] = param_3;
    (&DAT_2000483d)[(uint)bVar3 + uVar4 * 0xc0] = param_4;
    (&DAT_20001ff2)[uVar4] = 1;
  }
  return;
}


// ===================================================================
// FUN_08011378 @ 0x08011378  size=30  body=[[08011378, 08011395]]

void FUN_08011378(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  do {
    uVar2 = uVar1 + 1;
    FUN_08011338(uVar1,param_1,param_2,param_3);
    uVar1 = uVar2;
  } while (uVar2 != 0x58);
  return;
}


// ===================================================================
// FUN_08011398 @ 0x08011398  size=166  body=[[08011398, 0801143d]]

void FUN_08011398(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar3 = param_1 * 4;
  bVar5 = (&DAT_08016842)[iVar3];
  bVar1 = (&DAT_08016843)[iVar3];
  uVar2 = (byte)(&DAT_08016840)[param_1 * 4] & 3;
  uVar9 = (uint)((byte)(&DAT_08016841)[iVar3] >> 3);
  uVar8 = (uint)(bVar5 >> 3);
  uVar7 = (uint)(bVar1 >> 3);
  bVar4 = *(byte *)(uVar2 * 0x18 + 0x20001fc2 + uVar9);
  bVar6 = (byte)(1 << ((byte)(&DAT_08016841)[iVar3] & 7));
  if (param_2 == 0) {
    bVar6 = bVar4 & ~bVar6;
  }
  else {
    bVar6 = bVar6 | bVar4;
  }
  iVar3 = uVar2 * 0x18 + 0x20001fc2;
  *(byte *)(iVar3 + uVar9) = bVar6;
  bVar4 = *(byte *)(iVar3 + uVar8);
  bVar5 = (byte)(1 << (bVar5 & 7));
  if (param_3 == 0) {
    bVar4 = bVar4 & ~bVar5;
  }
  else {
    bVar4 = bVar4 | bVar5;
  }
  iVar3 = uVar2 * 0x18 + 0x20001fc2;
  *(byte *)(iVar3 + uVar8) = bVar4;
  bVar5 = *(byte *)(iVar3 + uVar7);
  bVar1 = (byte)(1 << (bVar1 & 7));
  if (param_4 == 0) {
    bVar5 = bVar5 & ~bVar1;
  }
  else {
    bVar5 = bVar5 | bVar1;
  }
  *(byte *)(uVar2 * 0x18 + 0x20001fc2 + uVar7) = bVar5;
  (&DAT_20001fc0)[uVar2] = 1;
  return;
}


// ===================================================================
// FUN_0801144c @ 0x0801144c  size=38  body=[[0801144c, 08011471]]

void FUN_0801144c(uint param_1)

{
  int iVar1;
  
  if (((&DAT_20001ff2)[param_1] != '\0') && (iVar1 = FUN_08011218(param_1), iVar1 == 0)) {
    (&DAT_20001fc0)[param_1] = 1;
  }
  (&DAT_20001ff2)[param_1] = 0;
  return;
}


// ===================================================================
// FUN_08011480 @ 0x08011480  size=40  body=[[08011480, 080114a7]]

uint FUN_08011480(uint param_1)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = param_1;
  if ((&DAT_20001fc0)[param_1] != '\0') {
    cVar1 = FUN_080111a0(param_1,0,0,param_1 * 0x18 + 0x20001fc2,0x18);
    uVar2 = (uint)cVar1;
  }
  (&DAT_20001fc0)[param_1] = 0;
  return uVar2;
}


// ===================================================================
// FUN_080114b0 @ 0x080114b0  size=70  body=[[080114b0, 080114f5]]

void FUN_080114b0(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_08015338((uint *)&DAT_40020400,0x80,1);
  DAT_40020418 = 0x80;
  FUN_08012674();
  FUN_0801124c(0);
  FUN_0801124c(1);
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    FUN_08011398(uVar1,1,1,1);
  } while (uVar2 != 0x58);
  FUN_08011480(0);
  FUN_08011480(1);
  return;
}


// ===================================================================
// FUN_080114fc @ 0x080114fc  size=18  body=[[080114fc, 0801150d]]

void FUN_080114fc(void)

{
  FUN_0801144c(0);
  FUN_0801144c(1);
  return;
}


// ===================================================================
// FUN_08011510 @ 0x08011510  size=8  body=[[08011510, 08011517]]

void FUN_08011510(void)

{
  DAT_4002041a = 0x80;
  return;
}


// ===================================================================
// FUN_0801151c @ 0x0801151c  size=8  body=[[0801151c, 08011523]]

void FUN_0801151c(void)

{
  DAT_40020418 = 0x80;
  return;
}


// ===================================================================
// FUN_08011528 @ 0x08011528  size=6  body=[[08011528, 0801152d]]

void FUN_08011528(int param_1,undefined *UNRECOVERED_JUMPTABLE,undefined *UNRECOVERED_JUMPTABLE_00)

{
  if (param_1 != 0) {
                    // WARNING: Could not recover jumptable at 0x0801152a. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)UNRECOVERED_JUMPTABLE_00)();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x0801152c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}


// ===================================================================
// process_rgb_matrix @ 0x08011530  size=128  body=[[08011530, 0801154f] [08011566, 080115c5]]

// VERIFIED: switch over 0x7820..0x783x (QK_RGB_MATRIX_* keycodes)

undefined1 process_rgb_matrix(undefined4 param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  code *UNRECOVERED_JUMPTABLE;
  code *UNRECOVERED_JUMPTABLE_00;
  
  if (*(char *)(param_2 + 5) != '\0') {
switchD_0801154c_caseD_782f:
    return 1;
  }
  bVar1 = FUN_0800e310();
  switch(param_1) {
  case 0x7820:
    FUN_08010eb4();
    return 0;
  case 0x7821:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010d8d;
    UNRECOVERED_JUMPTABLE = (code *)0x8010d65;
    break;
  case 0x7822:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010d65;
    UNRECOVERED_JUMPTABLE = (code *)0x8010d8d;
    break;
  case 0x7823:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010df1;
    UNRECOVERED_JUMPTABLE = (code *)0x8010dcd;
    break;
  case 0x7824:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010dcd;
    UNRECOVERED_JUMPTABLE = (code *)0x8010df1;
    break;
  case 0x7825:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010e45;
    UNRECOVERED_JUMPTABLE = (code *)0x8010e1d;
    break;
  case 0x7826:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010e1d;
    UNRECOVERED_JUMPTABLE = (code *)0x8010e45;
    break;
  case 0x7827:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f55;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f15;
    break;
  case 0x7828:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f15;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f55;
    break;
  case 0x7829:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f91;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f75;
    break;
  case 0x782a:
    UNRECOVERED_JUMPTABLE_00 = (code *)0x8010f75;
    UNRECOVERED_JUMPTABLE = (code *)0x8010f91;
    break;
  case 0x782b:
    uVar2 = 1;
    goto LAB_080115b0;
  case 0x782c:
    uVar2 = 2;
    goto LAB_080115b0;
  case 0x782d:
    uVar2 = 5;
    goto LAB_080115b0;
  case 0x782e:
    uVar2 = 10;
LAB_080115b0:
    FUN_08010d40(uVar2);
    return 0;
  case 0x782f:
  case 0x7830:
  case 0x7831:
  case 0x7832:
  case 0x7833:
  case 0x7834:
    goto switchD_0801154c_caseD_782f;
  default:
    goto switchD_0801154c_caseD_782f;
  }
  FUN_08011528(bVar1 & 0x22,UNRECOVERED_JUMPTABLE,UNRECOVERED_JUMPTABLE_00);
switchD_0801154c_caseD_782f:
  return 0;
}


// ===================================================================
// FUN_080115f0 @ 0x080115f0  size=112  body=[[080115f0, 0801165f]]

void FUN_080115f0(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = param_1 + param_2;
  for (; param_1 < uVar1; param_1 = param_1 + 1) {
  }
  return;
}


// ===================================================================
// FUN_08011660 @ 0x08011660  size=8  body=[[08011660, 08011667]]

void FUN_08011660(void)

{
  FUN_080135c8(0x12c0);
  return;
}


// ===================================================================
// FUN_08011668 @ 0x08011668  size=92  body=[[08011668, 080116c3]]

void FUN_08011668(void)

{
  undefined4 uVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  
  DAT_20001ff5 = 1;
  for (bVar5 = 0; bVar5 < DAT_20001ff5; bVar5 = bVar5 + 1) {
    FUN_08015338((uint *)&DAT_40020400,0x8000,0x20);
    FUN_08015338((uint *)&DAT_40020400,0x4000,0x20);
  }
  FUN_08011660();
  bVar5 = DAT_20001ff5;
  pbVar3 = &DAT_20001ff7;
  for (bVar4 = 0; bVar4 < bVar5; bVar4 = bVar4 + 1) {
    uVar1 = DAT_40020410;
    uVar2 = DAT_40020410;
    *pbVar3 = (byte)(uVar2 >> 0xd) & 2 | (byte)((uint)uVar1 >> 8) >> 7;
    pbVar3 = pbVar3 + 1;
  }
  return;
}


// ===================================================================
// FUN_080116d0 @ 0x080116d0  size=342  body=[[080116d0, 08011825]]

byte FUN_080116d0(void)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  uint extraout_r2;
  uint extraout_r2_00;
  uint extraout_r2_01;
  uint extraout_r2_02;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  byte bVar10;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 auStack_28 [4];
  
  bVar9 = 0;
  for (bVar10 = 0; uVar8 = (uint)bVar10, uVar8 < DAT_20001ff5; bVar10 = bVar10 + 1) {
    uVar4 = DAT_40020410;
    uVar6 = DAT_40020410;
    uVar4 = (uVar4 & 0xffff) >> 0xf;
    uVar6 = uVar6 >> 0xd & 2;
    uVar7 = uVar6 | uVar4;
    if ((((byte)(&DAT_20001ff7)[uVar8] & 3) != uVar7) || ((&DAT_20001ff8)[uVar8] != '\0')) {
      uVar1 = (uint)(byte)(&DAT_20001ff7)[uVar8] << 2;
      (&DAT_20001ff7)[uVar8] = (byte)uVar7 | (byte)uVar1;
      cVar3 = (&DAT_080170b4)[uVar7 | uVar1 & 0xf] + (&DAT_20001ff6)[uVar8];
      (&DAT_20001ff6)[uVar8] = cVar3;
      if (((byte)(cVar3 + 3U) < 7) && ((uVar6 | uVar4) != 3)) {
        bVar5 = false;
      }
      else {
        if ('\0' < cVar3) {
          (&DAT_20001ff4)[uVar8] = (&DAT_20001ff4)[uVar8] + '\x01';
          uVar4 = FUN_08012574();
          local_3c = CONCAT22(local_3c._2_2_,0x103);
          local_40 = CONCAT22((short)uVar4,CONCAT11(0xfc,bVar10));
          FUN_0800d50c(local_40,local_3c,extraout_r2,0x103);
          FUN_08013a7a(200);
          uVar4 = FUN_08012574();
          local_44 = CONCAT22(local_44._2_2_,3);
          local_48 = CONCAT22((short)uVar4,CONCAT11(0xfc,bVar10));
          FUN_0800d50c(local_48,local_44,extraout_r2_00,3);
          FUN_08013a7a(200);
        }
        cVar2 = (&DAT_20001ff6)[uVar8];
        if (cVar2 < '\0') {
          (&DAT_20001ff4)[uVar8] = (&DAT_20001ff4)[uVar8] + -1;
          uVar4 = FUN_08012574();
          local_2c = CONCAT22(local_2c._2_2_,0x102);
          local_30 = CONCAT22((short)uVar4,CONCAT11(0xfd,bVar10));
          FUN_0800d50c(local_30,local_2c,extraout_r2_01,auStack_28);
          FUN_08013a7a(200);
          uVar4 = FUN_08012574();
          local_34 = CONCAT22(local_34._2_2_,2);
          local_38 = CONCAT22((short)uVar4,CONCAT11(0xfd,bVar10));
          FUN_0800d50c(local_38,local_34,extraout_r2_02,2);
          FUN_08013a7a(200);
        }
        bVar5 = cVar2 < '\0' || '\0' < cVar3;
        (&DAT_20001ff6)[uVar8] = 0;
      }
      bVar9 = bVar9 | bVar5;
      (&DAT_20001ff8)[uVar8] = 0;
    }
  }
  return bVar9;
}


// ===================================================================
// FUN_08011890 @ 0x08011890  size=4  body=[[08011890, 08011893]]

undefined4 FUN_08011890(void)

{
  return 1;
}


// ===================================================================
// FUN_08011894 @ 0x08011894  size=8  body=[[08011894, 0801189b]]

void FUN_08011894(void)

{
  FUN_08011890();
  return;
}


// ===================================================================
// FUN_0801189c @ 0x0801189c  size=48  body=[[0801189c, 080118cb]]

void FUN_0801189c(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = DAT_40020010;
  uVar1 = ~(uVar1 >> 8) & 1;
  DAT_20001ffa = (byte)uVar1;
  if ((DAT_20001ff9 != uVar1) || (param_1 != 0)) {
    FUN_0800cd18(0,uVar1,param_3);
    FUN_08011894();
    DAT_20001ff9 = DAT_20001ffa;
  }
  return;
}


// ===================================================================
// FUN_080118d8 @ 0x080118d8  size=24  body=[[080118d8, 080118ef]]

void FUN_080118d8(void)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  FUN_08015338((uint *)&DAT_40020000,0x100,0x20);
  FUN_0801189c(1,extraout_r1,extraout_r2);
  return;
}


// ===================================================================
// process_leader @ 0x080118f4  size=74  body=[[080118f4, 0801193d]]

// VERIFIED: compares keycode == 0x7C58 (QK_LEADER) when pressed

undefined1 process_leader(uint param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  
  if (*(char *)(param_2 + 5) != '\0') {
    cVar1 = FUN_08011990();
    if ((cVar1 == '\0') || (bVar2 = FUN_080119c0(), bVar2)) {
      if (param_1 == 0x7c58) {
        FUN_08011940();
      }
    }
    else {
      if (param_1 - 0x2000 < 0x3000) {
        param_1 = param_1 & 0xff;
      }
      bVar2 = FUN_0801199c((short)param_1);
      if (bVar2) {
        FUN_080119f8();
        return 0;
      }
      FUN_0801197c();
    }
  }
  return 1;
}


// ===================================================================
// FUN_08011940 @ 0x08011940  size=44  body=[[08011940, 0801196b]]

void FUN_08011940(void)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = DAT_20002008;
  if (DAT_20002008 == '\0') {
    FUN_0800cdf4();
    DAT_20002008 = 1;
    uVar2 = FUN_08012574();
    DAT_20002006 = (undefined2)uVar2;
    DAT_20001ffb = cVar1;
    FUN_08008798((byte *)&DAT_20001ffc,0,10);
    return;
  }
  return;
}


// ===================================================================
// FUN_0801197c @ 0x0801197c  size=14  body=[[0801197c, 08011989]]

void FUN_0801197c(void)

{
  DAT_20002008 = 0;
  FUN_0800cdfe();
  return;
}


// ===================================================================
// FUN_08011990 @ 0x08011990  size=6  body=[[08011990, 08011995]]

undefined1 FUN_08011990(void)

{
  return DAT_20002008;
}


// ===================================================================
// FUN_0801199c @ 0x0801199c  size=26  body=[[0801199c, 080119b5]]

bool FUN_0801199c(undefined2 param_1)

{
  uint uVar1;
  
  uVar1 = (uint)DAT_20001ffb;
  if (uVar1 < 5) {
    (&DAT_20001ffc)[uVar1] = param_1;
    DAT_20001ffb = DAT_20001ffb + 1;
  }
  return uVar1 < 5;
}


// ===================================================================
// FUN_080119c0 @ 0x080119c0  size=24  body=[[080119c0, 080119d7]]

bool FUN_080119c0(void)

{
  uint uVar1;
  
  uVar1 = FUN_0801257e((uint)DAT_20002006);
  return 0x20d < uVar1;
}


// ===================================================================
// FUN_080119dc @ 0x080119dc  size=24  body=[[080119dc, 080119f3]]

void FUN_080119dc(void)

{
  bool bVar1;
  
  if ((DAT_20002008 != '\0') && (bVar1 = FUN_080119c0(), bVar1)) {
    FUN_0801197c();
    return;
  }
  return;
}


// ===================================================================
// FUN_080119f8 @ 0x080119f8  size=12  body=[[080119f8, 08011a03]]

void FUN_080119f8(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012574();
  DAT_20002006 = (short)uVar1;
  return;
}


// ===================================================================
// FUN_08011a08 @ 0x08011a08  size=46  body=[[08011a08, 08011a35]]

bool FUN_08011a08(uint param_1,uint param_2,uint param_3,uint param_4,short param_5)

{
  bool bVar1;
  
  if ((((DAT_20001ffc == param_1) && (DAT_20001ffe == param_2)) && (DAT_20002000 == param_3)) &&
     (DAT_20002002 == param_4)) {
    bVar1 = DAT_20002004 == param_5;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ===================================================================
// FUN_08011a3c @ 0x08011a3c  size=20  body=[[08011a3c, 08011a4f]]

bool FUN_08011a3c(uint param_1)

{
  bool bVar1;
  
  bVar1 = FUN_08011a08(param_1,0,0,0,0);
  return bVar1;
}


// ===================================================================
// FUN_08011a50 @ 0x08011a50  size=18  body=[[08011a50, 08011a61]]

bool FUN_08011a50(uint param_1,uint param_2)

{
  bool bVar1;
  
  bVar1 = FUN_08011a08(param_1,param_2,0,0,0);
  return bVar1;
}


// ===================================================================
// FUN_08011a62 @ 0x08011a62  size=42  body=[[08011a62, 08011a8b]]

int FUN_08011a62(short param_1)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = param_1 * 0xb5;
  if ((short)uVar1 < 0) {
    iVar2 = (int)(short)(uVar1 - 0x80);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
  }
  else {
    iVar2 = uVar1 + 0x80;
  }
  return (iVar2 << 0x10) >> 0x18;
}


// ===================================================================
// FUN_08011a8c @ 0x08011a8c  size=120  body=[[08011a8c, 08011b03]]

byte FUN_08011a8c(void)

{
  byte bVar1;
  uint uVar2;
  
  if ((int)((uint)DAT_20002012 << 0x1f) < 0) {
    uVar2 = 400;
  }
  else if ((int)((uint)DAT_20002012 << 0x1d) < 0) {
    uVar2 = 3000;
  }
  else if ((DAT_20002011 == '\0') || (DAT_2000200e == 0)) {
    uVar2 = 0x1e;
  }
  else {
    uVar2 = FUN_0801257e((uint)DAT_2000200e);
    uVar2 = uVar2 / 0x32 & 0xffff;
    uVar2 = uVar2 * 0x2d + 0x1e + ((int)(uVar2 * uVar2 * 0x2d) >> 1) & 0xffff;
    if (0x5db < uVar2) {
      uVar2 = 0x5dc;
    }
  }
  bVar1 = (byte)((ulonglong)uVar2 / (1000 / (ulonglong)DAT_20000ec5));
  if (bVar1 == 0) {
    bVar1 = 1;
  }
  if (0x7e < bVar1) {
    bVar1 = 0x7f;
  }
  return bVar1;
}


// ===================================================================
// FUN_08011b14 @ 0x08011b14  size=94  body=[[08011b14, 08011b71]]

undefined4 FUN_08011b14(void)

{
  uint uVar1;
  
  if ((DAT_20002012 & 1) == 0) {
    if ((int)((uint)DAT_20002012 << 0x1d) < 0) {
      uVar1 = 0x32;
    }
    else if ((DAT_20002010 == '\0') || (DAT_2000200e == 0)) {
      uVar1 = 0x40;
    }
    else {
      uVar1 = (uint)DAT_20000ec2;
      if (uVar1 != 0x20) {
        uVar1 = FUN_0801257e((uint)DAT_2000200e);
        uVar1 = uVar1 / 0x32 & 0xffff;
        uVar1 = uVar1 + 0x40 + ((int)(uVar1 * uVar1) >> 1) & 0xffff;
        if (0x1f < uVar1) {
          uVar1 = 0x20;
        }
      }
    }
  }
  else {
    uVar1 = 8;
  }
  DAT_20000ec2 = (short)(1000 / uVar1);
  return 1;
}


// ===================================================================
// FUN_08011b84 @ 0x08011b84  size=164  body=[[08011b84, 08011bb9] [08011bce, 08011c3b]]

void FUN_08011b84(int param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (DAT_2000200e == 0) {
    uVar2 = FUN_08012574();
    DAT_2000200e = (short)uVar2;
  }
  if (((DAT_20002015 != 0 || DAT_20002016 != 0) || DAT_20002018 != '\0') || DAT_20002017 != '\0') {
    uVar2 = FUN_08012574();
    DAT_2000200e = (short)uVar2 + -0xa0;
  }
  switch(param_1) {
  case 0xcd:
    bVar1 = FUN_08011a8c();
    DAT_20002016 = -bVar1;
    break;
  case 0xce:
    DAT_20002016 = FUN_08011a8c();
    break;
  case 0xcf:
    bVar1 = FUN_08011a8c();
    DAT_20002015 = -bVar1;
    break;
  case 0xd0:
    DAT_20002015 = FUN_08011a8c();
    break;
  case 0xd1:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xd8:
    DAT_20002014 = (byte)(1 << (param_1 - 0xd1U & 0xff)) | DAT_20002014;
    break;
  case 0xd9:
    uVar3 = FUN_08011b14();
    DAT_20002017 = (char)uVar3;
    break;
  case 0xda:
    uVar3 = FUN_08011b14();
    DAT_20002017 = -(char)uVar3;
    break;
  case 0xdb:
    uVar3 = FUN_08011b14();
    DAT_20002018 = -(char)uVar3;
    break;
  case 0xdc:
    uVar3 = FUN_08011b14();
    DAT_20002018 = (char)uVar3;
    break;
  case 0xdd:
    DAT_20002012 = DAT_20002012 | 1;
    break;
  case 0xde:
    DAT_20002012 = DAT_20002012 | 2;
    break;
  case 0xdf:
    DAT_20002012 = DAT_20002012 | 4;
  }
  return;
}


// ===================================================================
// FUN_08011c48 @ 0x08011c48  size=206  body=[[08011c48, 08011ce7] [08011d24, 08011d51]]

void FUN_08011c48(int param_1)

{
  if (param_1 == 0xcd) {
    if (-1 < DAT_20002016) goto switchD_08011ce4_caseD_8;
  }
  else {
    if (param_1 != 0xce) {
      if (param_1 == 0xcf) {
        if (-1 < DAT_20002015) goto switchD_08011ce4_caseD_8;
      }
      else {
        if (param_1 != 0xd0) {
          if (param_1 == 0xd9) {
            if (DAT_20002017 < '\x01') goto switchD_08011ce4_caseD_8;
          }
          else {
            if (param_1 != 0xda) {
              if (param_1 == 0xdb) {
                if (-1 < DAT_20002018) goto switchD_08011ce4_caseD_8;
              }
              else {
                if (param_1 != 0xdc) {
                  switch(param_1 - 0xd1U) {
                  case 0:
                  case 1:
                  case 2:
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                    DAT_20002014 = DAT_20002014 & ~(byte)(1 << (param_1 - 0xd1U & 0xff));
                    break;
                  case 0xc:
                    DAT_20002012 = DAT_20002012 & 0xfe;
                    break;
                  case 0xd:
                    DAT_20002012 = DAT_20002012 & 0xfd;
                    break;
                  case 0xe:
                    DAT_20002012 = DAT_20002012 & 0xfb;
                  }
                  goto switchD_08011ce4_caseD_8;
                }
                if (DAT_20002018 < '\x01') goto switchD_08011ce4_caseD_8;
              }
              DAT_20002018 = '\0';
              goto switchD_08011ce4_caseD_8;
            }
            if (-1 < DAT_20002017) goto switchD_08011ce4_caseD_8;
          }
          DAT_20002017 = '\0';
          goto switchD_08011ce4_caseD_8;
        }
        if (DAT_20002015 < '\x01') goto switchD_08011ce4_caseD_8;
      }
      DAT_20002015 = '\0';
      goto switchD_08011ce4_caseD_8;
    }
    if (DAT_20002016 < '\x01') goto switchD_08011ce4_caseD_8;
  }
  DAT_20002016 = '\0';
switchD_08011ce4_caseD_8:
  if (DAT_20002015 == '\0' && DAT_20002016 == '\0') {
    DAT_2000200e = 0;
    DAT_20002011 = 0;
  }
  if (DAT_20002018 == '\0' && DAT_20002017 == '\0') {
    DAT_20002010 = 0;
  }
  return;
}


// ===================================================================
// FUN_08011d68 @ 0x08011d68  size=58  body=[[08011d68, 08011d91] [08012174, 08012183]]

void FUN_08011d68(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012574();
  if (DAT_20002015 != '\0' || DAT_20002016 != '\0') {
    DAT_2000200c = (short)uVar1;
  }
  if (DAT_20002017 != '\0' || DAT_20002018 != '\0') {
    DAT_2000200a = (short)uVar1;
  }
  if (DAT_20002028 == 0) {
    return;
  }
  DAT_20002013 = 2;
                    // WARNING: Could not recover jumptable at 0x08012180. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(DAT_20002028 + 0xc))();
  return;
}


// ===================================================================
// FUN_08011da0 @ 0x08011da0  size=28  body=[[08011da0, 08011dbb]]

void FUN_08011da0(void)

{
  FUN_08008798(&DAT_20002013,0,6);
  DAT_20002011 = 0;
  DAT_20002010 = 0;
  DAT_20002012 = 0;
  return;
}


// ===================================================================
// FUN_08011dcc @ 0x08011dcc  size=34  body=[[08011dcc, 08011ded]]

bool FUN_08011dcc(int param_1)

{
  if (((*(char *)(param_1 + 2) == '\0') && (*(char *)(param_1 + 3) == '\0')) &&
     (*(char *)(param_1 + 4) == '\0')) {
    return *(char *)(param_1 + 5) != '\0';
  }
  return true;
}


// ===================================================================
// FUN_08011df0 @ 0x08011df0  size=374  body=[[08011df0, 08011f65]]

void FUN_08011df0(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  short extraout_r2;
  short extraout_r2_00;
  char cVar6;
  undefined4 uStack_10;
  undefined4 local_c;
  
  uStack_10 = param_1;
  local_c = param_2;
  memcpy(&uStack_10,(undefined4 *)&DAT_20002013,6);
  DAT_20002015 = '\0';
  DAT_20002016 = '\0';
  DAT_20002017 = '\0';
  DAT_20002018 = '\0';
  if (uStack_10._2_1_ != '\0' || uStack_10._3_1_ != '\0') {
    uVar3 = FUN_0801257e((uint)DAT_2000200c);
    if (DAT_20002011 == '\0') {
      if ((int)((uint)DAT_20002009 * 10) < (int)uVar3) {
LAB_08011e80:
        DAT_20002011 = DAT_20002011 + '\x01';
        goto LAB_08011e8a;
      }
    }
    else if ((int)(uint)DAT_20000ec5 < (int)uVar3) {
      if (DAT_20002011 != -1) goto LAB_08011e80;
LAB_08011e8a:
      if (uStack_10._2_1_ != '\0') {
        bVar2 = FUN_08011a8c();
        if (uStack_10._2_1_ < '\x01') {
          cVar6 = -1;
        }
        else {
          cVar6 = '\x01';
        }
        DAT_20002015 = bVar2 * cVar6;
      }
      if (uStack_10._3_1_ != '\0') {
        bVar2 = FUN_08011a8c();
        if (uStack_10._3_1_ < '\x01') {
          cVar6 = -1;
        }
        else {
          cVar6 = '\x01';
        }
        DAT_20002016 = bVar2 * cVar6;
      }
      if ((DAT_20002015 != '\0') && (DAT_20002016 != '\0')) {
        iVar5 = FUN_08011a62((short)DAT_20002015);
        if (iVar5 == 0) {
          iVar5 = 1;
        }
        DAT_20002015 = (char)iVar5;
        iVar5 = FUN_08011a62(extraout_r2);
        if (iVar5 == 0) {
          DAT_20002016 = '\x01';
        }
        else {
          DAT_20002016 = (char)iVar5;
        }
      }
    }
  }
  if ((char)local_c == '\0' && local_c._1_1_ == '\0') goto LAB_08011e4e;
  uVar3 = FUN_0801257e((uint)DAT_2000200a);
  if (DAT_20002010 == '\0') {
    if ((int)uVar3 <= (int)((uint)DAT_20000ec4 * 10)) goto LAB_08011e4e;
LAB_08011efa:
    DAT_20002010 = DAT_20002010 + '\x01';
  }
  else {
    if ((int)uVar3 <= (int)(uint)DAT_20000ec2) goto LAB_08011e4e;
    if (DAT_20002010 != -1) goto LAB_08011efa;
  }
  if ((char)local_c != '\0') {
    uVar4 = FUN_08011b14();
    if ((char)local_c < '\x01') {
      cVar6 = -1;
    }
    else {
      cVar6 = '\x01';
    }
    DAT_20002017 = (char)uVar4 * cVar6;
  }
  if (local_c._1_1_ != '\0') {
    uVar4 = FUN_08011b14();
    if (local_c._1_1_ < '\x01') {
      cVar6 = -1;
    }
    else {
      cVar6 = '\x01';
    }
    DAT_20002018 = (char)uVar4 * cVar6;
  }
  if ((DAT_20002017 != '\0') && (DAT_20002018 != '\0')) {
    iVar5 = FUN_08011a62((short)DAT_20002017);
    if (iVar5 == 0) {
      iVar5 = 1;
    }
    DAT_20002017 = (char)iVar5;
    iVar5 = FUN_08011a62(extraout_r2_00);
    if (iVar5 == 0) {
      DAT_20002018 = '\x01';
    }
    else {
      DAT_20002018 = (char)iVar5;
    }
  }
LAB_08011e4e:
  bVar1 = FUN_080123bc(0x20002013,(int)&uStack_10);
  if ((bVar1) || (bVar1 = FUN_08011dcc(0x20002013), bVar1)) {
    FUN_08011d68();
  }
  memcpy((undefined4 *)&DAT_20002013,&uStack_10,6);
  return;
}


// ===================================================================
// FUN_08011f8c @ 0x08011f8c  size=6  body=[[08011f8c, 08011f91]]

void FUN_08011f8c(undefined4 param_1,undefined4 param_2,undefined *UNRECOVERED_JUMPTABLE)

{
  if (UNRECOVERED_JUMPTABLE != (undefined *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08011f8e. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)UNRECOVERED_JUMPTABLE)();
    return;
  }
  return;
}


// ===================================================================
// FUN_08011f92 @ 0x08011f92  size=36  body=[[08011f92, 08011fb5]]

void FUN_08011f92(undefined4 *param_1)

{
  FUN_08011f8c(param_1,param_1[6],(undefined *)param_1[4]);
  FUN_0800e364(*(byte *)((int)param_1 + 3));
  FUN_0800e32c(*(byte *)(param_1 + 1));
  FUN_0800e4dc();
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  return;
}


// ===================================================================
// FUN_08011fb8 @ 0x08011fb8  size=66  body=[[08011fb8, 08011ff9]]

void FUN_08011fb8(undefined4 *param_1)

{
  if (-1 < (int)((uint)*(byte *)((int)param_1 + 5) << 0x1e)) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 2;
    FUN_0800e354(*(byte *)((int)param_1 + 3));
    FUN_0800e31c(*(byte *)(param_1 + 1));
    FUN_0800e4dc();
    FUN_08011f8c(param_1,param_1[6],(undefined *)param_1[3]);
  }
  DAT_2000201c = 0;
  if (-1 < (int)((uint)*(byte *)((int)param_1 + 5) << 0x1f)) {
    FUN_08011f92(param_1);
    return;
  }
  return;
}


// ===================================================================
// preprocess_tap_dance @ 0x08012000  size=54  body=[[08012000, 08012035]]

// INFERRED: called (keycode,record) right after get_record_keycode; nonzero result triggers keycode
// re-read (QMK 0.23 process_record_quantum)

char preprocess_tap_dance(uint param_1,int param_2)

{
  int iVar1;
  char cVar2;
  
  cVar2 = *(char *)(param_2 + 5);
  if (cVar2 != '\0') {
    if ((DAT_2000201c == 0) || (DAT_2000201c == param_1)) {
      cVar2 = '\0';
    }
    else {
      iVar1 = (uint)(byte)DAT_2000201c * 0x1c;
      (&DAT_20000e81)[iVar1] = (&DAT_20000e81)[iVar1] | 4;
      *(short *)(&DAT_20000e7c + iVar1) = (short)param_1;
      FUN_08011fb8((undefined4 *)(&DAT_20000e7c + iVar1));
      FUN_0800e374();
    }
  }
  return cVar2;
}


// ===================================================================
// process_tap_dance @ 0x08012040  size=132  body=[[08012040, 080120c3]]

// VERIFIED: (keycode-0x5700) < 0x100 = QK_TAP_DANCE range; per-dance state stride 0x1C based at
// 0x20000E7C; active-td keycode @0x2000201C

undefined4 process_tap_dance(uint param_1,int param_2)

{
  int iVar1;
  undefined1 uVar2;
  byte bVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if (param_1 - 0x5700 < 0x100) {
    bVar3 = *(byte *)(param_2 + 5);
    iVar1 = (param_1 & 0xff) * 0x1c;
    puVar5 = (undefined4 *)(&DAT_20000e7c + iVar1);
    (&DAT_20000e81)[iVar1] = (&DAT_20000e81)[iVar1] & 0xfe | bVar3 & 1;
    if (bVar3 == 0) {
      FUN_08011f8c(puVar5,*(undefined4 *)(&DAT_20000e94 + iVar1),
                   *(undefined **)(&DAT_20000e90 + iVar1));
      if (((int)((uint)(byte)(&DAT_20000e81)[iVar1] << 0x1e) < 0) &&
         (FUN_08011f92(puVar5), DAT_2000201c == param_1)) {
        DAT_2000201c = 0;
      }
    }
    else {
      uVar4 = FUN_08012574();
      DAT_2000201a = (undefined2)uVar4;
      (&DAT_20000e7e)[iVar1] = (&DAT_20000e7e)[iVar1] + '\x01';
      uVar2 = FUN_0800e310();
      (&DAT_20000e7f)[iVar1] = uVar2;
      bVar3 = FUN_0800e348();
      (&DAT_20000e7f)[iVar1] = bVar3 | (&DAT_20000e7f)[iVar1];
      uVar2 = FUN_0800e380();
      (&DAT_20000e80)[iVar1] = uVar2;
      FUN_08011f8c(puVar5,*(undefined4 *)(&DAT_20000e94 + iVar1),
                   *(undefined **)(&DAT_20000e84 + iVar1));
      if (((&DAT_20000e81)[iVar1] & 2) != 0) {
        param_1 = 0;
      }
      DAT_2000201c = (ushort)param_1;
    }
  }
  return 1;
}


// ===================================================================
// FUN_080120d0 @ 0x080120d0  size=66  body=[[080120d0, 08012111]]

void FUN_080120d0(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_2000201c != 0) {
    uVar1 = FUN_0801257e((uint)DAT_2000201a);
    uVar2 = FUN_0800defc();
    if ((uVar2 < uVar1) &&
       (-1 < (int)((uint)(byte)(&DAT_20000e81)[(uint)(byte)DAT_2000201c * 0x1c] << 0x1d))) {
      FUN_08011fb8((undefined4 *)(&DAT_20000e7c + (uint)(byte)DAT_2000201c * 0x1c));
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_08012120 @ 0x08012120  size=6  body=[[08012120, 08012125]]

void FUN_08012120(undefined4 param_1)

{
  DAT_20002028 = param_1;
  return;
}


// ===================================================================
// FUN_0801212c @ 0x0801212c  size=6  body=[[0801212c, 08012131]]

undefined4 FUN_0801212c(void)

{
  return DAT_20002028;
}


// ===================================================================
// FUN_08012138 @ 0x08012138  size=12  body=[[08012138, 08012143]]

void FUN_08012138(void)

{
  if (DAT_20002028 != (undefined4 *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08012140. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)*DAT_20002028)();
    return;
  }
  return;
}


// ===================================================================
// FUN_08012148 @ 0x08012148  size=8  body=[[08012148, 0801214f]]

void FUN_08012148(void)

{
  FUN_08012138();
  return;
}


// ===================================================================
// FUN_08012150 @ 0x08012150  size=12  body=[[08012150, 0801215b]]

void FUN_08012150(void)

{
  if (DAT_20002028 != 0) {
                    // WARNING: Could not recover jumptable at 0x08012158. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(DAT_20002028 + 4))();
    return;
  }
  return;
}


// ===================================================================
// FUN_08012160 @ 0x08012160  size=16  body=[[08012160, 0801216f]]

void FUN_08012160(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = DAT_20002028;
  if (DAT_20002028 != 0) {
    *param_1 = 6;
                    // WARNING: Could not recover jumptable at 0x0801216c. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(iVar1 + 8))();
    return;
  }
  return;
}


// ===================================================================
// FUN_08012188 @ 0x08012188  size=36  body=[[08012188, 080121ab]]

void FUN_08012188(uint param_1)

{
  if (DAT_20002026 != param_1) {
    DAT_20002026 = (ushort)param_1;
    if (DAT_20002028 != 0) {
      DAT_20002022 = (undefined1)param_1;
      DAT_20002023 = (undefined1)(param_1 >> 8);
      DAT_20002021 = 3;
                    // WARNING: Could not recover jumptable at 0x080121a8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(DAT_20002028 + 0x10))();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_080121b8 @ 0x080121b8  size=36  body=[[080121b8, 080121db]]

void FUN_080121b8(uint param_1)

{
  if (DAT_20002024 != param_1) {
    DAT_20002024 = (ushort)param_1;
    if (DAT_20002028 != 0) {
      DAT_2000201f = (undefined1)param_1;
      DAT_20002020 = (undefined1)(param_1 >> 8);
      DAT_2000201e = 4;
                    // WARNING: Could not recover jumptable at 0x080121d8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(DAT_20002028 + 0x10))();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_080121e8 @ 0x080121e8  size=64  body=[[080121e8, 08012227]]

char FUN_080121e8(void)

{
  char cVar1;
  char *pcVar2;
  int iVar4;
  int iVar5;
  char *pcVar3;
  
  if ((DAT_20000ec6 == '\0') || (-1 < (char)DAT_200047d4)) {
    iVar5 = 6;
    iVar4 = DAT_20000e9c;
  }
  else {
    iVar5 = 0x1e;
    iVar4 = DAT_20000e98;
  }
  cVar1 = '\0';
  pcVar3 = (char *)(iVar4 + 2);
  do {
    pcVar2 = pcVar3 + 1;
    if (*pcVar3 != '\0') {
      cVar1 = cVar1 + '\x01';
    }
    pcVar3 = pcVar2;
  } while (((uint)((char *)(iVar4 + 2) + (iVar5 - (int)pcVar2 & 0xff)) & 0xff) != 0);
  return cVar1;
}


// ===================================================================
// FUN_08012238 @ 0x08012238  size=82  body=[[08012238, 08012289]]

bool FUN_08012238(uint param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0) {
    return false;
  }
  if ((DAT_20000ec6 == '\0') || (-1 < (char)DAT_200047d4)) {
    pbVar1 = (byte *)(DAT_20000e9c + 1);
    do {
      pbVar1 = pbVar1 + 1;
      if (*pbVar1 == param_1) {
        return true;
      }
    } while (pbVar1 != (byte *)(DAT_20000e9c + 7));
  }
  else if (param_1 < 0xf0) {
    return ((uint)*(byte *)(DAT_20000e98 + (param_1 >> 3) + 2) & 1 << (param_1 & 7)) != 0;
  }
  return false;
}


// ===================================================================
// FUN_0801229c @ 0x0801229c  size=44  body=[[0801229c, 080122c7]]

void FUN_0801229c(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar1 = 0;
  pbVar3 = (byte *)(param_1 + 1);
  iVar2 = -1;
  do {
    pbVar3 = pbVar3 + 1;
    if (*pbVar3 == param_2) {
      return;
    }
    if ((iVar2 == -1) && (*pbVar3 == 0)) {
      iVar2 = (int)(char)iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 6);
  if (iVar2 != -1) {
    *(char *)(param_1 + iVar2 + 2) = (char)param_2;
  }
  return;
}


// ===================================================================
// FUN_080122c8 @ 0x080122c8  size=24  body=[[080122c8, 080122df]]

void FUN_080122c8(int param_1,uint param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_1 + 1);
  do {
    pbVar1 = pbVar1 + 1;
    if (*pbVar1 == param_2) {
      *pbVar1 = 0;
    }
  } while (pbVar1 != (byte *)(param_1 + 7));
  return;
}


// ===================================================================
// FUN_0801231c @ 0x0801231c  size=60  body=[[080122e0, 080122f9] [0801231c, 0801233d]]

void FUN_0801231c(uint param_1)

{
  int iVar1;
  
  if ((DAT_20000ec6 != '\0') && ((char)DAT_200047d4 < '\0')) {
    if (param_1 < 0xf0) {
      iVar1 = DAT_20000e98 + (param_1 >> 3);
      *(byte *)(iVar1 + 2) = (byte)(1 << (param_1 & 7)) | *(byte *)(iVar1 + 2);
    }
    return;
  }
  FUN_0801229c(DAT_20000e9c,param_1);
  return;
}


// ===================================================================
// FUN_08012350 @ 0x08012350  size=66  body=[[080122fa, 08012319] [08012350, 08012371]]

uint FUN_08012350(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  if ((DAT_20000ec6 != '\0') && ((char)DAT_200047d4 < '\0')) {
    uVar2 = param_1 >> 3;
    uVar1 = param_1;
    if (param_1 < 0xf0) {
      uVar2 = uVar2 + DAT_20000e98;
      uVar1 = param_1 & 7;
    }
    if (param_1 < 0xf0) {
      *(byte *)(uVar2 + 2) = *(byte *)(uVar2 + 2) & ~(byte)(1 << (uVar1 & 0xff));
    }
    return (uint)(param_1 < 0xf0);
  }
  uVar2 = FUN_080122c8(DAT_20000e9c,param_1);
  return uVar2;
}


// ===================================================================
// FUN_08012384 @ 0x08012384  size=38  body=[[08012384, 080123a9]]

void FUN_08012384(void)

{
  int iVar1;
  uint uVar2;
  
  if ((DAT_20000ec6 == '\0') || (-1 < (char)DAT_200047d4)) {
    uVar2 = 6;
    iVar1 = DAT_20000e9c;
  }
  else {
    uVar2 = 0x1e;
    iVar1 = DAT_20000e98;
  }
  FUN_08008798((byte *)(iVar1 + 2),0,uVar2);
  return;
}


// ===================================================================
// FUN_080123bc @ 0x080123bc  size=72  body=[[080123bc, 08012403]]

bool FUN_080123bc(int param_1,int param_2)

{
  bool bVar1;
  
  if ((((*(char *)(param_1 + 1) == *(char *)(param_2 + 1)) &&
       ((*(char *)(param_1 + 2) == '\0' || (*(char *)(param_2 + 2) == *(char *)(param_1 + 2))))) &&
      ((*(char *)(param_1 + 3) == '\0' || (*(char *)(param_2 + 3) == *(char *)(param_1 + 3))))) &&
     ((*(char *)(param_1 + 5) == '\0' || (*(char *)(param_2 + 5) == *(char *)(param_1 + 5))))) {
    bVar1 = false;
    if (*(char *)(param_1 + 4) != '\0') {
      return *(char *)(param_2 + 4) != *(char *)(param_1 + 4);
    }
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}


// ===================================================================
// FUN_08012404 @ 0x08012404  size=2  body=[[08012404, 08012405]]

void FUN_08012404(void)

{
  return;
}


// ===================================================================
// FUN_08012406 @ 0x08012406  size=8  body=[[08012406, 0801240d]]

void FUN_08012406(void)

{
  FUN_08012404();
  return;
}


// ===================================================================
// FUN_08012410 @ 0x08012410  size=16  body=[[08012410, 0801241f]]

void FUN_08012410(char param_1)

{
  DAT_2000202c = param_1 + '\x01';
  FUN_08012406();
  return;
}


// ===================================================================
// FUN_08012424 @ 0x08012424  size=14  body=[[08012424, 08012431]]

void FUN_08012424(void)

{
  DAT_2000202c = 3;
  FUN_08012406();
  return;
}


// ===================================================================
// thunk_FUN_08012410 @ 0x08012438  size=4  body=[[08012438, 0801243b]]

void thunk_FUN_08012410(char param_1)

{
  DAT_2000202c = param_1 + '\x01';
  FUN_08012406();
  return;
}


// ===================================================================
// FUN_0801243c @ 0x0801243c  size=14  body=[[0801243c, 08012449]]

void FUN_0801243c(void)

{
  DAT_2000202c = 1;
  FUN_08012406();
  return;
}


// ===================================================================
// thunk_FUN_0801243c @ 0x08012450  size=4  body=[[08012450, 08012453]]

void thunk_FUN_0801243c(void)

{
  DAT_2000202c = 1;
  FUN_08012406();
  return;
}


// ===================================================================
// FUN_08012454 @ 0x08012454  size=2  body=[[08012454, 08012455]]

void FUN_08012454(void)

{
  return;
}


// ===================================================================
// FUN_08012456 @ 0x08012456  size=2  body=[[08012456, 08012457]]

void FUN_08012456(void)

{
  return;
}


// ===================================================================
// FUN_08012458 @ 0x08012458  size=2  body=[[08012458, 08012459]]

void FUN_08012458(void)

{
  return;
}


// ===================================================================
// FUN_0801245a @ 0x0801245a  size=8  body=[[0801245a, 08012461]]

void FUN_0801245a(void)

{
  FUN_08012458();
  return;
}


// ===================================================================
// FUN_08012462 @ 0x08012462  size=2  body=[[08012462, 08012463]]

void FUN_08012462(void)

{
  return;
}


// ===================================================================
// FUN_08012464 @ 0x08012464  size=8  body=[[08012464, 0801246b]]

void FUN_08012464(void)

{
  FUN_08012462();
  return;
}


// ===================================================================
// FUN_0801246c @ 0x0801246c  size=36  body=[[0801246c, 0801248f]]

undefined4 FUN_0801246c(void)

{
  int iVar1;
  uint uVar2;
  
  FUN_08012454();
  FUN_0800ee8c();
  FUN_08012456();
  uVar2 = 0;
  do {
    iVar1 = FUN_0800ed20(uVar2 & 0xff);
    if (iVar1 != 0) {
      return 1;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 6);
  return 0;
}


// ===================================================================
// FUN_08012490 @ 0x08012490  size=14  body=[[08012490, 0801249d]]

void FUN_08012490(void)

{
  FUN_08013cd0();
  FUN_0801354c();
  return;
}


// ===================================================================
// FUN_0801249e @ 0x0801249e  size=18  body=[[0801249e, 080124af]]

void FUN_0801249e(void)

{
  FUN_0800d45c();
  FUN_08013a7a(0x6a4);
  return;
}


// ===================================================================
// FUN_080124b0 @ 0x080124b0  size=38  body=[[080124b0, 080124d5]]

void FUN_080124b0(void)

{
  FUN_0800e33c();
  FUN_0800e374();
  FUN_08012384();
  FUN_08011da0();
  FUN_08012188(0);
  FUN_080121b8(0);
  FUN_0800d474();
  return;
}


// ===================================================================
// FUN_080124d8 @ 0x080124d8  size=32  body=[[080124d8, 080124f7]]

void FUN_080124d8(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  DAT_20002038 = FUN_08013cfa();
  DAT_20002034 = 0;
  DAT_20002030 = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// thunk_FUN_080124d8 @ 0x08012504  size=4  body=[[08012504, 08012507]]

void thunk_FUN_080124d8(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  DAT_20002038 = FUN_08013cfa();
  DAT_20002034 = 0;
  DAT_20002030 = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08012508 @ 0x08012508  size=82  body=[[08012508, 08012559]]

int FUN_08012508(void)

{
  bool bVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar3 = FUN_08013cfa();
  uVar4 = iVar3 - DAT_20002038;
  if (uVar4 < DAT_20002034) {
    DAT_20002038 = DAT_20002038 + -0x106e0;
    DAT_20002030 = DAT_20002030 + 0x28f5988;
    uVar4 = uVar4 + 0x106e0;
  }
  iVar3 = DAT_20002030;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  lVar2 = (ulonglong)uVar4 * 1000 + 99999;
  DAT_20002034 = uVar4;
  uVar5 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
  return (int)uVar5 + iVar3;
}


// ===================================================================
// FUN_08012574 @ 0x08012574  size=10  body=[[08012574, 0801257d]]

uint FUN_08012574(void)

{
  uint uVar1;
  
  uVar1 = FUN_08012508();
  return uVar1 & 0xffff;
}


// ===================================================================
// FUN_0801257e @ 0x0801257e  size=14  body=[[0801257e, 0801258b]]

uint FUN_0801257e(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_08012508();
  return iVar1 - param_1 & 0xffff;
}


// ===================================================================
// FUN_0801258c @ 0x0801258c  size=12  body=[[0801258c, 08012597]]

int FUN_0801258c(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_08012508();
  return iVar1 - param_1;
}


// ===================================================================
// FUN_08012598 @ 0x08012598  size=26  body=[[08012598, 080125b1]]

void FUN_08012598(void)

{
  uint uVar1;
  
  DataSynchronizationBarrier(0xf);
  uVar1 = DAT_e000ed0c;
  DAT_e000ed0c = uVar1 & 0x700 | 0x5fa0004;
  DataSynchronizationBarrier(0xf);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// FUN_080125bc @ 0x080125bc  size=8  body=[[080125bc, 080125c3]]

void FUN_080125bc(void)

{
  DAT_2000fffc = 0xdeadbeef;
  return;
}


// ===================================================================
// FUN_080125cc @ 0x080125cc  size=14  body=[[080125cc, 080125d9]]

bool FUN_080125cc(void)

{
  return DAT_2000fffc == -0x21524111;
}


// ===================================================================
// FUN_080125e4 @ 0x080125e4  size=8  body=[[080125e4, 080125eb]]

void FUN_080125e4(void)

{
  DAT_2000fffc = 0;
  return;
}


// ===================================================================
// FUN_080125f0 @ 0x080125f0  size=10  body=[[080125f0, 080125f9]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_080125f0(void)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  FUN_080125bc();
  FUN_08012598();
  uVar10 = 0x80125fb;
  uVar9 = extraout_r3;
  FUN_08012598();
  uVar8 = 0x8012601;
  uVar7 = extraout_r3_00;
  bVar3 = FUN_080125cc();
  if (bVar3) {
    uVar4 = FUN_080125e4();
    disableIRQinterrupts();
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    uVar2 = DAT_e000ed24;
    DAT_e000ed24 = uVar2 & 0xfffeffff;
    uVar2 = DAT_e000ed94;
    DAT_e000ed94 = uVar2 & 0xfffffffe;
    DAT_e000e010 = 0;
    DAT_e000e018 = 0;
    DAT_e000e014 = 0;
    iVar5 = 0;
    do {
      iVar6 = iVar5 + 1;
      (&DAT_e000e180)[iVar5] = 0xffffffff;
      (&DAT_e000e280)[iVar5] = 0xffffffff;
      iVar5 = iVar6;
    } while (iVar6 != 8);
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setThreadModePrivileged(1);
      bVar3 = (bool)isThreadMode();
      if (bVar3) {
        cVar1 = isUsingMainStack();
        setStackMode(cVar1 == '\x01');
      }
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setMainStackPointer(_DAT_1fff0000);
    }
    enableIRQinterrupts();
    (*_DAT_1fff0004)(uVar4,0xffffffff,_DAT_1fff0000,_DAT_1fff0004,uVar7,uVar8,uVar9,uVar10);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  return;
}


// ===================================================================
// FUN_080125fa @ 0x080125fa  size=6  body=[[080125fa, 080125ff]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_080125fa(void)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 extraout_r3;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  FUN_08012598();
  uVar8 = 0x8012601;
  uVar7 = extraout_r3;
  bVar3 = FUN_080125cc();
  if (bVar3) {
    uVar4 = FUN_080125e4();
    disableIRQinterrupts();
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    uVar2 = DAT_e000ed24;
    DAT_e000ed24 = uVar2 & 0xfffeffff;
    uVar2 = DAT_e000ed94;
    DAT_e000ed94 = uVar2 & 0xfffffffe;
    DAT_e000e010 = 0;
    DAT_e000e018 = 0;
    DAT_e000e014 = 0;
    iVar5 = 0;
    do {
      iVar6 = iVar5 + 1;
      (&DAT_e000e180)[iVar5] = 0xffffffff;
      (&DAT_e000e280)[iVar5] = 0xffffffff;
      iVar5 = iVar6;
    } while (iVar6 != 8);
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setThreadModePrivileged(1);
      bVar3 = (bool)isThreadMode();
      if (bVar3) {
        cVar1 = isUsingMainStack();
        setStackMode(cVar1 == '\x01');
      }
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setMainStackPointer(_DAT_1fff0000);
    }
    enableIRQinterrupts();
    (*_DAT_1fff0004)(uVar4,0xffffffff,_DAT_1fff0000,_DAT_1fff0004,uVar7,uVar8);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  return;
}


// ===================================================================
// FUN_08012600 @ 0x08012600  size=108  body=[[08012600, 0801266b]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_08012600(void)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  bVar3 = FUN_080125cc();
  if (bVar3) {
    uVar4 = FUN_080125e4();
    disableIRQinterrupts();
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    uVar2 = DAT_e000ed24;
    DAT_e000ed24 = uVar2 & 0xfffeffff;
    uVar2 = DAT_e000ed94;
    DAT_e000ed94 = uVar2 & 0xfffffffe;
    DAT_e000e010 = 0;
    DAT_e000e018 = 0;
    DAT_e000e014 = 0;
    iVar5 = 0;
    do {
      iVar6 = iVar5 + 1;
      (&DAT_e000e180)[iVar5] = 0xffffffff;
      (&DAT_e000e280)[iVar5] = 0xffffffff;
      iVar5 = iVar6;
    } while (iVar6 != 8);
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setThreadModePrivileged(1);
      bVar3 = (bool)isThreadMode();
      if (bVar3) {
        cVar1 = isUsingMainStack();
        setStackMode(cVar1 == '\x01');
      }
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setMainStackPointer(_DAT_1fff0000);
    }
    enableIRQinterrupts();
    (*_DAT_1fff0004)(uVar4,0xffffffff,_DAT_1fff0000);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  return;
}


// ===================================================================
// FUN_08012674 @ 0x08012674  size=98  body=[[08012674, 080126d5]]

void FUN_08012674(void)

{
  char cVar1;
  
  cVar1 = DAT_2000203c;
  if (DAT_2000203c == '\0') {
    DAT_2000203c = '\x01';
    FUN_08015338((uint *)&DAT_40020000,0x20,0);
    FUN_08015338((uint *)&DAT_40020000,0x80,0);
    FUN_08015338((uint *)&DAT_40020000,0x40,0);
    FUN_08013a7a(1000);
    FUN_08015338((uint *)&DAT_40020000,0x20,0x29a);
    FUN_08015338((uint *)&DAT_40020000,0x80,0x29a);
    FUN_08015338((uint *)&DAT_40020000,0x40,0x29a);
    FUN_08014142(&DAT_20004b50);
    DAT_20002058 = cVar1;
  }
  return;
}


// ===================================================================
// FUN_080126e8 @ 0x080126e8  size=208  body=[[080126e8, 080127b7]]

undefined1 FUN_080126e8(uint param_1,short param_2,int param_3,uint param_4)

{
  undefined1 uVar1;
  uint uVar2;
  
  if (DAT_20002058 == '\0') {
    uVar1 = 0;
    if (param_1 != 0xffffffff) {
      for (uVar2 = 2; uVar2 < param_4; uVar2 = (uVar2 & 0x7fff) << 1) {
      }
      if (uVar2 - 2 < 0xff) {
        DAT_20002054 = param_2 << 7;
        if (param_3 == 2) {
          DAT_20002054 = DAT_20002054 | 2;
        }
        else if (param_3 == 3) {
          DAT_20002054 = DAT_20002054 | 3;
        }
        else if (param_3 == 1) {
          DAT_20002054 = DAT_20002054 | 1;
        }
        if (uVar2 == 0x20) {
          DAT_20002054 = DAT_20002054 | 0x20;
        }
        else if (uVar2 < 0x21) {
          if (uVar2 == 8) {
            DAT_20002054 = DAT_20002054 | 0x10;
          }
          else if (uVar2 == 0x10) {
            DAT_20002054 = DAT_20002054 | 0x18;
          }
          else if (uVar2 == 4) {
            DAT_20002054 = DAT_20002054 | 8;
          }
        }
        else if (uVar2 == 0x80) {
          DAT_20002054 = DAT_20002054 | 0x30;
        }
        else if (uVar2 == 0x100) {
          DAT_20002054 = DAT_20002054 | 0x38;
        }
        else if (uVar2 == 0x40) {
          DAT_20002054 = DAT_20002054 | 0x28;
        }
        DAT_20002050 = param_1 & 0xf;
        DAT_2000204c = (uint *)(param_1 & 0xfffffff0);
        DAT_20002058 = '\x01';
        FUN_08015338(DAT_2000204c,1 << DAT_20002050,1);
        FUN_08014120(&DAT_20004b50,&DAT_20002040);
        FUN_0801415e(0x20004b50);
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// ===================================================================
// FUN_080127c4 @ 0x080127c4  size=14  body=[[080127c4, 080127d1]]

undefined4 FUN_080127c4(uint param_1,uint param_2)

{
  FUN_080141de(&DAT_20004b50,param_2,param_1);
  return 0;
}


// ===================================================================
// FUN_080127d8 @ 0x080127d8  size=26  body=[[080127d8, 080127f1]]

void FUN_080127d8(void)

{
  if (DAT_20002058 != '\0') {
    FUN_0801417a(0x20004b50);
    FUN_08014142(&DAT_20004b50);
    DAT_20002058 = '\0';
  }
  return;
}


// ===================================================================
// FUN_080127fc @ 0x080127fc  size=2  body=[[080127fc, 080127fd]]

void FUN_080127fc(void)

{
  return;
}


// ===================================================================
// FUN_08012800 @ 0x08012800  size=256  body=[[08012800, 080128ff]]

undefined4 FUN_08012800(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined *puVar8;
  
  uVar5 = (uint)*(byte *)(param_1 + 0x44);
  if ((uVar5 & 0x7f) == 0x21) {
    cVar1 = *(char *)(param_1 + 0x45);
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
LAB_08012852:
      if (cVar1 == '\n') {
        DAT_20002068 = *(undefined1 *)(param_1 + 0x47);
        uVar2 = FUN_08013448(param_1);
        return uVar2;
      }
      if (cVar1 == '\v') {
        if (*(short *)(param_1 + 0x48) == 0) {
          DAT_20000ec6 = *(undefined1 *)(param_1 + 0x46);
        }
        uVar2 = 0;
        *(undefined4 *)(param_1 + 0x38) = 0;
        goto LAB_08012894;
      }
      if ((cVar1 != '\t') || ((*(ushort *)(param_1 + 0x48) & 0xfffd) != 0)) goto LAB_080128aa;
      *(undefined1 **)(param_1 + 0x38) = &DAT_20002064;
      uVar2 = 2;
      uVar6 = 0x8012959;
    }
    else {
      if (cVar1 == '\x02') {
        uVar2 = FUN_080133f8(param_1);
        return uVar2;
      }
      if (cVar1 != '\x03') {
        if (cVar1 == '\x01') {
          uVar2 = FUN_0801319c(param_1,param_2,uVar5,1);
          return uVar2;
        }
        goto LAB_08012852;
      }
      if (*(short *)(param_1 + 0x48) != 0) goto LAB_080128aa;
      *(undefined1 **)(param_1 + 0x38) = &DAT_20000ec6;
      uVar2 = 1;
      uVar6 = 0;
    }
LAB_08012842:
    *(undefined4 *)(param_1 + 0x3c) = uVar2;
    *(undefined4 *)(param_1 + 0x40) = uVar6;
LAB_08012846:
    uVar2 = 1;
  }
  else {
LAB_080128aa:
    if (((uVar5 & 0x9f) == 0x81) && (*(char *)(param_1 + 0x45) == '\x06')) {
      puVar3 = (undefined4 *)
               (**(code **)(*(int *)(param_1 + 4) + 4))
                         (param_1,*(undefined1 *)(param_1 + 0x46),*(undefined1 *)(param_1 + 0x47),
                          *(undefined2 *)(param_1 + 0x48));
      if (puVar3 != (undefined4 *)0x0) {
        uVar2 = *puVar3;
        *(undefined4 *)(param_1 + 0x38) = puVar3[1];
LAB_08012894:
        uVar6 = 0;
        goto LAB_08012842;
      }
    }
    else {
      puVar8 = &DAT_20000f64;
      iVar7 = 3;
      do {
        if ((*(code **)(puVar8 + 0x9c) != (code *)0x0) &&
           (iVar4 = (**(code **)(puVar8 + 0x9c))(param_1), iVar4 != 0)) goto LAB_08012846;
        iVar7 = iVar7 + -1;
        puVar8 = puVar8 + 0xa8;
      } while (iVar7 != 0);
    }
    uVar2 = 0;
  }
  return uVar2;
}


// ===================================================================
// FUN_08012914 @ 0x08012914  size=64  body=[[08012914, 08012953]]

undefined4 * FUN_08012914(int param_1)

{
  undefined4 *puVar1;
  
  DAT_20002060 = 0;
  DAT_2000205c = FUN_08012cb8((uint)*(ushort *)(param_1 + 0x46),
                              (undefined *)(uint)*(ushort *)(param_1 + 0x48),
                              (uint)*(ushort *)(param_1 + 0x4a),&DAT_20002060);
  puVar1 = (undefined4 *)0x0;
  if (DAT_20002060 != 0) {
    puVar1 = &DAT_2000205c;
  }
  return puVar1;
}


// ===================================================================
// FUN_08012958 @ 0x08012958  size=42  body=[[08012958, 08012981]]

void FUN_08012958(int param_1)

{
  if (*(short *)(param_1 + 0x4a) == 2) {
    if ((DAT_20002064 == '\x01') || (DAT_20002064 == '\x06')) {
      DAT_20002067 = DAT_20002065;
      return;
    }
  }
  else {
    DAT_20002067 = DAT_20002064;
  }
  return;
}


// ===================================================================
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


// ===================================================================
// FUN_080129b4 @ 0x080129b4  size=160  body=[[080129b4, 080129bf] [080129c6, 08012a59]]

void FUN_080129b4(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  
  switch(param_2) {
  case 0:
  case 3:
  case 4:
    iVar3 = FUN_0801298c((char)param_2);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    if (iVar3 == 0) {
      DAT_20000ec6 = 1;
    }
    FUN_08012e46((int *)&DAT_20000f64);
    FUN_08012e46((int *)&DAT_2000100c);
    FUN_08012e46((int *)&DAT_200010b4);
    FUN_08012e6e((int *)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  default:
    return;
  case 2:
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08012e94((int *)&DAT_20000f64);
    FUN_08012e94((int *)&DAT_2000100c);
    FUN_08012e94((int *)&DAT_200010b4);
    FUN_08012eb4((int *)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (DAT_20002066 != '\0') {
      FUN_0801298c(5);
    }
    uVar2 = 2;
    break;
  case 5:
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08012e88((int)&DAT_20000f64);
    FUN_08012e88((int)&DAT_2000100c);
    FUN_08012e88((int)&DAT_200010b4);
    FUN_08012e8e((int)&DAT_20000edc);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    uVar2 = 5;
  }
  FUN_0801298c(uVar2);
  return;
}


// ===================================================================
// FUN_08012a74 @ 0x08012a74  size=24  body=[[08012a74, 08012a8b]]

void FUN_08012a74(void)

{
  FUN_08008798(&DAT_200049bd,0,0x10);
  DAT_200049cd = 0;
  DAT_200049ce = 0;
  return;
}


// ===================================================================
// FUN_08012a98 @ 0x08012a98  size=138  body=[[08012a98, 08012b21]]

void FUN_08012a98(void)

{
  undefined *puVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  uint uVar5;
  
LAB_08012a9e:
  uVar5 = (uint)DAT_200049ce;
  bVar3 = false;
switchD_08012b1e_caseD_1:
  if (uVar5 == DAT_200049cd) {
    if (bVar3) {
      DAT_200049ce = (byte)uVar5;
    }
    return;
  }
  bVar3 = true;
  puVar1 = &DAT_200049bd + uVar5;
  uVar5 = uVar5 + 1 & 0xf;
  bVar2 = (byte)uVar5;
  switch(*puVar1) {
  case 0:
    goto switchD_08012b1e_caseD_0;
  default:
    goto switchD_08012b1e_caseD_1;
  case 2:
    cVar4 = '\0';
    if (DAT_20004b33 != '\0') {
      cVar4 = '\x01';
    }
    break;
  case 3:
    cVar4 = '\0';
    break;
  case 4:
    DAT_20002066 = 1;
    DAT_200049ce = bVar2;
    FUN_08012424();
    goto LAB_08012a9e;
  case 5:
    DAT_20002066 = 0;
    DAT_200049ce = bVar2;
    FUN_080124b0();
    thunk_FUN_08012410(DAT_20004b33 != '\0');
    goto LAB_08012a9e;
  }
  DAT_200049ce = bVar2;
  FUN_08012410(cVar4);
  goto LAB_08012a9e;
switchD_08012b1e_caseD_0:
  DAT_200049ce = bVar2;
  FUN_0801243c();
  goto LAB_08012a9e;
}


// ===================================================================
// FUN_08012b50 @ 0x08012b50  size=90  body=[[08012b50, 08012ba9]]

undefined4 FUN_08012b50(char *param_1)

{
  undefined4 uVar1;
  
  FUN_08012da8(0x20000f64);
  FUN_08012e08(0x20000f64);
  FUN_08012da8(0x2000100c);
  FUN_08012e08(0x2000100c);
  FUN_08012da8(0x200010b4);
  FUN_08012e08(0x200010b4);
  FUN_08012de0(0x20000edc);
  FUN_08012e28(0x20000edc);
  FUN_08014242(param_1);
  FUN_08013a7a(5000);
  uVar1 = FUN_0801421c(param_1,&PTR_FUN_080129b4_1_080170c4);
  return uVar1;
}


// ===================================================================
// FUN_08012bb8 @ 0x08012bb8  size=6  body=[[08012bb8, 08012bbd]]

undefined1 FUN_08012bb8(void)

{
  return DAT_20002067;
}


// ===================================================================
// FUN_08012bc4 @ 0x08012bc4  size=26  body=[[08012bc4, 08012bdd]]

void FUN_08012bc4(int param_1,undefined4 *param_2,uint param_3)

{
  FUN_08012fa2((int *)(&DAT_20000f64 + param_1 * 0xa8),param_2,param_3,10000,'\0');
  return;
}


// ===================================================================
// FUN_08012be4 @ 0x08012be4  size=10  body=[[08012be4, 08012bed]]

void FUN_08012be4(undefined4 *param_1)

{
  FUN_08012bc4(1,param_1,8);
  return;
}


// ===================================================================
// FUN_08012bee @ 0x08012bee  size=10  body=[[08012bee, 08012bf7]]

void FUN_08012bee(undefined4 *param_1)

{
  FUN_08012bc4(0,param_1,0x20);
  return;
}


// ===================================================================
// FUN_08012bf8 @ 0x08012bf8  size=10  body=[[08012bf8, 08012c01]]

void FUN_08012bf8(undefined4 *param_1)

{
  FUN_08012bc4(0,param_1,6);
  return;
}


// ===================================================================
// FUN_08012c02 @ 0x08012c02  size=10  body=[[08012c02, 08012c0b]]

void FUN_08012c02(undefined4 *param_1)

{
  FUN_08012bc4(0,param_1,3);
  return;
}


// ===================================================================
// raw_hid_send @ 0x08012c0c  size=16  body=[[08012c0c, 08012c1b]]

// VERIFIED use: called (data,length) at the end of kc_raw_hid_rx for the replying cases exactly
// where keychron_raw_hid.c calls raw_hid_send(data, length)

void raw_hid_send(undefined4 *param_1,int param_2)

{
  if (param_2 == 0x20) {
    FUN_08012bc4(2,param_1,0x20);
    return;
  }
  return;
}


// ===================================================================
// FUN_08012c1c @ 0x08012c1c  size=34  body=[[08012c1c, 08012c3d]]

void FUN_08012c1c(void)

{
  bool bVar1;
  byte abStack_28 [32];
  
  while (bVar1 = FUN_08013078(0x20000edc,(undefined4 *)abStack_28,0x20,0), bVar1) {
    FUN_0800c908(abStack_28,0x20);
  }
  return;
}


// ===================================================================
// thunk_FUN_08012600 @ 0x08012c44  size=4  body=[[08012c44, 08012c47]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void thunk_FUN_08012600(void)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  bVar3 = FUN_080125cc();
  if (bVar3) {
    uVar4 = FUN_080125e4();
    disableIRQinterrupts();
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    uVar2 = DAT_e000ed24;
    DAT_e000ed24 = uVar2 & 0xfffeffff;
    uVar2 = DAT_e000ed94;
    DAT_e000ed94 = uVar2 & 0xfffffffe;
    DAT_e000e010 = 0;
    DAT_e000e018 = 0;
    DAT_e000e014 = 0;
    iVar5 = 0;
    do {
      iVar6 = iVar5 + 1;
      (&DAT_e000e180)[iVar5] = 0xffffffff;
      (&DAT_e000e280)[iVar5] = 0xffffffff;
      iVar5 = iVar6;
    } while (iVar6 != 8);
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setThreadModePrivileged(1);
      bVar3 = (bool)isThreadMode();
      if (bVar3) {
        cVar1 = isUsingMainStack();
        setStackMode(cVar1 == '\x01');
      }
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setMainStackPointer(_DAT_1fff0000);
    }
    enableIRQinterrupts();
    (*_DAT_1fff0004)(uVar4,0xffffffff,_DAT_1fff0000);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  return;
}


// ===================================================================
// FUN_08012c48 @ 0x08012c48  size=2  body=[[08012c48, 08012c49]]

void FUN_08012c48(void)

{
  return;
}


// ===================================================================
// FUN_08012c4a @ 0x08012c4a  size=2  body=[[08012c4a, 08012c4b]]

void FUN_08012c4a(void)

{
  return;
}


// ===================================================================
// FUN_08012c4c @ 0x08012c4c  size=16  body=[[08012c4c, 08012c5b]]

void FUN_08012c4c(void)

{
  thunk_FUN_08012600();
  FUN_08016608();
  FUN_08012c48();
  return;
}


// ===================================================================
// FUN_08012c5c @ 0x08012c5c  size=12  body=[[08012c5c, 08012c67]]

void FUN_08012c5c(void)

{
  FUN_0801668c();
  FUN_08012c4a();
  return;
}


// ===================================================================
// thunk_FUN_0801243c @ 0x08012c68  size=4  body=[[08012c68, 08012c6b]]

void thunk_FUN_0801243c(void)

{
  DAT_2000202c = 1;
  FUN_08012406();
  return;
}


// ===================================================================
// FUN_08012c6c @ 0x08012c6c  size=30  body=[[08012c6c, 08012c89]]

void FUN_08012c6c(void)

{
  FUN_08012a74();
  FUN_08012b50(&DAT_20004ae4);
  DAT_2000206c = &DAT_20000ec8;
  FUN_08013a7a(5000);
  return;
}


// ===================================================================
// thunk_FUN_08012a98 @ 0x08012ca4  size=4  body=[[08012ca4, 08012ca7]]

void thunk_FUN_08012a98(void)

{
  undefined *puVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  uint uVar5;
  
LAB_08012a9e:
  uVar5 = (uint)DAT_200049ce;
  bVar3 = false;
switchD_08012b1e_caseD_1:
  if (uVar5 == DAT_200049cd) {
    if (bVar3) {
      DAT_200049ce = (byte)uVar5;
    }
    return;
  }
  bVar3 = true;
  puVar1 = &DAT_200049bd + uVar5;
  uVar5 = uVar5 + 1 & 0xf;
  bVar2 = (byte)uVar5;
  switch(*puVar1) {
  case 0:
    goto switchD_08012b1e_caseD_0;
  default:
    goto switchD_08012b1e_caseD_1;
  case 2:
    cVar4 = '\0';
    if (DAT_20004b33 != '\0') {
      cVar4 = '\x01';
    }
    break;
  case 3:
    cVar4 = '\0';
    break;
  case 4:
    DAT_20002066 = 1;
    DAT_200049ce = bVar2;
    FUN_08012424();
    goto LAB_08012a9e;
  case 5:
    DAT_20002066 = 0;
    DAT_200049ce = bVar2;
    FUN_080124b0();
    thunk_FUN_08012410(DAT_20004b33 != '\0');
    goto LAB_08012a9e;
  }
  DAT_200049ce = bVar2;
  FUN_08012410(cVar4);
  goto LAB_08012a9e;
switchD_08012b1e_caseD_0:
  DAT_200049ce = bVar2;
  FUN_0801243c();
  goto LAB_08012a9e;
}


// ===================================================================
// FUN_08012ca8 @ 0x08012ca8  size=14  body=[[08012ca8, 08012cb5]]

void FUN_08012ca8(void)

{
  FUN_08012c1c();
  FUN_08013304();
  return;
}


// ===================================================================
// FUN_08012cb8 @ 0x08012cb8  size=90  body=[[08012cb8, 08012d11]]

undefined * FUN_08012cb8(uint param_1,undefined *param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined *puVar1;
  uint uVar2;
  undefined *puVar3;
  
  uVar2 = param_1 >> 8;
  if (uVar2 == 3) {
    puVar1 = (undefined *)(param_1 & 0xff);
    if (puVar1 < (undefined *)0x3) {
      param_2 = &DAT_080170f0;
      puVar3 = (&PTR_DAT_080170f4)[(int)puVar1];
LAB_08012cec:
      puVar1 = (undefined *)(uint)(byte)puVar1[(int)param_2];
      goto LAB_08012ccc;
    }
  }
  else if (uVar2 < 4) {
    if (uVar2 == 1) {
      puVar3 = &DAT_08017197;
      puVar1 = (undefined *)0x12;
      goto LAB_08012ccc;
    }
    if (uVar2 == 2) {
      puVar1 = (undefined *)0x5b;
      puVar3 = &DAT_0801713c;
      goto LAB_08012ccc;
    }
  }
  else if (uVar2 == 0x21) {
    if (param_2 < (undefined *)0x3) {
      puVar1 = (undefined *)0x9;
      puVar3 = (&PTR_DAT_080170e4)[(int)param_2];
      goto LAB_08012ccc;
    }
  }
  else if ((uVar2 == 0x22) && (param_2 < (undefined *)0x3)) {
    puVar1 = &DAT_080170d4;
    puVar3 = (&PTR_DAT_080170d8)[(int)param_2];
    goto LAB_08012cec;
  }
  puVar1 = (undefined *)0x0;
  puVar3 = puVar1;
LAB_08012ccc:
  *param_4 = puVar3;
  return puVar1;
}


// ===================================================================
// FUN_08012d30 @ 0x08012d30  size=58  body=[[08012d30, 08012d69]]

void FUN_08012d30(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_c;
  
  iVar2 = *(int *)(param_1 + 0x34);
  if (((**(char **)(iVar2 + 0x88) == '\x04') &&
      ((1 << *(sbyte *)(iVar2 + 0x8c) & (uint)*(ushort *)(*(char **)(iVar2 + 0x88) + 8)) == 0)) &&
     (local_c = param_2, iVar1 = FUN_08013eba(iVar2,&local_c), iVar1 != 0)) {
    FUN_08014334(*(int *)(iVar2 + 0x88),(uint)*(byte *)(iVar2 + 0x8c),iVar1,local_c);
  }
  return;
}


// ===================================================================
// FUN_08012d6a @ 0x08012d6a  size=54  body=[[08012d6a, 08012d9f]]

void FUN_08012d6a(int param_1)

{
  int iVar1;
  
  if (((**(char **)(param_1 + 0x70) == '\x04') &&
      ((1 << *(sbyte *)(param_1 + 0x74) & (uint)*(ushort *)(*(char **)(param_1 + 0x70) + 10)) == 0))
     && (iVar1 = FUN_08013d68(param_1), iVar1 != 0)) {
    FUN_08014310(*(int *)(param_1 + 0x70),(uint)*(byte *)(param_1 + 0x74),iVar1,
                 *(int *)(param_1 + 0x1c) + -4);
    return;
  }
  return;
}


// ===================================================================
// FUN_08012da0 @ 0x08012da0  size=6  body=[[08012da0, 08012da5]]

void FUN_08012da0(int param_1)

{
  FUN_08012d6a(*(int *)(param_1 + 0x34));
  return;
}


// ===================================================================
// FUN_08012da8 @ 0x08012da8  size=52  body=[[08012da8, 08012ddb]]

void FUN_08012da8(int param_1)

{
  *(int *)(param_1 + 0x4c) = param_1 + 0x5c;
  if (*(char *)(param_1 + 0x84) != '\0') {
    *(int *)(param_1 + 0x50) = param_1 + 0x70;
  }
  FUN_08013e74(param_1,1,*(int *)(param_1 + 0x98),*(int *)(param_1 + 0x94),*(int *)(param_1 + 0x90),
               0x8012d31,param_1);
  return;
}


// ===================================================================
// FUN_08012de0 @ 0x08012de0  size=36  body=[[08012de0, 08012e03]]

void FUN_08012de0(int param_1)

{
  *(int *)(param_1 + 0x50) = param_1 + 0x5c;
  FUN_08013d24(param_1,1,*(int *)(param_1 + 0x80),*(int *)(param_1 + 0x7c),*(int *)(param_1 + 0x78),
               0x8012da1,param_1);
  return;
}


// ===================================================================
// FUN_08012e08 @ 0x08012e08  size=32  body=[[08012e08, 08012e27]]

void FUN_08012e08(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(int *)(*(int *)(param_1 + 0x88) + (uint)*(byte *)(param_1 + 0x8c) * 4 + 0x18) = param_1;
  *(undefined1 *)(param_1 + 0xa0) = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08012e28 @ 0x08012e28  size=30  body=[[08012e28, 08012e45]]

void FUN_08012e28(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(int *)(*(int *)(param_1 + 0x70) + (*(byte *)(param_1 + 0x74) + 9) * 4) = param_1;
  *(undefined1 *)(param_1 + 0x84) = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08012e46 @ 0x08012e46  size=40  body=[[08012e46, 08012e6d]]

void FUN_08012e46(int *param_1)

{
  undefined4 *puVar1;
  
  *(undefined1 *)(param_1 + 2) = 1;
  FUN_08013afa(param_1,-2);
  FUN_08013ea2(param_1);
  puVar1 = (undefined4 *)param_1[0x29];
  if (puVar1 != (undefined4 *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08012e6a. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)puVar1[3])(*puVar1);
    return;
  }
  return;
}


// ===================================================================
// FUN_08012e6e @ 0x08012e6e  size=26  body=[[08012e6e, 08012e87]]

void FUN_08012e6e(int *param_1)

{
  *(undefined1 *)(param_1 + 2) = 1;
  FUN_08013afa(param_1,-2);
  FUN_08013d52(param_1);
  return;
}


// ===================================================================
// FUN_08012e88 @ 0x08012e88  size=6  body=[[08012e88, 08012e8d]]

void FUN_08012e88(int param_1)

{
  *(undefined1 *)(param_1 + 8) = 0;
  return;
}


// ===================================================================
// FUN_08012e8e @ 0x08012e8e  size=6  body=[[08012e8e, 08012e93]]

void FUN_08012e8e(int param_1)

{
  *(undefined1 *)(param_1 + 8) = 0;
  return;
}


// ===================================================================
// FUN_08012e94 @ 0x08012e94  size=32  body=[[08012e94, 08012eb3]]

void FUN_08012e94(int *param_1)

{
  FUN_08014294(param_1[0x22],(uint)*(byte *)(param_1 + 0x23),(int)(param_1 + 0xe));
  FUN_08013ea2(param_1);
  *(undefined1 *)(param_1 + 2) = 0;
  return;
}


// ===================================================================
// FUN_08012eb4 @ 0x08012eb4  size=22  body=[[08012eb4, 08012ec9]]

void FUN_08012eb4(int *param_1)

{
  FUN_08013d52(param_1);
  *(undefined1 *)(param_1 + 2) = 0;
  FUN_08012d6a((int)param_1);
  return;
}


// ===================================================================
// FUN_08012eca @ 0x08012eca  size=150  body=[[08012eca, 08012f5f]]

void FUN_08012eca(int param_1,uint param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int *piVar6;
  uint local_1c;
  undefined4 uStack_18;
  
  piVar6 = *(int **)(param_1 + param_2 * 4 + 0x18);
  if (piVar6 == (int *)0x0) {
    return;
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined1 *)(piVar6 + 0x28) = 0;
  local_1c = param_2;
  uStack_18 = param_3;
  if (((piVar6[4] != piVar6[5]) || (piVar6[3] == 0)) &&
     (**(int **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x14) != 0)) {
    if (piVar6[0x29] != 0) {
      iVar3 = param_1;
      iVar2 = FUN_08013eba((int)piVar6,(int *)&local_1c);
      puVar4 = (undefined4 *)piVar6[0x29];
      (*(code *)puVar4[2])(*puVar4,iVar2,local_1c,puVar4,iVar3);
    }
    FUN_08013ed6(piVar6);
  }
  iVar3 = FUN_08013eba((int)piVar6,(int *)&local_1c);
  uVar5 = local_1c;
  if (iVar3 == 0) {
    piVar6 = *(int **)(param_1 + param_2 * 4 + 0xc);
    if (((*piVar6 != 2) || (*(uint *)piVar6[5] == 0)) ||
       ((*(ushort *)(piVar6 + 4) - 1 & *(uint *)piVar6[5]) != 0)) goto LAB_08012f34;
    iVar3 = param_1 + 0x44;
    uVar5 = 0;
  }
  FUN_08014334(param_1,param_2,iVar3,uVar5);
LAB_08012f34:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08012f60 @ 0x08012f60  size=66  body=[[08012f60, 08012fa1]]

void FUN_08012f60(int param_1,int param_2)

{
  bool bVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + (param_2 + 9) * 4);
  if (piVar2 != (int *)0x0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x18) + 4) != 0) {
      FUN_08013d7c(piVar2,*(undefined4 *)
                           (*(int *)(*(int *)(piVar2[0x1c] + (uint)*(byte *)(piVar2 + 0x1d) * 4 +
                                             0xc) + 0x18) + 4));
    }
    FUN_08012d6a((int)piVar2);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}


// ===================================================================
// FUN_08012fa2 @ 0x08012fa2  size=158  body=[[08012fa2, 0801303f]]

undefined4 FUN_08012fa2(int *param_1,undefined4 *param_2,uint param_3,uint param_4,char param_5)

{
  undefined4 uVar1;
  uint uVar2;
  byte bVar3;
  bool bVar4;
  
  bVar4 = (bool)isCurrentModePrivileged();
  if (bVar4) {
    setBasePriority(0x30);
  }
  uVar1 = 0;
  if (*(char *)param_1[0x22] == '\x04') {
    if (((char)param_1[0x28] != '\0') &&
       (bVar4 = param_4 != 0xffffffff, param_4 = 0xffffffff, bVar4)) {
      param_4 = 0;
    }
    bVar4 = (bool)isCurrentModePrivileged();
    if (bVar4) {
      setBasePriority(0);
    }
    while (uVar2 = FUN_08013f4c((int)param_1,param_2,param_3,param_4), uVar2 < param_3) {
      bVar4 = (bool)isCurrentModePrivileged();
      if (bVar4) {
        setBasePriority(0x30);
      }
      bVar3 = *(byte *)(param_1 + 0x28);
      if (uVar2 == 0) {
        bVar3 = bVar3 | 1;
      }
      *(byte *)(param_1 + 0x28) = bVar3;
      *(undefined1 *)(param_1 + 2) = 1;
      FUN_08013afa(param_1,-2);
      FUN_08013ea2(param_1);
      *(undefined1 *)(param_1 + 2) = 0;
      FUN_08013950();
      bVar4 = (bool)isCurrentModePrivileged();
      if (bVar4) {
        setBasePriority(0);
      }
    }
    if (param_5 == '\0') {
      FUN_08013fd2((int)param_1);
    }
    uVar1 = 1;
  }
  else {
    bVar4 = (bool)isCurrentModePrivileged();
    if (bVar4) {
      setBasePriority(0);
    }
  }
  return uVar1;
}


// ===================================================================
// FUN_08013040 @ 0x08013040  size=56  body=[[08013040, 08013077]]

undefined4 FUN_08013040(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  if (*(int *)(param_1 + 0x10) == *(int *)(param_1 + 0x14)) {
    if (*(int *)(param_1 + 0xc) == 0) {
      uVar2 = 0;
    }
    else if ((1 << *(sbyte *)(param_1 + 0x8c) & (uint)*(ushort *)(*(int *)(param_1 + 0x88) + 8)) ==
             0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return uVar2;
}


// ===================================================================
// FUN_08013078 @ 0x08013078  size=76  body=[[08013078, 080130c3]]

bool FUN_08013078(int param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  bool bVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = (bool)isCurrentModePrivileged();
  if (bVar3) {
    setBasePriority(0x30);
  }
  bVar3 = false;
  if (**(char **)(param_1 + 0x70) == '\x04') {
    if ((*(char *)(param_1 + 0x84) != '\0') &&
       (bVar3 = param_4 != 0xffffffff, param_4 = 0xffffffff, bVar3)) {
      param_4 = 0;
    }
    bVar3 = (bool)isCurrentModePrivileged();
    if (bVar3) {
      setBasePriority(0);
    }
    uVar2 = FUN_08013df2(param_1,param_2,param_3,param_4);
    *(bool *)(param_1 + 0x84) = uVar2 == 0;
    bVar3 = param_3 == uVar2;
  }
  else {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return bVar3;
}


// ===================================================================
// FUN_080130c4 @ 0x080130c4  size=38  body=[[080130c4, 080130e9]]

void FUN_080130c4(int *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (iVar2 != 0) {
    uVar1 = FUN_08013cfa();
    *(undefined4 *)(iVar2 + 4) = uVar1;
    iVar2 = *param_1;
    *(uint *)(iVar2 + 0x48) = param_3;
    memcpy((undefined4 *)(iVar2 + 8),param_2,param_3);
    return;
  }
  return;
}


// ===================================================================
// FUN_080130ea @ 0x080130ea  size=22  body=[[080130ea, 080130ff]]

void FUN_080130ea(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x48);
    *(uint *)(param_3 + 0x48) = uVar2;
    memcpy((undefined4 *)(param_3 + 8),(undefined4 *)(iVar1 + 8),uVar2);
    return;
  }
  return;
}


// ===================================================================
// FUN_08013100 @ 0x08013100  size=28  body=[[08013100, 0801311b]]

void FUN_08013100(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    FUN_08008798((byte *)(iVar1 + 8),0,*(uint *)(iVar1 + 0x48));
    puVar2 = (undefined4 *)*param_1;
    *puVar2 = 0;
    puVar2[1] = 0;
  }
  return;
}


// ===================================================================
// FUN_0801311c @ 0x0801311c  size=60  body=[[0801311c, 08013157]]

void FUN_0801311c(int param_1,byte *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*param_2 < 9) {
    iVar2 = (int)(short)(ushort)*param_2;
    iVar3 = *(int *)(param_1 + iVar2 * 4);
    if (iVar3 != 0) {
      uVar1 = FUN_08013cfa();
      *(undefined4 *)(iVar3 + 4) = uVar1;
      iVar2 = *(int *)(param_1 + iVar2 * 4);
      *(uint *)(iVar2 + 0x48) = param_3;
      memcpy((undefined4 *)(iVar2 + 8),(undefined4 *)param_2,param_3);
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_08013158 @ 0x08013158  size=28  body=[[08013158, 08013173]]

void FUN_08013158(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if ((param_2 < 9) && (iVar1 = *(int *)(param_1 + param_2 * 4), iVar1 != 0)) {
    uVar2 = *(uint *)(iVar1 + 0x48);
    *(uint *)(param_3 + 0x48) = uVar2;
    memcpy((undefined4 *)(param_3 + 8),(undefined4 *)(iVar1 + 8),uVar2);
    return;
  }
  return;
}


// ===================================================================
// FUN_08013174 @ 0x08013174  size=38  body=[[08013174, 08013199]]

void FUN_08013174(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  piVar3 = (int *)(param_1 + -4);
  do {
    piVar3 = piVar3 + 1;
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      FUN_08008798((byte *)(iVar1 + 8),0,*(uint *)(iVar1 + 0x48));
      puVar2 = (undefined4 *)*piVar3;
      *puVar2 = 0;
      puVar2[1] = 0;
    }
  } while (piVar3 != (int *)(param_1 + 0x20));
  return;
}


// ===================================================================
// FUN_0801319c @ 0x0801319c  size=74  body=[[0801319c, 080131e5]]

undefined4 FUN_0801319c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      (*(code *)puVar1[1])
                (*puVar1,*(byte *)(param_1 + 0x46),&DAT_200022a0,(code *)puVar1[1],param_4);
      *(undefined **)(param_1 + 0x38) = &DAT_200022a8;
      *(undefined4 *)(param_1 + 0x3c) = DAT_200022e8;
      *(undefined4 *)(param_1 + 0x40) = 0;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ===================================================================
// FUN_080131f4 @ 0x080131f4  size=24  body=[[080131f4, 0801320b]]

void FUN_080131f4(undefined4 *param_1,undefined4 param_2,int param_3)

{
  if (((int *)*param_1 != (int *)0x0) && (*(int *)*param_1 = param_3 << 2, param_3 != 0)) {
    DAT_200022ec = DAT_200022ec | 1;
  }
  return;
}


// ===================================================================
// FUN_08013210 @ 0x08013210  size=12  body=[[08013210, 0801321b]]

uint FUN_08013210(int *param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((uint *)*param_1 != (uint *)0x0) {
    uVar1 = (*(uint *)*param_1 & 0x3ff) >> 2;
  }
  return uVar1;
}


// ===================================================================
// FUN_0801321c @ 0x0801321c  size=72  body=[[0801321c, 08013263]]

undefined8 FUN_0801321c(int *param_1,undefined4 param_2)

{
  bool bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  
  if (*param_1 != 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    uVar3 = *(uint *)*param_1;
    uVar5 = ((uint *)*param_1)[1];
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (uVar3 != 0) {
      iVar4 = FUN_08013cfa();
      lVar2 = (ulonglong)(iVar4 - uVar5) * 1000 + 99999;
      uVar6 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
      param_2 = (undefined4)((ulonglong)uVar6 >> 0x20);
      uVar3 = (uint)(uVar3 <= (uint)uVar6);
      goto LAB_08013224;
    }
  }
  uVar3 = 0;
LAB_08013224:
  return CONCAT44(param_2,uVar3);
}


// ===================================================================
// FUN_0801326c @ 0x0801326c  size=32  body=[[0801326c, 0801328b]]

void FUN_0801326c(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  if (((param_2 - 1U < 8) && (piVar1 = *(int **)(param_1 + param_2 * 4), piVar1 != (int *)0x0)) &&
     (*piVar1 = param_3 << 2, param_3 != 0)) {
    DAT_200022ec = DAT_200022ec | 1;
  }
  return;
}


// ===================================================================
// FUN_08013290 @ 0x08013290  size=22  body=[[08013290, 080132a5]]

uint FUN_08013290(int param_1,uint param_2)

{
  uint *puVar1;
  
  if ((param_2 < 9) && (puVar1 = *(uint **)(param_1 + param_2 * 4), puVar1 != (uint *)0x0)) {
    return (*puVar1 & 0x3ff) >> 2;
  }
  return 0;
}


// ===================================================================
// FUN_080132a8 @ 0x080132a8  size=84  body=[[080132a8, 080132fb]]

undefined8 FUN_080132a8(int param_1,uint param_2)

{
  bool bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  undefined8 uVar7;
  
  if ((param_2 < 9) && (param_2 = (uint)(short)param_2, *(int *)(param_1 + param_2 * 4) != 0)) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    puVar5 = *(uint **)(param_1 + param_2 * 4);
    uVar3 = *puVar5;
    uVar6 = puVar5[1];
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (uVar3 != 0) {
      iVar4 = FUN_08013cfa();
      lVar2 = (ulonglong)(iVar4 - uVar6) * 1000 + 99999;
      uVar7 = FUN_08008158((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),100000,0);
      param_2 = (uint)((ulonglong)uVar7 >> 0x20);
      uVar3 = (uint)(uVar3 <= (uint)uVar7);
      goto LAB_080132b0;
    }
  }
  uVar3 = 0;
LAB_080132b0:
  return CONCAT44(param_2,uVar3);
}


// ===================================================================
// FUN_08013304 @ 0x08013304  size=232  body=[[08013304, 080133eb]]

void FUN_08013304(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  char cVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  
  cVar6 = DAT_200022ec;
  if (DAT_200022ec != '\0') {
    uVar5 = 0;
    puVar7 = &DAT_20000f64;
    cVar6 = '\0';
    do {
      puVar4 = *(undefined4 **)(puVar7 + 0xa4);
      if (puVar4 != (undefined4 *)0x0) {
        if (uVar5 == 0) {
          uVar8 = 1;
          do {
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0x30);
            }
            uVar9 = uVar8 & 0xff;
            iVar2 = (*(code *)puVar4[5])(*puVar4,uVar9);
            if (iVar2 != 0) {
              cVar6 = '\x01';
            }
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0);
            }
            iVar2 = FUN_08013040(0x20000f64);
            if ((iVar2 != 0) && (iVar2 = (*(code *)puVar4[6])(*puVar4,uVar9), iVar2 != 0)) {
              bVar1 = (bool)isCurrentModePrivileged();
              if (bVar1) {
                setBasePriority(0x30);
              }
              (*(code *)puVar4[1])(*puVar4,uVar9,&DAT_20002254);
              bVar1 = (bool)isCurrentModePrivileged();
              if (bVar1) {
                setBasePriority(0);
              }
              FUN_08012bc4(0,(undefined4 *)&DAT_2000225c,DAT_2000229c);
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 != 9);
        }
        else {
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          iVar2 = (*(code *)puVar4[5])(*puVar4,0);
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0);
          }
          iVar3 = FUN_08013040((int)puVar7);
          if ((iVar3 != 0) && (iVar3 = (*(code *)puVar4[6])(*puVar4,0), iVar3 != 0)) {
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0x30);
            }
            (*(code *)puVar4[1])(*puVar4,0,&DAT_20002254);
            bVar1 = (bool)isCurrentModePrivileged();
            if (bVar1) {
              setBasePriority(0);
            }
            FUN_08012bc4(uVar5 & 0xff,(undefined4 *)&DAT_2000225c,DAT_2000229c);
          }
          if (iVar2 != 0) {
            cVar6 = '\x01';
          }
        }
      }
      uVar5 = uVar5 + 1;
      puVar7 = puVar7 + 0xa8;
    } while (uVar5 != 3);
  }
  DAT_200022ec = cVar6;
  return;
}


// ===================================================================
// FUN_080133f8 @ 0x080133f8  size=68  body=[[080133f8, 0801343b]]

undefined4 FUN_080133f8(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      DAT_20002250 = (*(code *)puVar1[5])(*puVar1);
      *(undefined1 **)(param_1 + 0x38) = &DAT_20002250;
      uVar2 = 1;
      *(undefined4 *)(param_1 + 0x3c) = 1;
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ===================================================================
// FUN_08013448 @ 0x08013448  size=68  body=[[08013448, 0801348b]]

undefined4 FUN_08013448(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 0x48) < 3) && (*(byte *)(param_1 + 0x46) < 9)) &&
     ((byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] < 3)) {
    puVar1 = (undefined4 *)
             (&DAT_20001008)[(uint)(byte)(&DAT_200013a4)[*(byte *)(param_1 + 0x48)] * 0x2a];
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      (*(code *)puVar1[4])(*puVar1,*(byte *)(param_1 + 0x46),*(undefined1 *)(param_1 + 0x47));
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ===================================================================
// FUN_08013494 @ 0x08013494  size=12  body=[[08013494, 0801349f]]

void FUN_08013494(void)

{
  DAT_200049d0 = &DAT_20004b88;
  DAT_200049d4 = 0x20010000;
  return;
}


// ===================================================================
// FUN_080134ac @ 0x080134ac  size=38  body=[[080134ac, 080134d1]]

uint FUN_080134ac(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_3 + DAT_200049d0 + param_2 + -1 & -param_2;
  uVar1 = param_1 + uVar2;
  if ((DAT_200049d4 < uVar1) || (uVar1 < DAT_200049d0)) {
    uVar2 = 0;
    uVar1 = DAT_200049d0;
  }
  DAT_200049d0 = uVar1;
  return uVar2;
}


// ===================================================================
// FUN_080134d8 @ 0x080134d8  size=20  body=[[080134d8, 080134eb]]

void FUN_080134d8(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080134ac(param_1,param_2,param_3);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_080134ec @ 0x080134ec  size=2  body=[[080134ec, 080134ed]]

void FUN_080134ec(void)

{
  return;
}


// ===================================================================
// FUN_080134ee @ 0x080134ee  size=2  body=[[080134ee, 080134ef]]

void FUN_080134ee(void)

{
  return;
}


// ===================================================================
// FUN_080134f4 @ 0x080134f4  size=82  body=[[080134f4, 08013545]]

void FUN_080134f4(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  
  piVar7 = &DAT_080172c8;
  iVar8 = 8;
  do {
    puVar4 = (undefined4 *)piVar7[2];
    puVar5 = (undefined4 *)(*piVar7 + -4);
    puVar1 = (undefined4 *)piVar7[1];
    for (puVar3 = puVar1; puVar3 < puVar4; puVar3 = puVar3 + 1) {
      puVar5 = puVar5 + 1;
      *puVar3 = *puVar5;
    }
    uVar6 = (int)puVar4 + (3 - (int)puVar1) & 0xfffffffc;
    if (puVar4 < (undefined4 *)((int)puVar1 - 3U)) {
      uVar6 = 0;
    }
    pbVar2 = (byte *)((int)puVar1 + uVar6);
    uVar6 = (uint)((byte *)piVar7[3] + (3 - (int)pbVar2)) & 0xfffffffc;
    if ((byte *)piVar7[3] < pbVar2 + -3) {
      uVar6 = 0;
    }
    FUN_08008798(pbVar2,0,uVar6);
    iVar8 = iVar8 + -1;
    piVar7 = piVar7 + 4;
  } while (iVar8 != 0);
  return;
}


// ===================================================================
// FUN_0801354c @ 0x0801354c  size=34  body=[[0801354c, 0801356d]]

void FUN_0801354c(void)

{
  bool bVar1;
  
  DAT_200049d8 = 1;
  DAT_200049dc = 0;
  FUN_08013494();
  FUN_0801396c(0x200049e0,0x8017348);
  DAT_200049d8 = 2;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_0801357c @ 0x0801357c  size=14  body=[[0801357c, 08013589]]

void FUN_0801357c(void)

{
  disableIRQinterrupts();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


// ===================================================================
// thunk_FUN_08013774 @ 0x08013594  size=4  body=[[08013594, 08013597]]

void thunk_FUN_08013774(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  while( true ) {
    do {
      piVar2 = DAT_200049f0;
      iVar3 = FUN_08013cfa();
      uVar4 = piVar2[2];
      if ((uint)(iVar3 - DAT_200049fc) < uVar4) {
        if ((int **)DAT_200049f0 == &DAT_200049f0) {
          return;
        }
        uVar4 = (DAT_200049fc + uVar4) - iVar3;
        DAT_200049fc = iVar3;
        piVar2[2] = uVar4;
        FUN_08013616(iVar3,uVar4);
        return;
      }
      iVar3 = *piVar2;
      iVar7 = DAT_200049fc + uVar4;
      piVar5 = (int *)piVar2[1];
      DAT_200049fc = iVar7;
      *piVar5 = iVar3;
      *(int **)(iVar3 + 4) = piVar5;
      *piVar2 = 0;
      if ((int **)DAT_200049f0 == &DAT_200049f0) {
        FUN_08013d12();
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      (*(code *)piVar2[3])(piVar2,piVar2[4]);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
    } while (piVar2[5] == 0);
    iVar3 = FUN_08013cfa();
    uVar4 = iVar3 - iVar7;
    if ((uint)piVar2[5] < uVar4) {
      FUN_080135dc(2);
      uVar6 = 0;
    }
    else {
      uVar6 = (piVar2[5] + iVar7) - iVar3;
    }
    if ((int **)DAT_200049f0 == &DAT_200049f0) break;
    if (!CARRY4(uVar6,uVar4)) {
      uVar6 = uVar6 + uVar4;
    }
    FUN_080135ec((int *)&DAT_200049f0,piVar2,uVar6);
  }
  FUN_0801364c(piVar2,iVar3,uVar6);
  return;
}


// ===================================================================
// FUN_08013598 @ 0x08013598  size=18  body=[[08013598, 080135a9]]

void FUN_08013598(void)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = 0;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    iVar2 = getBasePriority();
  }
  if (iVar2 == 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      getCurrentExceptionNumber();
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
  }
  return;
}


// ===================================================================
// FUN_080135aa @ 0x080135aa  size=30  body=[[080135aa, 080135c7]]

void FUN_080135aa(int param_1)

{
  bool bVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    uVar2 = 0;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      uVar2 = getCurrentExceptionNumber();
      uVar2 = uVar2 & 0x1ff;
    }
    if (uVar2 == 0) {
      FUN_08013950();
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    else {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
  }
  return;
}


// ===================================================================
// FUN_080135c8 @ 0x080135c8  size=14  body=[[080135c8, 080135d5]]

void FUN_080135c8(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_e0001004;
  do {
    iVar2 = DAT_e0001004;
  } while ((uint)(iVar2 - iVar1) < param_1);
  return;
}


// ===================================================================
// FUN_080135dc @ 0x080135dc  size=10  body=[[080135dc, 080135e5]]

void FUN_080135dc(uint param_1)

{
  DAT_20004a0c = DAT_20004a0c | param_1;
  return;
}


// ===================================================================
// FUN_080135ec @ 0x080135ec  size=42  body=[[080135ec, 08013615]]

void FUN_080135ec(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  
  for (piVar1 = (int *)*param_1; (uint)piVar1[2] < param_3; piVar1 = (int *)*piVar1) {
    param_3 = param_3 - piVar1[2];
  }
  puVar2 = (undefined4 *)piVar1[1];
  param_2[2] = param_3;
  *param_2 = (int)piVar1;
  param_2[1] = (int)puVar2;
  *puVar2 = param_2;
  piVar1[1] = (int)param_2;
  piVar1[2] = piVar1[2] - param_3;
  param_1[2] = -1;
  return;
}


// ===================================================================
// FUN_08013616 @ 0x08013616  size=54  body=[[08013616, 0801364b]]

void FUN_08013616(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 < 2) {
    param_2 = 2;
  }
  uVar2 = 2;
  while( true ) {
    FUN_08013d1c(param_1 + param_2);
    iVar1 = FUN_08013cfa();
    if ((uint)(iVar1 - param_1) < param_2) break;
    param_2 = uVar2 + 1;
    param_1 = iVar1;
    uVar2 = param_2;
  }
  if (2 < uVar2) {
    FUN_080135dc(1);
    return;
  }
  return;
}


// ===================================================================
// FUN_0801364c @ 0x0801364c  size=82  body=[[0801364c, 0801369d]]

void FUN_0801364c(int *param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  DAT_200049fc = param_2;
  param_1[2] = param_3;
  param_1[1] = (int)&DAT_200049f0;
  *param_1 = (int)DAT_200049f0;
  if (param_3 < 2) {
    param_3 = 2;
  }
  *(int **)((int)DAT_200049f0 + 4) = param_1;
  DAT_200049f0 = param_1;
  FUN_08013d02(param_2 + param_3);
  uVar2 = 2;
  while (iVar1 = FUN_08013cfa(), param_3 <= (uint)(iVar1 - param_2)) {
    param_3 = uVar2 + 1;
    FUN_08013d1c(param_2 + param_3);
    param_2 = iVar1;
    uVar2 = param_3;
  }
  if (2 < uVar2) {
    FUN_080135dc(1);
    return;
  }
  return;
}


// ===================================================================
// FUN_080136a4 @ 0x080136a4  size=72  body=[[080136a4, 080136eb]]

void FUN_080136a4(int *param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_08013cfa();
  if ((undefined4 **)DAT_200049f0 == &DAT_200049f0) {
    FUN_0801364c(param_1,iVar1,param_2);
    return;
  }
  uVar2 = param_2 + (iVar1 - DAT_200049fc);
  if (CARRY4(param_2,iVar1 - DAT_200049fc)) {
    uVar2 = param_2;
  }
  if (uVar2 < (uint)DAT_200049f0[2]) {
    FUN_08013616(iVar1,param_2);
  }
  FUN_080135ec((int *)&DAT_200049f0,param_1,uVar2);
  return;
}


// ===================================================================
// FUN_080136f4 @ 0x080136f4  size=18  body=[[080136f4, 08013705]]

void FUN_080136f4(int *param_1,uint param_2,int param_3,int param_4)

{
  param_1[4] = param_4;
  param_1[3] = param_3;
  param_1[5] = 0;
  FUN_080136a4(param_1,param_2);
  return;
}


// ===================================================================
// FUN_08013708 @ 0x08013708  size=102  body=[[08013708, 0801376d]]

void FUN_08013708(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 == DAT_200049f0) {
    DAT_200049f0 = (int *)*param_1;
    DAT_200049f0[1] = (int)&DAT_200049f0;
    *param_1 = 0;
    if ((int **)DAT_200049f0 == &DAT_200049f0) {
      FUN_08013d12();
      return;
    }
    DAT_200049f0[2] = DAT_200049f0[2] + param_1[2];
    iVar1 = FUN_08013cfa();
    if ((uint)(iVar1 - DAT_200049fc) < (uint)DAT_200049f0[2]) {
      FUN_08013616(iVar1,(DAT_200049fc + DAT_200049f0[2]) - iVar1);
      return;
    }
  }
  else {
    iVar3 = *param_1;
    piVar2 = (int *)param_1[1];
    iVar1 = param_1[2];
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
    *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + iVar1;
    *param_1 = 0;
    DAT_200049f8 = 0xffffffff;
  }
  return;
}


// ===================================================================
// FUN_08013774 @ 0x08013774  size=188  body=[[08013774, 0801382f]]

void FUN_08013774(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  while( true ) {
    do {
      piVar2 = DAT_200049f0;
      iVar3 = FUN_08013cfa();
      uVar4 = piVar2[2];
      if ((uint)(iVar3 - DAT_200049fc) < uVar4) {
        if ((int **)DAT_200049f0 == &DAT_200049f0) {
          return;
        }
        uVar4 = (DAT_200049fc + uVar4) - iVar3;
        DAT_200049fc = iVar3;
        piVar2[2] = uVar4;
        FUN_08013616(iVar3,uVar4);
        return;
      }
      iVar3 = *piVar2;
      iVar7 = DAT_200049fc + uVar4;
      piVar5 = (int *)piVar2[1];
      DAT_200049fc = iVar7;
      *piVar5 = iVar3;
      *(int **)(iVar3 + 4) = piVar5;
      *piVar2 = 0;
      if ((int **)DAT_200049f0 == &DAT_200049f0) {
        FUN_08013d12();
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      (*(code *)piVar2[3])(piVar2,piVar2[4]);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
    } while (piVar2[5] == 0);
    iVar3 = FUN_08013cfa();
    uVar4 = iVar3 - iVar7;
    if ((uint)piVar2[5] < uVar4) {
      FUN_080135dc(2);
      uVar6 = 0;
    }
    else {
      uVar6 = (piVar2[5] + iVar7) - iVar3;
    }
    if ((int **)DAT_200049f0 == &DAT_200049f0) break;
    if (!CARRY4(uVar6,uVar4)) {
      uVar6 = uVar6 + uVar4;
    }
    FUN_080135ec((int *)&DAT_200049f0,piVar2,uVar6);
  }
  FUN_0801364c(piVar2,iVar3,uVar6);
  return;
}


// ===================================================================
// FUN_08013838 @ 0x08013838  size=28  body=[[08013838, 08013853]]

void FUN_08013838(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined1 *)(param_1 + 5) = 0;
  piVar2 = (int *)param_1[4];
  do {
    piVar2 = (int *)*piVar2;
  } while ((uint)param_1[2] <= (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_1 = (int)piVar2;
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  piVar2[1] = (int)param_1;
  return;
}


// ===================================================================
// FUN_08013854 @ 0x08013854  size=28  body=[[08013854, 0801386f]]

void FUN_08013854(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined1 *)(param_1 + 5) = 0;
  piVar2 = (int *)param_1[4];
  do {
    piVar2 = (int *)*piVar2;
  } while ((uint)param_1[2] < (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_1 = (int)piVar2;
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  piVar2[1] = (int)param_1;
  return;
}


// ===================================================================
// FUN_08013870 @ 0x08013870  size=62  body=[[08013870, 08013885] [0801388c, 080138b3]]

void FUN_08013870(undefined4 param_1,int *param_2)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  switch((char)param_2[5]) {
  case '\0':
    goto switchD_08013882_caseD_0;
  case '\x03':
    *(undefined4 *)param_2[6] = 0;
    break;
  case '\x05':
    *(int *)(param_2[6] + 8) = *(int *)(param_2[6] + 8) + 1;
  case '\x04':
    piVar2 = (int *)param_2[1];
    iVar3 = *param_2;
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
  }
  param_2[6] = -1;
  FUN_08013838(param_2);
switchD_08013882_caseD_0:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// thunk_FUN_08013838 @ 0x080138b4  size=4  body=[[080138b4, 080138b7]]

void thunk_FUN_08013838(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined1 *)(param_1 + 5) = 0;
  piVar2 = (int *)param_1[4];
  do {
    piVar2 = (int *)*piVar2;
  } while ((uint)param_1[2] <= (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_1 = (int)piVar2;
  param_1[1] = (int)puVar1;
  *puVar1 = param_1;
  piVar2[1] = (int)param_1;
  return;
}


// ===================================================================
// FUN_080138b8 @ 0x080138b8  size=24  body=[[080138b8, 080138cf]]

void FUN_080138b8(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = (int)DAT_200049ec;
  *(undefined1 *)((int)DAT_200049ec + 0x14) = param_1;
  DAT_200049ec = DAT_200049e0;
  DAT_200049e0 = (int *)*DAT_200049e0;
  *(int ***)((int)DAT_200049e0 + 4) = &DAT_200049e0;
  *(undefined1 *)(DAT_200049ec + 5) = 1;
  FUN_08008124(DAT_200049ec,iVar1);
  return;
}


// ===================================================================
// FUN_080138d4 @ 0x080138d4  size=52  body=[[080138d4, 08013907]]

undefined4 FUN_080138d4(undefined1 param_1,uint param_2)

{
  int iVar1;
  int local_28 [7];
  
  iVar1 = DAT_200049ec;
  if (param_2 == 0xffffffff) {
    FUN_080138b8(param_1);
  }
  else {
    FUN_080136f4(local_28,param_2,0x8013871,DAT_200049ec);
    FUN_080138b8(param_1);
    if (local_28[0] != 0) {
      FUN_08013708(local_28);
    }
  }
  return *(undefined4 *)(iVar1 + 0x18);
}


// ===================================================================
// FUN_08013910 @ 0x08013910  size=20  body=[[08013910, 08013923]]

bool FUN_08013910(void)

{
  return *(uint *)(DAT_200049ec + 8) < *(uint *)(DAT_200049e0 + 8);
}


// ===================================================================
// FUN_08013928 @ 0x08013928  size=36  body=[[08013928, 0801394b]]

void FUN_08013928(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = DAT_200049ec;
  piVar1 = DAT_200049e0;
  DAT_200049e0 = (int *)*DAT_200049e0;
  *(int ***)((int)DAT_200049e0 + 4) = &DAT_200049e0;
  *(undefined1 *)(piVar1 + 5) = 1;
  DAT_200049ec = piVar1;
  iVar3 = FUN_08013854(piVar2);
  FUN_08008124(piVar1,iVar3);
  return;
}


// ===================================================================
// FUN_08013950 @ 0x08013950  size=20  body=[[08013950, 08013963]]

void FUN_08013950(void)

{
  if (*(uint *)(DAT_200049ec + 8) < *(uint *)(DAT_200049e0 + 8)) {
    FUN_08013928();
    return;
  }
  return;
}


// ===================================================================
// FUN_08013968 @ 0x08013968  size=4  body=[[08013968, 0801396b]]

void FUN_08013968(void)

{
  do {
    WaitForInterrupt();
  } while( true );
}


// ===================================================================
// FUN_0801396c @ 0x0801396c  size=110  body=[[0801396c, 080139d9]]

void FUN_0801396c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  *(int *)(param_1 + 0x30) = param_2;
  *(undefined4 *)(param_1 + 0x28) = 0;
  DAT_200049dc = param_1;
  FUN_08013c34();
  *(int *)(param_1 + 0x10) = param_1 + 0x10;
  *(int *)(param_1 + 0x14) = param_1 + 0x10;
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  uVar1 = FUN_08013cfa();
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  iVar2 = FUN_080139ec(param_1,param_1 + 0x34,&DAT_0801680c,0x80);
  *(int *)(param_1 + 0xc) = iVar2;
  *(undefined1 *)(iVar2 + 0x14) = 1;
  local_28 = &DAT_08016811;
  local_24 = *(undefined4 *)(param_2 + 4);
  local_20 = *(undefined4 *)(param_2 + 8);
  uStack_1c = 1;
  local_18 = 0x8013969;
  uStack_14 = 0;
  FUN_08013a50((int)&local_28);
  return;
}


// ===================================================================
// FUN_080139ec @ 0x080139ec  size=20  body=[[080139ec, 080139ff]]

int FUN_080139ec(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_2 + 8) = param_4;
  *(undefined4 *)(param_2 + 0x24) = param_4;
  *(undefined4 *)(param_2 + 0x10) = param_1;
  *(undefined2 *)(param_2 + 0x14) = 2;
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  return param_2;
}


// ===================================================================
// FUN_08013a00 @ 0x08013a00  size=70  body=[[08013a00, 08013a45]]

int FUN_08013a00(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  *(int *)(iVar2 + -0x1c) = iVar2 + -0x8c;
  *(undefined4 *)(iVar2 + -0x4c) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(iVar2 + -0x48) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(iVar2 + -0x2c) = 0x800813d;
  *(undefined1 *)(iVar2 + -0x14) = 2;
  *(undefined4 **)(iVar2 + -0x18) = &DAT_200049e0;
  *(undefined4 *)(iVar2 + -0x20) = uVar1;
  *(undefined1 *)(iVar2 + -0x13) = 0;
  *(undefined4 *)(iVar2 + -4) = uVar1;
  *(undefined4 *)(iVar2 + -8) = 0;
  *(undefined4 *)(iVar2 + -0xc) = 0;
  return iVar2 + -0x28;
}


// ===================================================================
// FUN_08013a50 @ 0x08013a50  size=14  body=[[08013a50, 08013a5d]]

void FUN_08013a50(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_08013a00(param_1);
  thunk_FUN_08013838(piVar1);
  return;
}


// ===================================================================
// FUN_08013a60 @ 0x08013a60  size=12  body=[[08013a60, 08013a6b]]

void FUN_08013a60(undefined4 param_1)

{
  *(undefined4 *)(DAT_200049ec + 0x18) = param_1;
  FUN_080138b8(0xf);
  return;
}


// ===================================================================
// thunk_FUN_08013a60 @ 0x08013a70  size=10  body=[[08013a70, 08013a79]]

void thunk_FUN_08013a60(undefined4 param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013a60(param_1);
  return;
}


// ===================================================================
// FUN_08013a7a @ 0x08013a7a  size=24  body=[[08013a7a, 08013a91]]

void FUN_08013a7a(uint param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080138d4(8,param_1);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08013ab0 @ 0x08013ab0  size=18  body=[[08013ab0, 08013ac1]]

void FUN_08013ab0(undefined4 *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    *param_1 = 0;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
    return;
  }
  return;
}


// ===================================================================
// FUN_08013ac4 @ 0x08013ac4  size=28  body=[[08013ac4, 08013adf]]

undefined4 FUN_08013ac4(int param_1,uint param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  
  piVar1 = DAT_200049ec;
  if (param_2 != 0) {
    piVar3 = *(int **)(param_1 + 4);
    *DAT_200049ec = param_1;
    piVar1[1] = (int)piVar3;
    *piVar3 = (int)piVar1;
    *(int **)(param_1 + 4) = piVar1;
    uVar2 = FUN_080138d4(4,param_2);
    return uVar2;
  }
  return 0xffffffff;
}


// ===================================================================
// FUN_08013ae4 @ 0x08013ae4  size=22  body=[[08013ae4, 08013af9]]

void FUN_08013ae4(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (param_1 != piVar1) {
    iVar2 = *piVar1;
    *param_1 = iVar2;
    *(int **)(iVar2 + 4) = param_1;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
    return;
  }
  return;
}


// ===================================================================
// FUN_08013afa @ 0x08013afa  size=28  body=[[08013afa, 08013b15]]

void FUN_08013afa(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  while (piVar1 = (int *)*param_1, param_1 != piVar1) {
    iVar2 = *piVar1;
    *param_1 = iVar2;
    *(int **)(iVar2 + 4) = param_1;
    piVar1[6] = param_2;
    thunk_FUN_08013838(piVar1);
  }
  return;
}


// ===================================================================
// FUN_08013b16 @ 0x08013b16  size=30  body=[[08013b16, 08013b33]]

void FUN_08013b16(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  piVar2 = param_1;
  do {
    piVar2 = (int *)*piVar2;
    if (param_1 == piVar2) break;
  } while ((uint)param_2[2] <= (uint)piVar2[2]);
  puVar1 = (undefined4 *)piVar2[1];
  *param_2 = (int)piVar2;
  param_2[1] = (int)puVar1;
  *puVar1 = param_2;
  piVar2[1] = (int)param_2;
  return;
}


// ===================================================================
// FUN_08013b34 @ 0x08013b34  size=10  body=[[08013b34, 08013b3d]]

void FUN_08013b34(int param_1)

{
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


// ===================================================================
// FUN_08013b40 @ 0x08013b40  size=94  body=[[08013b40, 08013b9d]]

void FUN_08013b40(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int extraout_r1;
  int *piVar4;
  int iVar5;
  
  piVar1 = DAT_200049ec;
  piVar3 = (int *)param_1[2];
  if (piVar3 == (int *)0x0) {
    iVar5 = DAT_200049ec[8];
    param_1[2] = (int)DAT_200049ec;
    param_1[3] = iVar5;
    piVar1[8] = (int)param_1;
    return;
  }
  do {
    if ((uint)piVar1[2] <= (uint)piVar3[2]) {
LAB_08013b8a:
      FUN_08013b16(param_1,piVar1);
      piVar1[6] = (int)param_1;
      FUN_080138b8(6);
      return;
    }
    piVar3[2] = piVar1[2];
    if ((char)piVar3[5] == '\0') {
      piVar2 = (int *)piVar3[1];
      iVar5 = *piVar3;
      *piVar2 = iVar5;
      *(int **)(iVar5 + 4) = piVar2;
      thunk_FUN_08013838(piVar3);
      goto LAB_08013b8a;
    }
    if ((char)piVar3[5] != '\x06') goto LAB_08013b8a;
    iVar5 = *piVar3;
    piVar4 = (int *)piVar3[1];
    piVar2 = (int *)piVar3[6];
    *piVar4 = iVar5;
    *(int **)(iVar5 + 4) = piVar4;
    FUN_08013b16(piVar2,piVar3);
    piVar3 = *(int **)(*(int *)(extraout_r1 + 0x18) + 8);
  } while( true );
}


// ===================================================================
// FUN_08013ba4 @ 0x08013ba4  size=20  body=[[08013ba4, 08013bb7]]

void FUN_08013ba4(int *param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013b40(param_1);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08013bb8 @ 0x08013bb8  size=86  body=[[08013bb8, 08013c0d]]

void FUN_08013bb8(int *param_1)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = DAT_200049ec;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  piVar4 = (int *)param_1[3];
  piVar2 = (int *)*param_1;
  *(int **)(DAT_200049ec + 0x20) = piVar4;
  if (piVar2 == param_1) {
    piVar2[2] = 0;
  }
  else {
    uVar3 = *(uint *)(iVar5 + 0x24);
    for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[3]) {
      if ((piVar4 != (int *)*piVar4) && (uVar6 = ((int *)*piVar4)[2], uVar3 < uVar6)) {
        uVar3 = uVar6;
      }
    }
    *(uint *)(iVar5 + 8) = uVar3;
    piVar2 = (int *)*param_1;
    iVar5 = *piVar2;
    *param_1 = iVar5;
    *(int **)(iVar5 + 4) = param_1;
    iVar5 = piVar2[8];
    param_1[2] = (int)piVar2;
    param_1[3] = iVar5;
    piVar2[8] = (int)param_1;
    thunk_FUN_08013838(piVar2);
    FUN_08013950();
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// SVCall_Handler @ 0x08013c14  size=28  body=[[08013c14, 08013c2f]]

void SVCall_Handler(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = getProcessStackPointer();
  uVar2 = DAT_e000ef34;
  DAT_e000ef34 = uVar2 & 0xfffffffe;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(iVar3 + 0x68);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08013c34 @ 0x08013c34  size=58  body=[[08013c34, 08013c6d]]

void FUN_08013c34(void)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  enableIRQinterrupts();
  uVar2 = DAT_e000ed0c;
  DAT_e000ed0c = uVar2 & 0xf8ff | 0x5fa0300;
  uVar2 = DAT_e000edfc;
  DAT_e000edfc = uVar2 | 0x1000000;
  uVar2 = DAT_e0001000;
  DAT_e0001000 = uVar2 | 1;
  DAT_e000ed1f = 0x20;
  DAT_e000ed22 = 0x30;
  return;
}


// ===================================================================
// FUN_08013c7c @ 0x08013c7c  size=66  body=[[08013c7c, 08013cbd]]

void FUN_08013c7c(void)

{
  uint uVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(0x30);
  }
  uVar1 = DAT_e000ed04;
  if ((uVar1 & 0x800) == 0) {
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0);
    }
  }
  else {
    iVar4 = getProcessStackPointer();
    *(undefined4 *)(iVar4 + -0x4c) = 0x1000000;
    uVar3 = DAT_e000ef3c;
    *(undefined4 *)(iVar4 + -8) = uVar3;
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setProcessStackPointer(iVar4 + -0x68);
    }
    bVar2 = FUN_08013910();
    if (bVar2) {
      uVar3 = 0x800814f;
    }
    else {
      uVar3 = 0x8008152;
    }
    *(undefined4 *)(iVar4 + -0x50) = uVar3;
  }
  return;
}


// ===================================================================
// FUN_08013cd0 @ 0x08013cd0  size=106  body=[[08013cd0, 08013cf9] [08016578, 080165b7]]

void FUN_08013cd0(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  FUN_08014ab4();
  FUN_0801531c();
  thunk_FUN_08014c78();
  thunk_FUN_080163c8();
  thunk_FUN_08015538();
  thunk_FUN_08015fe0();
  FUN_08012c5c();
  uVar1 = DAT_40023840;
  DAT_40023840 = uVar1 | 1;
  uVar1 = DAT_40023860;
  DAT_40023860 = uVar1 | 1;
  uVar2 = DAT_40023860;
  uVar1 = DAT_e0042008;
  DAT_e0042008 = uVar1 | 1;
  DAT_40000028 = 0x1df;
  DAT_4000002c = 0xffffffff;
  DAT_40000018 = 0;
  DAT_40000034 = 0;
  DAT_4000000c = 0;
  DAT_40000004 = 0;
  DAT_40000014 = 1;
  DAT_40000000 = 1;
  return;
}


// ===================================================================
// FUN_08013cfa @ 0x08013cfa  size=8  body=[[08013cfa, 08013d01]]

undefined4 FUN_08013cfa(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_40000024;
  return uVar1;
}


// ===================================================================
// FUN_08013d02 @ 0x08013d02  size=16  body=[[08013d02, 08013d11]]

void FUN_08013d02(undefined4 param_1)

{
  DAT_40000034 = param_1;
  DAT_40000010 = 0;
  DAT_4000000c = 2;
  return;
}


// ===================================================================
// FUN_08013d12 @ 0x08013d12  size=10  body=[[08013d12, 08013d1b]]

void FUN_08013d12(void)

{
  DAT_4000000c = 0;
  return;
}


// ===================================================================
// FUN_08013d1c @ 0x08013d1c  size=8  body=[[08013d1c, 08013d23]]

void FUN_08013d1c(undefined4 param_1)

{
  DAT_40000034 = param_1;
  return;
}


// ===================================================================
// FUN_08013d24 @ 0x08013d24  size=46  body=[[08013d24, 08013d51]]

void FUN_08013d24(int param_1,undefined1 param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6,undefined4 param_7)

{
  *(undefined1 *)(param_1 + 8) = param_2;
  *(int *)(param_1 + 0x1c) = param_4 + 4;
  *(undefined4 *)(param_1 + 0x30) = param_6;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(int *)(param_1 + 0x14) = param_3;
  *(int *)(param_1 + 0x10) = param_3;
  *(int *)(param_1 + 0x18) = param_5 * (param_4 + 4) + param_3;
  *(int *)(param_1 + 0x20) = param_5;
  *(int *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x34) = param_7;
  return;
}


// ===================================================================
// FUN_08013d52 @ 0x08013d52  size=22  body=[[08013d52, 08013d67]]

void FUN_08013d52(int *param_1)

{
  param_1[5] = param_1[9];
  param_1[4] = param_1[9];
  param_1[3] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  FUN_08013afa(param_1,-2);
  return;
}


// ===================================================================
// FUN_08013d68 @ 0x08013d68  size=20  body=[[08013d68, 08013d7b]]

int FUN_08013d68(int param_1)

{
  if ((*(int *)(param_1 + 0x10) == *(int *)(param_1 + 0x14)) && (*(int *)(param_1 + 0xc) != 0)) {
    return 0;
  }
  return *(int *)(param_1 + 0x10) + 4;
}


// ===================================================================
// FUN_08013d7c @ 0x08013d7c  size=32  body=[[08013d7c, 08013d9b]]

void FUN_08013d7c(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)param_1[4];
  *puVar1 = param_2;
  param_1[3] = param_1[3] + 1;
  uVar2 = (int)puVar1 + param_1[7];
  param_1[4] = uVar2;
  if ((uint)param_1[6] <= uVar2) {
    param_1[4] = param_1[9];
  }
  FUN_08013ae4(param_1,0);
  return;
}


// ===================================================================
// FUN_08013d9c @ 0x08013d9c  size=50  body=[[08013d9c, 08013dcd]]

int FUN_08013d9c(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  
  while( true ) {
    if (*(int *)(param_1 + 0xc) != 0) {
      piVar2 = *(int **)(param_1 + 0x14) + 1;
      iVar1 = **(int **)(param_1 + 0x14);
      *(int **)(param_1 + 0x28) = piVar2;
      *(int *)(param_1 + 0x2c) = (int)piVar2 + iVar1;
      return 0;
    }
    if (*(char *)(param_1 + 8) != '\0') break;
    iVar1 = FUN_08013ac4(param_1,param_2);
    if (iVar1 < 0) {
      return iVar1;
    }
  }
  return -2;
}


// ===================================================================
// FUN_08013dce @ 0x08013dce  size=36  body=[[08013dce, 08013df1]]

void FUN_08013dce(int param_1)

{
  uint uVar1;
  
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  uVar1 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x1c);
  *(uint *)(param_1 + 0x14) = uVar1;
  if (*(uint *)(param_1 + 0x18) <= uVar1) {
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x24);
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (*(code **)(param_1 + 0x30) == (code *)0x0) {
    return;
  }
                    // WARNING: Could not recover jumptable at 0x08013dee. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_1 + 0x30))();
  return;
}


// ===================================================================
// FUN_08013df2 @ 0x08013df2  size=130  body=[[08013df2, 08013e73]]

uint FUN_08013df2(int param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  uVar6 = 0;
  while( true ) {
    if ((*(int *)(param_1 + 0x28) == 0) && (iVar2 = FUN_08013d9c(param_1,param_4), iVar2 != 0)) {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      return uVar6;
    }
    puVar3 = *(undefined4 **)(param_1 + 0x28);
    uVar5 = *(int *)(param_1 + 0x2c) - (int)puVar3;
    if (param_3 - uVar6 <= uVar5) {
      uVar5 = param_3 - uVar6;
    }
    if (uVar5 < 0x41) {
      memcpy(param_2,puVar3,uVar5);
      param_2 = (undefined4 *)((int)param_2 + uVar5);
      uVar4 = *(int *)(param_1 + 0x28) + uVar5;
      uVar6 = uVar6 + uVar5;
    }
    else {
      memcpy(param_2,puVar3,0x40);
      param_2 = param_2 + 0x10;
      uVar4 = *(int *)(param_1 + 0x28) + 0x40;
      uVar6 = uVar6 + 0x40;
    }
    *(uint *)(param_1 + 0x28) = uVar4;
    if (*(uint *)(param_1 + 0x2c) <= uVar4) {
      FUN_08013dce(param_1);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (param_3 <= uVar6) break;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
  }
  return uVar6;
}


// ===================================================================
// FUN_08013e74 @ 0x08013e74  size=46  body=[[08013e74, 08013ea1]]

void FUN_08013e74(int param_1,undefined1 param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6,undefined4 param_7)

{
  *(undefined1 *)(param_1 + 8) = param_2;
  *(int *)(param_1 + 0x1c) = param_4 + 4;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = param_6;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(int *)(param_1 + 0xc) = param_5;
  *(int *)(param_1 + 0x14) = param_3;
  *(int *)(param_1 + 0x10) = param_3;
  *(int *)(param_1 + 0x18) = (param_4 + 4) * param_5 + param_3;
  *(int *)(param_1 + 0x20) = param_5;
  *(int *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x34) = param_7;
  return;
}


// ===================================================================
// FUN_08013ea2 @ 0x08013ea2  size=24  body=[[08013ea2, 08013eb9]]

void FUN_08013ea2(int *param_1)

{
  param_1[3] = param_1[8];
  param_1[5] = param_1[9];
  param_1[4] = param_1[9];
  param_1[10] = 0;
  param_1[0xb] = 0;
  FUN_08013afa(param_1,-2);
  return;
}


// ===================================================================
// FUN_08013eba @ 0x08013eba  size=28  body=[[08013eba, 08013ed5]]

int FUN_08013eba(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = *(int **)(param_1 + 0x14);
  if ((*(int **)(param_1 + 0x10) == piVar1) && (*(int *)(param_1 + 0xc) != 0)) {
    piVar3 = (int *)0x0;
    iVar2 = (int)piVar3;
  }
  else {
    piVar3 = piVar1 + 1;
    iVar2 = *piVar1;
  }
  *param_2 = iVar2;
  return (int)piVar3;
}


// ===================================================================
// FUN_08013ed6 @ 0x08013ed6  size=30  body=[[08013ed6, 08013ef3]]

void FUN_08013ed6(int *param_1)

{
  int iVar1;
  
  param_1[3] = param_1[3] + 1;
  iVar1 = param_1[5];
  param_1[5] = iVar1 + param_1[7];
  if ((uint)param_1[6] <= (uint)(iVar1 + param_1[7])) {
    param_1[5] = param_1[9];
  }
  FUN_08013ae4(param_1,0);
  return;
}


// ===================================================================
// FUN_08013ef4 @ 0x08013ef4  size=50  body=[[08013ef4, 08013f25]]

int FUN_08013ef4(int param_1,uint param_2)

{
  int iVar1;
  
  while( true ) {
    if (*(int *)(param_1 + 0xc) != 0) {
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x10) + 4;
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x1c);
      return 0;
    }
    if (*(char *)(param_1 + 8) != '\0') break;
    iVar1 = FUN_08013ac4(param_1,param_2);
    if (iVar1 < 0) {
      return iVar1;
    }
  }
  return -2;
}


// ===================================================================
// FUN_08013f26 @ 0x08013f26  size=38  body=[[08013f26, 08013f4b]]

void FUN_08013f26(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x10);
  *puVar1 = param_2;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  uVar2 = (int)puVar1 + *(int *)(param_1 + 0x1c);
  *(uint *)(param_1 + 0x10) = uVar2;
  if (*(uint *)(param_1 + 0x18) <= uVar2) {
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x24);
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (*(code **)(param_1 + 0x30) == (code *)0x0) {
    return;
  }
                    // WARNING: Could not recover jumptable at 0x08013f48. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_1 + 0x30))();
  return;
}


// ===================================================================
// FUN_08013f4c @ 0x08013f4c  size=134  body=[[08013f4c, 08013fd1]]

uint FUN_08013f4c(int param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  uVar6 = 0;
  while( true ) {
    if ((*(int *)(param_1 + 0x28) == 0) && (iVar2 = FUN_08013ef4(param_1,param_4), iVar2 != 0)) {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
      return uVar6;
    }
    puVar3 = *(undefined4 **)(param_1 + 0x28);
    uVar5 = *(int *)(param_1 + 0x2c) - (int)puVar3;
    if (param_3 - uVar6 <= uVar5) {
      uVar5 = param_3 - uVar6;
    }
    if (uVar5 < 0x41) {
      memcpy(puVar3,param_2,uVar5);
      param_2 = (undefined4 *)((int)param_2 + uVar5);
      uVar4 = *(int *)(param_1 + 0x28) + uVar5;
      uVar6 = uVar6 + uVar5;
    }
    else {
      memcpy(puVar3,param_2,0x40);
      param_2 = param_2 + 0x10;
      uVar4 = *(int *)(param_1 + 0x28) + 0x40;
      uVar6 = uVar6 + 0x40;
    }
    *(uint *)(param_1 + 0x28) = uVar4;
    if (*(uint *)(param_1 + 0x2c) <= uVar4) {
      FUN_08013f26(param_1,*(int *)(param_1 + 0x1c) + -4);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    if (param_3 <= uVar6) break;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
  }
  return uVar6;
}


// ===================================================================
// FUN_08013fd2 @ 0x08013fd2  size=32  body=[[08013fd2, 08013ff1]]

void FUN_08013fd2(int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  if ((*(int *)(param_1 + 0x28) != 0) &&
     (iVar2 = (*(int *)(param_1 + 0x28) + -4) - *(int *)(param_1 + 0x10), iVar2 != 0)) {
    FUN_08013f26(param_1,iVar2);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08013ff4 @ 0x08013ff4  size=56  body=[[08013ff4, 0801402b]]

void FUN_08013ff4(int *param_1,uint param_2)

{
  longlong lVar1;
  int iVar2;
  undefined8 uVar3;
  uint local_14;
  
  local_14 = param_2;
  while (iVar2 = (**(code **)(*param_1 + 0x18))(param_1,&local_14), iVar2 == 1) {
    lVar1 = (ulonglong)local_14 * 100000 + 999;
    uVar3 = FUN_08008158((uint)lVar1,(uint)((ulonglong)lVar1 >> 0x20),1000,0);
    FUN_08013a7a((uint)uVar3);
  }
  return;
}


// ===================================================================
// FUN_08014030 @ 0x08014030  size=26  body=[[08014030, 08014049]]

int FUN_08014030(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  if (*(int *)(iVar1 + 0xc) == 0) {
    iVar1 = param_2 * *(int *)(iVar1 + 0x10);
  }
  else {
    iVar1 = *(int *)(*(int *)(iVar1 + 0xc) + param_2 * 8);
  }
  return iVar1;
}


// ===================================================================
// FUN_0801404a @ 0x0801404a  size=26  body=[[0801404a, 08014063]]

undefined4 FUN_0801404a(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  if (*(int *)(iVar1 + 0xc) == 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0x10);
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(iVar1 + 0xc) + param_2 * 8 + 4);
  }
  return uVar2;
}


// ===================================================================
// FUN_08014064 @ 0x08014064  size=16  body=[[08014064, 08014073]]

int FUN_08014064(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  return *(int *)(iVar1 + 0x14) + param_2;
}


// ===================================================================
// FUN_08014074 @ 0x08014074  size=12  body=[[08014074, 0801407f]]

undefined4 FUN_08014074(int param_1)

{
  FUN_08013bb8((int *)(param_1 + 0xc));
  return 0;
}


// ===================================================================
// FUN_08014080 @ 0x08014080  size=12  body=[[08014080, 0801408b]]

undefined4 FUN_08014080(int param_1)

{
  FUN_08013ba4((int *)(param_1 + 0xc));
  return 0;
}


// ===================================================================
// thunk_FUN_08014c78 @ 0x0801408c  size=4  body=[[0801408c, 0801408f]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void thunk_FUN_08014c78(void)

{
  FUN_08014090(&DAT_20004a40);
  DAT_20004a5c = &DAT_40023c00;
  if (_DAT_1fff7a22 == 0x80) {
    DAT_20004a60 = &DAT_080173d8;
  }
  else if (_DAT_1fff7a22 == 0x100) {
    DAT_20004a60 = &DAT_080173bc;
  }
  else if (_DAT_1fff7a22 == 0x180) {
    DAT_20004a60 = &DAT_080173a0;
  }
  else if (_DAT_1fff7a22 == 0x200) {
    DAT_20004a60 = &DAT_08017384;
  }
  return;
}


// ===================================================================
// FUN_08014090 @ 0x08014090  size=14  body=[[08014090, 0801409d]]

void FUN_08014090(undefined4 *param_1)

{
  *param_1 = &DAT_08017354;
  *(undefined1 *)(param_1 + 1) = 1;
  FUN_08013b34((int)(param_1 + 3));
  return;
}


// ===================================================================
// FUN_080140a4 @ 0x080140a4  size=28  body=[[080140a4, 080140bf]]

undefined4 FUN_080140a4(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  FUN_08014cd4(param_1);
  *(undefined1 *)(param_1 + 4) = 2;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return 0;
}


// ===================================================================
// FUN_080140c0 @ 0x080140c0  size=26  body=[[080140c0, 080140d9]]

void FUN_080140c0(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08014cfc(param_1);
  *(undefined1 *)(param_1 + 4) = 1;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_080140dc @ 0x080140dc  size=18  body=[[080140dc, 080140ed]]

void FUN_080140dc(uint param_1,undefined4 param_2,undefined4 param_3)

{
  (&DAT_20004a64)[(param_1 & 0xf) * 2] = param_2;
  (&DAT_20004a68)[(param_1 & 0xf) * 2] = param_3;
  return;
}


// ===================================================================
// thunk_FUN_08015fe0 @ 0x080140f4  size=4  body=[[080140f4, 080140f7]]

void thunk_FUN_08015fe0(void)

{
  undefined *puVar1;
  undefined *extraout_r1;
  uint uVar2;
  
  FUN_080140f8((undefined4 *)&DAT_20004b44);
  puVar1 = &DAT_40002800;
  DAT_20004b48 = &DAT_40002800;
  DAT_40002824 = 0xca;
  DAT_40002824 = 0x53;
  uVar2 = DAT_4000280c;
  if ((uVar2 & 0x10) == 0) {
    FUN_08015e74();
    *(undefined4 *)(extraout_r1 + 8) = 0;
    *(undefined4 *)(extraout_r1 + 0x40) = 0;
    *(undefined4 *)(extraout_r1 + 0xc) = 0x80;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    uVar2 = *(uint *)(extraout_r1 + 0xc) & 0xffffff7f;
    puVar1 = extraout_r1;
  }
  else {
    uVar2 = DAT_4000280c;
    uVar2 = uVar2 & 0xffffffdf;
  }
  *(uint *)(puVar1 + 0xc) = uVar2;
  DAT_20004b4c = 0;
  FUN_080152b0(0x620000,1);
  FUN_0801486a(2,'\x0f');
  FUN_0801486a(3,'\x0f');
  FUN_0801486a(0x29,'\x0f');
  return;
}


// ===================================================================
// FUN_080140f8 @ 0x080140f8  size=6  body=[[080140f8, 080140fd]]

void FUN_080140f8(undefined4 *param_1)

{
  *param_1 = &DAT_200013a8;
  return;
}


// ===================================================================
// thunk_FUN_08016058 @ 0x08014104  size=4  body=[[08014104, 08014107]]

void thunk_FUN_08016058(int param_1,byte *param_2)

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


// ===================================================================
// thunk_FUN_08016130 @ 0x08014108  size=4  body=[[08014108, 0801410b]]

void thunk_FUN_08016130(int param_1,uint *param_2)

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


// ===================================================================
// thunk_FUN_080163c8 @ 0x0801410c  size=4  body=[[0801410c, 0801410f]]

void thunk_FUN_080163c8(void)

{
  FUN_08014110(&DAT_20004b50);
  DAT_20004b6c = &DAT_40013000;
  DAT_20004b70 = 0;
  DAT_20004b74 = 0;
  DAT_20004b78 = 0x6010016;
  DAT_20004b7c = 0x6010046;
  return;
}


// ===================================================================
// FUN_08014110 @ 0x08014110  size=16  body=[[08014110, 0801411f]]

void FUN_08014110(undefined1 *param_1)

{
  *param_1 = 1;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  FUN_08013b34((int)(param_1 + 0xc));
  return;
}


// ===================================================================
// FUN_08014120 @ 0x08014120  size=34  body=[[08014120, 08014141]]

void FUN_08014120(char *param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined4 *)(param_1 + 4) = param_2;
  iVar2 = FUN_080163f4(param_1);
  if (iVar2 == 0) {
    cVar3 = '\x02';
  }
  else {
    cVar3 = '\x01';
  }
  *param_1 = cVar3;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08014142 @ 0x08014142  size=28  body=[[08014142, 0801415d]]

void FUN_08014142(char *param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_080164c0(param_1);
  param_1[4] = '\0';
  param_1[5] = '\0';
  param_1[6] = '\0';
  param_1[7] = '\0';
  *param_1 = '\x01';
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_0801415e @ 0x0801415e  size=28  body=[[0801415e, 08014179]]

void FUN_0801415e(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(short *)(*(int *)(*(int *)(param_1 + 4) + 0xc) + 0x1a) =
       (short)(1 << (*(uint *)(*(int *)(param_1 + 4) + 0x10) & 0xff));
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_0801417a @ 0x0801417a  size=28  body=[[0801417a, 08014195]]

void FUN_0801417a(int param_1)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(short *)(*(int *)(*(int *)(param_1 + 4) + 0xc) + 0x18) =
       (short)(1 << (*(uint *)(*(int *)(param_1 + 4) + 0x10) & 0xff));
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08014196 @ 0x08014196  size=14  body=[[08014196, 080141a3]]

undefined4 FUN_08014196(undefined1 *param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  
  *param_1 = 3;
  uVar1 = FUN_0801650c((int)param_1,param_2,param_3,param_4);
  return uVar1;
}


// ===================================================================
// FUN_080141a4 @ 0x080141a4  size=62  body=[[080141a4, 080141ab] [08016542, 08016577]]

undefined4 FUN_080141a4(undefined1 *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  *param_1 = 3;
  puVar3 = (uint *)**(undefined4 **)(param_1 + 0x20);
  puVar3[3] = (uint)(param_1 + 0x30);
  uVar1 = *(uint *)(param_1 + 0x28);
  puVar3[1] = param_2;
  *puVar3 = uVar1;
  puVar2 = (uint *)**(undefined4 **)(param_1 + 0x24);
  puVar2[3] = param_3;
  uVar1 = *(uint *)(param_1 + 0x2c);
  puVar2[1] = param_2;
  *puVar2 = uVar1 | 0x400;
  *puVar3 = *puVar3 | 1;
  *puVar2 = *puVar2 | 1;
  return 0;
}


// ===================================================================
// FUN_080141ac @ 0x080141ac  size=38  body=[[08013a94, 08013aa9] [080141ac, 080141bb]]

undefined4 FUN_080141ac(char *param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_200049ec;
  if (*param_1 != '\x03') {
    return 0;
  }
  if (param_2 != 0) {
    *(int *)(param_1 + 8) = DAT_200049ec;
    *(char **)(iVar1 + 0x18) = param_1 + 8;
    uVar2 = FUN_080138d4(3,param_2);
    return uVar2;
  }
  return 0xffffffff;
}


// ===================================================================
// FUN_080141bc @ 0x080141bc  size=34  body=[[080141bc, 080141dd]]

void FUN_080141bc(char *param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar2 = FUN_08014196(param_1,param_2,param_3,param_4);
  if (iVar2 == 0) {
    FUN_080141ac(param_1,0xffffffff);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_080141de @ 0x080141de  size=34  body=[[080141de, 080141ff]]

void FUN_080141de(char *param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar2 = FUN_080141a4(param_1,param_2,param_3);
  if (iVar2 == 0) {
    FUN_080141ac(param_1,0xffffffff);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// thunk_FUN_08015538 @ 0x08014200  size=4  body=[[08014200, 08014203]]

void thunk_FUN_08015538(void)

{
  FUN_08014204(&DAT_20004ae4);
  DAT_20004b38 = &DAT_50000000;
  DAT_20004b3c = &DAT_08017584;
  return;
}


// ===================================================================
// FUN_08014204 @ 0x08014204  size=24  body=[[08014204, 0801421b]]

void FUN_08014204(undefined1 *param_1)

{
  *param_1 = 1;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


// ===================================================================
// FUN_0801421c @ 0x0801421c  size=38  body=[[0801421c, 08014241]]

undefined4 FUN_0801421c(char *param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined4 *)(param_1 + 4) = param_2;
  param_1[0xc] = '\0';
  param_1[0xd] = '\0';
  param_1[0xe] = '\0';
  param_1[0xf] = '\0';
  param_1[0x10] = '\0';
  param_1[0x11] = '\0';
  param_1[0x12] = '\0';
  param_1[0x13] = '\0';
  param_1[0x14] = '\0';
  param_1[0x15] = '\0';
  param_1[0x16] = '\0';
  param_1[0x17] = '\0';
  param_1[0x18] = '\0';
  param_1[0x19] = '\0';
  param_1[0x1a] = '\0';
  param_1[0x1b] = '\0';
  FUN_08015558(param_1);
  *param_1 = '\x02';
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return 0;
}


// ===================================================================
// FUN_08014242 @ 0x08014242  size=82  body=[[08014242, 08014293]]

void FUN_08014242(char *param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08015624(param_1);
  param_1[4] = '\0';
  param_1[5] = '\0';
  param_1[6] = '\0';
  param_1[7] = '\0';
  piVar3 = (int *)(param_1 + 8);
  *param_1 = '\x01';
  do {
    piVar3 = piVar3 + 1;
    if (*piVar3 != 0) {
      iVar2 = *(int *)(*piVar3 + 0x14);
      if (iVar2 != 0) {
        FUN_08013ab0((undefined4 *)(iVar2 + 0xc),-2);
      }
      if (*(int *)(*piVar3 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x18) + 0xc),-2);
      }
    }
    *piVar3 = 0;
  } while (piVar3 != (int *)(param_1 + 0x18));
  FUN_08013950();
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08014294 @ 0x08014294  size=50  body=[[08014294, 080142c5]]

void FUN_08014294(int param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  
  pbVar1 = *(byte **)(param_3 + 0x14);
  *(int *)(param_1 + param_2 * 4 + 0xc) = param_3;
  if (pbVar1 != (byte *)0x0) {
    FUN_08008798(pbVar1,0,0x14);
  }
  if (*(byte **)(param_3 + 0x18) != (byte *)0x0) {
    FUN_08008798(*(byte **)(param_3 + 0x18),0,0x14);
  }
  FUN_08015730(param_1,param_2);
  return;
}


// ===================================================================
// FUN_080142c6 @ 0x080142c6  size=84  body=[[080142c6, 0801430f] [08015844, 0801584d]]

void FUN_080142c6(int param_1)

{
  int iVar1;
  int *piVar2;
  
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0x10001;
  piVar2 = (int *)(param_1 + 0xc);
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 != 0) {
      iVar1 = *(int *)(*piVar2 + 0x14);
      if (iVar1 != 0) {
        FUN_08013ab0((undefined4 *)(iVar1 + 0xc),-2);
      }
      if (*(int *)(*piVar2 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x18) + 0xc),-2);
      }
    }
    *piVar2 = 0;
  } while (piVar2 != (int *)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x5c) = **(undefined4 **)(param_1 + 0x58);
  FUN_080154cc(param_1);
  return;
}


// ===================================================================
// FUN_08014310 @ 0x08014310  size=36  body=[[08014310, 08014333]]

void FUN_08014310(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x18);
  *(ushort *)(param_1 + 10) = (ushort)(1 << (param_2 & 0xff)) | *(ushort *)(param_1 + 10);
  *puVar1 = param_4;
  puVar1[2] = param_3;
  puVar1[1] = 0;
  puVar1[3] = 0;
  FUN_08015894(param_1,param_2);
  return;
}


// ===================================================================
// FUN_08014334 @ 0x08014334  size=36  body=[[08014334, 08014357]]

void FUN_08014334(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x14);
  *(ushort *)(param_1 + 8) = (ushort)(1 << (param_2 & 0xff)) | *(ushort *)(param_1 + 8);
  *puVar1 = param_4;
  puVar1[2] = param_3;
  puVar1[1] = 0;
  puVar1[3] = 0;
  FUN_080159c0(param_1,param_2);
  return;
}


// ===================================================================
// FUN_08014358 @ 0x08014358  size=62  body=[[08014358, 08014395]]

void FUN_08014358(char *param_1)

{
  int iVar1;
  
  if (*param_1 == '\x05') {
    iVar1 = *(int *)(param_1 + 0x54);
    *(uint *)(iVar1 + 0x804) = *(uint *)(iVar1 + 0x804) | 1;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 8;
    *(uint *)(iVar1 + 0x18) = *(uint *)(iVar1 + 0x18) | 8;
    FUN_08013a7a(200);
    *(uint *)(*(int *)(param_1 + 0x54) + 0x804) =
         *(uint *)(*(int *)(param_1 + 0x54) + 0x804) & 0xfffffffe;
  }
  return;
}


// ===================================================================
// FUN_08014396 @ 0x08014396  size=112  body=[[08014396, 08014405]]

void FUN_08014396(undefined1 *param_1)

{
  bool bVar1;
  int *piVar2;
  
  *param_1 = 2;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  piVar2 = (int *)(param_1 + 8);
  *piVar2 = 0;
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 != 0) {
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      if (*(int *)(*piVar2 + 0x14) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x14) + 0xc),-2);
      }
      if (*(int *)(*piVar2 + 0x18) != 0) {
        FUN_08013ab0((undefined4 *)(*(int *)(*piVar2 + 0x18) + 0xc),-2);
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    *piVar2 = 0;
  } while (piVar2 != (int *)(param_1 + 0x18));
  param_1[0x34] = 0;
  FUN_08015668((int)param_1);
  if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08014400. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0);
    return;
  }
  return;
}


// ===================================================================
// FUN_08014406 @ 0x08014406  size=92  body=[[08014406, 08014461]]

void FUN_08014406(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  code *pcVar2;
  int *piVar3;
  
  if (*param_1 != '\x05') {
    param_1[0x50] = *param_1;
    *param_1 = '\x05';
    pcVar2 = (code *)**(undefined4 **)(param_1 + 4);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(param_1,4,param_3,pcVar2,param_4);
    }
    piVar3 = (int *)(param_1 + 8);
    *piVar3 = 0;
    do {
      piVar3 = piVar3 + 1;
      if (*piVar3 != 0) {
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        if (*(int *)(*piVar3 + 0x14) != 0) {
          FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x14) + 0xc),-2);
        }
        if (*(int *)(*piVar3 + 0x18) != 0) {
          FUN_08013ab0((undefined4 *)(*(int *)(*piVar3 + 0x18) + 0xc),-2);
        }
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0);
        }
      }
    } while (piVar3 != (int *)(param_1 + 0x18));
  }
  return;
}


// ===================================================================
// FUN_08014462 @ 0x08014462  size=22  body=[[08014462, 08014477]]

void FUN_08014462(char *param_1)

{
  if (*param_1 == '\x05') {
    *param_1 = param_1[0x50];
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08014474. Too many branches
                    // WARNING: Treating indirect jump as call
      (*(code *)**(undefined4 **)(param_1 + 4))();
      return;
    }
  }
  return;
}


// ===================================================================
// FUN_08014478 @ 0x08014478  size=700  body=[[08014478, 08014733]]

void FUN_08014478(char *param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 *puVar3;
  ushort uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined *puVar7;
  uint uVar8;
  int iVar9;
  
  if (param_1[0x34] != '\0') {
    param_1[0x34] = '\0';
  }
  FUN_08015882((int)param_1,param_2,(undefined4 *)(param_1 + 0x44));
  if ((*(code **)(*(int *)(param_1 + 4) + 8) == (code *)0x0) ||
     (iVar9 = (**(code **)(*(int *)(param_1 + 4) + 8))(param_1), iVar9 == 0)) {
    bVar1 = param_1[0x44];
    uVar8 = bVar1 & 0x60;
    if ((bVar1 & 0x60) != 0) {
LAB_080144a2:
      FUN_08015e38((int)param_1,0);
      FUN_08015e24((int)param_1,0);
      if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
        (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
      }
      param_1[0x34] = '\x06';
      return;
    }
    uVar5 = bVar1 & 0x7f | (uint)(byte)param_1[0x45] << 8;
    if (uVar5 == 0x302) {
      if (param_1[0x46] != '\0') goto LAB_080144a2;
      bVar1 = param_1[0x48];
      uVar8 = bVar1 & 0xf;
      if ((bVar1 & 0xf) != 0) {
        if ((int)((uint)bVar1 << 0x18) < 0) {
          FUN_08015e38((int)param_1,uVar8);
        }
        else {
          FUN_08015e24((int)param_1,uVar8);
        }
      }
      goto LAB_08014616;
    }
    if (uVar5 < 0x303) {
      if (uVar5 == 0x100) {
        if (param_1[0x46] != '\x01') goto LAB_080144a2;
        uVar4 = *(ushort *)(param_1 + 0x4c) & 0xfffd;
      }
      else {
        if (uVar5 < 0x101) {
          if (uVar5 == 1) {
LAB_080145c4:
            puVar7 = &DAT_08017380;
          }
          else {
            if (uVar5 != 2) {
              if (uVar5 != 0) goto LAB_080144a2;
              *(char **)(param_1 + 0x38) = param_1 + 0x4c;
              param_1[0x3c] = '\x02';
              param_1[0x3d] = '\0';
              param_1[0x3e] = '\0';
              param_1[0x3f] = '\0';
              goto LAB_0801454e;
            }
            uVar8 = (byte)param_1[0x48] & 0xf;
            if ((int)((uint)(byte)param_1[0x48] << 0x18) < 0) {
              iVar9 = FUN_08015868((int)param_1,uVar8);
            }
            else {
              iVar9 = FUN_0801584e((int)param_1,uVar8);
            }
            if (iVar9 == 1) {
              puVar7 = &DAT_0801737c;
            }
            else {
              if (iVar9 != 2) goto LAB_080144a2;
              puVar7 = &DAT_0801737e;
            }
          }
          *(undefined **)(param_1 + 0x38) = puVar7;
          param_1[0x3c] = '\x02';
          param_1[0x3d] = '\0';
          param_1[0x3e] = '\0';
          param_1[0x3f] = '\0';
          goto LAB_0801454e;
        }
        if (uVar5 == 0x102) {
          if (param_1[0x46] != '\0') goto LAB_080144a2;
          bVar1 = param_1[0x48];
          uVar8 = bVar1 & 0xf;
          if ((bVar1 & 0xf) != 0) {
            if ((int)((uint)bVar1 << 0x18) < 0) {
              FUN_08015e60((int)param_1,uVar8);
            }
            else {
              FUN_08015e4c((int)param_1,uVar8);
            }
          }
          goto LAB_08014616;
        }
        if ((uVar5 != 0x300) || (param_1[0x46] != '\x01')) goto LAB_080144a2;
        uVar4 = *(ushort *)(param_1 + 0x4c) | 2;
      }
      *(ushort *)(param_1 + 0x4c) = uVar4;
      *(uint *)(param_1 + 0x38) = uVar8;
      *(uint *)(param_1 + 0x3c) = uVar8;
    }
    else {
      if (uVar5 != 0x800) {
        if (uVar5 < 0x801) {
          if (uVar5 != 0x500) {
            if ((1 < uVar5 - 0x600) ||
               (puVar3 = (undefined4 *)
                         (**(code **)(*(int *)(param_1 + 4) + 4))
                                   (param_1,param_1[0x47],param_1[0x46],
                                    *(undefined2 *)(param_1 + 0x48)), puVar3 == (undefined4 *)0x0))
            goto LAB_080144a2;
            *(undefined4 *)(param_1 + 0x38) = puVar3[1];
            uVar6 = *puVar3;
            goto LAB_080145b0;
          }
          if (*(short *)(param_1 + 0x44) == 0x500) {
            param_1[0x4e] = param_1[0x46];
            FUN_08015718((int)param_1);
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1);
            }
            *param_1 = '\x03';
          }
        }
        else {
          if (uVar5 != 0x900) {
            if (uVar5 != 0xc02) goto LAB_080144a2;
            goto LAB_080145c4;
          }
          if (*param_1 == '\x04') {
            bVar2 = (bool)isCurrentModePrivileged();
            if (bVar2) {
              setBasePriority(0x30);
            }
            FUN_080142c6((int)param_1);
            bVar2 = (bool)isCurrentModePrivileged();
            if (bVar2) {
              setBasePriority(uVar8);
            }
            param_1[0x4f] = (char)uVar8;
            *param_1 = '\x03';
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1);
            }
          }
          if (param_1[0x46] != '\0') {
            param_1[0x4f] = param_1[0x46];
            *param_1 = '\x04';
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1,2);
            }
          }
        }
LAB_08014616:
        param_1[0x38] = '\0';
        param_1[0x39] = '\0';
        param_1[0x3a] = '\0';
        param_1[0x3b] = '\0';
        param_1[0x3c] = '\0';
        param_1[0x3d] = '\0';
        param_1[0x3e] = '\0';
        param_1[0x3f] = '\0';
LAB_0801454e:
        param_1[0x40] = '\0';
        param_1[0x41] = '\0';
        param_1[0x42] = '\0';
        param_1[0x43] = '\0';
        goto LAB_080144ce;
      }
      *(char **)(param_1 + 0x38) = param_1 + 0x4f;
      uVar6 = 1;
LAB_080145b0:
      *(undefined4 *)(param_1 + 0x3c) = uVar6;
    }
    *(uint *)(param_1 + 0x40) = uVar8;
  }
LAB_080144ce:
  if ((uint)*(ushort *)(param_1 + 0x4a) < *(uint *)(param_1 + 0x3c)) {
    *(uint *)(param_1 + 0x3c) = (uint)*(ushort *)(param_1 + 0x4a);
  }
  iVar9 = *(int *)(param_1 + 0x3c);
  if (param_1[0x44] < '\0') {
    if (iVar9 == 0) {
      param_1[0x34] = '\x14';
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014310((int)param_1,0,0,0);
LAB_080146fc:
      bVar2 = (bool)isCurrentModePrivileged();
      if (!bVar2) {
        return;
      }
      setBasePriority(iVar9);
      return;
    }
    param_1[0x34] = '\t';
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08014334((int)param_1,0,*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x3c));
  }
  else {
    if (iVar9 == 0) {
      param_1[0x34] = '\v';
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014334((int)param_1,0,0,0);
      goto LAB_080146fc;
    }
    param_1[0x34] = '\x15';
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08014310((int)param_1,0,*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x3c));
  }
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_08014740 @ 0x08014740  size=162  body=[[08014740, 0801475b] [0801476c, 080147f1]]

void FUN_08014740(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  
  cVar1 = *(char *)(param_1 + 0x34);
  if (cVar1 == '\0') {
LAB_080147d2:
    FUN_08015e38(param_1,0);
    FUN_08015e24(param_1,0);
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
      (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
    }
    uVar3 = 6;
  }
  else {
    if (0xf < (byte)(cVar1 - 6U)) {
      return;
    }
    switch(cVar1) {
    case '\x06':
    case '\x14':
    case '\x15':
      goto LAB_080147d2;
    default:
      goto LAB_080147c6;
    case '\t':
      uVar5 = *(uint *)(param_1 + 0x3c);
      if ((*(ushort *)(param_1 + 0x4a) <= uVar5) ||
         (uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0xc) + 0x10),
         uVar5 != uVar4 * (uVar5 / uVar4))) goto LAB_080147a8;
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014334(param_1,0,0,0);
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0);
      }
      uVar3 = 10;
      break;
    case '\n':
LAB_080147a8:
      *(undefined1 *)(param_1 + 0x34) = 0x14;
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014310(param_1,0,0,0);
      bVar2 = (bool)isCurrentModePrivileged();
      if (!bVar2) {
        return;
      }
      setBasePriority(0);
      return;
    case '\v':
      if (*(code **)(param_1 + 0x40) != (code *)0x0) {
        (**(code **)(param_1 + 0x40))();
      }
      uVar3 = 0;
    }
  }
  *(undefined1 *)(param_1 + 0x34) = uVar3;
LAB_080147c6:
  return;
}


// ===================================================================
// FUN_080147f2 @ 0x080147f2  size=120  body=[[080147f2, 08014869]]

void FUN_080147f2(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  uint uVar3;
  
  uVar3 = (uint)*(byte *)(param_1 + 0x34);
  if (uVar3 == 0x14) {
    if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + 0x18) + 4) != 0) {
      return;
    }
    if (*(code **)(param_1 + 0x40) != (code *)0x0) {
      (**(code **)(param_1 + 0x40))();
    }
    uVar2 = 0;
  }
  else {
    if (0x14 < uVar3) {
      if (uVar3 != 0x15) {
        return;
      }
      *(undefined1 *)(param_1 + 0x34) = 0xb;
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_08014334(param_1,0,0,0);
      bVar1 = (bool)isCurrentModePrivileged();
      if (!bVar1) {
        return;
      }
      setBasePriority(0);
      return;
    }
    if (uVar3 != 6) {
      if (uVar3 < 7) {
        if (uVar3 != 0) {
          return;
        }
      }
      else if (2 < uVar3 - 9) {
        return;
      }
    }
    FUN_08015e38(param_1,0);
    FUN_08015e24(param_1,0);
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
      (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
    }
    uVar2 = 6;
  }
  *(undefined1 *)(param_1 + 0x34) = uVar2;
  return;
}


// ===================================================================
// FUN_0801486a @ 0x0801486a  size=44  body=[[0801486a, 08014895]]

void FUN_0801486a(uint param_1,char param_2)

{
  int iVar1;
  
  (&DAT_e000e400)[param_1] = param_2 << 4;
  iVar1 = 1 << (param_1 & 0x1f);
  (&DAT_e000e280)[param_1 >> 5] = iVar1;
  *(int *)(&DAT_e000e100 + (param_1 >> 5) * 4) = iVar1;
  return;
}


// ===================================================================
// FUN_08014896 @ 0x08014896  size=44  body=[[08014896, 080148c1]]

void FUN_08014896(uint param_1)

{
  int iVar1;
  
  iVar1 = 1 << (param_1 & 0x1f);
  (&DAT_e000e180)[param_1 >> 5] = iVar1;
  (&DAT_e000e280)[param_1 >> 5] = iVar1;
  (&DAT_e000e400)[param_1] = 0;
  return;
}


// ===================================================================
// Vector58_IRQ6_EXTI0 @ 0x080148c4  size=32  body=[[080148c4, 080148e3]]

void Vector58_IRQ6_EXTI0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 1;
  if (((uVar1 & 1) != 0) && (DAT_20004a64 != (code *)0x0)) {
    (*DAT_20004a64)(DAT_20004a68);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector5C_IRQ7_EXTI1 @ 0x080148ec  size=32  body=[[080148ec, 0801490b]]

void Vector5C_IRQ7_EXTI1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 2;
  if (((uVar1 & 2) != 0) && (DAT_20004a6c != (code *)0x0)) {
    (*DAT_20004a6c)(DAT_20004a70);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector60_IRQ8_EXTI2 @ 0x08014914  size=32  body=[[08014914, 08014933]]

void Vector60_IRQ8_EXTI2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 4;
  if (((uVar1 & 4) != 0) && (DAT_20004a74 != (code *)0x0)) {
    (*DAT_20004a74)(DAT_20004a78);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector64_IRQ9_EXTI3 @ 0x0801493c  size=32  body=[[0801493c, 0801495b]]

void Vector64_IRQ9_EXTI3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 8;
  if (((uVar1 & 8) != 0) && (DAT_20004a7c != (code *)0x0)) {
    (*DAT_20004a7c)(DAT_20004a80);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector68_IRQ10_EXTI4 @ 0x08014964  size=32  body=[[08014964, 08014983]]

void Vector68_IRQ10_EXTI4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0x10;
  if (((uVar1 & 0x10) != 0) && (DAT_20004a84 != (code *)0x0)) {
    (*DAT_20004a84)(DAT_20004a88);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector9C_IRQ23_EXTI9_5 @ 0x0801498c  size=90  body=[[0801498c, 080149e5]]

void Vector9C_IRQ23_EXTI9_5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0x3e0;
  if (((int)(uVar1 << 0x1a) < 0) && (DAT_20004a8c != (code *)0x0)) {
    (*DAT_20004a8c)(DAT_20004a90);
  }
  if (((int)(uVar1 << 0x19) < 0) && (DAT_20004a94 != (code *)0x0)) {
    (*DAT_20004a94)(DAT_20004a98);
  }
  if (((int)(uVar1 << 0x18) < 0) && (DAT_20004a9c != (code *)0x0)) {
    (*DAT_20004a9c)(DAT_20004aa0);
  }
  if (((int)(uVar1 << 0x17) < 0) && (DAT_20004aa4 != (code *)0x0)) {
    (*DAT_20004aa4)(DAT_20004aa8);
  }
  if (((int)(uVar1 << 0x16) < 0) && (DAT_20004aac != (code *)0x0)) {
    (*DAT_20004aac)(DAT_20004ab0);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// VectorE0_IRQ40_EXTI15_10 @ 0x080149f0  size=104  body=[[080149f0, 08014a57]]

void VectorE0_IRQ40_EXTI15_10(void)

{
  uint uVar1;
  
  uVar1 = DAT_40013c14;
  DAT_40013c14 = uVar1 & 0xfc00;
  if (((int)(uVar1 << 0x15) < 0) && (DAT_20004ab4 != (code *)0x0)) {
    (*DAT_20004ab4)(DAT_20004ab8);
  }
  if (((int)(uVar1 << 0x14) < 0) && (DAT_20004abc != (code *)0x0)) {
    (*DAT_20004abc)(DAT_20004ac0);
  }
  if (((int)(uVar1 << 0x13) < 0) && (DAT_20004ac4 != (code *)0x0)) {
    (*DAT_20004ac4)(DAT_20004ac8);
  }
  if (((int)(uVar1 << 0x12) < 0) && (DAT_20004acc != (code *)0x0)) {
    (*DAT_20004acc)(DAT_20004ad0);
  }
  if (((int)(uVar1 << 0x11) < 0) && (DAT_20004ad4 != (code *)0x0)) {
    (*DAT_20004ad4)(DAT_20004ad8);
  }
  if (((int)(uVar1 << 0x10) < 0) && (DAT_20004adc != (code *)0x0)) {
    (*DAT_20004adc)(DAT_20004ae0);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// VectorB0_IRQ28_TIM2 @ 0x08014a60  size=14  body=[[08014a60, 08014a6d]]

void VectorB0_IRQ28_TIM2(void)

{
  FUN_080165c0();
  FUN_08013c7c();
  return;
}


// ===================================================================
// FUN_08014ab4 @ 0x08014ab4  size=228  body=[[08014a6e, 08014b51]]

void FUN_08014ab4(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 | 0xffffff60;
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 & 0x9f;
  uVar2 = DAT_40023810;
  uVar2 = DAT_40023814;
  DAT_40023814 = 0xffffffff;
  uVar2 = DAT_40023814;
  DAT_40023814 = 0;
  uVar2 = DAT_40023814;
  uVar1 = DAT_40023820;
  DAT_40023820 = uVar1 | 0xefffffff;
  uVar1 = DAT_40023820;
  DAT_40023820 = uVar1 & 0x10000000;
  uVar2 = DAT_40023820;
  uVar2 = DAT_40023824;
  DAT_40023824 = 0xffffffff;
  uVar2 = DAT_40023824;
  DAT_40023824 = 0;
  uVar2 = DAT_40023824;
  uVar1 = DAT_40023840;
  DAT_40023840 = uVar1 | 0x10000000;
  uVar1 = DAT_40023860;
  DAT_40023860 = uVar1 | 0x10000000;
  uVar2 = DAT_40023860;
  uVar1 = DAT_40007000;
  DAT_40007000 = uVar1 | 0x100;
  uVar1 = DAT_40023870;
  if ((uVar1 & 0x300) != 0x200) {
    DAT_40023870 = 0x10000;
    DAT_40023870 = 0;
  }
  iVar3 = DAT_40023870;
  if (-1 < iVar3 << 0x10) {
    uVar1 = DAT_40023870;
    DAT_40023870 = uVar1 | 0x200;
    uVar1 = DAT_40023870;
    DAT_40023870 = uVar1 | 0x8000;
  }
  uVar1 = DAT_40007004;
  DAT_40007004 = uVar1 & 0xfffffdff;
  FUN_08015164();
  FUN_0801486a(6,'\x06');
  FUN_0801486a(7,'\x06');
  FUN_0801486a(8,'\x06');
  FUN_0801486a(9,'\x06');
  FUN_0801486a(10,'\x06');
  FUN_0801486a(0x17,'\x06');
  FUN_0801486a(0x28,'\x06');
  FUN_0801486a(0x1c,'\a');
  return;
}


// ===================================================================
// FUN_08014b5c @ 0x08014b5c  size=212  body=[[08014b5c, 08014c2f]]

void FUN_08014b5c(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  DAT_40023840 = 0x10000000;
  DAT_40007000 = 0x4000;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 1;
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 0x1e);
  uVar2 = DAT_40023808;
  DAT_40023808 = uVar2 & 0xfffffffc;
  do {
    uVar2 = DAT_40023808;
  } while ((uVar2 & 0xc) != 0);
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 & 0xf9;
  DAT_40023808 = 0;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 0x10000;
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 0xe);
  uVar2 = DAT_40023874;
  DAT_40023874 = uVar2 | 1;
  do {
    iVar1 = DAT_40023874;
  } while (-1 < iVar1 << 0x1e);
  DAT_40023804 = 0x4411808;
  uVar2 = DAT_40023800;
  DAT_40023800 = uVar2 | 0x1000000;
  do {
    iVar1 = DAT_40007004;
  } while (-1 < iVar1 << 0x11);
  do {
    iVar1 = DAT_40023800;
  } while (-1 < iVar1 << 6);
  DAT_40023808 = 0x38881000;
  DAT_4002388c = 3;
  iVar1 = DAT_e0042000;
  if ((iVar1 == 0x20006411) && (iVar1 = DAT_e000ed00, iVar1 == 0x410fc241)) {
    uVar3 = 0x101;
  }
  else {
    uVar3 = 0x701;
  }
  DAT_40023c00 = uVar3;
  do {
    uVar2 = DAT_40023c00;
  } while ((uVar2 & 0xf) != 1);
  uVar2 = DAT_40023808;
  DAT_40023808 = uVar2 | 2;
  do {
    uVar2 = DAT_40023808;
  } while ((uVar2 & 0xc) != 8);
  uVar2 = DAT_40023844;
  DAT_40023844 = uVar2 | 0x4000;
  uVar2 = DAT_40023864;
  DAT_40023864 = uVar2 | 0x4000;
  uVar3 = DAT_40023864;
  return;
}


// ===================================================================
// FUN_08014c54 @ 0x08014c54  size=36  body=[[08014c54, 08014c77]]

undefined4 FUN_08014c54(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x1c) + 0xc);
  *(uint *)(*(int *)(param_1 + 0x1c) + 0xc) = uVar2 & 0xffff;
  if ((int)(uVar2 << 0x1b) < 0) {
    uVar1 = 6;
  }
  else {
    uVar1 = 0;
    if ((uVar2 & 0x62) != 0) {
      if (*(char *)(param_1 + 4) == '\x04') {
        uVar1 = 3;
      }
      else {
        uVar1 = 4;
      }
      return uVar1;
    }
  }
  return uVar1;
}


// ===================================================================
// FUN_08014c78 @ 0x08014c78  size=62  body=[[08014c78, 08014cb5]]

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_08014c78(void)

{
  FUN_08014090(&DAT_20004a40);
  DAT_20004a5c = &DAT_40023c00;
  if (_DAT_1fff7a22 == 0x80) {
    DAT_20004a60 = &DAT_080173d8;
  }
  else if (_DAT_1fff7a22 == 0x100) {
    DAT_20004a60 = &DAT_080173bc;
  }
  else if (_DAT_1fff7a22 == 0x180) {
    DAT_20004a60 = &DAT_080173a0;
  }
  else if (_DAT_1fff7a22 == 0x200) {
    DAT_20004a60 = &DAT_08017384;
  }
  return;
}


// ===================================================================
// FUN_08014cd4 @ 0x08014cd4  size=26  body=[[08014cd4, 08014ced]]

void FUN_08014cd4(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x1c);
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x45670123;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0xcdef89ab;
  DAT_40023c10 = 0;
  return;
}


// ===================================================================
// FUN_08014cfc @ 0x08014cfc  size=12  body=[[08014cfc, 08014d07]]

void FUN_08014cfc(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x10) =
       *(uint *)(*(int *)(param_1 + 0x1c) + 0x10) | 0x80000000;
  return;
}


// ===================================================================
// FUN_08014d08 @ 0x08014d08  size=4  body=[[08014d08, 08014d0b]]

undefined4 FUN_08014d08(int param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}


// ===================================================================
// FUN_08014d0c @ 0x08014d0c  size=46  body=[[08014d0c, 08014d39]]

bool FUN_08014d0c(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  bool bVar1;
  
  bVar1 = *(char *)(param_1 + 4) == '\x05';
  if (!bVar1) {
    *(undefined1 *)(param_1 + 4) = 3;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0xffff;
    memcpy(param_4,(undefined4 *)(param_2 + *(int *)(*(int *)(param_1 + 0x20) + 0x14)),param_3);
    *(undefined1 *)(param_1 + 4) = 2;
  }
  return bVar1;
}


// ===================================================================
// FUN_08014d3a @ 0x08014d3a  size=176  body=[[08014d3a, 08014de9]]

int FUN_08014d3a(int param_1,uint param_2,int param_3,undefined1 *param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint local_24;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    iVar2 = 1;
  }
  else {
    iVar5 = *(int *)(param_1 + 0x1c);
    iVar6 = *(int *)(param_1 + 0x20);
    *(undefined1 *)(param_1 + 4) = 4;
    *(undefined4 *)(iVar5 + 0xc) = 0xffff;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) & 0xfffffcff;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) | 0x200;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) | 1;
    local_24 = param_2;
    do {
      if (param_3 == 0) {
        iVar2 = 0;
        break;
      }
      uVar4 = *(uint *)(iVar6 + 4);
      bVar1 = 0;
      while( true ) {
        uVar3 = (uint)bVar1;
        bVar1 = bVar1 + 1;
        if (uVar4 <= uVar3) break;
        *(undefined1 *)((int)&local_24 + uVar3) = 0xff;
      }
      iVar2 = *(int *)(iVar6 + 0x14);
      uVar4 = param_2 & 0xfffffffc;
      puVar7 = param_4;
      do {
        param_4 = puVar7 + 1;
        *(undefined1 *)((int)&local_24 + (param_2 & 3)) = *puVar7;
        param_2 = param_2 + 1;
        param_3 = param_3 + -1;
        if ((param_2 & 3) == 0) break;
        puVar7 = param_4;
      } while (param_3 != 0);
      *(uint *)(iVar2 + uVar4) = local_24;
      do {
      } while (*(int *)(iVar5 + 0xc) << 0xf < 0);
      iVar2 = FUN_08014c54(param_1);
    } while (iVar2 == 0);
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) & 0xfffffffe;
    *(undefined1 *)(param_1 + 4) = 2;
  }
  return iVar2;
}


// ===================================================================
// FUN_08014dea @ 0x08014dea  size=12  body=[[08014dea, 08014df5]]

undefined4 FUN_08014dea(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    uVar1 = 1;
  }
  else {
    uVar1 = 7;
  }
  return uVar1;
}


// ===================================================================
// FUN_08014df6 @ 0x08014df6  size=70  body=[[08014df6, 08014e3b]]

undefined4 FUN_08014df6(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 4) != '\x05') {
    *(undefined1 *)(param_1 + 4) = 5;
    iVar1 = *(int *)(param_1 + 0x1c);
    *(undefined4 *)(iVar1 + 0xc) = 0xffff;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 2;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xffffff07;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xfffffcff;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | param_2 << 3 | 0x200;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x10000;
    return 0;
  }
  return 1;
}


// ===================================================================
// FUN_08014e3c @ 0x08014e3c  size=50  body=[[08014e3c, 08014e6d]]

undefined4 FUN_08014e3c(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    iVar2 = *(int *)(param_1 + 0x1c);
    if (*(int *)(iVar2 + 0xc) << 0xf < 0) {
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = 5;
      }
      uVar1 = 1;
    }
    else {
      *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) & 0xfffffff9;
      uVar1 = FUN_08014c54(param_1);
      *(undefined1 *)(param_1 + 4) = 2;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// ===================================================================
// FUN_08014e6e @ 0x08014e6e  size=70  body=[[08014e6e, 08014eb3]]

undefined4 FUN_08014e6e(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  if ((char)param_1[1] == '\x05') {
    uVar3 = 1;
  }
  else {
    iVar5 = *(int *)(param_1[8] + 0x14);
    iVar1 = FUN_08014030(param_1,param_2);
    piVar6 = (int *)(iVar5 + iVar1);
    *(undefined1 *)(param_1 + 1) = 3;
    uVar2 = FUN_0801404a(param_1,param_2);
    piVar4 = piVar6;
    do {
      if (piVar4 == (int *)((uVar2 & 0xfffffffc) + (int)piVar6)) {
        uVar3 = 0;
        goto LAB_08014e9e;
      }
      iVar1 = *piVar4;
      piVar4 = piVar4 + 1;
    } while (iVar1 == -1);
    uVar3 = 5;
LAB_08014e9e:
    *(undefined1 *)(param_1 + 1) = 2;
  }
  return uVar3;
}


// ===================================================================
// Vector6C_IRQ11_DMA1_Stream0 @ 0x08014eb4  size=30  body=[[08014eb4, 08014ed1]]

void Vector6C_IRQ11_DMA1_Stream0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = uVar1 & 0x3d;
  if (DAT_200024d4 != (code *)0x0) {
    (*DAT_200024d4)(DAT_200024d8);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector70_IRQ12_DMA1_Stream1 @ 0x08014edc  size=34  body=[[08014edc, 08014efd]]

void Vector70_IRQ12_DMA1_Stream1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_200024dc != (code *)0x0) {
    (*DAT_200024dc)(DAT_200024e0);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector74_IRQ13_DMA1_Stream2 @ 0x08014f08  size=34  body=[[08014f08, 08014f29]]

void Vector74_IRQ13_DMA1_Stream2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_200024e4 != (code *)0x0) {
    (*DAT_200024e4)(DAT_200024e8);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector78_IRQ14_DMA1_Stream3 @ 0x08014f34  size=34  body=[[08014f34, 08014f55]]

void Vector78_IRQ14_DMA1_Stream3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026000;
  DAT_40026008 = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_200024ec != (code *)0x0) {
    (*DAT_200024ec)(DAT_200024f0);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector7C_IRQ15_DMA1_Stream4 @ 0x08014f60  size=30  body=[[08014f60, 08014f7d]]

void Vector7C_IRQ15_DMA1_Stream4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = uVar1 & 0x3d;
  if (DAT_200024f4 != (code *)0x0) {
    (*DAT_200024f4)(DAT_200024f8);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector80_IRQ16_DMA1_Stream5 @ 0x08014f88  size=34  body=[[08014f88, 08014fa9]]

void Vector80_IRQ16_DMA1_Stream5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_200024fc != (code *)0x0) {
    (*DAT_200024fc)(DAT_20002500);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector84_IRQ17_DMA1_Stream6 @ 0x08014fb4  size=34  body=[[08014fb4, 08014fd5]]

void Vector84_IRQ17_DMA1_Stream6(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002504 != (code *)0x0) {
    (*DAT_20002504)(DAT_20002508);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// VectorFC_IRQ47_DMA1_Stream7 @ 0x08014fe0  size=34  body=[[08014fe0, 08015001]]

void VectorFC_IRQ47_DMA1_Stream7(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026004;
  DAT_4002600c = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000250c != (code *)0x0) {
    (*DAT_2000250c)(DAT_20002510);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector120_IRQ56_DMA2_Stream0 @ 0x0801500c  size=30  body=[[0801500c, 08015029]]

void Vector120_IRQ56_DMA2_Stream0(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = uVar1 & 0x3d;
  if (DAT_20002514 != (code *)0x0) {
    (*DAT_20002514)(DAT_20002518);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector124_IRQ57_DMA2_Stream1 @ 0x08015034  size=34  body=[[08015034, 08015055]]

void Vector124_IRQ57_DMA2_Stream1(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_2000251c != (code *)0x0) {
    (*DAT_2000251c)(DAT_20002520);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector128_IRQ58_DMA2_Stream2 @ 0x08015060  size=34  body=[[08015060, 08015081]]

void Vector128_IRQ58_DMA2_Stream2(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002524 != (code *)0x0) {
    (*DAT_20002524)(DAT_20002528);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector12C_IRQ59_DMA2_Stream3 @ 0x0801508c  size=34  body=[[0801508c, 080150ad]]

void Vector12C_IRQ59_DMA2_Stream3(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026400;
  DAT_40026408 = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000252c != (code *)0x0) {
    (*DAT_2000252c)(DAT_20002530);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector130_IRQ60_DMA2_Stream4 @ 0x080150b8  size=30  body=[[080150b8, 080150d5]]

void Vector130_IRQ60_DMA2_Stream4(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = uVar1 & 0x3d;
  if (DAT_20002534 != (code *)0x0) {
    (*DAT_20002534)(DAT_20002538);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector150_IRQ68_DMA2_Stream5 @ 0x080150e0  size=34  body=[[080150e0, 08015101]]

void Vector150_IRQ68_DMA2_Stream5(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 6 & 0x3d) << 6;
  if (DAT_2000253c != (code *)0x0) {
    (*DAT_2000253c)(DAT_20002540);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector154_IRQ69_DMA2_Stream6 @ 0x0801510c  size=34  body=[[0801510c, 0801512d]]

void Vector154_IRQ69_DMA2_Stream6(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 0x10 & 0x3d) << 0x10;
  if (DAT_20002544 != (code *)0x0) {
    (*DAT_20002544)(DAT_20002548);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector158_IRQ70_DMA2_Stream7 @ 0x08015138  size=36  body=[[08015138, 0801515b]]

void Vector158_IRQ70_DMA2_Stream7(void)

{
  uint uVar1;
  
  uVar1 = DAT_40026404;
  DAT_4002640c = (uVar1 >> 0x16 & 0x3d) << 0x16;
  if (DAT_2000254c != (code *)0x0) {
    (*DAT_2000254c)(DAT_20002550);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// FUN_08015164 @ 0x08015164  size=54  body=[[08015164, 08015199]]

void FUN_08015164(void)

{
  int iVar1;
  
  iVar1 = 0;
  DAT_200024d0 = 0;
  do {
    *(undefined4 *)(&DAT_080174c4)[iVar1 * 3] = 0;
    (&DAT_200024d4)[iVar1 * 2] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x10);
  DAT_40026008 = 0xffffffff;
  DAT_4002600c = 0xffffffff;
  DAT_40026408 = 0xffffffff;
  DAT_4002640c = 0xffffffff;
  return;
}


// ===================================================================
// FUN_080151a8 @ 0x080151a8  size=164  body=[[080151a8, 0801524b]]

undefined4 * FUN_080151a8(uint param_1,char param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint *puVar5;
  
  if ((param_1 < 0x10) && (uVar4 = 1 << (param_1 & 0xff), (DAT_200024d0 & uVar4) == 0)) {
    DAT_200024d0 = DAT_200024d0 | uVar4;
    (&DAT_200024d8)[param_1 * 2] = param_4;
    (&DAT_200024d4)[param_1 * 2] = param_3;
    if ((uVar4 & 0xff) != 0) {
      uVar2 = DAT_40023830;
      DAT_40023830 = uVar2 | 0x200000;
      uVar2 = DAT_40023850;
      DAT_40023850 = uVar2 | 0x200000;
      uVar3 = DAT_40023850;
    }
    if ((uVar4 & 0xff00) != 0) {
      uVar4 = DAT_40023830;
      DAT_40023830 = uVar4 | 0x400000;
      uVar4 = DAT_40023850;
      DAT_40023850 = uVar4 | 0x400000;
      uVar3 = DAT_40023850;
    }
    puVar5 = (uint *)(&DAT_080174c4)[param_1 * 3];
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((*puVar5 & 1) != 0);
    iVar1 = param_1 * 0xc;
    **(int **)(&DAT_080174c8 + iVar1) = 0x3d << (&DAT_080174cd)[iVar1];
    *puVar5 = 0;
    puVar5[5] = 0x21;
    if (param_3 != 0) {
      FUN_0801486a((uint)(byte)(&DAT_080174cf)[iVar1],param_2);
    }
    return &DAT_080174c4 + param_1 * 3;
  }
  return (undefined4 *)0x0;
}


// ===================================================================
// FUN_08015258 @ 0x08015258  size=78  body=[[08015258, 080152a5]]

void FUN_08015258(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  FUN_08014896((uint)*(byte *)(param_1 + 0xb));
  DAT_200024d0 = DAT_200024d0 & ~(1 << *(sbyte *)(param_1 + 10));
  if ((DAT_200024d0 & 0xff) == 0) {
    uVar1 = DAT_40023830;
    DAT_40023830 = uVar1 & 0xffdfffff;
    uVar1 = DAT_40023850;
    DAT_40023850 = uVar1 & 0xffdfffff;
    uVar2 = DAT_40023850;
  }
  if ((DAT_200024d0 & 0xff00) == 0) {
    uVar1 = DAT_40023830;
    DAT_40023830 = uVar1 & 0xffbfffff;
    uVar1 = DAT_40023850;
    DAT_40023850 = uVar1 & 0xffbfffff;
    uVar2 = DAT_40023850;
  }
  return;
}


// ===================================================================
// FUN_080152b0 @ 0x080152b0  size=104  body=[[080152b0, 08015317]]

void FUN_080152b0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = ~param_1;
  if ((param_2 & 3) == 0) {
    uVar2 = DAT_40013c00;
    DAT_40013c00 = uVar2 & uVar1;
    uVar2 = DAT_40013c04;
    DAT_40013c04 = uVar2 & uVar1;
    uVar2 = DAT_40013c08;
    DAT_40013c08 = uVar2 & uVar1;
    uVar2 = DAT_40013c0c;
    DAT_40013c0c = uVar1 & uVar2;
    DAT_40013c14 = param_1;
  }
  else {
    uVar2 = DAT_40013c08;
    if ((param_2 & 1) == 0) {
      uVar2 = uVar2 & uVar1;
    }
    else {
      uVar2 = uVar2 | param_1;
    }
    DAT_40013c08 = uVar2;
    uVar2 = DAT_40013c0c;
    if ((param_2 & 2) == 0) {
      uVar2 = uVar2 & uVar1;
    }
    else {
      uVar2 = uVar2 | param_1;
    }
    DAT_40013c0c = uVar2;
    if ((int)(param_2 << 0x1d) < 0) {
      uVar2 = DAT_40013c04;
      DAT_40013c04 = param_1 | uVar2;
      uVar2 = DAT_40013c00;
      DAT_40013c00 = uVar1 & uVar2;
    }
    else {
      uVar2 = DAT_40013c00;
      DAT_40013c00 = uVar2 | param_1;
      uVar2 = DAT_40013c04;
      DAT_40013c04 = uVar1 & uVar2;
    }
  }
  return;
}


// ===================================================================
// FUN_0801531c @ 0x0801531c  size=22  body=[[0801531c, 08015331]]

void FUN_0801531c(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_20004a64;
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 2;
  } while (iVar2 != 0x10);
  return;
}


// ===================================================================
// FUN_08015338 @ 0x08015338  size=214  body=[[08015338, 0801540d]]

void FUN_08015338(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar7 = (param_3 & 7) >> 2;
  uVar6 = (param_3 & 0x1f) >> 3;
  uVar9 = (param_3 & 0x7f) >> 5;
  uVar1 = 0;
  uVar5 = param_3 & 3;
  while( true ) {
    if ((int)(param_2 << 0x1f) < 0) {
      iVar2 = (uVar1 & 7) << 2;
      uVar8 = ((param_3 & 0x7ff) >> 7) << iVar2;
      param_1[1] = param_1[1] & ~(1 << (uVar1 & 0xff)) | uVar7;
      uVar4 = 3 << ((uVar1 & 0x7f) << 1);
      param_1[2] = param_1[2] & ~uVar4 | uVar6;
      param_1[3] = param_1[3] & ~uVar4 | uVar9;
      uVar3 = ~(0xf << iVar2);
      if ((param_3 & 3) == 2) {
        if (uVar1 < 8) {
          param_1[8] = param_1[8] & uVar3 | uVar8;
        }
        else {
          param_1[9] = param_1[9] & uVar3 | uVar8;
        }
        *param_1 = *param_1 & ~uVar4 | uVar5;
      }
      else {
        *param_1 = ~uVar4 & *param_1 | uVar5;
        if (uVar1 < 8) {
          param_1[8] = param_1[8] & uVar3 | uVar8;
        }
        else {
          param_1[9] = param_1[9] & uVar3 | uVar8;
        }
      }
    }
    param_2 = param_2 >> 1;
    if (param_2 == 0) break;
    uVar7 = uVar7 << 1;
    uVar6 = uVar6 << 2;
    uVar9 = uVar9 << 2;
    uVar5 = uVar5 << 2;
    uVar1 = uVar1 + 1;
  }
  return;
}


// ===================================================================
// FUN_08015410 @ 0x08015410  size=94  body=[[08015410, 0801546d]]

void FUN_08015410(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = 1 << (param_2 & 0xff);
  iVar3 = (param_2 & 3) << 2;
  *(uint *)(&DAT_40013808 + (param_2 & 0xfffffffc)) =
       ((param_1 & 0x3fff) >> 10) << iVar3 |
       *(uint *)(&DAT_40013808 + (param_2 & 0xfffffffc)) & ~(0xf << iVar3);
  uVar4 = DAT_40013c08;
  uVar1 = ~uVar2;
  if ((param_3 & 1) == 0) {
    uVar4 = uVar4 & uVar1;
  }
  else {
    uVar4 = uVar4 | uVar2;
  }
  DAT_40013c08 = uVar4;
  uVar4 = DAT_40013c0c;
  if ((param_3 & 2) == 0) {
    uVar4 = uVar4 & uVar1;
  }
  else {
    uVar4 = uVar4 | uVar2;
  }
  DAT_40013c0c = uVar4;
  uVar4 = DAT_40013c00;
  DAT_40013c00 = uVar2 | uVar4;
  uVar4 = DAT_40013c04;
  DAT_40013c04 = uVar4 & uVar1;
  return;
}


// ===================================================================
// FUN_08015474 @ 0x08015474  size=76  body=[[08015474, 080154bf]]

void FUN_08015474(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = DAT_40013c08;
  uVar3 = DAT_40013c0c;
  uVar4 = 1 << (param_2 & 0xff);
  if (((uVar2 | uVar3) & uVar4) != 0) {
    uVar1 = DAT_40013c00;
    DAT_40013c00 = uVar1 & ~uVar4;
    uVar1 = DAT_40013c04;
    DAT_40013c04 = uVar1 & ~uVar4;
    DAT_40013c08 = uVar2 & ~uVar4;
    DAT_40013c0c = uVar3 & ~uVar4;
    DAT_40013c14 = uVar4;
    (&DAT_20004a64)[param_2 * 2] = 0;
    (&DAT_20004a68)[param_2 * 2] = 0;
  }
  return;
}


// ===================================================================
// FUN_080154cc @ 0x080154cc  size=86  body=[[080154cc, 08015521]]

void FUN_080154cc(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = *(int *)(param_1 + 0x54);
  uVar5 = *(uint *)(*(int *)(param_1 + 0x58) + 8);
  uVar2 = 0;
  do {
    iVar3 = iVar4 + uVar2 * 0x20;
    iVar1 = uVar2 * 0x20;
    if (*(int *)(iVar3 + 0x900) < 0) {
      *(uint *)(iVar3 + 0x900) = *(uint *)(iVar3 + 0x900) | 0x40000000;
    }
    if (*(int *)(iVar3 + 0xb00) < 0) {
      *(uint *)(iVar3 + 0xb00) = *(uint *)(iVar3 + 0xb00) | 0x40000000;
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar4 + iVar1;
    *(undefined4 *)(iVar1 + 0x908) = 0xffffffff;
    *(undefined4 *)(iVar1 + 0xb08) = 0xffffffff;
  } while (uVar2 <= uVar5);
  *(undefined4 *)(iVar4 + 0x81c) = 0x10001;
  return;
}


// ===================================================================
// FUN_08015522 @ 0x08015522  size=20  body=[[08015522, 08015535]]

void FUN_08015522(int param_1,int param_2)

{
  *(uint *)(param_1 + 0x10) = param_2 << 6 | 0x20;
  do {
  } while (*(int *)(param_1 + 0x10) << 0x1a < 0);
  FUN_080135c8(0x12);
  return;
}


// ===================================================================
// FUN_08015538 @ 0x08015538  size=22  body=[[08015538, 0801554d]]

void FUN_08015538(void)

{
  FUN_08014204(&DAT_20004ae4);
  DAT_20004b38 = &DAT_50000000;
  DAT_20004b3c = &DAT_08017584;
  return;
}


// ===================================================================
// FUN_08015558 @ 0x08015558  size=178  body=[[08015558, 08015609]]

void FUN_08015558(char *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  if (*param_1 == '\x01') {
    puVar3 = *(undefined4 **)(param_1 + 0x54);
    if (param_1 == &DAT_20004ae4) {
      uVar1 = DAT_40023834;
      DAT_40023834 = uVar1 | 0x80;
      uVar1 = DAT_40023854;
      DAT_40023854 = uVar1 | 0x80;
      uVar2 = DAT_40023854;
      uVar1 = DAT_40023814;
      DAT_40023814 = uVar1 | 0x80;
      uVar1 = DAT_40023814;
      DAT_40023814 = uVar1 & 0xffffff7f;
      uVar2 = DAT_40023814;
      FUN_0801486a(0x43,'\x0e');
      puVar3[3] = &DAT_40001440;
      puVar3[0x200] = 0x2200003;
    }
    puVar3[0x380] = 0;
    *puVar3 = 0xc0;
    iVar4 = *(int *)(param_1 + 0x54);
    puVar3[0xe] = 0x210000;
    do {
    } while (-1 < *(int *)(iVar4 + 0x10));
    *(undefined4 *)(iVar4 + 0x10) = 1;
    FUN_080135c8(0xc);
    do {
    } while (*(int *)(iVar4 + 0x10) << 0x1f < 0);
    FUN_080135c8(0x12);
    do {
    } while (-1 < *(int *)(iVar4 + 0x10));
    puVar3[2] = 0;
    FUN_080154cc((int)param_1);
    iVar4 = *(int *)(param_1 + 4);
    puVar3[0x204] = 0;
    iVar4 = *(int *)(iVar4 + 0xc);
    puVar3[0x205] = 0;
    puVar3[0x207] = 0;
    if (iVar4 == 0) {
      uVar2 = 0xc0303c00;
    }
    else {
      uVar2 = 0xc0303c08;
    }
    puVar3[6] = uVar2;
    puVar3[5] = 0xffffffff;
    puVar3[2] = puVar3[2] | 1;
  }
  return;
}


// ===================================================================
// FUN_08015624 @ 0x08015624  size=60  body=[[08015624, 0801565f]]

void FUN_08015624(char *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x54);
  if (*param_1 != '\x01') {
    FUN_080154cc((int)param_1);
    *(undefined4 *)(iVar3 + 0x81c) = 0;
    *(undefined4 *)(iVar3 + 8) = 0;
    *(undefined4 *)(iVar3 + 0x38) = 0;
    if (param_1 == &DAT_20004ae4) {
      FUN_08014896(0x43);
      uVar1 = DAT_40023834;
      DAT_40023834 = uVar1 & 0xffffff7f;
      uVar1 = DAT_40023854;
      DAT_40023854 = uVar1 & 0xffffff7f;
      uVar2 = DAT_40023854;
    }
  }
  return;
}


// ===================================================================
// FUN_08015668 @ 0x08015668  size=168  body=[[08015668, 0801570f]]

void FUN_08015668(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = *(int *)(param_1 + 0x54);
  FUN_08015522(iVar5,0);
  puVar1 = *(undefined4 **)(param_1 + 0x58);
  uVar3 = 0;
  uVar6 = puVar1[2];
  *(undefined4 *)(iVar5 + 0x834) = 0;
  *(undefined4 *)(iVar5 + 0x81c) = 0x10001;
  do {
    iVar2 = iVar5 + uVar3 * 0x20;
    uVar3 = uVar3 + 1;
    *(undefined4 *)(iVar2 + 0x900) = 0x8000000;
    *(undefined4 *)(iVar2 + 0xb00) = 0x8000000;
    *(undefined4 *)(iVar2 + 0x908) = 0xffffffff;
    *(undefined4 *)(iVar2 + 0xb08) = 0xffffffff;
  } while (uVar3 <= uVar6);
  uVar4 = *puVar1;
  iVar2 = *(int *)(param_1 + 0x54);
  *(undefined4 *)(param_1 + 0x5c) = uVar4;
  *(undefined4 *)(iVar5 + 0x24) = uVar4;
  *(undefined4 *)(iVar2 + 0x10) = 0x10;
  do {
  } while ((*(uint *)(iVar2 + 0x10) & 0x10) != 0);
  FUN_080135c8(0x12);
  *(uint *)(iVar5 + 0x800) = *(uint *)(iVar5 + 0x800) & 0xfffff80f;
  *(uint *)(iVar5 + 0x18) = *(uint *)(iVar5 + 0x18) | 0xc0010;
  *(undefined4 *)(iVar5 + 0x810) = 9;
  *(undefined4 *)(iVar5 + 0x814) = 9;
  *(undefined **)(param_1 + 0xc) = &DAT_08017590;
  *(undefined4 *)(iVar5 + 0xb10) = 0x60000000;
  *(undefined4 *)(iVar5 + 0xb00) = 0x10008040;
  *(undefined4 *)(iVar5 + 0x910) = 0;
  *(undefined4 *)(iVar5 + 0x900) = 0x10008040;
  uVar3 = *(uint *)(param_1 + 0x5c);
  *(uint *)(param_1 + 0x5c) = uVar3 + 0x10;
  *(uint *)(iVar5 + 0x28) = uVar3 | 0x100000;
  return;
}


// ===================================================================
// FUN_08015718 @ 0x08015718  size=24  body=[[08015718, 0801572f]]

void FUN_08015718(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x54) + 0x800) =
       *(uint *)(*(int *)(param_1 + 0x54) + 0x800) & 0xfffff80f |
       (uint)*(byte *)(param_1 + 0x4e) << 4;
  return;
}


// ===================================================================
// FUN_08015730 @ 0x08015730  size=268  body=[[08015730, 0801583b]]

void FUN_08015730(int param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = (int)(short)param_2;
  puVar1 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  iVar5 = *(int *)(param_1 + 0x54);
  uVar6 = *puVar1 & 3;
  uVar3 = uVar6 - 1;
  *(undefined4 *)(iVar5 + param_2 * 0x20 + 0xb10) = 0;
  if (uVar3 < 3) {
    uVar6 = uVar6 << 0x12;
  }
  uVar4 = 1 << (param_2 + 0x10 & 0xff);
  if (uVar3 < 3) {
    uVar6 = uVar6 + 0x10008000;
  }
  else {
    uVar6 = 0x10008000;
  }
  if (puVar1[6] == 0) {
    iVar7 = iVar5 + iVar8 * 0x20;
    *(uint *)(iVar7 + 0xb00) = *(uint *)(iVar7 + 0xb00) & 0xffff7fff;
    uVar4 = *(uint *)(iVar5 + 0x81c) & ~uVar4;
  }
  else {
    *(uint *)(iVar5 + (param_2 + 0x58) * 0x20) = *(ushort *)((int)puVar1 + 0x12) | uVar6;
    uVar4 = uVar4 | *(uint *)(iVar5 + 0x81c);
  }
  *(uint *)(iVar5 + 0x81c) = uVar4;
  *(undefined4 *)(iVar5 + param_2 * 0x20 + 0x910) = 0;
  uVar3 = 1 << (param_2 & 0xff);
  if (puVar1[5] == 0) {
    *(undefined4 *)(iVar5 + (param_2 + 0x3f) * 4 + 4) = 0x2000400;
    FUN_08015522(iVar5,param_2);
    iVar8 = iVar5 + iVar8 * 0x20;
    *(uint *)(iVar8 + 0x900) = *(uint *)(iVar8 + 0x900) & 0xffff7fff;
    uVar3 = *(uint *)(iVar5 + 0x81c) & ~uVar3;
  }
  else {
    uVar4 = (uint)(ushort)((ushort)puVar1[4] >> 2);
    if (1 < (ushort)puVar1[7]) {
      uVar4 = (ushort)puVar1[7] * uVar4;
    }
    uVar2 = *(uint *)(param_1 + 0x5c);
    *(uint *)(param_1 + 0x5c) = uVar4 + uVar2;
    *(uint *)(iVar5 + (param_2 + 0x3f) * 4 + 4) = uVar2 | uVar4 << 0x10;
    FUN_08015522(iVar5,param_2);
    *(uint *)(iVar5 + (param_2 + 0x48) * 0x20) =
         (uint)*(ushort *)(*(int *)(param_1 + iVar8 * 4 + 0xc) + 0x10) | param_2 << 0x16 | uVar6;
    uVar3 = *(uint *)(iVar5 + 0x81c) | uVar3;
  }
  *(uint *)(iVar5 + 0x81c) = uVar3;
  return;
}


// ===================================================================
// FUN_0801584e @ 0x0801584e  size=26  body=[[0801584e, 08015867]]

undefined4 FUN_0801584e(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x54) + (param_2 + 0x58) * 0x20);
  uVar1 = 0;
  if ((uVar2 & 0x8000) != 0) {
    if ((uVar2 & 0x200000) == 0) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}


// ===================================================================
// FUN_08015868 @ 0x08015868  size=26  body=[[08015868, 08015881]]

undefined4 FUN_08015868(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x54) + (param_2 + 0x48) * 0x20);
  uVar1 = 0;
  if ((uVar2 & 0x8000) != 0) {
    if ((uVar2 & 0x200000) == 0) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}


// ===================================================================
// FUN_08015882 @ 0x08015882  size=18  body=[[08015882, 08015893]]

void FUN_08015882(int param_1,int param_2,undefined4 *param_3)

{
  memcpy(param_3,*(undefined4 **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x20),8);
  return;
}


// ===================================================================
// FUN_08015894 @ 0x08015894  size=122  body=[[08015894, 0801590d]]

void FUN_08015894(int param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  puVar6 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  puVar2 = (uint *)puVar6[6];
  puVar2[4] = *puVar2;
  if ((param_2 == 0) && (0x40 < *puVar2)) {
    *puVar2 = 0x40;
  }
  uVar4 = (uint)*(ushort *)((int)puVar6 + 0x12);
  iVar3 = *(int *)(param_1 + 0x54);
  uVar5 = ((*puVar2 + uVar4) - 1) / uVar4;
  *(uint *)(iVar3 + param_2 * 0x20 + 0xb10) =
       uVar5 * uVar4 + 3 & 0xfffffffc | uVar5 << 0x13 | 0x60000000;
  if ((*puVar6 & 3) == 1) {
    iVar1 = iVar3 + (short)param_2 * 0x20;
    uVar4 = *(uint *)(iVar1 + 0xb00);
    if ((*(uint *)(iVar3 + 0x808) & 0x100) == 0) {
      uVar4 = uVar4 | 0x20000000;
    }
    else {
      uVar4 = uVar4 | 0x10000000;
    }
    *(uint *)(iVar1 + 0xb00) = uVar4;
  }
  iVar3 = iVar3 + (short)param_2 * 0x20;
  *(uint *)(iVar3 + 0xb00) = *(uint *)(iVar3 + 0xb00) | 0x84000000;
  return;
}


// ===================================================================
// FUN_08015910 @ 0x08015910  size=170  body=[[08015910, 080159b9]]

void FUN_08015910(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  
  iVar2 = DAT_20004b38;
  iVar3 = DAT_20004b38 + param_1 * 0x20;
  iVar5 = *(int *)(iVar3 + 0xb08);
  *(int *)(iVar3 + 0xb08) = iVar5;
  if ((iVar5 << 0x1c < 0) && (*(int *)(iVar2 + 0x814) << 0x1c < 0)) {
    (**(code **)((&DAT_20004af0)[param_1] + 4))
              (&DAT_20004ae4,param_1,param_3,*(code **)((&DAT_20004af0)[param_1] + 4),param_4);
  }
  if ((iVar5 << 0x1f < 0) && (*(int *)(iVar2 + 0x814) << 0x1f < 0)) {
    iVar2 = (&DAT_20004ae8)[param_1 + 2];
    puVar4 = *(uint **)(iVar2 + 0x18);
    if ((param_1 == 0) &&
       (puVar4[1] == (uint)*(ushort *)(iVar2 + 0x12) * (puVar4[1] / (uint)*(ushort *)(iVar2 + 0x12))
       )) {
      if (*puVar4 < puVar4[4]) {
        *puVar4 = puVar4[4] - *puVar4;
        puVar4[1] = 0;
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        FUN_08015894(0x20004ae4,0);
        bVar1 = (bool)isCurrentModePrivileged();
        if (!bVar1) {
          return;
        }
        setBasePriority(0);
        return;
      }
    }
    DAT_20004aee = DAT_20004aee & ~(ushort)(1 << (param_1 & 0xff));
    if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
      (**(code **)(iVar2 + 0xc))(&DAT_20004ae4,param_1);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x18) + 0xc),
                 *(int *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x18) + 4));
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}


// ===================================================================
// FUN_080159c0 @ 0x080159c0  size=138  body=[[080159c0, 08015a49]]

void FUN_080159c0(int param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  
  puVar4 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  iVar1 = *(int *)(param_1 + 0x54);
  puVar2 = (uint *)puVar4[5];
  uVar5 = *puVar2;
  puVar2[4] = uVar5;
  if (uVar5 == 0) {
    uVar5 = 0x80000;
  }
  else {
    if ((param_2 == 0) && (0x40 < uVar5)) {
      *puVar2 = 0x40;
    }
    uVar5 = *puVar2 | ((*puVar2 + (uint)(ushort)puVar4[4]) - 1) / (uint)(ushort)puVar4[4] << 0x13 |
            0x20000000;
  }
  *(uint *)(param_2 * 0x20 + iVar1 + 0x910) = uVar5;
  if ((*puVar4 & 3) == 1) {
    iVar3 = iVar1 + (short)param_2 * 0x20;
    uVar5 = *(uint *)(iVar3 + 0x900);
    if ((*(uint *)(iVar1 + 0x808) & 0x100) == 0) {
      uVar5 = uVar5 | 0x20000000;
    }
    else {
      uVar5 = uVar5 | 0x10000000;
    }
    *(uint *)(iVar3 + 0x900) = uVar5;
  }
  iVar3 = iVar1 + (short)param_2 * 0x20;
  *(uint *)(iVar3 + 0x900) = *(uint *)(iVar3 + 0x900) | 0x84000000;
  *(uint *)(iVar1 + 0x834) = 1 << (param_2 & 0xff) | *(uint *)(iVar1 + 0x834);
  return;
}


// ===================================================================
// FUN_08015a4c @ 0x08015a4c  size=268  body=[[08015a4c, 08015b57]]

void FUN_08015a4c(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  code *pcVar6;
  uint uVar7;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  uint uVar13;
  
  iVar9 = DAT_20004b38;
  iVar4 = DAT_20004b38 + param_1 * 0x20;
  uVar10 = *(uint *)(iVar4 + 0x908);
  *(uint *)(iVar4 + 0x908) = uVar10;
  if (((uVar10 & 1) != 0) && (*(int *)(iVar9 + 0x810) << 0x1f < 0)) {
    puVar5 = *(uint **)((&DAT_20004ae8)[param_1 + 2] + 0x14);
    if (*puVar5 < puVar5[4]) {
      *puVar5 = puVar5[4] - *puVar5;
      puVar5[1] = 0;
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_080159c0(0x20004ae4,param_1);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    else {
      iVar4 = 1 << (param_1 & 0xff);
      DAT_20004aec = DAT_20004aec & ~(ushort)iVar4;
      pcVar6 = *(code **)((&DAT_20004ae8)[param_1 + 2] + 8);
      if (pcVar6 != (code *)0x0) {
        (*pcVar6)(&DAT_20004ae4,param_1,iVar4,pcVar6,param_4);
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x14) + 0xc),0);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
  }
  iVar4 = DAT_20004b38;
  if (((uVar10 & 0x80) != 0) &&
     (uVar10 = 1 << (param_1 & 0xff), (*(uint *)(iVar9 + 0x834) & uVar10) != 0)) {
    iVar12 = (&DAT_20004af0)[param_1];
    puVar5 = *(uint **)(iVar12 + 0x14);
    uVar13 = *puVar5;
    puVar8 = (undefined4 *)(DAT_20004b38 + (param_1 + 1 & 0xff) * 0x1000);
    iVar9 = param_1 * 0x20 + DAT_20004b38;
    while (uVar3 = puVar5[1], uVar3 < uVar13) {
      uVar2 = (uint)*(ushort *)(iVar12 + 0x10);
      uVar7 = uVar13 - uVar3;
      if (uVar2 <= uVar7) {
        uVar7 = uVar2;
      }
      if ((*(uint *)(iVar9 + 0x918) & 0xffff) * 4 < uVar7) {
        return;
      }
      uVar2 = puVar5[2];
      puVar11 = (undefined4 *)(uVar2 - 4);
      do {
        puVar11 = puVar11 + 1;
        *puVar8 = *puVar11;
      } while (4 < (uVar2 - (int)puVar11) + uVar7);
      puVar5[2] = uVar2 + uVar7;
      puVar5[1] = uVar3 + uVar7;
    }
    *(uint *)(iVar4 + 0x834) = *(uint *)(iVar4 + 0x834) & ~uVar10;
  }
  return;
}


// ===================================================================
// Vector14C_IRQ67_OTG_FS @ 0x08015b5c  size=706  body=[[08015b5c, 08015dff] [08015e04, 08015e21]]

void Vector14C_IRQ67_OTG_FS(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  bool bVar1;
  undefined4 extraout_r1;
  undefined1 *puVar2;
  undefined1 *extraout_r1_00;
  undefined1 *extraout_r1_01;
  undefined1 *extraout_r1_02;
  undefined1 *extraout_r1_03;
  undefined1 *extraout_r1_04;
  undefined1 *extraout_r1_05;
  undefined1 *extraout_r1_06;
  int iVar3;
  int extraout_r1_07;
  int extraout_r1_08;
  undefined1 *extraout_r2;
  undefined4 extraout_r2_00;
  undefined1 *extraout_r2_01;
  undefined1 *extraout_r2_02;
  undefined1 *extraout_r2_03;
  undefined1 *extraout_r2_04;
  undefined1 *extraout_r2_05;
  undefined1 *extraout_r2_06;
  undefined1 *extraout_r2_07;
  undefined1 *extraout_r2_08;
  undefined1 *extraout_r2_09;
  int extraout_r2_10;
  undefined1 *puVar4;
  undefined4 extraout_r3;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined1 *extraout_r3_00;
  undefined1 *extraout_r3_01;
  undefined1 *extraout_r3_02;
  undefined1 *extraout_r3_03;
  undefined1 *extraout_r3_04;
  int iVar8;
  uint uVar9;
  undefined1 *puVar10;
  uint *puVar11;
  int *piVar12;
  
  iVar8 = DAT_20004b38;
  uVar9 = *(uint *)(DAT_20004b38 + 0x14) & *(uint *)(DAT_20004b38 + 0x18);
  *(uint *)(DAT_20004b38 + 0x14) = uVar9;
  if ((uVar9 & 0x1000) == 0) {
    if ((int)uVar9 < 0) {
      if ((*(uint *)(iVar8 + 0xe00) & 3) != 0) {
        *(uint *)(iVar8 + 0xe00) = *(uint *)(iVar8 + 0xe00) & 0xfffffffc;
      }
      *(uint *)(iVar8 + 0x804) = *(uint *)(iVar8 + 0x804) & 0xfffffffe;
      FUN_08014462(&DAT_20004ae4);
      param_3 = extraout_r2;
    }
    if ((int)(uVar9 << 0x14) < 0) {
      FUN_080154cc(0x20004ae4);
      FUN_08014406(&DAT_20004ae4,extraout_r1,extraout_r2_00,extraout_r3);
      param_3 = extraout_r2_01;
    }
    if ((int)(uVar9 << 0x12) < 0) {
      uVar5 = *(uint *)(iVar8 + 0xc) & 0xffffc3ff;
      if ((*(uint *)(iVar8 + 0x808) & 6) == 0) {
        uVar5 = uVar5 | 0x2400;
      }
      else {
        uVar5 = uVar5 | 0x1400;
      }
      *(uint *)(iVar8 + 0xc) = uVar5;
    }
    puVar2 = (undefined1 *)(uVar9 << 0x1c);
    if ((int)puVar2 < 0) {
      if (*(int *)(DAT_20004ae8 + 0xc) == 0) {
        *(uint *)(iVar8 + 0x18) = *(uint *)(iVar8 + 0x18) & 0xfffffff7;
      }
      if (DAT_20004ae4 == '\x05') {
        if ((*(uint *)(iVar8 + 0xe00) & 3) != 0) {
          *(uint *)(iVar8 + 0xe00) = *(uint *)(iVar8 + 0xe00) & 0xfffffffc;
        }
        FUN_08014462(&DAT_20004ae4);
        puVar2 = extraout_r1_00;
        param_3 = extraout_r2_02;
      }
      if (*(code **)(DAT_20004ae8 + 0xc) != (code *)0x0) {
        (**(code **)(DAT_20004ae8 + 0xc))(&DAT_20004ae4);
        puVar2 = extraout_r1_01;
        param_3 = extraout_r2_03;
      }
    }
    iVar3 = DAT_20004b38;
    puVar6 = (undefined1 *)(uVar9 << 0xb);
    if ((int)puVar6 < 0) {
      puVar2 = (undefined1 *)0x0;
      do {
        iVar7 = iVar3 + (int)puVar2 * 0x20;
        param_3 = (undefined1 *)(*(uint *)(iVar7 + 0x900) & 0xc0000);
        if ((param_3 == (undefined1 *)0x40000) &&
           (param_3 = *(undefined1 **)(iVar7 + 0x900), (int)param_3 < 0)) {
          *(uint *)(iVar7 + 0x900) = *(uint *)(iVar7 + 0x900) | 0x48000000;
          do {
          } while (*(int *)(iVar7 + 0x900) < 0);
          FUN_08015522(DAT_20004b38,(int)puVar2);
          DAT_20004aec = DAT_20004aec & ~(ushort)(1 << (int)puVar2);
          if (*(code **)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 8) != (code *)0x0) {
            (**(code **)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 8))(&DAT_20004ae4,puVar2);
          }
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 0x14) + 0xc),0);
          bVar1 = (bool)isCurrentModePrivileged();
          param_3 = extraout_r2_04;
          if (bVar1) {
            setBasePriority(0);
          }
        }
        puVar6 = *(undefined1 **)(DAT_20004b3c + 8);
        puVar2 = (undefined1 *)((uint)(puVar2 + 1) & 0xff);
      } while (puVar2 <= puVar6);
    }
    iVar3 = DAT_20004b38;
    if ((int)(uVar9 << 10) < 0) {
      puVar10 = (undefined1 *)0x0;
      do {
        param_3 = (undefined1 *)(iVar3 + (int)puVar10 * 0x20);
        if (((*(uint *)(param_3 + 0xb00) & 0xc0000) == 0x40000) && (*(int *)(param_3 + 0xb00) < 0))
        {
          DAT_20004aee = DAT_20004aee & ~(ushort)(1 << (int)puVar10);
          if (*(code **)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0xc) != (code *)0x0) {
            (**(code **)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0xc))(&DAT_20004ae4,puVar10);
          }
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0x18) + 0xc),
                       *(int *)(*(int *)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0x18) + 4));
          bVar1 = (bool)isCurrentModePrivileged();
          puVar2 = extraout_r1_02;
          param_3 = extraout_r2_05;
          if (bVar1) {
            setBasePriority(0);
          }
        }
        puVar6 = *(undefined1 **)(DAT_20004b3c + 8);
        puVar10 = (undefined1 *)((uint)(puVar10 + 1) & 0xff);
      } while (puVar10 <= puVar6);
    }
    if ((int)(uVar9 << 0x1b) < 0) {
      uVar5 = *(uint *)(DAT_20004b38 + 0x20);
      puVar10 = (undefined1 *)((uVar5 & 0x7fff) >> 4);
      puVar6 = (undefined1 *)(uVar5 & 0xf);
      param_3 = (undefined1 *)(uVar5 & 0x1e0000);
      if (param_3 == (undefined1 *)0x40000) {
        puVar11 = (uint *)(DAT_20004b38 + 0x1000);
        piVar12 = *(int **)((&DAT_20004ae8)[(int)(puVar6 + 2)] + 0x18);
        puVar4 = (undefined1 *)piVar12[2];
        iVar3 = *piVar12;
        iVar7 = piVar12[1];
        uVar5 = 0;
        for (puVar2 = (undefined1 *)0x0; puVar10 != puVar2; puVar2 = puVar2 + 1) {
          if (((uint)puVar2 & 3) == 0) {
            uVar5 = *puVar11;
          }
          if (puVar2 < (undefined1 *)(iVar3 - iVar7)) {
            *puVar4 = (char)uVar5;
            uVar5 = uVar5 >> 8;
            puVar4 = puVar4 + 1;
          }
        }
        puVar6 = *(undefined1 **)((&DAT_20004ae8)[(int)(puVar6 + 2)] + 0x18);
        *(undefined1 **)(puVar6 + 8) = puVar10 + *(int *)(puVar6 + 8);
        param_3 = puVar10 + *(int *)(puVar6 + 4);
        *(undefined1 **)(puVar6 + 4) = param_3;
      }
      else if (param_3 == (undefined1 *)0xc0000) {
        puVar6 = *(undefined1 **)((&DAT_20004af0)[(int)puVar6] + 0x20);
        puVar11 = (uint *)(DAT_20004b38 + 0x1000);
        uVar5 = 0;
        for (param_3 = (undefined1 *)0x0; puVar10 != param_3; param_3 = param_3 + 1) {
          puVar2 = (undefined1 *)((int)param_3 << 0x1e);
          if (puVar2 == (undefined1 *)0x0) {
            uVar5 = *puVar11;
          }
          if (param_3 < &NMI) {
            *puVar6 = (char)uVar5;
            uVar5 = uVar5 >> 8;
            puVar6 = puVar6 + 1;
          }
        }
      }
    }
    iVar8 = *(int *)(iVar8 + 0x818);
    if ((int)(uVar9 << 0xc) < 0) {
      puVar2 = (undefined1 *)(iVar8 << 0xf);
      if ((int)puVar2 < 0) {
        FUN_08015910(0,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_03;
        puVar6 = extraout_r3_00;
      }
      param_3 = (undefined1 *)(iVar8 << 0xe);
      if ((int)param_3 < 0) {
        FUN_08015910(1,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_04;
        param_3 = extraout_r2_06;
      }
      puVar6 = (undefined1 *)(iVar8 << 0xd);
      if ((int)puVar6 < 0) {
        FUN_08015910(2,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_05;
        param_3 = extraout_r2_07;
        puVar6 = extraout_r3_01;
      }
      if (iVar8 << 0xc < 0) {
        FUN_08015910(3,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_06;
        param_3 = extraout_r2_08;
        puVar6 = extraout_r3_02;
      }
    }
    if ((int)(uVar9 << 0xd) < 0) {
      if (iVar8 << 0x1f < 0) {
        FUN_08015a4c(0,puVar2,param_3,puVar6);
        param_3 = extraout_r2_09;
        puVar6 = extraout_r3_03;
      }
      iVar3 = iVar8 << 0x1e;
      if (iVar3 < 0) {
        FUN_08015a4c(1,iVar3,param_3,puVar6);
        iVar3 = extraout_r1_07;
        puVar6 = extraout_r3_04;
      }
      iVar7 = iVar8 << 0x1d;
      if (iVar7 < 0) {
        FUN_08015a4c(2,iVar3,iVar7,puVar6);
        iVar3 = extraout_r1_08;
        iVar7 = extraout_r2_10;
      }
      if (iVar8 << 0x1c < 0) {
        FUN_08015a4c(3,iVar3,iVar7,iVar8 << 0x1c);
      }
    }
  }
  else {
    FUN_08014396(&DAT_20004ae4);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// FUN_08015e24 @ 0x08015e24  size=20  body=[[08015e24, 08015e37]]

void FUN_08015e24(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0xb00) = *(uint *)(iVar1 + 0xb00) | 0x200000;
  return;
}


// ===================================================================
// FUN_08015e38 @ 0x08015e38  size=20  body=[[08015e38, 08015e4b]]

void FUN_08015e38(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0x900) = *(uint *)(iVar1 + 0x900) | 0x200000;
  return;
}


// ===================================================================
// FUN_08015e4c @ 0x08015e4c  size=20  body=[[08015e4c, 08015e5f]]

void FUN_08015e4c(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0xb00) = *(uint *)(iVar1 + 0xb00) & 0xffdfffff;
  return;
}


// ===================================================================
// FUN_08015e60 @ 0x08015e60  size=20  body=[[08015e60, 08015e73]]

void FUN_08015e60(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54) + param_2 * 0x20;
  *(uint *)(iVar1 + 0x900) = *(uint *)(iVar1 + 0x900) & 0xffdfffff;
  return;
}


// ===================================================================
// FUN_08015e74 @ 0x08015e74  size=20  body=[[08015e74, 08015e87]]

void FUN_08015e74(void)

{
  int iVar1;
  
  iVar1 = DAT_20004b48;
  *(uint *)(DAT_20004b48 + 0xc) = *(uint *)(DAT_20004b48 + 0xc) | 0x80;
  do {
  } while (-1 < *(int *)(iVar1 + 0xc) << 0x19);
  return;
}


// ===================================================================
// FUN_08015e8c @ 0x08015e8c  size=4  body=[[08015e8c, 08015e8f]]

undefined4 FUN_08015e8c(void)

{
  return 0x50;
}


// ===================================================================
// FUN_08015e90 @ 0x08015e90  size=42  body=[[08015e90, 08015eb9]]

undefined4 FUN_08015e90(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 4);
  puVar2 = param_4 + param_3;
  iVar1 = param_2 - (int)param_4;
  for (; param_4 != puVar2; param_4 = param_4 + 1) {
    *param_4 = (char)(*(uint *)(iVar3 + 0x50 + ((uint)(param_4 + iVar1) & 0xfffffffc)) >>
                     (((uint)(param_4 + iVar1) & 3) << 3));
  }
  return 0;
}


// ===================================================================
// FUN_08015eba @ 0x08015eba  size=58  body=[[08015eba, 08015ef3]]

undefined4 FUN_08015eba(int param_1,int param_2,int param_3,byte *param_4)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  
  pbVar3 = param_4 + param_3;
  iVar4 = *(int *)(param_1 + 4) + 0x50;
  iVar2 = param_2 - (int)param_4;
  for (; param_4 != pbVar3; param_4 = param_4 + 1) {
    uVar5 = (uint)(param_4 + iVar2) & 0xfffffffc;
    iVar1 = ((uint)(param_4 + iVar2) & 3) << 3;
    *(uint *)(iVar4 + uVar5) = (uint)*param_4 << iVar1 | *(uint *)(iVar4 + uVar5) & ~(0xff << iVar1)
    ;
  }
  return 0;
}


// ===================================================================
// Vector48_IRQ2_TAMP_STAMP @ 0x08015ef4  size=94  body=[[08015ef4, 08015f51]]

void Vector48_IRQ2_TAMP_STAMP(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_20004b48;
  uVar2 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar2 & 0xffff87ff;
  DAT_40013c14 = 0x200000;
  if (DAT_20004b4c != (code *)0x0) {
    if (*(int *)(iVar1 + 8) << 0x10 < 0) {
      if ((int)(uVar2 << 0x14) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,2);
      }
      if ((int)(uVar2 << 0x13) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,3);
      }
    }
    if (*(int *)(DAT_20004b48 + 0x40) << 0x1d < 0) {
      if ((int)(uVar2 << 0x12) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,4);
      }
      if ((int)(uVar2 << 0x11) < 0) {
        (*DAT_20004b4c)(&DAT_20004b44,5);
      }
    }
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// Vector4C_IRQ3_RTC_WKUP @ 0x08015f5c  size=48  body=[[08015f5c, 08015f8b]]

void Vector4C_IRQ3_RTC_WKUP(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_20004b48;
  uVar2 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar2 & 0xfffffbff;
  DAT_40013c14 = 0x400000;
  if (((DAT_20004b4c != (code *)0x0) && (*(int *)(iVar1 + 8) << 0x11 < 0)) &&
     ((int)(uVar2 << 0x15) < 0)) {
    (*DAT_20004b4c)(&DAT_20004b44,7);
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// VectorE4_IRQ41_RTC_Alarm @ 0x08015f94  size=66  body=[[08015f94, 08015fd5]]

void VectorE4_IRQ41_RTC_Alarm(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_20004b48;
  uVar1 = *(uint *)(DAT_20004b48 + 0xc);
  *(uint *)(DAT_20004b48 + 0xc) = uVar1 & 0xfffffcff;
  DAT_40013c14 = 0x20000;
  if (DAT_20004b4c != (code *)0x0) {
    iVar2 = *(int *)(iVar2 + 8);
    if ((iVar2 << 0x13 < 0) && ((int)(uVar1 << 0x17) < 0)) {
      (*DAT_20004b4c)(&DAT_20004b44,0);
    }
    if ((iVar2 << 0x12 < 0) && ((int)(uVar1 << 0x16) < 0)) {
      (*DAT_20004b4c)(&DAT_20004b44,1);
    }
  }
  FUN_08013c7c();
  return;
}


// ===================================================================
// FUN_08015fe0 @ 0x08015fe0  size=106  body=[[08015fe0, 08016049]]

void FUN_08015fe0(void)

{
  undefined *puVar1;
  undefined *extraout_r1;
  uint uVar2;
  
  FUN_080140f8((undefined4 *)&DAT_20004b44);
  puVar1 = &DAT_40002800;
  DAT_20004b48 = &DAT_40002800;
  DAT_40002824 = 0xca;
  DAT_40002824 = 0x53;
  uVar2 = DAT_4000280c;
  if ((uVar2 & 0x10) == 0) {
    FUN_08015e74();
    *(undefined4 *)(extraout_r1 + 8) = 0;
    *(undefined4 *)(extraout_r1 + 0x40) = 0;
    *(undefined4 *)(extraout_r1 + 0xc) = 0x80;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    uVar2 = *(uint *)(extraout_r1 + 0xc) & 0xffffff7f;
    puVar1 = extraout_r1;
  }
  else {
    uVar2 = DAT_4000280c;
    uVar2 = uVar2 & 0xffffffdf;
  }
  *(uint *)(puVar1 + 0xc) = uVar2;
  DAT_20004b4c = 0;
  FUN_080152b0(0x620000,1);
  FUN_0801486a(2,'\x0f');
  FUN_0801486a(3,'\x0f');
  FUN_0801486a(0x29,'\x0f');
  return;
}


// ===================================================================
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


// ===================================================================
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


// ===================================================================
// FUN_0801622c @ 0x0801622c  size=46  body=[[0801622c, 08016259]]

void FUN_0801622c(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = *(uint **)(param_1 + 0x1c);
  iVar2 = *(int *)(param_1 + 4);
  uVar1 = *(ushort *)(iVar2 + 0x16);
  *puVar3 = 0;
  uVar5 = *(ushort *)(iVar2 + 0x14) & 0xffffffbb;
  if (*(char *)(iVar2 + 1) == '\0') {
    uVar5 = uVar5 | 0x304;
    uVar4 = uVar1 | 7;
  }
  else {
    uVar4 = uVar1 | 3;
  }
  puVar3[1] = uVar4;
  *puVar3 = uVar5;
  *puVar3 = uVar5 | 0x40;
  return;
}


// ===================================================================
// FUN_0801625c @ 0x0801625c  size=160  body=[[0801625c, 080162fb]]

undefined4 FUN_0801625c(undefined1 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint *puVar5;
  
  puVar3 = *(undefined4 **)(param_1 + 0x24);
  puVar5 = (uint *)*puVar3;
  if (*(char *)(*(int *)(param_1 + 4) + 1) == '\0') {
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    iVar4 = *(int *)(param_1 + 0x1c);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    do {
    } while (*(int *)(iVar4 + 8) << 0x18 < 0);
    puVar3 = *(undefined4 **)(param_1 + 0x20);
    puVar5 = (uint *)*puVar3;
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
  }
  else {
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    puVar3 = *(undefined4 **)(param_1 + 0x20);
    puVar5 = (uint *)*puVar3;
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    if (param_1 == &DAT_20004b50) {
      uVar1 = DAT_40023824;
      DAT_40023824 = uVar1 | 0x1000;
      uVar1 = DAT_40023824;
      DAT_40023824 = uVar1 & 0xffffefff;
      uVar2 = DAT_40023824;
    }
    FUN_0801622c((int)param_1);
  }
  return 0;
}


// ===================================================================
// FUN_08016304 @ 0x08016304  size=56  body=[[08016304, 0801633b]]

void FUN_08016304(undefined1 *param_1,uint param_2)

{
  bool bVar1;
  
  if ((param_2 & 0xc) != 0) {
    FUN_0801357c();
    FUN_0801625c(param_1);
    if (*(code **)(*(int *)(param_1 + 4) + 8) != (code *)0x0) {
      (**(code **)(*(int *)(param_1 + 4) + 8))(param_1);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08013ab0((undefined4 *)(param_1 + 8),0);
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}


// ===================================================================
// FUN_08016340 @ 0x08016340  size=132  body=[[08016340, 080163c3]]

void FUN_08016340(char *param_1,uint param_2)

{
  bool bVar1;
  code *pcVar2;
  char *pcVar3;
  
  if ((param_2 & 0xc) == 0) {
    pcVar3 = *(char **)(param_1 + 4);
    if (*pcVar3 != '\0') {
      if (((int)(param_2 << 0x1b) < 0) && (*(code **)(pcVar3 + 4) != (code *)0x0)) {
        (**(code **)(pcVar3 + 4))();
      }
      if (-1 < (int)(param_2 << 0x1a)) {
        return;
      }
      pcVar2 = *(code **)(*(int *)(param_1 + 4) + 4);
      if (pcVar2 == (code *)0x0) {
        return;
      }
      *param_1 = '\x04';
      (*pcVar2)(param_1);
      if (*param_1 != '\x04') {
        return;
      }
      *param_1 = '\x03';
      return;
    }
    FUN_0801625c(param_1);
    pcVar2 = *(code **)(pcVar3 + 4);
    if (pcVar2 != (code *)0x0) {
      *param_1 = '\x04';
      (*pcVar2)(param_1);
      if (*param_1 != '\x04') goto LAB_08016362;
    }
    *param_1 = '\x02';
  }
  else {
    FUN_0801357c();
    FUN_0801625c(param_1);
    if (*(code **)(*(int *)(param_1 + 4) + 8) != (code *)0x0) {
      (**(code **)(*(int *)(param_1 + 4) + 8))(param_1);
    }
  }
LAB_08016362:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013ab0((undefined4 *)(param_1 + 8),0);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}


// ===================================================================
// FUN_080163c8 @ 0x080163c8  size=30  body=[[080163c8, 080163e5]]

void FUN_080163c8(void)

{
  FUN_08014110(&DAT_20004b50);
  DAT_20004b6c = &DAT_40013000;
  DAT_20004b70 = 0;
  DAT_20004b74 = 0;
  DAT_20004b78 = 0x6010016;
  DAT_20004b7c = 0x6010046;
  return;
}


// ===================================================================
// FUN_080163f4 @ 0x080163f4  size=186  body=[[080163f4, 080164ad]]

undefined4 FUN_080163f4(char *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  param_1[0x34] = -1;
  param_1[0x35] = -1;
  param_1[0x36] = -1;
  param_1[0x37] = -1;
  if (*param_1 == '\x01') {
    if (param_1 == &DAT_20004b50) {
      DAT_20004b70 = FUN_080151a8(8,'\n',0x8016341,&DAT_20004b50);
      if (DAT_20004b70 == (undefined4 *)0x0) {
        return 0xffffffef;
      }
      DAT_20004b74 = FUN_080151a8(0xb,'\n',0x8016305,&DAT_20004b50);
      if (DAT_20004b74 == (undefined4 *)0x0) {
        FUN_08015258((int)DAT_20004b70);
        return 0xffffffef;
      }
      uVar2 = DAT_40023844;
      DAT_40023844 = uVar2 | 0x1000;
      uVar2 = DAT_40023864;
      DAT_40023864 = uVar2 | 0x1000;
      uVar1 = DAT_40023864;
      uVar2 = DAT_40023824;
      DAT_40023824 = uVar2 | 0x1000;
      uVar2 = DAT_40023824;
      DAT_40023824 = uVar2 & 0xffffefff;
      uVar1 = DAT_40023824;
    }
    iVar3 = *(int *)(param_1 + 0x1c);
    *(int *)(**(int **)(param_1 + 0x20) + 8) = iVar3 + 0xc;
    *(int *)(**(int **)(param_1 + 0x24) + 8) = iVar3 + 0xc;
  }
  uVar2 = *(uint *)(param_1 + 0x28) & 0xffff87ff;
  uVar4 = *(uint *)(param_1 + 0x2c) & 0xffff87ff;
  if ((int)((uint)*(ushort *)(*(char **)(param_1 + 4) + 0x14) << 0x14) < 0) {
    uVar2 = uVar2 | 0x2800;
    uVar4 = uVar4 | 0x2800;
  }
  if (**(char **)(param_1 + 4) == '\0') {
    uVar2 = uVar2 & 0xfffffef7;
    uVar4 = uVar4 & 0xfffffef7;
  }
  else {
    uVar2 = uVar2 | 0x108;
    uVar4 = uVar4 | 0x108;
  }
  *(uint *)(param_1 + 0x28) = uVar2;
  *(uint *)(param_1 + 0x2c) = uVar4;
  FUN_0801622c((int)param_1);
  return 0;
}


// ===================================================================
// FUN_080164c0 @ 0x080164c0  size=66  body=[[080164c0, 08016501]]

void FUN_080164c0(char *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (*param_1 == '\x02') {
    FUN_0801625c(param_1);
    puVar4 = *(undefined4 **)(param_1 + 0x1c);
    iVar3 = *(int *)(param_1 + 0x24);
    *puVar4 = 0;
    puVar4[1] = 0;
    FUN_08015258(iVar3);
    FUN_08015258(*(int *)(param_1 + 0x20));
    param_1[0x20] = '\0';
    param_1[0x21] = '\0';
    param_1[0x22] = '\0';
    param_1[0x23] = '\0';
    param_1[0x24] = '\0';
    param_1[0x25] = '\0';
    param_1[0x26] = '\0';
    param_1[0x27] = '\0';
    if (param_1 == &DAT_20004b50) {
      uVar1 = DAT_40023844;
      DAT_40023844 = uVar1 & 0xffffefff;
      uVar1 = DAT_40023864;
      DAT_40023864 = uVar1 & 0xffffefff;
      uVar2 = DAT_40023864;
    }
  }
  return;
}


// ===================================================================
// FUN_0801650c @ 0x0801650c  size=54  body=[[0801650c, 08016541]]

undefined4 FUN_0801650c(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar3 = (uint *)**(undefined4 **)(param_1 + 0x20);
  puVar3[3] = param_4;
  uVar1 = *(uint *)(param_1 + 0x28);
  puVar3[1] = param_2;
  *puVar3 = uVar1 | 0x400;
  puVar2 = (uint *)**(undefined4 **)(param_1 + 0x24);
  puVar2[3] = param_3;
  uVar1 = *(uint *)(param_1 + 0x2c);
  puVar2[1] = param_2;
  *puVar2 = uVar1 | 0x400;
  *puVar3 = *puVar3 | 1;
  *puVar2 = *puVar2 | 1;
  return 0;
}


// ===================================================================
// FUN_080165c0 @ 0x080165c0  size=40  body=[[080165c0, 080165e7]]

void FUN_080165c0(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = DAT_40000010;
  uVar2 = DAT_4000000c;
  DAT_40000010 = ~(uVar2 & uVar3 & 0xff);
  if ((int)((uVar2 & uVar3) << 0x1e) < 0) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    thunk_FUN_08013774();
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}


// ===================================================================
// FUN_080165e8 @ 0x080165e8  size=30  body=[[080165e8, 08016605]]

void FUN_080165e8(undefined4 *param_1,undefined4 *param_2)

{
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[5] = param_2[4];
  param_1[8] = param_2[5];
  param_1[9] = param_2[6];
  *param_1 = *param_2;
  return;
}


// ===================================================================
// FUN_08016608 @ 0x08016608  size=118  body=[[08016608, 0801667d]]

void FUN_08016608(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int extraout_r2;
  int extraout_r2_00;
  int extraout_r2_01;
  int extraout_r2_02;
  int extraout_r2_03;
  
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 | 0x9f;
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 & 0xffffff60;
  uVar2 = DAT_40023810;
  uVar1 = DAT_40023830;
  DAT_40023830 = uVar1 | 0x9f;
  uVar1 = DAT_40023850;
  DAT_40023850 = uVar1 | 0x9f;
  uVar2 = DAT_40023850;
  iVar3 = FUN_080165e8((undefined4 *)&DAT_40020000,(undefined4 *)&DAT_080175b4);
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2 + 0x1c));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_00 + 0x38));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_01 + 0x54));
  iVar3 = FUN_080165e8((undefined4 *)(iVar3 + 0x400),(undefined4 *)(extraout_r2_02 + 0x70));
  FUN_080165e8((undefined4 *)(iVar3 + 0xc00),(undefined4 *)(extraout_r2_03 + 0x8c));
  FUN_08014b5c();
  return;
}


// ===================================================================
// FUN_0801668c @ 0x0801668c  size=2  body=[[0801668c, 0801668d]]

void FUN_0801668c(void)

{
  return;
}


// ===================================================================
// FUN_0801668e @ 0x0801668e  size=10  body=[[0801668e, 08016697]]

undefined4 FUN_0801668e(undefined4 *param_1)

{
  *param_1 = 0x16;
  return 0xffffffff;
}


// ===================================================================
// FUN_08016698 @ 0x08016698  size=4  body=[[08016698, 0801669b]]

undefined4 FUN_08016698(void)

{
  return 0;
}


// ===================================================================
// FUN_080166a4 @ 0x080166a4  size=26  body=[[080166a4, 080166bd]]

int FUN_080166a4(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_080134d8(param_2,1,0);
  if (iVar1 == 0) {
    *param_1 = 0xc;
    iVar1 = -1;
  }
  return iVar1;
}


// ===================================================================
// FUN_080166be @ 0x080166be  size=24  body=[[080166be, 080166d5]]

undefined4 FUN_080166be(undefined4 param_1,undefined4 param_2,byte *param_3)

{
  int iVar1;
  
  iVar1 = FUN_08008798(param_3,0,0x58);
  *(undefined4 *)(iVar1 + 4) = 0x2000;
  return 0;
}


// ===================================================================
// FUN_080166d6 @ 0x080166d6  size=4  body=[[080166d6, 080166d9]]

undefined4 FUN_080166d6(void)

{
  return 1;
}


// ===================================================================
// FUN_080166dc @ 0x080166dc  size=16  body=[[080166dc, 080166eb]]

undefined8 FUN_080166dc(void)

{
  FUN_0801357c();
  FUN_080085e8();
  FUN_0801357c();
  FUN_080085e8();
  return 1;
}


// ===================================================================
// FUN_080166ec @ 0x080166ec  size=16  body=[[080166ec, 080166fb]]

undefined8 FUN_080166ec(void)

{
  FUN_0801357c();
  FUN_080085e8();
  return 1;
}


// ===================================================================
// FUN_080166fc @ 0x080166fc  size=4  body=[[080166fc, 080166ff]]

undefined4 FUN_080166fc(void)

{
  return 1;
}


// ===================================================================
// FUN_08016700 @ 0x08016700  size=2  body=[[08016700, 08016701]]

void FUN_08016700(void)

{
  return;
}


