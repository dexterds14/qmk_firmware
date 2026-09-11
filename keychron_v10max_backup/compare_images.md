# Image comparison: dump vs reference builds

Generated 2026-09-11T01:26:27+00:00 by tools/compare_images.py. Metrics use the code+rodata span [0x8000, image end) of the row image; all-0x00/0xFF windows excluded. Block hits are exact byte matches of aligned K-byte blocks found at *any* offset of the column image.

## Images

| label | size | image end | code+rodata B | sha256 (16) | build date | SP / Reset | product str @ | newlib rand.c __FILE__ | toolchain guess |
|---|---|---|---|---|---|---|---|---|---|
| dump | 262144 | 0x17F04 | 65284 | `21c97cd5f838063d` | 2024-07-09-13:57:36 | 0x20000400 / 0x0800811D | 0x1679B | `../../../../../../newlib/libc/stdlib/rand.c` @0x17674 | relative srcdir, 6 levels (in-tree build/ dir; newlib >=4.2 non-recursive automake layout) |
| stock_via_2024-11 | 96448 | 0x178C0 | 63680 | `4394f106516584c0` | 2024-11-09-10:54:47 | 0x20000400 / 0x0800811D | 0x160A7 | `/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/src/newlib/newlib/libc/stdlib/rand.c` @0x16F7F | Arm GNU Toolchain 10.3-2021.10 (GCC 10) Jenkins build |
| off_v1.0.0 | 94740 | 0x17214 | 61972 | `2791d382aedf5149` | 2024-01-10-17:15:03 | 0x20000400 / 0x0800811D | 0x15DC3 | `/mnt/workspace/workspace/GCC-10-pipeline/jenkins-GCC-10-pipeline-338_20211018_1634516203/src/newlib/newlib/libc/stdlib/rand.c` @0x16C6F | Arm GNU Toolchain 10.3-2021.10 (GCC 10) Jenkins build |
| off_v1.1.0 | 134764 | 0x20E6C | 101996 | `57140b39c65f1e7f` | 2025-02-19-17:12:43 | 0x20000400 / 0x0800811D | 0x1F700 | `../../../../../../../../newlib/libc/stdlib/rand.c` @0x20464 | relative srcdir, 8 levels (in-tree build/ dir; newlib <=4.1 recursive automake layout) |
| off_v1.1.1 | 114936 | 0x1C0F8 | 82168 | `65260dece19e939f` | 2025-07-02-16:39:32 | 0x20000400 / 0x0800811D | 0x1A874 | `/data/jenkins/workspace/GNU-toolchain/arm-11/src/newlib-cygwin/newlib/libc/stdlib/rand.c` @0x1B5DC | Arm GNU Toolchain 11.x Jenkins build |
| today_default_gcc15 | 93556 | 0x16D74 | 60788 | `04fc5ce684aeb3e9` | 2026-09-10-20:51:10 | 0x20000400 / 0x0800811D | 0x1576B | `/t/build/host_macosARM64-target_baremetalARM/.build/HOST-aarch64-apple-darwin24/arm-none-eabi/src/newlib-nano/newlib/libc/stdlib/rand.c` @0x1581D | crosstool-NG build (qmk/qmk_toolchains style) |
| ref1011_default_gcc15 | 92480 | 0x16940 | 59712 | `c74911aed08f3aa1` | 2026-09-10-20:53:45 | 0x20000400 / 0x0800811D | 0x1534B | `/t/build/host_macosARM64-target_baremetalARM/.build/HOST-aarch64-apple-darwin24/arm-none-eabi/src/newlib-nano/newlib/libc/stdlib/rand.c` @0x153F3 | crosstool-NG build (qmk/qmk_toolchains style) |
| ref1011_via_gcc15 | 95164 | 0x173BC | 62396 | `c864aacf6e1d3666` | 2026-09-10-20:54:06 | 0x20000400 / 0x0800811D | 0x15C0F | `/t/build/host_macosARM64-target_baremetalARM/.build/HOST-aarch64-apple-darwin24/arm-none-eabi/src/newlib-nano/newlib/libc/stdlib/rand.c` @0x15CB7 | crosstool-NG build (qmk/qmk_toolchains style) |
| ref1011_default_lto_gcc15 | 85688 | 0x14EB8 | 52920 | `a84ddf6aa2303a5d` | 2026-09-10-20:53:54 | 0x20000400 / 0x0800811D | 0x1489F | `/t/build/host_macosARM64-target_baremetalARM/.build/HOST-aarch64-apple-darwin24/arm-none-eabi/src/newlib-nano/newlib/libc/stdlib/rand.c` @0x1476B | crosstool-NG build (qmk/qmk_toolchains style) |

Identical to dump: stock_via_2024-11=no, off_v1.0.0=no, off_v1.1.0=no, off_v1.1.1=no, today_default_gcc15=no, ref1011_default_gcc15=no, ref1011_via_gcc15=no, ref1011_default_lto_gcc15=no

Vector table words equal to the dump (of 120): stock_via_2024-11=91, off_v1.0.0=91, off_v1.1.0=91, off_v1.1.1=91, today_default_gcc15=91, ref1011_default_gcc15=91, ref1011_via_gcc15=91, ref1011_default_lto_gcc15=91

## Toolchain marker strings per image

| label | marker hits (count) | dotted-version-like strings |
|---|---|---|
| dump | newlib:1 | - |
| stock_via_2024-11 | jenkins:1, newlib:2 | - |
| off_v1.0.0 | jenkins:1, newlib:2 | - |
| off_v1.1.0 | newlib:1 | - |
| off_v1.1.1 | GNU:1, jenkins:1, newlib:2 | - |
| today_default_gcc15 | newlib:2, nano:1 | - |
| ref1011_default_gcc15 | newlib:2, nano:1 | - |
| ref1011_via_gcc15 | newlib:2, nano:1 | - |
| ref1011_default_lto_gcc15 | newlib:2, nano:1 | - |

## newlib rand.c __FILE__ forms in reference libc archives

| libc archive | rand.c __FILE__ strings found | matches dump | matches images |
|---|---|---|---|
| ubuntu_noble_newlib_4.4.0-2 (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/libnewlib-arm-none-eabi_4.4.0.20231231-2_all/usr/lib/arm-none-eabi/newlib/thumb/v7e-m+fp/hard/libc_nano.a`) | `../../../../../../newlib/libc/stdlib/rand.c` | YES | - |
| ubuntu_jammy_newlib_3.3.0-1.3 (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/libnewlib-arm-none-eabi_3.3.0-1.3_all/usr/lib/arm-none-eabi/newlib/thumb/v7e-m+fp/hard/libc_nano.a`) | `../../../../../../../../newlib/libc/stdlib/rand.c` | no | off_v1.1.0 |
| qmk_toolchain_gcc15.2_newlib_nano (`/Users/dexter/Library/Application Support/qmk/newlib-nano/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc_nano.a`) | `/t/build/host_macosARM64-target_baremetalARM/.build/HOST-aarch64-apple-darwin24/arm-none-eabi/src/newlib-nano/newlib/libc/stdlib/rand.c` | no | today_default_gcc15, ref1011_default_gcc15, ref1011_via_gcc15, ref1011_default_lto_gcc15 |

## 64-byte block hit fraction (row blocks found anywhere in column image)

| row \ col | dump | stock_via_2024-11 | off_v1.0.0 | off_v1.1.0 | off_v1.1.1 | today_default_gcc15 | ref1011_default_gcc15 | ref1011_via_gcc15 | ref1011_default_lto_gcc15 |
|---|---|---|---|---|---|---|---|---|---|
| dump (1019 blk) | - | 9.8% | 7.3% | 3.3% | 2.9% | 10.1% | 10.4% | 10.4% | 4.9% |
| stock_via_2024-11 (993 blk) | 9.4% | - | 22.5% | 4.7% | 5.4% | 7.8% | 7.8% | 8.2% | 5.0% |
| off_v1.0.0 (964 blk) | 7.4% | 23.1% | - | 4.2% | 4.9% | 6.4% | 6.5% | 6.9% | 5.0% |
| off_v1.1.0 (1591 blk) | 1.9% | 2.8% | 2.3% | - | 7.1% | 2.1% | 2.1% | 2.3% | 1.9% |
| off_v1.1.1 (1281 blk) | 1.9% | 4.2% | 3.5% | 8.9% | - | 3.0% | 2.9% | 3.1% | 2.9% |
| today_default_gcc15 (947 blk) | 9.1% | 7.1% | 6.0% | 3.1% | 3.4% | - | 36.6% | 35.3% | 10.9% |
| ref1011_default_gcc15 (932 blk) | 11.4% | 8.6% | 7.3% | 3.4% | 3.8% | 37.8% | - | 40.1% | 11.4% |
| ref1011_via_gcc15 (970 blk) | 10.7% | 8.1% | 6.9% | 3.3% | 3.6% | 34.7% | 38.9% | - | 10.9% |
| ref1011_default_lto_gcc15 (825 blk) | 5.6% | 5.9% | 5.8% | 3.8% | 4.0% | 13.2% | 13.2% | 13.1% | - |

## 16-byte block hit fraction (row blocks found anywhere in column image)

| row \ col | dump | stock_via_2024-11 | off_v1.0.0 | off_v1.1.0 | off_v1.1.1 | today_default_gcc15 | ref1011_default_gcc15 | ref1011_via_gcc15 | ref1011_default_lto_gcc15 |
|---|---|---|---|---|---|---|---|---|---|
| dump (4033 blk) | - | 26.4% | 21.2% | 7.8% | 7.5% | 24.4% | 26.5% | 26.2% | 11.4% |
| stock_via_2024-11 (3919 blk) | 27.2% | - | 46.8% | 8.4% | 11.3% | 21.9% | 22.6% | 23.5% | 12.3% |
| off_v1.0.0 (3844 blk) | 22.2% | 47.5% | - | 7.6% | 10.7% | 18.4% | 18.8% | 19.8% | 11.2% |
| off_v1.1.0 (6313 blk) | 4.9% | 5.1% | 4.7% | - | 18.2% | 4.5% | 4.4% | 4.7% | 3.9% |
| off_v1.1.1 (5080 blk) | 5.9% | 8.8% | 8.2% | 22.3% | - | 6.9% | 6.8% | 7.1% | 6.0% |
| today_default_gcc15 (3755 blk) | 25.6% | 22.4% | 18.9% | 7.4% | 9.1% | - | 60.5% | 58.4% | 23.9% |
| ref1011_default_gcc15 (3687 blk) | 28.7% | 23.7% | 19.8% | 7.7% | 9.3% | 61.8% | - | 68.1% | 25.1% |
| ref1011_via_gcc15 (3848 blk) | 26.6% | 23.6% | 19.8% | 7.8% | 9.7% | 56.3% | 64.7% | - | 24.0% |
| ref1011_default_lto_gcc15 (3259 blk) | 13.8% | 14.2% | 13.1% | 7.5% | 9.1% | 27.2% | 27.7% | 27.7% | - |

## Dump code vs rodata split (k64; rodata assumed from 0x16704)

| image | code blocks hit | rodata blocks hit |
|---|---|---|
| stock_via_2024-11 | 66/924 (7.1%) | 33/95 (34.7%) |
| off_v1.0.0 | 45/924 (4.9%) | 28/95 (29.5%) |
| off_v1.1.0 | 9/924 (1.0%) | 25/95 (26.3%) |
| off_v1.1.1 | 4/924 (0.4%) | 25/95 (26.3%) |
| today_default_gcc15 | 59/924 (6.4%) | 44/95 (46.3%) |
| ref1011_default_gcc15 | 61/924 (6.6%) | 44/95 (46.3%) |
| ref1011_via_gcc15 | 61/924 (6.6%) | 44/95 (46.3%) |
| ref1011_default_lto_gcc15 | 15/924 (1.6%) | 33/95 (34.7%) |

## Longest common byte runs (dump vs each image; seeded by 32-byte windows, runs >= 48 B)

### stock_via_2024-11: 138 runs >= 48 B covering 14078 B of the dump; dominant deltas (img_off - dump_off): -6100 (1437 B), -6124 (1025 B), -6084 (888 B), -8320 (472 B), -6080 (445 B), -8468 (444 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x1682B | 0x160CB | 385 | -1888 | rodata/data |
| 0x17853 | 0x171AC | 372 | -1703 | rodata/data |
| 0x12566 | 0x10D4A | 290 | -6172 | code |
| 0x16FB4 | 0x166E5 | 272 | -2255 | rodata/data |
| 0x14B49 | 0x13375 | 267 | -6100 | code |
| 0x13CF9 | 0x1250D | 255 | -6124 | code |
| 0x1450D | 0x12D39 | 247 | -6100 | code |
| 0xFA66 | 0xD952 | 242 | -8468 | code |
| 0x1621B | 0x14A8B | 225 | -6032 | code |
| 0x14A6E | 0x1329A | 218 | -6100 | code |
| 0x16506 | 0x14D82 | 216 | -6020 | code |
| 0x16EBC | 0x165A4 | 216 | -2328 | rodata/data |

### off_v1.0.0: 112 runs >= 48 B covering 11013 B of the dump; dominant deltas (img_off - dump_off): -6788 (1437 B), -6800 (888 B), -7048 (545 B), -6796 (445 B), -7380 (444 B), -6812 (426 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x1682B | 0x15DE7 | 385 | -2628 | rodata/data |
| 0x17853 | 0x16E98 | 372 | -2491 | rodata/data |
| 0x14B49 | 0x130C5 | 267 | -6788 | code |
| 0x16FB4 | 0x16401 | 257 | -2995 | rodata/data |
| 0x1450D | 0x12A89 | 247 | -6788 | code |
| 0xFA66 | 0xDD92 | 242 | -7380 | code |
| 0x14A6E | 0x12FEA | 218 | -6788 | code |
| 0x16EBC | 0x162C0 | 216 | -3068 | rodata/data |
| 0x171A9 | 0x16730 | 216 | -2681 | rodata/data |
| 0x15E8A | 0x143F6 | 198 | -6804 | code |
| 0x174C4 | 0x169A4 | 192 | -2848 | rodata/data |
| 0x15893 | 0x13E07 | 191 | -6796 | code |

### off_v1.1.0: 47 runs >= 48 B covering 4672 B of the dump; dominant deltas (img_off - dump_off): +36632 (364 B), -1492 (310 B), +36248 (272 B), +0 (230 B), +36624 (208 B), +37148 (206 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x16840 | 0x1F758 | 364 | +36632 | rodata/data |
| 0x883A | 0x8266 | 310 | -1492 | code |
| 0x16FB4 | 0x1FD4C | 272 | +36248 | rodata/data |
| 0x174C4 | 0x20340 | 192 | +36476 | rodata/data |
| 0x171CB | 0x20064 | 182 | +36505 | rodata/data |
| 0x9A58 | 0x9CC8 | 168 | +624 | code |
| 0x16C44 | 0x1FB54 | 158 | +36624 | rodata/data |
| 0x86D9 | 0x885B | 137 | +386 | code |
| 0x17853 | 0x207BC | 114 | +36713 | rodata/data |
| 0x17434 | 0x20258 | 106 | +36388 | rodata/data |
| 0x149EE | 0x1CF66 | 104 | +34168 | code |
| 0x8000 | 0x8000 | 100 | +0 | code |

### off_v1.1.1: 45 runs >= 48 B covering 4176 B of the dump; dominant deltas (img_off - dump_off): +16524 (364 B), +16164 (272 B), +0 (230 B), +16516 (208 B), +17228 (206 B), +16789 (203 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x16840 | 0x1A8CC | 364 | +16524 | rodata/data |
| 0x16FB4 | 0x1AED8 | 272 | +16164 | rodata/data |
| 0x174C4 | 0x1B4BC | 192 | +16376 | rodata/data |
| 0x171CB | 0x1B1F0 | 182 | +16421 | rodata/data |
| 0x9A5C | 0x819C | 164 | -6336 | code |
| 0x16C44 | 0x1ACC8 | 158 | +16516 | rodata/data |
| 0x17853 | 0x1B9E8 | 114 | +16789 | rodata/data |
| 0x17434 | 0x1B3D4 | 106 | +16288 | rodata/data |
| 0x149EE | 0x1752A | 104 | +11068 | code |
| 0x8000 | 0x8000 | 100 | +0 | code |
| 0x177F0 | 0x1B824 | 99 | +16436 | rodata/data |
| 0x16F34 | 0x1AE0C | 96 | +16088 | rodata/data |

### today_default_gcc15: 126 runs >= 48 B covering 13547 B of the dump; dominant deltas (img_off - dump_off): -7840 (1492 B), -4264 (1435 B), -7836 (1268 B), -7844 (1145 B), -4604 (858 B), -7760 (638 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x177EA | 0x16602 | 478 | -4584 | rodata/data |
| 0x170FE | 0x16056 | 458 | -4264 | rodata/data |
| 0x173E6 | 0x1633E | 430 | -4264 | rodata/data |
| 0x144E8 | 0x12648 | 408 | -7840 | code |
| 0x1682C | 0x15939 | 372 | -3827 | rodata/data |
| 0x17DB5 | 0x16BB9 | 323 | -4604 | rodata/data |
| 0x12566 | 0x10716 | 290 | -7760 | code |
| 0x16FB3 | 0x15F0B | 273 | -4264 | rodata/data |
| 0x14B49 | 0x12CA5 | 267 | -7844 | code |
| 0xEAB4 | 0xC9C8 | 260 | -8428 | code |
| 0x13CF9 | 0x11E5D | 259 | -7836 | code |
| 0x16161 | 0x142BD | 257 | -7844 | code |

### ref1011_default_gcc15: 136 runs >= 48 B covering 14352 B of the dump; dominant deltas (img_off - dump_off): -5332 (1555 B), -8896 (1494 B), -8892 (1269 B), -8900 (1147 B), -5680 (937 B), -8920 (702 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x177EA | 0x161D2 | 478 | -5656 | rodata/data |
| 0x170FE | 0x15C2A | 458 | -5332 | rodata/data |
| 0x173E6 | 0x15F12 | 430 | -5332 | rodata/data |
| 0x144E8 | 0x12228 | 408 | -8896 | code |
| 0x1682C | 0x1550F | 372 | -4893 | rodata/data |
| 0x17DB5 | 0x16785 | 323 | -5680 | rodata/data |
| 0x12566 | 0x102F6 | 290 | -8816 | code |
| 0x16FB3 | 0x15ADF | 273 | -5332 | rodata/data |
| 0x14B49 | 0x12885 | 267 | -8900 | code |
| 0xEAB4 | 0xC7E8 | 260 | -8908 | code |
| 0x13CF9 | 0x11A3D | 259 | -8892 | code |
| 0x16161 | 0x13E9D | 257 | -8900 | code |

### ref1011_via_gcc15: 134 runs >= 48 B covering 14276 B of the dump; dominant deltas (img_off - dump_off): -6652 (1494 B), -6648 (1269 B), -6656 (1147 B), -2912 (1058 B), -2996 (937 B), -6572 (686 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x177EA | 0x16C4A | 478 | -2976 | rodata/data |
| 0x170FE | 0x1659E | 458 | -2912 | rodata/data |
| 0x173E6 | 0x16886 | 430 | -2912 | rodata/data |
| 0x144E8 | 0x12AEC | 408 | -6652 | code |
| 0x1682C | 0x15DD3 | 372 | -2649 | rodata/data |
| 0x17DB5 | 0x17201 | 323 | -2996 | rodata/data |
| 0x12566 | 0x10BBA | 290 | -6572 | code |
| 0x16FB3 | 0x163A3 | 273 | -3088 | rodata/data |
| 0x14B49 | 0x13149 | 267 | -6656 | code |
| 0xEAB4 | 0xC860 | 260 | -8788 | code |
| 0x13CF9 | 0x12301 | 259 | -6648 | code |
| 0x16161 | 0x14761 | 257 | -6656 | code |

### ref1011_default_lto_gcc15: 64 runs >= 48 B covering 6620 B of the dump; dominant deltas (img_off - dump_off): -15011 (372 B), -11532 (352 B), -11944 (342 B), -13316 (307 B), -25084 (260 B), -13072 (257 B)

| dump off | image off | len | delta | dump block class |
|---|---|---|---|---|
| 0x17853 | 0x13DB0 | 372 | -15011 | rodata/data |
| 0x16840 | 0x13B34 | 352 | -11532 | rodata/data |
| 0x17DBD | 0x149B9 | 307 | -13316 | rodata/data |
| 0xEAB4 | 0x88B8 | 260 | -25084 | code |
| 0x16FB4 | 0x13CA4 | 257 | -13072 | rodata/data |
| 0x14B5C | 0x115E8 | 248 | -13684 | code |
| 0x174C4 | 0x14538 | 192 | -12172 | rodata/data |
| 0x175B4 | 0x146AC | 191 | -12040 | rodata/data |
| 0x16C44 | 0x141B0 | 190 | -10900 | rodata/data |
| 0xFA9E | 0x928E | 186 | -26640 | code |
| 0x171CE | 0x13933 | 179 | -14491 | rodata/data |
| 0x9A58 | 0x8158 | 168 | -6400 | code |

