#!/usr/bin/env python3
"""Verifier tool (compile-and-compare) for custom_code/rgb_hooks.c.

Compiles rgb_matrix_indicators_advanced_user source-spelling variants with the ORIGINAL
compiler major (xPack GCC 13.2.1 20231009, same code generator as Ubuntu's 13.2.rel1) and
QMK's exact in-tree CFLAGS, then compares the masked instruction stream (bl/b.w immediates and
ldr-literal offsets masked) with dump_a.bin 0x0800CF74..0x0800CFFC.

Result (2026-09-10): the reconstruction as written (bool flags, cases 1..5) reproduces the
control flow but NOT the dump's tbb table {18,03,14,1B,1E} nor the 'ldrb;ldrb;orrs;beq' white
test. Exactly-matching spellings: flags typed uint8_t AND case order (2,3,1,4,5) -- with any of
'|'/'||', either operand order, and switch / if-else chain (12 exact matches out of 2880).
Dropping the same source into a scratch keymap in /Users/dexter/code/qmk-keychron-ref and
building with gcc 13 gave masked-identical code for keyboard_post_init_user,
rgb_matrix_indicators_advanced_user, handle_oneshots, both one-shot thunks,
eeconfig_update_rgb_matrix_default (0x41) and rgb_matrix_mode, and .bss order caps<gui<shift
when the flags are DECLARED shift_active, gui_active, caps_active (gcc emits statics in reverse).
"""
import itertools, os, struct, subprocess, sys, tempfile

GCC_DIR = '/Users/dexter/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin'
GCC = os.path.join(GCC_DIR, 'arm-none-eabi-gcc')
OBJCOPY = os.path.join(GCC_DIR, 'arm-none-eabi-objcopy')
FLAGS = ('-mcpu=cortex-m4 -mthumb -mno-thumb-interwork -mno-unaligned-access -mfloat-abi=hard '
         '-mfpu=fpv4-sp-d16 -fsingle-precision-constant -fomit-frame-pointer -ffunction-sections '
         '-fdata-sections -fno-common -fshort-wchar -fno-builtin-printf -ggdb -Os -Wall '
         '-Wstrict-prototypes -std=gnu11 -fcommon').split()
DUMP = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'dump_a.bin')
FUNC_START, FUNC_CODE_LEN = 0xCF74, 0x88   # code only; literal pool follows at 0xCFFC

COL = {1: 'RGB_GREEN', 2: 'RGB_BLUE', 3: 'RGB_ORANGE', 4: 'RGB_TEAL', 5: 'RGB_RED'}
HDR = '''#include <stdint.h>
#include <stdbool.h>
extern void rgb_matrix_set_color(int index, uint8_t r, uint8_t g, uint8_t b);
extern uint8_t biton16(uint16_t);
extern uint16_t layer_state, default_layer_state;
#define get_highest_layer(s) biton16(s)
#define RGB_GREEN 0x00,0xFF,0x00
#define RGB_BLUE 0x00,0x00,0xFF
#define RGB_ORANGE 0xFF,0x80,0x00
#define RGB_TEAL 0x00,0x80,0x80
#define RGB_RED 0xFF,0x00,0x00
#define RGB_YELLOW 0xFF,0xFF,0x00
#define RGB_WHITE 0xFF,0xFF,0xFF
static %(T)s caps_active, gui_active, shift_active;
void writer(uint8_t m) { caps_active = m & 1; gui_active = m & 2; shift_active = m & 4; }
'''


def mask(b):
    hw = list(struct.unpack('<%dH' % (len(b) // 2), b[:len(b) // 2 * 2]))
    i = 0
    while i < len(hw):
        h = hw[i]
        if 0xF000 <= h <= 0xF7FF and i + 1 < len(hw) and (hw[i + 1] & 0x9000) == 0x9000:  # bl / b.w
            hw[i], hw[i + 1] = 0xF000, 0xF800
            i += 2
            continue
        if 0x4800 <= h <= 0x4FFF:            # ldr rX,[pc,#imm]
            hw[i] = h & 0xFF00
        if h == 0xF8DF and i + 1 < len(hw):  # ldr.w rX,[pc,#imm]
            hw[i + 1] &= 0xF000
            i += 2
            continue
        i += 1
    return hw


def body(form, order, white):
    if form == 'switch':
        s = '        switch (get_highest_layer(layer_state | default_layer_state)) {\n'
        s += ''.join('            case %d: rgb_matrix_set_color(i, %s); break;\n' % (c, COL[c]) for c in order)
        s += '            default: break;\n        }\n'
    else:
        s = '        uint8_t layer = get_highest_layer(layer_state | default_layer_state);\n'
        for k, c in enumerate(order):
            s += '        %sif (layer == %d) { rgb_matrix_set_color(i, %s); }\n' % ('' if k == 0 else 'else ', c, COL[c])
    return s + ('        if (gui_active) {\n            rgb_matrix_set_color(i, RGB_YELLOW);\n'
                '        } else if (%s) {\n            rgb_matrix_set_color(i, RGB_WHITE);\n        }\n' % white)


def source(T, form, order, white):
    return (HDR % {'T': T} + 'bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {\n'
            '    for (uint8_t i = led_min; i < led_max; i++) {\n' + body(form, order, white) +
            '    }\n    return false;\n}\n')


def compile_code(text, workdir):
    c = os.path.join(workdir, 'v.c'); o = os.path.join(workdir, 'v.o'); b = os.path.join(workdir, 'v.bin')
    open(c, 'w').write(text)
    r = subprocess.run([GCC, '-c'] + FLAGS + ['-o', o, c], capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError(r.stderr)
    subprocess.run([OBJCOPY, '-O', 'binary', '-j', '.text.rgb_matrix_indicators_advanced_user', o, b], check=True)
    return open(b, 'rb').read()


def main():
    dump = open(DUMP, 'rb').read()
    want = mask(dump[FUNC_START:FUNC_START + FUNC_CODE_LEN])
    whites = ['shift_active || caps_active', 'shift_active | caps_active',
              'caps_active || shift_active', 'caps_active | shift_active']
    exact = []
    with tempfile.TemporaryDirectory() as wd:
        for T in ('bool', 'uint8_t'):
            for white in whites:
                for form in ('switch', 'ifchain'):
                    for order in itertools.permutations([1, 2, 3, 4, 5]):
                        code = compile_code(source(T, form, list(order), white), wd)
                        if len(code) >= FUNC_CODE_LEN and mask(code[:FUNC_CODE_LEN]) == want:
                            exact.append((T, white, form, order))
                            print('EXACT:', T, white, form, order)
    print('exact matches:', len(exact))
    return 0 if exact else 1


if __name__ == '__main__':
    sys.exit(main())
