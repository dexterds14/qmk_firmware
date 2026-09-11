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

