// FUN_0800a8d4 @ 0x0800a8d4  size=162  body=[[0800a8d4, 0800a975]]

void FUN_0800a8d4(void)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  undefined2 *puVar4;
  code *pcVar5;
  
  cVar1 = FUN_0800a77c();
  if ((cVar1 != '\x03') ||
     (((bVar2 = FUN_0800a874(), bVar2 && (DAT_20001504 == '\0')) || (bVar2 = FUN_0800a89c(), !bVar2)
      ))) {
    return;
  }
  if (DAT_20001504 == '\0') {
    bVar2 = FUN_0800a840((undefined4 *)&DAT_20002594);
    if (!bVar2) {
      return;
    }
    if (DAT_20002594 == '\0') {
      return;
    }
    uVar3 = FUN_08012508();
    if (uVar3 < 3) {
      return;
    }
    DAT_20001504 = '\x1e';
  }
  else {
    uVar3 = FUN_0801258c(DAT_20001508);
    if (uVar3 < 3) {
      return;
    }
    DAT_20001504 = DAT_20001504 + -1;
  }
  DAT_20001508 = FUN_08012508();
  if (DAT_20002594 == '\x02') {
    if (DAT_20000c88 == (code *)0x0) goto LAB_0800a942;
    puVar4 = (undefined2 *)0x20002597;
    pcVar5 = DAT_20000c88;
LAB_0800a930:
    (*pcVar5)(puVar4);
  }
  else if (DAT_20002594 == '\x01') {
    if (DAT_20000c84 == (code *)0x0) goto LAB_0800a942;
    puVar4 = &DAT_20002596;
    pcVar5 = DAT_20000c84;
    goto LAB_0800a930;
  }
  if ((DAT_20002594 == '\x03') && (DAT_20000c8c != (code *)0x0)) {
    (*DAT_20000c8c)(DAT_20002596);
  }
LAB_0800a942:
  DAT_2000150c = FUN_08012508();
  FUN_0800bc70();
  return;
}

