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

