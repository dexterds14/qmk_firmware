// FUN_08012800 @ 0x08012800  size=256  body=[[08012800, 080128ff]]

undefined4 FUN_08012800(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined *puVar8;
  
  uVar5 = (uint)*(byte *)(param_1 + 0x44);
  if ((uVar5 & 0x7f) == 0x21) {
    cVar1 = *(char *)(param_1 + 0x45);
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
LAB_08012852:
      if (cVar1 == '\n') {
        DAT_20002068 = *(undefined1 *)(param_1 + 0x47);
        uVar2 = FUN_08013448(param_1);
        return uVar2;
      }
      if (cVar1 == '\v') {
        if (*(short *)(param_1 + 0x48) == 0) {
          DAT_20000ec6 = *(undefined1 *)(param_1 + 0x46);
        }
        uVar2 = 0;
        *(undefined4 *)(param_1 + 0x38) = 0;
        goto LAB_08012894;
      }
      if ((cVar1 != '\t') || ((*(ushort *)(param_1 + 0x48) & 0xfffd) != 0)) goto LAB_080128aa;
      *(undefined1 **)(param_1 + 0x38) = &DAT_20002064;
      uVar2 = 2;
      uVar6 = 0x8012959;
    }
    else {
      if (cVar1 == '\x02') {
        uVar2 = FUN_080133f8(param_1);
        return uVar2;
      }
      if (cVar1 != '\x03') {
        if (cVar1 == '\x01') {
          uVar2 = FUN_0801319c(param_1,param_2,uVar5,1);
          return uVar2;
        }
        goto LAB_08012852;
      }
      if (*(short *)(param_1 + 0x48) != 0) goto LAB_080128aa;
      *(undefined1 **)(param_1 + 0x38) = &DAT_20000ec6;
      uVar2 = 1;
      uVar6 = 0;
    }
LAB_08012842:
    *(undefined4 *)(param_1 + 0x3c) = uVar2;
    *(undefined4 *)(param_1 + 0x40) = uVar6;
LAB_08012846:
    uVar2 = 1;
  }
  else {
LAB_080128aa:
    if (((uVar5 & 0x9f) == 0x81) && (*(char *)(param_1 + 0x45) == '\x06')) {
      puVar3 = (undefined4 *)
               (**(code **)(*(int *)(param_1 + 4) + 4))
                         (param_1,*(undefined1 *)(param_1 + 0x46),*(undefined1 *)(param_1 + 0x47),
                          *(undefined2 *)(param_1 + 0x48));
      if (puVar3 != (undefined4 *)0x0) {
        uVar2 = *puVar3;
        *(undefined4 *)(param_1 + 0x38) = puVar3[1];
LAB_08012894:
        uVar6 = 0;
        goto LAB_08012842;
      }
    }
    else {
      puVar8 = &DAT_20000f64;
      iVar7 = 3;
      do {
        if ((*(code **)(puVar8 + 0x9c) != (code *)0x0) &&
           (iVar4 = (**(code **)(puVar8 + 0x9c))(param_1), iVar4 != 0)) goto LAB_08012846;
        iVar7 = iVar7 + -1;
        puVar8 = puVar8 + 0xa8;
      } while (iVar7 != 0);
    }
    uVar2 = 0;
  }
  return uVar2;
}

