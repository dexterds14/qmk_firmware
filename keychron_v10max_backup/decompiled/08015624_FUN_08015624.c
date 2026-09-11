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

