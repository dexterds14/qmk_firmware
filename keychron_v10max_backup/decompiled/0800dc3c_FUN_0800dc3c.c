// FUN_0800dc3c @ 0x0800dc3c  size=24  body=[[0800dc3c, 0800dc53]]

uint FUN_0800dc3c(uint param_1)

{
  if (layer_state == 0) {
    return (uint)(param_1 == 0);
  }
  return (int)(uint)layer_state >> (param_1 & 0xff) & 1;
}

