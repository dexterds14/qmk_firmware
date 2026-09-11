// FUN_0800813c @ 0x0800813c  size=18  body=[[0800813c, 0800814d]]

void FUN_0800813c(void)

{
  bool bVar1;
  code *unaff_r4;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  (*unaff_r4)();
  thunk_FUN_08013a60(0);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

