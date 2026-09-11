// FUN_080141a4 @ 0x080141a4  size=62  body=[[080141a4, 080141ab] [08016542, 08016577]]

undefined4 FUN_080141a4(undefined1 *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  *param_1 = 3;
  puVar3 = (uint *)**(undefined4 **)(param_1 + 0x20);
  puVar3[3] = (uint)(param_1 + 0x30);
  uVar1 = *(uint *)(param_1 + 0x28);
  puVar3[1] = param_2;
  *puVar3 = uVar1;
  puVar2 = (uint *)**(undefined4 **)(param_1 + 0x24);
  puVar2[3] = param_3;
  uVar1 = *(uint *)(param_1 + 0x2c);
  puVar2[1] = param_2;
  *puVar2 = uVar1 | 0x400;
  *puVar3 = *puVar3 | 1;
  *puVar2 = *puVar2 | 1;
  return 0;
}

