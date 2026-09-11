// process_record_wireless @ 0x0800a788  size=62  body=[[0800a788, 0800a7c5]]

// INFERRED: 2nd callee of process_record_kb (process_record_keychron order in keychron_task.c);
// body tests 0x7E0B 0x7E0E 0x7E0F (BT_HST*/P2P4G/BAT_LVL range)

undefined4 process_record_wireless(uint param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 uVar3;
  uint extraout_r1;
  undefined4 extraout_r2;
  
  bVar1 = FUN_0800bbb4();
  if ((bVar1 & 6) != 0) {
    FUN_0800bc70();
    bVar2 = FUN_0800c144();
    if (((bVar2) && (DAT_20001501 == '\x03')) && (*(char *)(param_2 + 5) != '\0')) {
      FUN_0800b3ec(1);
      FUN_0800b420(1,extraout_r1,extraout_r2);
    }
  }
  uVar3 = FUN_0800c4b4(param_1,param_2);
  return uVar3;
}

