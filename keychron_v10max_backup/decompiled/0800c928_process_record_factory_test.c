// process_record_factory_test @ 0x0800c928  size=226  body=[[0800c928, 0800ca09]]

// VERIFIED vs factory_test.c:171: keycodes 0x0D KC_J 0x1D KC_Z 0x4A KC_HOME (BL_TRIG_KEY) 0x4D
// KC_END 0x4F KC_RIGHT (BL_CYCLE_KEY) 0x5221/0x5223 MO(1)/MO(3) FN keys; state byte @0x200015D1;
// timer start 0x0800C918 when state==7 or 0x19

byte process_record_factory_test(uint param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  
  if (param_1 != 0x4d) {
    if (0x4d < param_1) {
      if ((param_1 & 0xfffffffd) == 0x5221) {
        pbVar1 = &factory_reset_state;
        if (*(char *)(param_2 + 5) == '\0') {
          factory_reset_state = factory_reset_state & 0xfe;
          DAT_200015d4 = 0;
          return 1;
        }
        bVar2 = factory_reset_state | 1;
LAB_0800c976:
        *pbVar1 = bVar2;
        return 1;
      }
      if (param_1 != 0x4f) {
        return 1;
      }
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xf7;
        DAT_200015d4 = 0;
        return 1;
      }
      pbVar1 = (byte *)&DAT_200015d0;
      if (DAT_200015d0 != '\0') {
        bVar2 = DAT_200015d0 + 1;
        if (4 < bVar2) {
          bVar2 = 1;
        }
        goto LAB_0800c976;
      }
      factory_reset_state = factory_reset_state | 8;
      goto LAB_0800c9ce;
    }
    if (param_1 == 0x1d) {
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xfb;
        DAT_200015d4 = 0;
        return 1;
      }
      factory_reset_state = factory_reset_state | 4;
LAB_0800c992:
      if (factory_reset_state == 7) {
        FUN_0800c918();
      }
      return ~factory_reset_state & 1;
    }
    if (param_1 != 0x4a) {
      if (param_1 != 0xd) {
        return 1;
      }
      if (*(char *)(param_2 + 5) == '\0') {
        factory_reset_state = factory_reset_state & 0xfd;
        DAT_200015d4 = 0;
        return 1;
      }
      factory_reset_state = factory_reset_state | 2;
      goto LAB_0800c992;
    }
  }
  if (*(char *)(param_2 + 5) == '\0') {
    factory_reset_state = factory_reset_state & 0xef;
    DAT_200015d4 = 0;
    return 1;
  }
  if (DAT_200015d0 != '\0') {
    DAT_200015d0 = 0;
    return 1;
  }
  factory_reset_state = factory_reset_state | 0x10;
LAB_0800c9ce:
  if (factory_reset_state == 0x19) {
    FUN_0800c918();
  }
  return 1;
}

