// FUN_0800c5ec @ 0x0800c5ec  size=164  body=[[0800c5ec, 0800c68f]]

void FUN_0800c5ec(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  
  if (DAT_200015b8 == 0) {
    uVar5 = DAT_40020010;
    uVar1 = DAT_40020010;
    if ((uVar5 >> 8 & 2 | (uVar1 & 0x7ff) >> 10) != (uint)DAT_200015b5) {
      uVar2 = DAT_40020010;
      iVar3 = DAT_40020010;
      DAT_200015b5 = (byte)((uint)uVar2 >> 8) & 2 | (byte)((uint)(iVar3 << 0x15) >> 0x1f);
      DAT_200015b8 = FUN_08012508();
    }
  }
  if (((DAT_200015b8 != 0) && (uVar5 = FUN_0801258c(DAT_200015b8), 100 < uVar5)) ||
     (cVar4 = FUN_0800bbb4(), cVar4 == '\0')) {
    uVar5 = DAT_40020010;
    uVar1 = DAT_40020010;
    uVar5 = uVar5 >> 8 & 2 | (uVar1 & 0x7ff) >> 10;
    if (uVar5 == DAT_200015b5) {
      DAT_200015b8 = 0;
      if (uVar5 == 2) {
        uVar5 = 4;
      }
      else if (uVar5 == 3) {
        uVar5 = 1;
      }
      else {
        if (uVar5 != 1) {
          DAT_200015b8 = 0;
          return;
        }
        uVar5 = 2;
      }
      FUN_0800ba9c(uVar5);
      return;
    }
    uVar2 = DAT_40020010;
    iVar3 = DAT_40020010;
    DAT_200015b5 = (byte)((uint)uVar2 >> 8) & 2 | (byte)((uint)(iVar3 << 0x15) >> 0x1f);
    DAT_200015b8 = FUN_08012508();
  }
  return;
}

