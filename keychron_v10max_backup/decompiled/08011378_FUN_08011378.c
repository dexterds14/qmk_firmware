// FUN_08011378 @ 0x08011378  size=30  body=[[08011378, 08011395]]

void FUN_08011378(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  do {
    uVar2 = uVar1 + 1;
    FUN_08011338(uVar1,param_1,param_2,param_3);
    uVar1 = uVar2;
  } while (uVar2 != 0x58);
  return;
}

