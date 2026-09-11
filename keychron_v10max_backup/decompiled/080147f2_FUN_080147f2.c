// FUN_080147f2 @ 0x080147f2  size=120  body=[[080147f2, 08014869]]

void FUN_080147f2(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  uint uVar3;
  
  uVar3 = (uint)*(byte *)(param_1 + 0x34);
  if (uVar3 == 0x14) {
    if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + 0x18) + 4) != 0) {
      return;
    }
    if (*(code **)(param_1 + 0x40) != (code *)0x0) {
      (**(code **)(param_1 + 0x40))();
    }
    uVar2 = 0;
  }
  else {
    if (0x14 < uVar3) {
      if (uVar3 != 0x15) {
        return;
      }
      *(undefined1 *)(param_1 + 0x34) = 0xb;
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_08014334(param_1,0,0,0);
      bVar1 = (bool)isCurrentModePrivileged();
      if (!bVar1) {
        return;
      }
      setBasePriority(0);
      return;
    }
    if (uVar3 != 6) {
      if (uVar3 < 7) {
        if (uVar3 != 0) {
          return;
        }
      }
      else if (2 < uVar3 - 9) {
        return;
      }
    }
    FUN_08015e38(param_1,0);
    FUN_08015e24(param_1,0);
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
      (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
    }
    uVar2 = 6;
  }
  *(undefined1 *)(param_1 + 0x34) = uVar2;
  return;
}

