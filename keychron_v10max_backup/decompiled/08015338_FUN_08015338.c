// FUN_08015338 @ 0x08015338  size=214  body=[[08015338, 0801540d]]

void FUN_08015338(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar7 = (param_3 & 7) >> 2;
  uVar6 = (param_3 & 0x1f) >> 3;
  uVar9 = (param_3 & 0x7f) >> 5;
  uVar1 = 0;
  uVar5 = param_3 & 3;
  while( true ) {
    if ((int)(param_2 << 0x1f) < 0) {
      iVar2 = (uVar1 & 7) << 2;
      uVar8 = ((param_3 & 0x7ff) >> 7) << iVar2;
      param_1[1] = param_1[1] & ~(1 << (uVar1 & 0xff)) | uVar7;
      uVar4 = 3 << ((uVar1 & 0x7f) << 1);
      param_1[2] = param_1[2] & ~uVar4 | uVar6;
      param_1[3] = param_1[3] & ~uVar4 | uVar9;
      uVar3 = ~(0xf << iVar2);
      if ((param_3 & 3) == 2) {
        if (uVar1 < 8) {
          param_1[8] = param_1[8] & uVar3 | uVar8;
        }
        else {
          param_1[9] = param_1[9] & uVar3 | uVar8;
        }
        *param_1 = *param_1 & ~uVar4 | uVar5;
      }
      else {
        *param_1 = ~uVar4 & *param_1 | uVar5;
        if (uVar1 < 8) {
          param_1[8] = param_1[8] & uVar3 | uVar8;
        }
        else {
          param_1[9] = param_1[9] & uVar3 | uVar8;
        }
      }
    }
    param_2 = param_2 >> 1;
    if (param_2 == 0) break;
    uVar7 = uVar7 << 1;
    uVar6 = uVar6 << 2;
    uVar9 = uVar9 << 2;
    uVar5 = uVar5 << 2;
    uVar1 = uVar1 + 1;
  }
  return;
}

