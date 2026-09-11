// FUN_0801650c @ 0x0801650c  size=54  body=[[0801650c, 08016541]]

undefined4 FUN_0801650c(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar3 = (uint *)**(undefined4 **)(param_1 + 0x20);
  puVar3[3] = param_4;
  uVar1 = *(uint *)(param_1 + 0x28);
  puVar3[1] = param_2;
  *puVar3 = uVar1 | 0x400;
  puVar2 = (uint *)**(undefined4 **)(param_1 + 0x24);
  puVar2[3] = param_3;
  uVar1 = *(uint *)(param_1 + 0x2c);
  puVar2[1] = param_2;
  *puVar2 = uVar1 | 0x400;
  *puVar3 = *puVar3 | 1;
  *puVar2 = *puVar2 | 1;
  return 0;
}

