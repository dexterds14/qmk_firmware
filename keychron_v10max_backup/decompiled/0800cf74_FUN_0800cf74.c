// FUN_0800cf74 @ 0x0800cf74  size=130  body=[[0800cf74, 0800cfa5] [0800cfac, 0800cffb]]

undefined4 FUN_0800cf74(uint param_1,uint param_2)

{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  do {
    if (param_2 <= (param_1 & 0xff)) {
      return 0;
    }
    iVar1 = get_highest_layer((uint)(layer_state | default_layer_state));
    switch(iVar1) {
    case 1:
      uVar3 = 0;
      uVar4 = 0xff;
      break;
    case 2:
      uVar3 = 0xff;
      uVar4 = 0;
      break;
    case 3:
      uVar4 = 0x80;
      goto LAB_0800cfd2;
    case 4:
      uVar4 = 0x80;
      uVar3 = uVar4;
      break;
    case 5:
      uVar4 = 0;
LAB_0800cfd2:
      uVar3 = 0;
      uVar2 = 0xff;
      goto LAB_0800cfb2;
    default:
      goto switchD_0800cfa2_default;
    }
    uVar2 = 0;
LAB_0800cfb2:
    FUN_0800fe78(param_1,uVar2,uVar4,uVar3);
switchD_0800cfa2_default:
    if (DAT_200015dd == '\0') {
      if (DAT_200015de != '\0' || user_capslock_flag != '\0') {
        uVar4 = 0xff;
        goto LAB_0800cfc4;
      }
    }
    else {
      uVar4 = 0;
LAB_0800cfc4:
      FUN_0800fe78(param_1,0xff,0xff,uVar4);
    }
    param_1 = param_1 + 1;
  } while( true );
}

