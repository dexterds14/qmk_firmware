// process_record_kb @ 0x0800c6e8  size=26  body=[[0800c6e8, 0800c701]]

// VERIFIED shape of keychron_task.c:111 with process_record_keychron inlined: 0x0800D104
// (process_record_user) && 0x0800A788 (wireless) && 0x0800C928 (factory test) && 0x0800C69C

undefined4 process_record_kb(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = process_record_user(param_1,param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_0800c6a0(param_1,param_2);
    return uVar2;
  }
  return 0;
}

