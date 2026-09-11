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

