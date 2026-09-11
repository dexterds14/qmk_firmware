# Library member match: dump_a.bin

Generated 2026-09-11T01:25:29+00:00 by tools/lib_match.py. Member .text matched with 16-byte relocation-free windows; a member counts as matched when >= 90% of its windows occur in the dump and its longest exact run is >= 48 B. Members with .text < 32 B ignored.

| library | members considered | matched | matched .text bytes |
|---|---|---|---|
| ubuntu_noble_newlib_4.4.0-2_libc_nano (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/libnewlib-arm-none-eabi_4.4.0.20231231-2_all/usr/lib/arm-none-eabi/newlib/thumb/v7e-m+fp/hard/libc_nano.a`) | 410 | 23 | 7428 |
| ubuntu_jammy_newlib_3.3.0-1.3_libc_nano (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/libnewlib-arm-none-eabi_3.3.0-1.3_all/usr/lib/arm-none-eabi/newlib/thumb/v7e-m+fp/hard/libc_nano.a`) | 409 | 3 | 612 |
| qmk_toolchain_gcc15.2_newlib_nano_libc (`/Users/dexter/Library/Application Support/qmk/newlib-nano/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc_nano.a`) | 373 | 1 | 160 |
| ubuntu_noble_gcc13.2.rel1-2_libgcc (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/gcc-arm-none-eabi_13.2.rel1-2_amd64/usr/lib/gcc/arm-none-eabi/13.2.1/thumb/v7e-m+fp/hard/libgcc.a`) | 275 | 1 | 700 |
| ubuntu_gcc14.2.rel1-1_libgcc (`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/debs/gcc-arm-none-eabi_14.2.rel1-1_amd64/usr/lib/gcc/arm-none-eabi/14.2.1/thumb/v7e-m+fp/hard/libgcc.a`) | 274 | 0 | 0 |
| qmk_toolchain_gcc15.2_libgcc (`/Users/dexter/Library/Application Support/qmk/lib/gcc/arm-none-eabi/15.2.0/thumb/v7e-m+fp/hard/libgcc.a`) | 214 | 0 | 0 |

## ubuntu_noble_newlib_4.4.0-2_libc_nano

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| libc_a-nano-vfprintf_i.o | 936 | 16 | 875 | 875 | 1.00 | 446 | 0x9C28 | 0x0 |
| libc_a-nano-vfprintf.o | 788 | 64 | 568 | 568 | 1.00 | 202 | 0x8C10 | 0x1E0 |
| libc_a-fvwrite.o | 768 | 52 | 522 | 522 | 1.00 | 172 | 0x8F14 | 0x130 |
| libc_a-signal.o | 608 | 56 | 353 | 353 | 1.00 | 78 | 0x91EA | 0x106 |
| libc_a-findfp.o | 548 | 128 | 201 | 201 | 1.00 | 72 | 0x9474 | 0x130 |
| libc_a-fflush.o | 424 | 40 | 327 | 327 | 1.00 | 200 | 0x95EA | 0x82 |
| libc_a-mallocr.o | 328 | 36 | 169 | 169 | 1.00 | 68 | 0x97C2 | 0xB2 |
| libc_a-memcpy.o | 308 | 0 | 293 | 293 | 1.00 | 308 | 0x883C | 0x0 |
| libc_a-makebuf.o | 276 | 20 | 169 | 169 | 1.00 | 72 | 0xA068 | 0x90 |
| libc_a-memmove.o | 256 | 0 | 241 | 241 | 1.00 | 256 | 0x9914 | 0x0 |
| libc_a-rand.o | 252 | 40 | 111 | 111 | 1.00 | 48 | 0x84AC | 0x64 |
| libc_a-strlen.o | 216 | 0 | 201 | 201 | 1.00 | 216 | 0x86C0 | 0x0 |
| libc_a-wsetup.o | 196 | 16 | 120 | 120 | 1.00 | 118 | 0x9B00 | 0x0 |
| libc_a-freer.o | 188 | 20 | 106 | 106 | 1.00 | 86 | 0x98B4 | 0x5C |
| libc_a-memset.o | 164 | 0 | 149 | 149 | 1.00 | 164 | 0x8798 | 0x0 |
| libc_a-memchr.o | 160 | 0 | 145 | 145 | 1.00 | 160 | 0x9A60 | 0x0 |
| libc_a-utoa.o | 160 | 8 | 137 | 137 | 1.00 | 152 | 0x85F8 | 0x0 |
| libc_a-wbuf.o | 160 | 24 | 72 | 72 | 1.00 | 82 | 0x8D44 | 0x0 |
| libc_a-stdio.o | 148 | 20 | 67 | 67 | 1.00 | 68 | 0xA0F8 | 0xC |
| libc_a-fflush_u.o | 132 | 36 | 54 | 54 | 1.00 | 50 | 0x96BA | 0x2E |
| libc_a-memcmp.o | 92 | 0 | 77 | 77 | 1.00 | 92 | 0x89D4 | 0x0 |
| libc_a-fwalk.o | 68 | 0 | 53 | 53 | 1.00 | 68 | 0x9A14 | 0x0 |
| libc_a-random.o | 252 | 40 | 111 | 107 | 0.96 | 48 | 0x84AC | 0x64 |
| libc_a-mstats.o | 120 | 52 | 1 | 1 | 1.00 | 18 | 0x8DCC | 0x20 |
| libc_a-reallocr.o | 100 | 24 | 2 | 2 | 1.00 | 18 | 0x9BD6 | 0x12 |
| libc_a-itoa.o | 88 | 8 | 36 | 36 | 1.00 | 40 | 0x85A2 | 0x12 |
| libc_a-assert.o | 76 | 28 | 17 | 17 | 1.00 | 32 | 0x8544 | 0x0 |
| libc_a-dprintf.o | 68 | 12 | 15 | 15 | 1.00 | 30 | 0x89A2 | 0x12 |
| libc_a-fprintf.o | 68 | 12 | 15 | 15 | 1.00 | 30 | 0x89A2 | 0x12 |
| libc_a-fscanf.o | 68 | 12 | 5 | 5 | 1.00 | 20 | 0x89AC | 0x0 |
| libc_a-fwprintf.o | 68 | 12 | 15 | 15 | 1.00 | 30 | 0x89A2 | 0x12 |
| libc_a-fwscanf.o | 68 | 12 | 5 | 5 | 1.00 | 20 | 0x89AC | 0x0 |
| libc_a-getenv.o | 52 | 16 | 1 | 1 | 1.00 | 18 | 0x8DCC | 0x0 |
| libc_a-signalr.o | 48 | 12 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-fstatr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-getentropyr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-gettimeofdayr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-linkr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-mkdirr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-setenv.o | 44 | 16 | 3 | 3 | 1.00 | 20 | 0x8D28 | 0x0 |
| libc_a-statr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| libc_a-fseek.o | 32 | 12 | 3 | 3 | 1.00 | 20 | 0x8D28 | 0x4 |
| libc_a-strtold.o | 72 | 28 | 6 | 3 | 0.50 | 20 | 0x8D28 | 0xC |

Unmatched members with >= 20% window hits (partial similarity): libc_a-assert.o (100%), libc_a-dprintf.o (100%), libc_a-fprintf.o (100%), libc_a-fscanf.o (100%), libc_a-fseek.o (100%), libc_a-fstatr.o (100%), libc_a-fwprintf.o (100%), libc_a-fwscanf.o (100%), libc_a-getentropyr.o (100%), libc_a-getenv.o (100%), libc_a-gettimeofdayr.o (100%), libc_a-itoa.o (100%), libc_a-linkr.o (100%), libc_a-mkdirr.o (100%), libc_a-mstats.o (100%), libc_a-reallocr.o (100%), libc_a-setenv.o (100%), libc_a-signalr.o (100%), libc_a-statr.o (100%), libc_a-strtold.o (50%)

## ubuntu_jammy_newlib_3.3.0-1.3_libc_nano

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| lib_a-memcpy.o | 308 | 0 | 293 | 293 | 1.00 | 308 | 0x883C | 0x0 |
| lib_a-memchr.o | 160 | 0 | 145 | 145 | 1.00 | 160 | 0x9A60 | 0x0 |
| lib_a-stdio.o | 144 | 20 | 63 | 57 | 0.91 | 68 | 0xA0F8 | 0xC |
| lib_a-assert.o | 76 | 28 | 17 | 17 | 1.00 | 32 | 0x8544 | 0x0 |
| lib_a-fprintf.o | 68 | 12 | 15 | 15 | 1.00 | 30 | 0x89A2 | 0x12 |
| lib_a-fscanf.o | 68 | 12 | 5 | 5 | 1.00 | 20 | 0x89AC | 0x0 |
| lib_a-fwprintf.o | 68 | 12 | 15 | 15 | 1.00 | 30 | 0x89A2 | 0x12 |
| lib_a-fwscanf.o | 68 | 12 | 5 | 5 | 1.00 | 20 | 0x89AC | 0x0 |
| lib_a-getenv.o | 52 | 16 | 1 | 1 | 1.00 | 18 | 0x8DCC | 0x0 |
| lib_a-signalr.o | 48 | 12 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-fstatr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-gettimeofdayr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-linkr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-mkdirr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-setenv.o | 44 | 16 | 3 | 3 | 1.00 | 20 | 0x8D28 | 0x0 |
| lib_a-statr.o | 44 | 8 | 6 | 6 | 1.00 | 18 | 0xA190 | 0x0 |
| lib_a-fseek.o | 32 | 12 | 3 | 3 | 1.00 | 20 | 0x8D28 | 0x4 |
| lib_a-rand.o | 252 | 40 | 111 | 87 | 0.78 | 43 | 0x84E3 | 0x9B |
| lib_a-random.o | 252 | 40 | 111 | 87 | 0.78 | 43 | 0x84E3 | 0x9B |
| lib_a-utoa.o | 160 | 8 | 137 | 105 | 0.77 | 116 | 0x85F8 | 0x0 |
| lib_a-strlen.o | 220 | 0 | 205 | 156 | 0.76 | 137 | 0x86D9 | 0x1B |
| lib_a-memmove.o | 248 | 0 | 233 | 154 | 0.66 | 89 | 0x9961 | 0x49 |
| lib_a-strtold.o | 72 | 28 | 6 | 3 | 0.50 | 20 | 0x8D28 | 0xC |

Unmatched members with >= 20% window hits (partial similarity): lib_a-assert.o (100%), lib_a-fprintf.o (100%), lib_a-fscanf.o (100%), lib_a-fseek.o (100%), lib_a-fstatr.o (100%), lib_a-fwprintf.o (100%), lib_a-fwscanf.o (100%), lib_a-getenv.o (100%), lib_a-gettimeofdayr.o (100%), lib_a-itoa.o (25%), lib_a-linkr.o (100%), lib_a-memmove.o (66%), lib_a-memset.o (28%), lib_a-mkdirr.o (100%), lib_a-rand.o (78%), lib_a-random.o (78%), lib_a-setenv.o (100%), lib_a-signalr.o (100%), lib_a-statr.o (100%), lib_a-strlen.o (76%), lib_a-strtold.o (50%), lib_a-utoa.o (77%)

## qmk_toolchain_gcc15.2_newlib_nano_libc

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| libc_a-memchr.o | 160 | 0 | 145 | 145 | 1.00 | 160 | 0x9A60 | 0x0 |

Unmatched members with >= 20% window hits (partial similarity): none

## ubuntu_noble_gcc13.2.rel1-2_libgcc

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| _udivmoddi4.o | 700 | 0 | 685 | 685 | 1.00 | 700 | 0x8188 | 0x0 |
| _aeabi_uldivmod.o | 48 | 8 | 5 | 5 | 1.00 | 20 | 0x8158 | 0x0 |

Unmatched members with >= 20% window hits (partial similarity): _aeabi_uldivmod.o (100%)

## ubuntu_gcc14.2.rel1-1_libgcc

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| _aeabi_uldivmod.o | 48 | 8 | 5 | 5 | 1.00 | 20 | 0x8158 | 0x0 |

Unmatched members with >= 20% window hits (partial similarity): _aeabi_uldivmod.o (100%)

## qmk_toolchain_gcc15.2_libgcc

Matched members (dump offset of the longest run):

| member | .text B | reloc B | windows | hits | frac | longest run | dump off | member off |
|---|---|---|---|---|---|---|---|---|
| _aeabi_uldivmod.o | 48 | 8 | 5 | 5 | 1.00 | 20 | 0x8158 | 0x0 |

Unmatched members with >= 20% window hits (partial similarity): _aeabi_uldivmod.o (100%)

