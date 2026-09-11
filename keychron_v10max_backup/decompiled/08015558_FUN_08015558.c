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

