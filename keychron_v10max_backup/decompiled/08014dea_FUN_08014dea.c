// FUN_08014dea @ 0x08014dea  size=12  body=[[08014dea, 08014df5]]

undefined4 FUN_08014dea(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    uVar1 = 1;
  }
  else {
    uVar1 = 7;
  }
  return uVar1;
}

