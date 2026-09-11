#!/usr/bin/env python3
"""Extract and classify strings / string-like data from a QMK flash dump.

Writes strings_classified.md (+ .json) into --out.  Stdlib only; reuses the block classifier
from dump_triage.py (same directory) to tag every hit with the class of the block it sits in
(code / data / ascii / ptr / sparse) so that opcode-garbage "strings" inside code can be
separated from real .rodata literals.

Usage:
  python3 tools/strings_triage.py keychron_v10max_backup/dump_a.bin --out keychron_v10max_backup \
      --exclude 0x169B8:0x16EC8 --rodata-start 0x16700

Sections:
  USB descriptor strings (UTF-16LE, with/without a bLength/0x03 header), build date, toolchain
  paths, ChibiOS/QMK/newlib identifiers, Keychron/wireless identifiers, printf-style formats,
  lookup tables (monotone byte runs that happen to be printable), SEND_STRING/leader/macro text
  candidates (every remaining printable run, scored), SEND_STRING control-code sequences
  (SS_QMK_PREFIX=1 followed by SS_TAP/DOWN/UP/DELAY_CODE 1..4), and u16 keycode-like arrays
  terminated by 0x0000 outside the keymap table (combo/tap-dance style key lists).
"""
import argparse, json, os, re, struct, sys, datetime

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dump_triage import classify_blocks  # noqa: E402

PRINTABLE = set(range(0x20, 0x7F)) | {9, 10, 13}
DATE_RE = re.compile(r'\d{4}-\d{2}-\d{2}-\d{2}:\d{2}:\d{2}')
FMT_RE = re.compile(r'%[-+ #0]*\d*(?:\.\d+)?(?:hh|h|ll|l|z)?[diouxXcspeEfgG%]')
TOOLCHAIN_KW = ('newlib', 'libc/', 'gcc', 'GCC', 'crosstool', 'xpack', 'xPack', 'Arm GNU', 'homebrew', 'jenkins',
                '/src/', 'clang', 'LLVM', 'GNU')
CHIBIOS_QMK_KW = ('wear_leveling', 'DMA failure', 'REENT', 'assertion', 'ChibiOS', 'chSys', 'panic', 'QMK', 'qmk',
                  'eeprom', 'EEPROM', 'Invalid', 'failed', 'succeeded')
KEYCHRON_KW = ('keychron', 'lkbt', 'ckbt', 'bluetooth', 'factory', '2.4g', 'p2p4g', 'wireless', 'pairing',
               'battery', 'dongle', 'BT_', 'firmware', 'version')
KC_NAMES = {0x00: 'KC_NO', 0x01: 'KC_TRNS', 0x28: 'KC_ENT', 0x29: 'KC_ESC', 0x2A: 'KC_BSPC', 0x2B: 'KC_TAB', 0x2C: 'KC_SPC',
            0x2D: 'KC_MINS', 0x2E: 'KC_EQL', 0x2F: 'KC_LBRC', 0x30: 'KC_RBRC', 0x31: 'KC_BSLS', 0x32: 'KC_NUHS',
            0x33: 'KC_SCLN', 0x34: 'KC_QUOT', 0x35: 'KC_GRV', 0x36: 'KC_COMM', 0x37: 'KC_DOT', 0x38: 'KC_SLSH',
            0x39: 'KC_CAPS', 0x46: 'KC_PSCR', 0x47: 'KC_SCRL', 0x48: 'KC_PAUS', 0x49: 'KC_INS', 0x4A: 'KC_HOME',
            0x4B: 'KC_PGUP', 0x4C: 'KC_DEL', 0x4D: 'KC_END', 0x4E: 'KC_PGDN', 0x4F: 'KC_RGHT', 0x50: 'KC_LEFT',
            0x51: 'KC_DOWN', 0x52: 'KC_UP', 0x53: 'KC_NUM', 0xE0: 'KC_LCTL', 0xE1: 'KC_LSFT', 0xE2: 'KC_LALT',
            0xE3: 'KC_LGUI', 0xE4: 'KC_RCTL', 0xE5: 'KC_RSFT', 0xE6: 'KC_RALT', 0xE7: 'KC_RGUI'}
for _i in range(26):
    KC_NAMES[0x04 + _i] = 'KC_' + chr(ord('A') + _i)
for _i in range(10):
    KC_NAMES[0x1E + _i] = 'KC_' + '1234567890'[_i]
for _i in range(12):
    KC_NAMES[0x3A + _i] = 'KC_F%d' % (_i + 1)
KC_NAMES.update({0xA5: 'KC_PWR', 0xA6: 'KC_SLEP', 0xA7: 'KC_WAKE', 0xA8: 'KC_MUTE', 0xA9: 'KC_VOLU', 0xAA: 'KC_VOLD',
                 0xAB: 'KC_MNXT', 0xAC: 'KC_MPRV', 0xAD: 'KC_MSTP', 0xAE: 'KC_MPLY', 0xAF: 'KC_MSEL', 0xB0: 'KC_EJCT',
                 0xBB: 'KC_MFFD', 0xBC: 'KC_MRWD', 0xBD: 'KC_BRIU', 0xBE: 'KC_BRID', 0xC1: 'KC_MCTL', 0xC2: 'KC_LPAD',
                 0x7820: 'RGB_TOG', 0x7821: 'RGB_MOD', 0x7822: 'RGB_RMOD', 0x7823: 'RGB_HUI', 0x7824: 'RGB_HUD',
                 0x7825: 'RGB_SAI', 0x7826: 'RGB_SAD', 0x7827: 'RGB_VAI', 0x7828: 'RGB_VAD', 0x7829: 'RGB_SPI',
                 0x782A: 'RGB_SPD', 0x7C00: 'QK_BOOT', 0x7C58: 'QK_LEAD', 0x7013: 'NK_TOGG',
                 0x7E04: 'KC_MCTRL', 0x7E05: 'KC_LNPAD', 0x7E0F: 'BAT_LVL', 0x7E40: 'QK_USER_0', 0x7E41: 'QK_USER_1'})
HID_ITEMS = {0x05, 0x06, 0x09, 0x0A, 0x15, 0x16, 0x19, 0x1A, 0x25, 0x26, 0x29, 0x2A, 0x35, 0x45, 0x55, 0x65, 0x75,
             0x81, 0x85, 0x91, 0x95, 0xA1, 0xB1, 0xC0}


def keylist_note(d, off, count):
    raw = d[off:off + 2 * count]
    if all(b in PRINTABLE for b in raw):
        return 'ASCII text read as u16, not keycodes'
    if sum(1 for b in raw[0::2] if b in HID_ITEMS) >= 0.6 * count:
        return 'USB HID report-descriptor items (0x05 usage page, 0x95 count, 0x75 size, 0x81 input, 0xC0 end) read as u16'
    if raw[:2] in (b'\x22\x03', b'\x12\x03') or (raw[1] == 3 and raw[0] == 2 * count):
        return 'USB string descriptor header + UTF-16 read as u16'
    return ''


def kc_name(v):
    if v in KC_NAMES:
        return KC_NAMES[v]
    if 0x0100 <= v <= 0x1FFF and (v & 0xFF) in KC_NAMES:
        mods = v >> 8
        names = [n for b, n in ((1, 'LCTL'), (2, 'LSFT'), (4, 'LALT'), (8, 'LGUI')) if mods & b]
        if mods & 0x10:
            names = ['R' + n[1:] for n in names]
        return '%s(%s)' % ('|'.join(names) or 'MOD?', KC_NAMES[v & 0xFF])
    return '0x%04X' % v


def plausible_kc(v):
    """Keycode ranges worth listing in a key-list scan (QMK keycode spec 0.0.3 ranges)."""
    if 0x0004 <= v <= 0x00E7 and (v <= 0xA4 or v >= 0xE0 or 0xA5 <= v <= 0xDF):
        return True
    if 0x0100 <= v <= 0x1FFF and 4 <= (v & 0xFF) <= 0xE7:      # modified basic keycode
        return True
    return (0x4000 <= v <= 0x4FFF or 0x5000 <= v <= 0x52FF or 0x5700 <= v <= 0x57FF   # LT, layer ops, TD
            or 0x7000 <= v <= 0x70FF or 0x7700 <= v <= 0x77FF or 0x7800 <= v <= 0x78FF  # magic, macros, rgb
            or 0x7C00 <= v <= 0x7FFF)                                                  # quantum/kb/user


def ascii_runs(d, minlen):
    out, i, n = [], 0, len(d)
    while i < n:
        if d[i] in PRINTABLE:
            j = i
            while j < n and d[j] in PRINTABLE:
                j += 1
            if j - i >= minlen:
                out.append({'offset': i, 'len': j - i, 'text': d[i:j].decode('ascii'),
                            'nul_terminated': j < n and d[j] == 0})
            i = j
        else:
            i += 1
    return out


def utf16_runs(d, minchars):
    out, i, n = [], 0, len(d)
    while i + 1 < n:
        if d[i] in PRINTABLE and d[i + 1] == 0:
            j = i
            while j + 1 < n and d[j] in PRINTABLE and d[j + 1] == 0:
                j += 2
            nch = (j - i) // 2
            if nch >= minchars:
                hdr = d[i - 2:i] if i >= 2 else b''
                hdr_ok = len(hdr) == 2 and hdr[1] == 0x03 and hdr[0] == 2 + 2 * nch
                out.append({'offset': i, 'chars': nch, 'text': d[i:j:2].decode('ascii'),
                            'descriptor_header': hdr.hex(), 'header_ok': hdr_ok})
            i = j if j > i else i + 1
        else:
            i += 1
    return out


def text_score(t):
    letters = sum(1 for c in t if c.isalpha() or c in " ,.'-")
    vowel_word = bool(re.search(r'[A-Za-z]*[aeiouAEIOU][A-Za-z]{2,}|[A-Za-z]{2,}[aeiouAEIOU][A-Za-z]*', t))
    lower_ratio = sum(1 for c in t if c.islower() or c == ' ') / len(t)
    return round(0.5 * letters / len(t) + 0.3 * vowel_word + 0.2 * lower_ratio, 2)


def monotone(t):
    b = t.encode('ascii')
    diffs = [b[i + 1] - b[i] for i in range(len(b) - 1)]
    if all(x >= 0 for x in diffs) and len(b) >= 6:
        return 'non-decreasing byte run (LUT such as CIE1931/gamma curve)'
    if len(set(diffs)) == 1 and len(b) >= 6:
        return 'arithmetic progression step %d' % diffs[0]
    return None


def classify(run, rodata_start, block_cls):
    t = run['text']
    if DATE_RE.fullmatch(t.strip()):
        return 'build-date'
    if any(k in t for k in TOOLCHAIN_KW) and ('/' in t or 'GCC' in t or 'GNU' in t):
        return 'toolchain-path'
    if FMT_RE.search(t):
        return 'printf-format'
    if any(k in t for k in CHIBIOS_QMK_KW):
        return 'chibios-qmk-newlib'
    if any(k.lower() in t.lower() for k in KEYCHRON_KW):
        return 'keychron-wireless'
    if re.fullmatch(r'0123456789[a-zA-Z]*|0123456789ABCDEF|efgEFG|[0-9A-Fa-f]{16}', t):
        return 'ctype-digit-table'
    if monotone(t):
        return 'lookup-table'
    if run['offset'] >= rodata_start or block_cls in ('data', 'ascii', 'ptr', 'sparse'):
        return 'text-candidate'
    return 'code-garbage'


def send_string_sequences(d, lo, hi):
    """Find runs of SS_QMK_PREFIX(1) + {TAP=1,DOWN=2,UP=3,DELAY=4} + keycode, mixed with ASCII, NUL terminated."""
    out, i = [], lo
    while i < hi - 2:
        if d[i] == 1 and 1 <= d[i + 1] <= 4:
            j, parts, ctl = i, [], 0
            while j < hi and d[j] != 0:
                if d[j] == 1 and j + 2 < hi and 1 <= d[j + 1] <= 4:
                    code, kc = d[j + 1], d[j + 2]
                    if code == 4:
                        k = j + 2
                        digits = ''
                        while k < hi and 0x30 <= d[k] <= 0x39:
                            digits += chr(d[k])
                            k += 1
                        if k < hi and d[k] == ord('|'):
                            parts.append('SS_DELAY(%s)' % digits)
                            j = k + 1
                            ctl += 1
                            continue
                        break
                    if not (4 <= kc <= 0xE7):
                        break
                    parts.append('SS_%s(%s)' % ({1: 'TAP', 2: 'DOWN', 3: 'UP'}[code], kc_name(kc)))
                    ctl += 1
                    j += 3
                elif d[j] in PRINTABLE:
                    parts.append(repr(chr(d[j])))
                    j += 1
                else:
                    break
            if ctl >= 1 and j < hi and d[j] == 0 and len(parts) >= 2:
                out.append({'offset': i, 'end': j, 'decoded': ' '.join(parts), 'control_codes': ctl})
                i = j
        i += 1
    return out


def u16_key_lists(d, exclude, block_classes, block):
    """Maximal 2-byte-aligned runs of >=2 plausible keycodes terminated by 0x0000."""
    out, i, n = [], 0, len(d) - 1
    while i < n:
        v = struct.unpack_from('<H', d, i)[0]
        if plausible_kc(v):
            j, vals = i, []
            while j < n:
                w = struct.unpack_from('<H', d, j)[0]
                if not plausible_kc(w):
                    break
                vals.append(w)
                j += 2
            term = j < n and struct.unpack_from('<H', d, j)[0] == 0
            if len(vals) >= 2 and term and not any(lo <= i < hi for lo, hi in exclude):
                basic = sum(1 for v in vals if v <= 0xE7)
                out.append({'offset': i, 'count': len(vals), 'values': ['0x%04X' % v for v in vals],
                            'names': [kc_name(v) for v in vals], 'basic_count': basic,
                            'block_class': block_classes[i // block], 'note': keylist_note(d, i, len(vals))})
            i = j + 2
        else:
            i += 2
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('dump')
    ap.add_argument('--out', default='.')
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--min-ascii', type=int, default=6)
    ap.add_argument('--min-utf16', type=int, default=4)
    ap.add_argument('--rodata-start', type=lambda x: int(x, 0), default=None,
                    help='file offset where .rodata starts (default: end of last code block from dump_triage)')
    ap.add_argument('--exclude', action='append', default=[], help='start:end file ranges to skip in the key-list scan')
    ap.add_argument('--note', action='append', default=[], help='start:end:text  annotation attached to key lists overlapping the range')
    a = ap.parse_args()
    d = open(a.dump, 'rb').read()
    block = 256
    classes, _ = classify_blocks(d, a.base, block)
    img_end = max(i for i in range(len(d)) if d[i] != 0xFF) + 1
    if a.rodata_start is None:
        code_blocks = [i for i, c in enumerate(classes) if c == 'code']
        a.rodata_start = (code_blocks[-1] + 1) * block if code_blocks else 0
    exclude = [tuple(int(x, 0) for x in e.split(':')) for e in a.exclude]

    runs = ascii_runs(d, a.min_ascii)
    for r in runs:
        r['block_class'] = classes[r['offset'] // block]
        r['category'] = classify(r, a.rodata_start, r['block_class'])
        r['text_score'] = text_score(r['text'])
        r['flash'] = a.base + r['offset']
    short_rodata = [r for r in ascii_runs(d[:img_end], 3) if r['offset'] >= a.rodata_start and r['len'] < a.min_ascii]
    u16 = utf16_runs(d, a.min_utf16)
    for u in u16:
        u['flash'] = a.base + u['offset']
        u['block_class'] = classes[u['offset'] // block]
        u['in_excluded'] = any(lo <= u['offset'] < hi for lo, hi in exclude)
    if a.rodata_start:
        for r in runs:
            pass
    ss = send_string_sequences(d, 0, img_end)
    for s in ss:
        s['flash'] = a.base + s['offset']
        s['block_class'] = classes[s['offset'] // block]
    keylists = u16_key_lists(d[:img_end], exclude, classes, block)
    notes = [(int(x.split(':', 2)[0], 0), int(x.split(':', 2)[1], 0), x.split(':', 2)[2]) for x in a.note]
    for k in keylists:
        k['flash'] = a.base + k['offset']
        for lo, hi, text in notes:
            if lo < k['offset'] + 2 * k['count'] and hi > k['offset']:
                k['note'] = (k.get('note') + '; ' if k.get('note') else '') + text

    res = {'file': os.path.abspath(a.dump), 'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
           'rodata_start': a.rodata_start, 'image_end': img_end, 'exclude': exclude,
           'ascii_runs': runs, 'short_rodata_runs': short_rodata, 'utf16_runs': u16,
           'send_string_sequences': ss, 'u16_key_lists': keylists}
    os.makedirs(a.out, exist_ok=True)
    json.dump(res, open(os.path.join(a.out, 'strings_classified.json'), 'w'), indent=1)
    open(os.path.join(a.out, 'strings_classified.md'), 'w').write(render(res, a))
    print('wrote strings_classified.md/.json;', len(runs), 'ascii runs,', len(u16), 'utf16 runs,',
          len(ss), 'send_string seqs,', len(keylists), 'u16 key lists')


def md_escape(t):
    return t.replace('|', '\\|').replace('`', '\\`').replace('\n', '\\n').replace('\r', '\\r').replace('\t', '\\t')


def render(res, a):
    L = ['# Strings triage: %s\n' % os.path.basename(res['file']),
         'Generated %s by tools/strings_triage.py. ASCII runs >= %d printable bytes; UTF-16LE runs >= %d chars. '
         '`.rodata` taken to start at file 0x%X (--rodata-start if given, else end of the last code block from dump_triage heuristics); '
         'key-list scan excludes %s.\n' % (res['generated'], a.min_ascii, a.min_utf16, res['rodata_start'],
                                           ', '.join('0x%X..0x%X' % e for e in res['exclude']) or 'nothing')]
    runs = res['ascii_runs']
    cats = {}
    for r in runs:
        cats.setdefault(r['category'], []).append(r)
    L.append('## Summary\n')
    L.append('| category | count |\n|---|---|')
    for c in ('usb-descriptor(utf16)', 'build-date', 'toolchain-path', 'chibios-qmk-newlib', 'keychron-wireless',
              'printf-format', 'ctype-digit-table', 'lookup-table', 'text-candidate', 'code-garbage'):
        n = len(res['utf16_runs']) if c.startswith('usb') else len(cats.get(c, []))
        L.append('| %s | %d |' % (c, n))
    L.append('| SEND_STRING control-code sequences | %d |' % len(res['send_string_sequences']))
    L.append('| u16 keycode lists (0-terminated, outside keymap) | %d |\n' % len(res['u16_key_lists']))

    L.append('## UTF-16LE strings (USB string descriptors)\n')
    L.append('A valid USB string descriptor is preceded by `bLength, 0x03` with bLength = 2 + 2*chars.\n')
    L.append('| file off | flash | block | header bytes | header ok | chars | text |\n|---|---|---|---|---|---|---|')
    for u in res['utf16_runs']:
        L.append('| 0x%X | 0x%08X | %s | %s | %s | %d | `%s` |' % (u['offset'], u['flash'],
                                                                   u['block_class'] + (' (inside excluded keymap table: u16 keycodes, not text)' if u.get('in_excluded') else ''),
                                                                   u['descriptor_header'], 'yes' if u['header_ok'] else 'no', u['chars'], md_escape(u['text'])))
    L.append('')

    def table(cat, title, note=''):
        L.append('## %s\n' % title)
        if note:
            L.append(note + '\n')
        rows = cats.get(cat, [])
        if not rows:
            L.append('_none found_\n')
            return
        L.append('| file off | flash | block | len | NUL-term | text |\n|---|---|---|---|---|---|')
        for r in rows:
            L.append('| 0x%X | 0x%08X | %s | %d | %s | `%s` |' % (r['offset'], r['flash'], r['block_class'], r['len'],
                                                                'y' if r['nul_terminated'] else 'n', md_escape(r['text'])))
        L.append('')

    table('build-date', 'Build date')
    table('toolchain-path', 'Toolchain / newlib paths')
    table('chibios-qmk-newlib', 'ChibiOS / QMK / newlib identifiers')
    table('printf-format', 'printf-style format strings')
    table('keychron-wireless', 'Keychron / wireless identifiers (lkbt51, bluetooth, factory test, ...)')
    table('ctype-digit-table', 'Digit / ctype tables (newlib)')
    table('lookup-table', 'Lookup tables that happen to be printable (monotone byte runs)',
          'Non-decreasing byte runs through 0x20..0x7E are slices of u8 curves (CIE1931 / gamma / sine tables), not text.')

    L.append('## SEND_STRING / leader / macro text candidates\n')
    L.append('Every remaining printable run. `text_score` = 0.5*letters/spaces fraction + 0.3*(has a vowel word) + 0.2*lower-case ratio; '
             'real SEND_STRING literals in .rodata score >= ~0.6 and are NUL-terminated. Runs whose block is classified `code` are '
             'almost always Thumb opcode bytes (e.g. `pGpGpG` = repeated `bx lr` 0x4770).\n')
    L.append('### In .rodata (file >= 0x%X) or data-classified blocks\n' % res['rodata_start'])
    rows = [r for r in cats.get('text-candidate', [])]
    if rows:
        L.append('| file off | flash | block | len | NUL-term | score | text |\n|---|---|---|---|---|---|---|')
        for r in rows:
            L.append('| 0x%X | 0x%08X | %s | %d | %s | %.2f | `%s` |' % (r['offset'], r['flash'], r['block_class'], r['len'],
                                                                       'y' if r['nul_terminated'] else 'n', r['text_score'], md_escape(r['text'])))
    else:
        L.append('_none_')
    L.append('')
    L.append('### Short (3..%d byte) printable runs in .rodata\n' % (a.min_ascii - 1))
    L.append('Listed so that very short macro text (e.g. SEND_STRING("hi")) cannot hide below the length cut-off.\n')
    sr = res['short_rodata_runs']
    if sr:
        L.append('| file off | len | NUL-term | text |\n|---|---|---|---|')
        for r in sr:
            L.append('| 0x%X | %d | %s | `%s` |' % (r['offset'], r['len'], 'y' if r['nul_terminated'] else 'n', md_escape(r['text'])))
    else:
        L.append('_none_')
    L.append('')
    L.append('### In code-classified blocks (low confidence, opcode bytes), sorted by score\n')
    rows = sorted(cats.get('code-garbage', []), key=lambda r: -r['text_score'])
    L.append('| file off | flash | len | score | text |\n|---|---|---|---|---|')
    for r in rows:
        L.append('| 0x%X | 0x%08X | %d | %.2f | `%s` |' % (r['offset'], r['flash'], r['len'], r['text_score'], md_escape(r['text'])))
    L.append('')

    L.append('## SEND_STRING control-code sequences\n')
    L.append('Pattern: SS_QMK_PREFIX (0x01) then SS_TAP_CODE/SS_DOWN_CODE/SS_UP_CODE (0x01/0x02/0x03) + 8-bit keycode, or SS_DELAY_CODE (0x04) + digits + `|`; '
             'optionally interleaved with ASCII; NUL-terminated (quantum/send_string/send_string_keycodes.h).\n')
    if res['send_string_sequences']:
        L.append('| file off | flash | block | ctl codes | decoded |\n|---|---|---|---|---|')
        for s in res['send_string_sequences']:
            L.append('| 0x%X | 0x%08X | %s | %d | `%s` |' % (s['offset'], s['flash'], s['block_class'], s['control_codes'], md_escape(s['decoded'])))
    else:
        L.append('_none found anywhere in the image_')
    L.append('')

    L.append('## u16 keycode-like arrays terminated by 0x0000 (outside the keymap table)\n')
    L.append('Combo key lists (`{KC_A, KC_B, COMBO_END}`), tap-dance pairs and similar are 2-byte aligned u16 arrays of plausible keycodes '
             'ending in 0. Inside code blocks, Thumb halfwords (e.g. `0x2000 movs`, `0x4770 bx lr`) also satisfy the filter, so only '
             'data/ptr/sparse-block hits are meaningful; code-block hits are listed for completeness.\n')
    kl = res['u16_key_lists']
    good = [k for k in kl if k['block_class'] != 'code']
    bad = [k for k in kl if k['block_class'] == 'code']
    L.append('### In data-classified blocks (%d)\n' % len(good))
    if good:
        L.append('| file off | flash | block | n | values | decoded | note |\n|---|---|---|---|---|---|---|')
        for k in good:
            L.append('| 0x%X | 0x%08X | %s | %d | %s | %s | %s |' % (k['offset'], k['flash'], k['block_class'], k['count'],
                                                                   ' '.join(k['values']), ' '.join(k['names']), k.get('note', '')))
    else:
        L.append('_none_')
    L.append('')
    L.append('### In code-classified blocks (%d, low confidence; only lists with >= 3 entries shown, all are in the JSON)\n' % len(bad))
    shown = [k for k in bad if k['count'] >= 3]
    if shown:
        L.append('| file off | flash | n | values | decoded |\n|---|---|---|---|---|')
        for k in shown:
            L.append('| 0x%X | 0x%08X | %d | %s | %s |' % (k['offset'], k['flash'], k['count'], ' '.join(k['values']), ' '.join(k['names'])))
    else:
        L.append('_none_')
    L.append('')
    return '\n'.join(L) + '\n'


if __name__ == '__main__':
    main()
