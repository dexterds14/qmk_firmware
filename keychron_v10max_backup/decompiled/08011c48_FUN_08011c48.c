// FUN_08011c48 @ 0x08011c48  size=206  body=[[08011c48, 08011ce7] [08011d24, 08011d51]]

void FUN_08011c48(int param_1)

{
  if (param_1 == 0xcd) {
    if (-1 < DAT_20002016) goto switchD_08011ce4_caseD_8;
  }
  else {
    if (param_1 != 0xce) {
      if (param_1 == 0xcf) {
        if (-1 < DAT_20002015) goto switchD_08011ce4_caseD_8;
      }
      else {
        if (param_1 != 0xd0) {
          if (param_1 == 0xd9) {
            if (DAT_20002017 < '\x01') goto switchD_08011ce4_caseD_8;
          }
          else {
            if (param_1 != 0xda) {
              if (param_1 == 0xdb) {
                if (-1 < DAT_20002018) goto switchD_08011ce4_caseD_8;
              }
              else {
                if (param_1 != 0xdc) {
                  switch(param_1 - 0xd1U) {
                  case 0:
                  case 1:
                  case 2:
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                    DAT_20002014 = DAT_20002014 & ~(byte)(1 << (param_1 - 0xd1U & 0xff));
                    break;
                  case 0xc:
                    DAT_20002012 = DAT_20002012 & 0xfe;
                    break;
                  case 0xd:
                    DAT_20002012 = DAT_20002012 & 0xfd;
                    break;
                  case 0xe:
                    DAT_20002012 = DAT_20002012 & 0xfb;
                  }
                  goto switchD_08011ce4_caseD_8;
                }
                if (DAT_20002018 < '\x01') goto switchD_08011ce4_caseD_8;
              }
              DAT_20002018 = '\0';
              goto switchD_08011ce4_caseD_8;
            }
            if (-1 < DAT_20002017) goto switchD_08011ce4_caseD_8;
          }
          DAT_20002017 = '\0';
          goto switchD_08011ce4_caseD_8;
        }
        if (DAT_20002015 < '\x01') goto switchD_08011ce4_caseD_8;
      }
      DAT_20002015 = '\0';
      goto switchD_08011ce4_caseD_8;
    }
    if (DAT_20002016 < '\x01') goto switchD_08011ce4_caseD_8;
  }
  DAT_20002016 = '\0';
switchD_08011ce4_caseD_8:
  if (DAT_20002015 == '\0' && DAT_20002016 == '\0') {
    DAT_2000200e = 0;
    DAT_20002011 = 0;
  }
  if (DAT_20002018 == '\0' && DAT_20002017 == '\0') {
    DAT_20002010 = 0;
  }
  return;
}

