// FUN_0800ac1c @ 0x0800ac1c  size=70  body=[[0800ac1c, 0800ac61]]

void FUN_0800ac1c(int param_1)

{
  char cVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)FUN_08008798(&DAT_20001519,0,0x3f);
  puVar2[-1] = 0x16;
  *puVar2 = *(undefined1 *)(param_1 + 1);
  cVar1 = *(char *)(param_1 + 2);
  puVar2[1] = cVar1;
  puVar2[2] = cVar1 >> 7;
  cVar1 = *(char *)(param_1 + 3);
  puVar2[3] = cVar1;
  puVar2[4] = cVar1 >> 7;
  puVar2[5] = *(undefined1 *)(param_1 + 4);
  puVar2[6] = *(undefined1 *)(param_1 + 5);
  FUN_0800aa64(puVar2 + -1,8,'\0',0);
  return;
}

