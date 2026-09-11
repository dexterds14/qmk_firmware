// process_record_user @ 0x0800d104  size=180  body=[[0800d104, 0800d1b7]]

// CUSTOM KEYMAP CODE. INFERRED name: first callee of process_record_kb and begins with
// process_record_keychron_common (0x0800C720) exactly like the default keymap template. VERIFIED
// body: flag@0x200015E8 cleared unless keycode==0x5700 TD(0); flag@0x200015E9 cleared when
// 0x0800DC3C(1)==0; only when pressed: 0x39 KC_CAPS -> flag@0x200015DC from 0x08012148() bit1;
// (kc-0x52A2)<0x17 with mask 0x410041 = OSM(MOD_LSFT) 0x52A2 / OSM(MOD_LGUI) 0x52A8 / OSM(MOD_RSFT)
// 0x52B2 / OSM(MOD_RGUI) 0x52B8 -> custom one-shot handling via
// 0x0800D090/0x0800E310/0x0800E424/0x0800E3B0/0x0800E380/0x0800D684; 0x7E40 QK_USER_0 ->
// register/unregister_code 0x37 KC_DOT then 0x38 KC_SLASH ('./'); 0x7E41 QK_USER_1 -> DOT then
// falls into USER_0 path ('../'); returns false after handling

int process_record_user(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  
  iVar1 = process_record_keychron_common(param_1,param_2);
  if (iVar1 != 0) {
    if ((user_td0_flag != '\0') && (param_1 != 0x5700)) {
      user_td0_flag = '\0';
    }
    if ((DAT_200015e9 != '\0') && (uVar2 = FUN_0800dc3c(1), uVar2 == 0)) {
      DAT_200015e9 = '\0';
    }
    if (*(char *)(param_2 + 5) == '\0') {
      return iVar1;
    }
    if (param_1 == 0x39) {
      iVar3 = FUN_08012148();
      if (-1 < iVar3 << 0x1e) {
        user_capslock_flag = 1;
        return iVar1;
      }
      iVar3 = FUN_08012148();
      if (-1 < iVar3 << 0x1e) {
        return iVar1;
      }
      user_capslock_flag = 0;
      return iVar1;
    }
    if ((param_1 - 0x52a2 & 0xffff) < 0x17) {
      if (-1 < (int)((0x410041U >> (param_1 - 0x52a2 & 0xff)) << 0x1f)) {
        return iVar1;
      }
      iVar1 = FUN_0800d0b4(param_1);
      return iVar1;
    }
    if (param_1 != 0x7e40) {
      if (param_1 != 0x7e41) {
        return iVar1;
      }
      register_code(0x37);
      unregister_code(0x37,extraout_r1_01);
    }
    register_code(0x37);
    unregister_code(0x37,extraout_r1);
    register_code(0x38);
    unregister_code(0x38,extraout_r1_00);
  }
  return 0;
}

