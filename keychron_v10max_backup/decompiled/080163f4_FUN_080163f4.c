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

