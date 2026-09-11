# Strings triage: dump_a.bin

Generated 2026-09-11T01:18:30+00:00 by tools/strings_triage.py. ASCII runs >= 6 printable bytes; UTF-16LE runs >= 4 chars. `.rodata` taken to start at file 0x16704 (--rodata-start if given, else end of the last code block from dump_triage heuristics); key-list scan excludes 0x169B8..0x16EC8.

## Summary

| category | count |
|---|---|
| usb-descriptor(utf16) | 9 |
| build-date | 1 |
| toolchain-path | 1 |
| chibios-qmk-newlib | 3 |
| keychron-wireless | 1 |
| printf-format | 3 |
| ctype-digit-table | 4 |
| lookup-table | 10 |
| text-candidate | 5 |
| code-garbage | 138 |
| SEND_STRING control-code sequences | 4 |
| u16 keycode lists (0-terminated, outside keymap) | 13 |

## UTF-16LE strings (USB string descriptors)

A valid USB string descriptor is preceded by `bLength, 0x03` with bLength = 2 + 2*chars.

| file off | flash | block | header bytes | header ok | chars | text |
|---|---|---|---|---|---|---|
| 0x9D7A | 0x08009D7A | code | e600 | no | 10 | `ffffffffff` |
| 0x9D90 | 0x08009D90 | code | ac00 | no | 11 | `pffffpffff!` |
| 0x169E4 | 0x080169E4 | data (inside excluded keymap table: u16 keycodes, not text) | 1f00 | no | 8 | ` !"#$%&'` |
| 0x16A92 | 0x08016A92 | data (inside excluded keymap table: u16 keycodes, not text) | 2078 | no | 13 | `*:;<=>?@ABCDE` |
| 0x16B0E | 0x08016B0E | data (inside excluded keymap table: u16 keycodes, not text) | 0b01 | no | 5 | `RPQOM` |
| 0x16B6A | 0x08016B6A | data (inside excluded keymap table: u16 keycodes, not text) | a800 | no | 14 | `):;<=>?@ABCDEI` |
| 0x16B8E | 0x08016B8E | data (inside excluded keymap table: u16 keycodes, not text) | 0177 | no | 14 | `E:;<=>?@ABCD.*` |
| 0x17102 | 0x08017102 | data | 2203 | yes | 16 | `Keychron V10 Max` |
| 0x17126 | 0x08017126 | data | 1203 | yes | 8 | `Keychron` |

## Build date

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x167AC | 0x080167AC | data | 19 | y | `2024-07-09-13:57:36` |

## Toolchain / newlib paths

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x17674 | 0x08017674 | ascii | 43 | y | `../../../../../../newlib/libc/stdlib/rand.c` |

## ChibiOS / QMK / newlib identifiers

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x167C0 | 0x080167C0 | data | 59 | y | `Invalid sector count intended to be used with wear_leveling` |
| 0x16816 | 0x08016816 | code | 11 | y | `DMA failure` |
| 0x1765C | 0x0801765C | ascii | 22 | y | `REENT malloc succeeded` |

## printf-style format strings

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x16C8A | 0x08016C8A | data | 12 | y | ` x!x'x#x%x)x` |
| 0x16D62 | 0x08016D62 | sparse | 12 | y | ` x!x'x#x%x)x` |
| 0x176B0 | 0x080176B0 | ascii | 46 | y | `assertion "%s" failed: file "%s", line %d%s%s\n` |

## Keychron / wireless identifiers (lkbt51, bluetooth, factory test, ...)

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x1679B | 0x0801679B | data | 16 | y | `Keychron V10 Max` |

## Digit / ctype tables (newlib)

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x176E0 | 0x080176E0 | ascii | 36 | y | `0123456789abcdefghijklmnopqrstuvwxyz` |
| 0x17714 | 0x08017714 | ptr | 6 | y | `efgEFG` |
| 0x1771C | 0x0801771C | ptr | 16 | y | `0123456789ABCDEF` |
| 0x17730 | 0x08017730 | ptr | 16 | y | `0123456789abcdef` |

## Lookup tables that happen to be printable (monotone byte runs)

Non-decreasing byte runs through 0x20..0x7E are slices of u8 curves (CIE1931 / gamma / sine tables), not text.

| file off | flash | block | len | NUL-term | text |
|---|---|---|---|---|---|
| 0x10A93 | 0x08010A93 | code | 15 | n | `'+/37;?CGKOSW[_` |
| 0x11BBE | 0x08011BBE | code | 8 | n | `********` |
| 0x167FC | 0x080167FC | data | 12 | y | `            ` |
| 0x16FE9 | 0x08016FE9 | data | 7 | n | `\t\t\t\t\n\n\n` |
| 0x1701E | 0x0801701E | ptr | 88 | n | `  !""#$$%&&'())*+,--./01223456789:;<=>?@ABCDEFGHIJLMNOPQSTUVXYZ[]^_abdefhiklmoprsuwxz{}~` |
| 0x17878 | 0x08017878 | data | 6 | n | ` !"#$%` |
| 0x1787F | 0x0801787F | data | 8 | n | `&'()*+,-` |
| 0x17888 | 0x08017888 | data | 8 | n | `./012345` |
| 0x17891 | 0x08017891 | data | 7 | n | `6789:;<` |
| 0x1789E | 0x0801789E | data | 12 | n | `@ABCDEFGHIJK` |

## SEND_STRING / leader / macro text candidates

Every remaining printable run. `text_score` = 0.5*letters/spaces fraction + 0.3*(has a vowel word) + 0.2*lower-case ratio; real SEND_STRING literals in .rodata score >= ~0.6 and are NUL-terminated. Runs whose block is classified `code` are almost always Thumb opcode bytes (e.g. `pGpGpG` = repeated `bx lr` 0x4770).

### In .rodata (file >= 0x16704) or data-classified blocks

| file off | flash | block | len | NUL-term | score | text |
|---|---|---|---|---|---|---|
| 0x16CB0 | 0x08016CB0 | data | 10 | y | 0.35 | `"x(x$x&x*x` |
| 0x176A0 | 0x080176A0 | ascii | 12 | y | 0.93 | `, function: ` |
| 0x17920 | 0x08017920 | data | 13 | n | 0.21 | `"("5#A%M'Y*v*` |
| 0x1793E | 0x0801793E | data | 15 | n | 0.25 | `-,-9.E0Q3]5p6\|4` |
| 0x1795C | 0x0801795C | data | 11 | n | 0.05 | `7!789M=\`@}?` |

### Short (3..5 byte) printable runs in .rodata

Listed so that very short macro text (e.g. SEND_STRING("hi")) cannot hide below the length cut-off.

| file off | len | NUL-term | text |
|---|---|---|---|
| 0x1680C | 4 | y | `main` |
| 0x16811 | 4 | y | `idle` |
| 0x16822 | 4 | y | `exit` |
| 0x16827 | 4 | y | `kill` |
| 0x168BD | 3 | y | `0P@` |
| 0x168C1 | 3 | y | `1QA` |
| 0x168C5 | 3 | y | `2RB` |
| 0x168C9 | 3 | y | `3SC` |
| 0x168CD | 3 | y | `4TD` |
| 0x168D1 | 3 | y | `5UE` |
| 0x168D5 | 3 | y | `6VF` |
| 0x168D9 | 3 | y | `8XH` |
| 0x168DD | 3 | y | `9YI` |
| 0x168E1 | 3 | y | `:ZJ` |
| 0x168E5 | 3 | y | `;[K` |
| 0x168E9 | 3 | y | `<\L` |
| 0x168ED | 3 | y | `=]M` |
| 0x168F1 | 3 | y | `>^N` |
| 0x168F5 | 3 | y | `?_O` |
| 0x16939 | 3 | n | `?_O` |
| 0x1693D | 3 | n | `>^N` |
| 0x16941 | 3 | n | `<\L` |
| 0x16945 | 3 | n | `;[K` |
| 0x16949 | 3 | n | `:ZJ` |
| 0x1694D | 3 | n | `9YI` |
| 0x16951 | 3 | n | `8XH` |
| 0x16955 | 3 | n | `7WG` |
| 0x16959 | 3 | n | `6VF` |
| 0x1695D | 3 | n | `5UE` |
| 0x16961 | 3 | n | `4TD` |
| 0x16965 | 3 | n | `3SC` |
| 0x16969 | 3 | n | `2RB` |
| 0x1696D | 3 | n | `1QA` |
| 0x169A4 | 4 | n | `'x(x` |
| 0x169B4 | 4 | n | `'x(x` |
| 0x169C3 | 5 | n | `~(x'x` |
| 0x16A90 | 3 | y | ` x*` |
| 0x16B36 | 5 | n | `@~A~8` |
| 0x16C4B | 5 | n | `~(x'x` |
| 0x16C6B | 3 | n | `~\r~` |
| 0x16D23 | 5 | n | `~(x'x` |
| 0x16D43 | 3 | n | `~\r~` |
| 0x16DFB | 5 | n | `~(x'x` |
| 0x16F95 | 4 | n | `11)Z` |
| 0x16FF6 | 3 | n | `\r\r\r` |
| 0x1719E | 3 | n | `@44` |
| 0x171E9 | 4 | n | `\t0\t1` |
| 0x174E7 | 3 | n | `\rX\`` |
| 0x1752F | 3 | n | `8(d` |
| 0x1753A | 4 | n | `\t9@d` |
| 0x17546 | 4 | n | `\n:Xd` |
| 0x17553 | 3 | n | `;pd` |
| 0x175A7 | 3 | y | ` \%` |
| 0x175F8 | 4 | n | `UYUU` |
| 0x17614 | 4 | n | `UUUU` |
| 0x17630 | 4 | n | `UUUU` |
| 0x1764C | 4 | n | `PUUU` |
| 0x17708 | 5 | y | `#-0+ ` |
| 0x17710 | 3 | y | `hlL` |
| 0x1789A | 3 | n | `=>?` |
| 0x178AD | 3 | n | `MNO` |
| 0x178BC | 3 | n | `UVW` |
| 0x178E3 | 3 | n | `0\r=` |
| 0x1790B | 3 | n | `q!}` |
| 0x17D83 | 3 | n | ` Y1` |

### In code-classified blocks (low confidence, opcode bytes), sorted by score

| file off | flash | len | score | text |
|---|---|---|---|---|
| 0x14ACD | 0x08014ACD | 7 | 0.91 | `iZiXaZi` |
| 0x14BAA | 0x08014BAA | 6 | 0.90 | `Zg KZo` |
| 0x1625C | 0x0801625C | 6 | 0.90 | `AhBjIx` |
| 0x1557A | 0x0801557A | 7 | 0.89 | `ZeZmZiB` |
| 0x13CFD | 0x08013CFD | 6 | 0.87 | `CXjpGO` |
| 0x8FDD | 0x08008FDD | 7 | 0.84 | ` pGuh3F` |
| 0x10140 | 0x08010140 | 8 | 0.84 | `\nyIyBpAr` |
| 0xA87E | 0x0800A87E | 6 | 0.83 | `XBXApG` |
| 0xEF38 | 0x0800EF38 | 6 | 0.83 | `'xEJEN` |
| 0x125D4 | 0x080125D4 | 6 | 0.83 | `XBXApG` |
| 0x159C7 | 0x080159C7 | 10 | 0.82 | `hCmli&h&aJ` |
| 0x15865 | 0x08015865 | 8 | 0.81 | ` pGH1CmI` |
| 0x9DBA | 0x08009DBA | 6 | 0.77 | `+h"hai` |
| 0x8639 | 0x08008639 | 7 | 0.71 | `S(3kDaF` |
| 0xB83E | 0x0800B83E | 6 | 0.70 | `#M#Nki` |
| 0xB304 | 0x0800B304 | 8 | 0.68 | `JB+FJA0F` |
| 0x15ACD | 0x08015ACD | 8 | 0.66 | `4/DQhqE!` |
| 0x9DEC | 0x08009DEC | 8 | 0.64 | `#iJF9F0F` |
| 0x13334 | 0x08013334 | 6 | 0.63 | `ci hYF` |
| 0x133CE | 0x080133CE | 6 | 0.63 | `ch hRF` |
| 0x155A9 | 0x080155A9 | 6 | 0.62 | `##\`nmO` |
| 0xA42B | 0x0800A42B | 13 | 0.61 | ` pGpGpGpGpGpG` |
| 0xD4B3 | 0x0800D4B3 | 7 | 0.61 | ` pGpGpG` |
| 0x14AEB | 0x08014AEB | 11 | 0.61 | `jYjXbYjZbYj` |
| 0x12454 | 0x08012454 | 6 | 0.60 | `pGpGpG` |
| 0x8E1C | 0x08008E1C | 9 | 0.58 | `=FUE+F:F(` |
| 0x14C1B | 0x08014C1B | 6 | 0.57 | `BZdZnB` |
| 0x1643F | 0x0801643F | 6 | 0.57 | `RZdZnB` |
| 0x16447 | 0x08016447 | 8 | 0.57 | `RZfZnZjB` |
| 0xAC9B | 0x0800AC9B | 9 | 0.54 | `p#y+qcykq` |
| 0x1335E | 0x0801335E | 8 | 0.54 | `%Jch hYF` |
| 0x97E6 | 0x080097E6 | 6 | 0.52 | `cQchK\`` |
| 0x15E8B | 0x08015E8B | 6 | 0.52 | ` P pG0` |
| 0xF732 | 0x0800F732 | 6 | 0.50 | `JCLCKC` |
| 0xA573 | 0x0800A573 | 9 | 0.48 | `ClNmM0x+x` |
| 0xEAFE | 0x0800EAFE | 6 | 0.48 | `) pG-J` |
| 0x135C9 | 0x080135C9 | 6 | 0.48 | `JQhSh[` |
| 0x13D1F | 0x08013D1F | 6 | 0.48 | `CXcpG0` |
| 0x162E9 | 0x080162E9 | 6 | 0.48 | `RZbZj"` |
| 0x16451 | 0x08016451 | 6 | 0.48 | `RZbZj"` |
| 0x164F3 | 0x080164F3 | 6 | 0.48 | `RZdZn"` |
| 0xEBA2 | 0x0800EBA2 | 8 | 0.47 | `1 pG9 pG` |
| 0x15A2E | 0x08015A2E | 7 | 0.47 | `@  \` h.` |
| 0xA692 | 0x0800A692 | 6 | 0.45 | `'O+p,K` |
| 0xE4AE | 0x0800E4AE | 10 | 0.45 | `hp$h\tI " F` |
| 0x14C23 | 0x08014C23 | 8 | 0.45 | `BZf[npG@` |
| 0xC27B | 0x0800C27B | 7 | 0.44 | `$ F4p,p` |
| 0xF9D9 | 0x0800F9D9 | 7 | 0.44 | `yp;KC 8` |
| 0xFA29 | 0x0800FA29 | 7 | 0.44 | `yp;KC 8` |
| 0x12C23 | 0x08012C23 | 7 | 0.44 | `# "iF F` |
| 0x16459 | 0x08016459 | 7 | 0.44 | `RZb[j#j` |
| 0xBFD3 | 0x0800BFD3 | 6 | 0.43 | `ppG\nx"` |
| 0x10578 | 0x08010578 | 6 | 0.43 | `2F)ykx` |
| 0x14CD7 | 0x08014CD7 | 9 | 0.43 | `JYh\nCZ\`Yh` |
| 0x14D69 | 0x08014D69 | 6 | 0.43 | `s#a#iC` |
| 0x8E54 | 0x08008E54 | 6 | 0.42 | `SF:FHF` |
| 0xE87C | 0x0800E87C | 6 | 0.42 | `ZF!FHF` |
| 0xA3FB | 0x0800A3FB | 7 | 0.41 | `K)F[h F` |
| 0xC893 | 0x0800C893 | 7 | 0.41 | `#Cp)F F` |
| 0xC986 | 0x0800C986 | 7 | 0.41 | `"LJy#xZ` |
| 0x1105B | 0x0801105B | 7 | 0.41 | `C=L>O h` |
| 0x15FEF | 0x08015FEF | 7 | 0.41 | `#KbS#Kb` |
| 0x8DD1 | 0x08008DD1 | 6 | 0.40 | `F\nF h]` |
| 0x16276 | 0x08016276 | 6 | 0.40 | `QhRz=#` |
| 0x1629A | 0x0801629A | 6 | 0.40 | `YzZh=#` |
| 0x162B6 | 0x080162B6 | 6 | 0.40 | `QhRz=#` |
| 0x162D2 | 0x080162D2 | 6 | 0.40 | `YzZh=#` |
| 0x164FB | 0x080164FB | 6 | 0.40 | `RZf[n8` |
| 0x13E6B | 0x08013E6B | 7 | 0.39 | `j/D+D.D` |
| 0x13FC9 | 0x08013FC9 | 7 | 0.39 | `j/D+D.D` |
| 0xB4EC | 0x0800B4EC | 6 | 0.37 | `"F!F F` |
| 0xF156 | 0x0800F156 | 6 | 0.37 | `"FiF(F` |
| 0xF3B6 | 0x0800F3B6 | 6 | 0.37 | `*F9F F` |
| 0x138E2 | 0x080138E2 | 6 | 0.37 | `+F\tJhF` |
| 0x14D60 | 0x08014D60 | 7 | 0.37 | `@s#a#iC` |
| 0x1654F | 0x0801654F | 7 | 0.37 | `ja\`#\`Cj` |
| 0x12A9A | 0x08012A9A | 8 | 0.36 | `(M(L.x#x` |
| 0xCAE3 | 0x0800CAE3 | 6 | 0.35 | `#+p h\`` |
| 0x9823 | 0x08009823 | 7 | 0.34 | ` +D#\`Sh` |
| 0xBB26 | 0x0800BB26 | 8 | 0.34 | `\tA2F;F F` |
| 0x12FE2 | 0x08012FE2 | 8 | 0.34 | `+F2F9F F` |
| 0x146F0 | 0x080146F0 | 8 | 0.34 | `+F*F)F F` |
| 0x14726 | 0x08014726 | 8 | 0.34 | `+F*F)F F` |
| 0x10315 | 0x08010315 | 8 | 0.33 | `  :p9+F@` |
| 0x13311 | 0x08013311 | 6 | 0.33 | `%7O.FO` |
| 0x13806 | 0x08013806 | 6 | 0.33 | `JF)F8F` |
| 0x9090 | 0x08009090 | 10 | 0.32 | `#hSD#\`!FHF` |
| 0xA9B3 | 0x0800A9B3 | 6 | 0.32 | `" ! F\n` |
| 0xAC8B | 0x0800AC8B | 6 | 0.32 | `F!#+pc` |
| 0xD123 | 0x0800D123 | 6 | 0.32 | `p%O;x#` |
| 0xE242 | 0x0800E242 | 6 | 0.32 | `%L(x;x` |
| 0xE476 | 0x0800E476 | 6 | 0.32 | `(p$h\tI` |
| 0x130D4 | 0x080130D4 | 6 | 0.32 | `x\`(h"F` |
| 0x134B4 | 0x080134B4 | 10 | 0.32 | `"DIB*D\n@Yh` |
| 0xCA86 | 0x0800CA86 | 7 | 0.31 | `(M(L(hX` |
| 0x1008B | 0x0801008B | 7 | 0.31 | `F4M+x#D` |
| 0x14E85 | 0x08014E85 | 7 | 0.31 | `D+q1F(F` |
| 0x11381 | 0x08011381 | 9 | 0.30 | `$ F;F2F)F` |
| 0x9C8D | 0x08009C8D | 7 | 0.29 | `#ZF9F0F` |
| 0x9E1D | 0x08009E1D | 7 | 0.29 | `#RF9F0F` |
| 0x960E | 0x0800960E | 6 | 0.28 | `+F2F!j` |
| 0x97FC | 0x080097FC | 6 | 0.28 | `#h9F0F` |
| 0x98A6 | 0x080098A6 | 6 | 0.28 | `c\`T\`(F` |
| 0x9E92 | 0x08009E92 | 6 | 0.28 | `o*LH+\`` |
| 0x8470 | 0x08008470 | 6 | 0.25 | `\tK\nH\nI` |
| 0x8FEE | 0x08008FEE | 6 | 0.25 | `*F\n!XF` |
| 0x9BEF | 0x08009BEF | 6 | 0.25 | `B"F)F(` |
| 0xBEA9 | 0x0800BEA9 | 8 | 0.25 | `$8M0&'FU` |
| 0xC0B6 | 0x0800C0B6 | 6 | 0.25 | `<"SC\nJ` |
| 0xC840 | 0x0800C840 | 8 | 0.25 | `\tN\nH"F1F` |
| 0xD022 | 0x0800D022 | 6 | 0.25 | `*F)F(F` |
| 0xD050 | 0x0800D050 | 6 | 0.25 | `2F1F0F` |
| 0xF162 | 0x0800F162 | 6 | 0.25 | `"F1F(F` |
| 0x14792 | 0x08014792 | 6 | 0.25 | `+F*F)F` |
| 0x157C8 | 0x080157C8 | 6 | 0.25 | `Y\`(F!F` |
| 0x15816 | 0x08015816 | 8 | 0.25 | `\nJZ\`!F(F` |
| 0x15301 | 0x08015301 | 7 | 0.24 | `\`Yh\n@Z\`` |
| 0x9D05 | 0x08009D05 | 7 | 0.21 | `#"F9F0F` |
| 0x95C5 | 0x080095C5 | 7 | 0.20 | `#c\`#i#\`` |
| 0x9F0A | 0x08009F0A | 6 | 0.20 | `#\`x"/H` |
| 0xA367 | 0x0800A367 | 6 | 0.20 | `# "!F\r` |
| 0xA9CD | 0x0800A9CD | 6 | 0.20 | `"@! F\n` |
| 0xBD63 | 0x0800BD63 | 6 | 0.20 | `H@" !\t` |
| 0x12CCD | 0x08012CCD | 6 | 0.20 | `\`pG!*\r` |
| 0x1522D | 0x0801522D | 6 | 0.20 | `\`!&Fa"` |
| 0xAAB9 | 0x0800AAB9 | 6 | 0.17 | `01FU7\r` |
| 0xCA9B | 0x0800CA9B | 7 | 0.17 | `#+\`$M+x` |
| 0xCB57 | 0x0800CB57 | 6 | 0.17 | `#*F!F\r` |
| 0x16420 | 0x08016420 | 6 | 0.17 | `%J#F\n!` |
| 0x135FB | 0x080135FB | 7 | 0.14 | `\`L\`!\`Y\`` |
| 0xC7FF | 0x0800C7FF | 6 | 0.12 | `#+p#\`8` |
| 0x13E3F | 0x08013E3F | 7 | 0.10 | `j@7@3@6` |
| 0x13F99 | 0x08013F99 | 7 | 0.10 | `j@7@3@6` |
| 0xF40F | 0x0800F40F | 6 | 0.08 | `09F3\n\r` |
| 0x11556 | 0x08011556 | 15 | 0.08 | ` #&),/357\r\r\r\r\r\r` |
| 0xEAD9 | 0x0800EAD9 | 9 | 0.06 | `@#(1@<A9(` |
| 0xC888 | 0x0800C888 | 10 | 0.05 | `+.::::::47` |
| 0x14760 | 0x08014760 | 12 | 0.00 | `&655555555;;` |

## SEND_STRING control-code sequences

Pattern: SS_QMK_PREFIX (0x01) then SS_TAP_CODE/SS_DOWN_CODE/SS_UP_CODE (0x01/0x02/0x03) + 8-bit keycode, or SS_DELAY_CODE (0x04) + digits + `|`; optionally interleaved with ASCII; NUL-terminated (quantum/send_string/send_string_keycodes.h).

| file off | flash | block | ctl codes | decoded |
|---|---|---|---|---|
| 0x10E84 | 0x08010E84 | code | 1 | `SS_UP(KC_6) 'p' '\t' 'K'` |
| 0x1300E | 0x0801300E | code | 1 | `SS_TAP(KC_3) 'F'` |
| 0x1653A | 0x0801653A | code | 1 | `SS_DOWN(KC_W) '\`'` |
| 0x16570 | 0x08016570 | code | 1 | `SS_DOWN(KC_W) '\`'` |

## u16 keycode-like arrays terminated by 0x0000 (outside the keymap table)

Combo key lists (`{KC_A, KC_B, COMBO_END}`), tap-dance pairs and similar are 2-byte aligned u16 arrays of plausible keycodes ending in 0. Inside code blocks, Thumb halfwords (e.g. `0x2000 movs`, `0x4770 bx lr`) also satisfy the filter, so only data/ptr/sparse-block hits are meaningful; code-block hits are listed for completeness.

### In data-classified blocks (11)

| file off | flash | block | n | values | decoded | note |
|---|---|---|---|---|---|---|
| 0x16722 | 0x08016722 | data | 2 | 0x4002 0x0004 | 0x4002 KC_A |  |
| 0x1672C | 0x0801672C | data | 2 | 0x1211 0x0013 | RSFT(KC_N) KC_P |  |
| 0x169A0 | 0x080169A0 | data | 6 | 0x00A9 0x00AA 0x7827 0x7828 0x00A9 0x00AA | KC_VOLU KC_VOLD RGB_VAI RGB_VAD KC_VOLU KC_VOLD | encoder_map[6][1][2]: loaded via literal 0x080169A0 at file 0xD2C4 by keycode_at_encodermap_location_raw (0x0800D2A8); index 0 = clockwise, so L0/L2 = ENCODER_CCW_CW(KC_VOLD,KC_VOLU), L1/L5 = ENCODER_CCW_CW(RGB_VAD,RGB_VAI), L3/L4 = {KC_NO,KC_NO} |
| 0x169B4 | 0x080169B4 | data | 17 | 0x7827 0x7828 0x00A8 0x0029 0x00BE 0x00BD 0x7E04 0x7E05 0x7828 0x7827 0x00AC 0x00AE 0x00AB 0x00A8 0x00AA 0x00A9 0x0049 | RGB_VAI RGB_VAD KC_MUTE KC_ESC KC_BRID KC_BRIU KC_MCTRL KC_LNPAD RGB_VAD RGB_VAI KC_MPRV KC_MPLY KC_MNXT KC_MUTE KC_VOLD KC_VOLU KC_INS | encoder_map[6][1][2]: loaded via literal 0x080169A0 at file 0xD2C4 by keycode_at_encodermap_location_raw (0x0800D2A8); index 0 = clockwise, so L0/L2 = ENCODER_CCW_CW(KC_VOLD,KC_VOLU), L1/L5 = ENCODER_CCW_CW(RGB_VAD,RGB_VAI), L3/L4 = {KC_NO,KC_NO}; keymaps[] start (table excluded from scan; run begins 4 B before it) |
| 0x17100 | 0x08017100 | data | 17 | 0x0322 0x004B 0x0065 0x0079 0x0063 0x0068 0x0072 0x006F 0x006E 0x0020 0x0056 0x0031 0x0030 0x0020 0x004D 0x0061 0x0078 | LCTL|LSFT(KC_5) KC_PGUP 0x0065 0x0079 0x0063 0x0068 0x0072 0x006F 0x006E KC_3 0x0056 KC_BSLS KC_RBRC KC_3 KC_END 0x0061 0x0078 | USB string descriptor header + UTF-16 read as u16 |
| 0x17124 | 0x08017124 | data | 9 | 0x0312 0x004B 0x0065 0x0079 0x0063 0x0068 0x0072 0x006F 0x006E | LCTL|LSFT(KC_O) KC_PGUP 0x0065 0x0079 0x0063 0x0068 0x0072 0x006F 0x006E | USB string descriptor header + UTF-16 read as u16 |
| 0x172A8 | 0x080172A8 | data | 15 | 0x0695 0x0875 0x0081 0x0805 0x0119 0x0529 0x0015 0x0125 0x0595 0x0175 0x0291 0x0195 0x0375 0x0191 0x00C0 | 0x0695 0x0875 0x0081 LGUI(KC_B) LCTL(KC_V) LCTL|LALT(KC_ESC) KC_R LCTL(KC_8) 0x0595 0x0175 0x0291 0x0195 0x0375 0x0191 0x00C0 | USB HID report-descriptor items (0x05 usage page, 0x95 count, 0x75 size, 0x81 input, 0xC0 end) read as u16 |
| 0x17582 | 0x08017582 | data | 2 | 0x460F 0x0080 | 0x460F 0x0080 |  |
| 0x17716 | 0x08017716 | ptr | 2 | 0x4567 0x4746 | 0x4567 0x4746 | ASCII text read as u16, not keycodes |
| 0x17726 | 0x08017726 | ptr | 3 | 0x4241 0x4443 0x4645 | 0x4241 0x4443 0x4645 | ASCII text read as u16, not keycodes |
| 0x17C48 | 0x08017C48 | sparse | 2 | 0x0020 0x0020 | KC_3 KC_3 |  |

### In code-classified blocks (2, low confidence; only lists with >= 3 entries shown, all are in the JSON)

_none_

