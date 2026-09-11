// FUN_0800ccf0 @ 0x0800ccf0  size=36  body=[[0800ccf0, 0800cd13]]

undefined4 FUN_0800ccf0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 local_c;
  undefined2 local_a;
  undefined4 uStack_8;
  
  if (DAT_200015c9 != '\0') {
    local_a._1_1_ = (undefined1)((uint)param_2 >> 0x18);
    _local_c = CONCAT22(CONCAT11(local_a._1_1_,(char)param_2),0x102);
    uStack_8 = param_3;
    FUN_0800cb44((undefined4 *)&local_c,3);
  }
  return 1;
}

