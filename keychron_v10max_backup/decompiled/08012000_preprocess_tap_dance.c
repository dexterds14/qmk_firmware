// preprocess_tap_dance @ 0x08012000  size=54  body=[[08012000, 08012035]]

// INFERRED: called (keycode,record) right after get_record_keycode; nonzero result triggers keycode
// re-read (QMK 0.23 process_record_quantum)

char preprocess_tap_dance(uint param_1,int param_2)

{
  int iVar1;
  char cVar2;
  
  cVar2 = *(char *)(param_2 + 5);
  if (cVar2 != '\0') {
    if ((DAT_2000201c == 0) || (DAT_2000201c == param_1)) {
      cVar2 = '\0';
    }
    else {
      iVar1 = (uint)(byte)DAT_2000201c * 0x1c;
      (&DAT_20000e81)[iVar1] = (&DAT_20000e81)[iVar1] | 4;
      *(short *)(&DAT_20000e7c + iVar1) = (short)param_1;
      FUN_08011fb8((undefined4 *)(&DAT_20000e7c + iVar1));
      FUN_0800e374();
    }
  }
  return cVar2;
}

