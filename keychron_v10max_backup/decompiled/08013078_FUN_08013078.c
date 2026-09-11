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

