// FUN_08015718 @ 0x08015718  size=24  body=[[08015718, 0801572f]]

void FUN_08015718(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x54) + 0x800) =
       *(uint *)(*(int *)(param_1 + 0x54) + 0x800) & 0xfffff80f |
       (uint)*(byte *)(param_1 + 0x4e) << 4;
  return;
}

