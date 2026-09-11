// FUN_08014740 @ 0x08014740  size=162  body=[[08014740, 0801475b] [0801476c, 080147f1]]

void FUN_08014740(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  
  cVar1 = *(char *)(param_1 + 0x34);
  if (cVar1 == '\0') {
LAB_080147d2:
    FUN_08015e38(param_1,0);
    FUN_08015e24(param_1,0);
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
      (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
    }
    uVar3 = 6;
  }
  else {
    if (0xf < (byte)(cVar1 - 6U)) {
      return;
    }
    switch(cVar1) {
    case '\x06':
    case '\x14':
    case '\x15':
      goto LAB_080147d2;
    default:
      goto LAB_080147c6;
    case '\t':
      uVar5 = *(uint *)(param_1 + 0x3c);
      if ((*(ushort *)(param_1 + 0x4a) <= uVar5) ||
         (uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0xc) + 0x10),
         uVar5 != uVar4 * (uVar5 / uVar4))) goto LAB_080147a8;
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014334(param_1,0,0,0);
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0);
      }
      uVar3 = 10;
      break;
    case '\n':
LAB_080147a8:
      *(undefined1 *)(param_1 + 0x34) = 0x14;
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014310(param_1,0,0,0);
      bVar2 = (bool)isCurrentModePrivileged();
      if (!bVar2) {
        return;
      }
      setBasePriority(0);
      return;
    case '\v':
      if (*(code **)(param_1 + 0x40) != (code *)0x0) {
        (**(code **)(param_1 + 0x40))();
      }
      uVar3 = 0;
    }
  }
  *(undefined1 *)(param_1 + 0x34) = uVar3;
LAB_080147c6:
  return;
}

