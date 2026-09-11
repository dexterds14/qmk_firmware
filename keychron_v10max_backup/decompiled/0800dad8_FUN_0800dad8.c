// FUN_0800dad8 @ 0x0800dad8  size=56  body=[[0800dad8, 0800db0f]]

void FUN_0800dad8(uint *param_1)

{
  byte bVar1;
  int iVar2;
  
  if ((char)param_1[1] != '\0') {
    iVar2 = process_record_quantum(param_1);
    if (iVar2 == 0) {
      bVar1 = FUN_0800e2fc();
      if (((bVar1 != 0) && (*(char *)((int)param_1 + 5) != '\0')) &&
         ((int)((uint)DAT_200047d4._1_1_ << 0x1d) < 0)) {
        FUN_0800e548(2);
        return;
      }
    }
    else {
      FUN_0800dab4(param_1);
      FUN_0800d35e(param_1);
    }
  }
  return;
}

