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

