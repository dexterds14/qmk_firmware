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

