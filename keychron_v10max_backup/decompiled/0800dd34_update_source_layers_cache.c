// update_source_layers_cache @ 0x0800dd34  size=110  body=[[0800dcda, 0800dd0b] [0800dd34, 0800dd6f]]

// INFERRED: second callee (key,layer) in the pressed&&update_layer_cache branch of
// get_event_keycode (QMK 0.23 action.c order)

void update_source_layers_cache(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  undefined *puVar5;
  
  uVar3 = param_1 & 0xff;
  uVar2 = (param_1 & 0xffff) >> 8;
  if (uVar2 < 6) {
    if (0x11 < uVar3) {
      return;
    }
    puVar5 = &DAT_200015f5;
    uVar3 = uVar3 + uVar2 * 0x12;
  }
  else {
    if (1 < (uVar2 + 4 & 0xff)) {
      return;
    }
    puVar5 = &DAT_200015f1;
  }
  pbVar4 = puVar5 + (uVar3 >> 3) * 4 + -1;
  uVar2 = 0;
  do {
    pbVar4 = pbVar4 + 1;
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    *pbVar4 = *pbVar4 ^ ((byte)((int)((param_2 >> uVar1) << 0x1f) >> 0x1f) ^ *pbVar4) &
                        (byte)(1 << (uVar3 & 7));
  } while (uVar2 != 4);
  return;
}

