// FUN_0800ac68 @ 0x0800ac68  size=118  body=[[0800ac68, 0800acdd]]

void FUN_0800ac68(undefined1 param_1,undefined4 ***param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 ***pppuVar3;
  undefined4 ***local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  FUN_08008798(&DAT_2000151a,0,0x3e);
  local_1c = (undefined4 ***)0x0;
  local_18 = 0x103;
  local_14 = 0;
  if (param_2 == (undefined4 ***)0x0) {
    param_2 = &local_1c;
  }
  DAT_20001518 = 0x21;
  DAT_2000151a = (undefined1)*(undefined2 *)((int)param_2 + 2);
  pppuVar3 = (undefined4 ***)param_2[2];
  DAT_2000151b = (undefined1)((ushort)*(undefined2 *)((int)param_2 + 2) >> 8);
  DAT_2000151c = *(undefined1 *)(param_2 + 1);
  DAT_2000151d = *(undefined1 *)((int)param_2 + 5);
  DAT_2000151e = *(undefined1 *)((int)param_2 + 6);
  DAT_20001519 = param_1;
  if (pppuVar3 == (undefined4 ***)0x0) {
    uVar1 = 7;
  }
  else {
    uVar1 = FUN_080086c0((uint)pppuVar3);
    memcpy((undefined4 *)&DAT_2000151f,pppuVar3,uVar1);
    iVar2 = FUN_080086c0((uint)param_2[2]);
    uVar1 = iVar2 + 7U & 0xff;
  }
  FUN_0800aa20();
  FUN_0800aa64(&DAT_20001518,uVar1,'\x01',0);
  return;
}

