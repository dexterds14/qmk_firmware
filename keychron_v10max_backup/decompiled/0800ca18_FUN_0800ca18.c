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

