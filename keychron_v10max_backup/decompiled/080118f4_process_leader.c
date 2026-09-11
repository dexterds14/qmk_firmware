// process_leader @ 0x080118f4  size=74  body=[[080118f4, 0801193d]]

// VERIFIED: compares keycode == 0x7C58 (QK_LEADER) when pressed

undefined1 process_leader(uint param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  
  if (*(char *)(param_2 + 5) != '\0') {
    cVar1 = FUN_08011990();
    if ((cVar1 == '\0') || (bVar2 = FUN_080119c0(), bVar2)) {
      if (param_1 == 0x7c58) {
        FUN_08011940();
      }
    }
    else {
      if (param_1 - 0x2000 < 0x3000) {
        param_1 = param_1 & 0xff;
      }
      bVar2 = FUN_0801199c((short)param_1);
      if (bVar2) {
        FUN_080119f8();
        return 0;
      }
      FUN_0801197c();
    }
  }
  return 1;
}

