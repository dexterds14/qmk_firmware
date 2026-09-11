// FUN_0800ea9e @ 0x0800ea9e  size=22  body=[[0800ea9e, 0800eab3]]

uint FUN_0800ea9e(uint param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = keymap_key_to_keycode(param_1,param_2);
  uVar2 = FUN_0800e8b0((uint)uVar1);
  return uVar2;
}

