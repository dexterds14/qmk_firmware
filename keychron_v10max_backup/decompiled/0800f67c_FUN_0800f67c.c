// FUN_0800f67c @ 0x0800f67c  size=50  body=[[0800f67c, 0800f6ad]]

// WARNING: Removing unreachable block (ram,0x0800f6a2)

undefined1 FUN_0800f67c(int param_1,uint *param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)FUN_08014064(DAT_20001f10,DAT_20000ea8 + param_1);
  DAT_20001f0d = 0;
  DAT_20001f0c = 0;
  *param_2 = ~*puVar1;
  return 1;
}

