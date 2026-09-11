#!/usr/bin/env python3
"""Triage a raw STM32 flash dump: hashes, vector-table sanity, 256-byte block classification,
image end and a region list.  Writes triage.json and triage.md into --out.

Usage (stdlib only):
  python3 tools/dump_triage.py keychron_v10max_backup/dump_a.bin --out keychron_v10max_backup \
      --annotate 0x4000:0x5000:eeprom_wear_leveling_backing --annotate 0x169B8:0x16EC8:keymaps[]

Heuristics (deliberately simple, see block_metrics/classify_block):
  erased  = every byte 0xFF                  zero = every byte 0x00
  ascii   = >=60% printable bytes            ptr  = >=20% of aligned words point into flash/SRAM
  code    = >=50% of Thumb decode units hit an opcode marker: 16-bit push/pop/bx lr/mov/ldr-lit/
            movs/cmp imm/b<c>/b/ldr-str imm/ldrh-strh/cbz/uxt/adr/it, or a well-formed 32-bit
            Thumb-2 instruction (first halfword 0xE800..0xFFFF, weight 0.8); and <60% printable
  sparse  = >=50% zero bytes (e.g. keymap tails)   mixed = partly 0xFF (image tail)
  data    = anything else with content
"""
import argparse, collections, datetime, hashlib, json, math, os, re, struct

BLOCK_DEFAULT = 256
# Cortex-M core exceptions (vector index) and STM32F401 NVIC IRQ numbers (vector index - 16).
CORE = {1: 'Reset', 2: 'NMI', 3: 'HardFault', 4: 'MemManage', 5: 'BusFault', 6: 'UsageFault',
        7: 'rsvd7', 8: 'rsvd8', 9: 'rsvd9', 10: 'rsvd10', 11: 'SVCall', 12: 'DebugMon', 13: 'rsvd13',
        14: 'PendSV', 15: 'SysTick'}
STM32F401_IRQ = {0: 'WWDG', 1: 'PVD', 2: 'TAMP_STAMP', 3: 'RTC_WKUP', 4: 'FLASH', 5: 'RCC', 6: 'EXTI0', 7: 'EXTI1',
                 8: 'EXTI2', 9: 'EXTI3', 10: 'EXTI4', 11: 'DMA1_Stream0', 12: 'DMA1_Stream1', 13: 'DMA1_Stream2',
                 14: 'DMA1_Stream3', 15: 'DMA1_Stream4', 16: 'DMA1_Stream5', 17: 'DMA1_Stream6', 18: 'ADC',
                 23: 'EXTI9_5', 24: 'TIM1_BRK_TIM9', 25: 'TIM1_UP_TIM10', 26: 'TIM1_TRG_COM_TIM11', 27: 'TIM1_CC',
                 28: 'TIM2', 29: 'TIM3', 30: 'TIM4', 31: 'I2C1_EV', 32: 'I2C1_ER', 33: 'I2C2_EV', 34: 'I2C2_ER',
                 35: 'SPI1', 36: 'SPI2', 37: 'USART1', 38: 'USART2', 40: 'EXTI15_10', 41: 'RTC_Alarm',
                 42: 'OTG_FS_WKUP', 47: 'DMA1_Stream7', 49: 'SDIO', 50: 'TIM5', 51: 'SPI3', 56: 'DMA2_Stream0',
                 57: 'DMA2_Stream1', 58: 'DMA2_Stream2', 59: 'DMA2_Stream3', 60: 'DMA2_Stream4', 67: 'OTG_FS',
                 68: 'DMA2_Stream5', 69: 'DMA2_Stream6', 70: 'DMA2_Stream7', 71: 'USART6', 72: 'I2C3_EV',
                 73: 'I2C3_ER', 81: 'FPU', 84: 'SPI4'}
LEGEND = {'erased': '.', 'zero': '0', 'code': 'C', 'data': 'D', 'ascii': 'A', 'ptr': 'P',
          'mixed': 'm', 'sparse': 's', 'vectors': 'V'}


def sha256(b):
    return hashlib.sha256(b).hexdigest()


def image_end(d):
    """Offset one past the last byte that is not 0xFF (erased flash)."""
    i = len(d)
    while i > 0 and d[i - 1] == 0xFF:
        i -= 1
    return i


def content_end(d):
    """Offset one past the last byte that is neither 0xFF nor 0x00."""
    i = len(d)
    while i > 0 and d[i - 1] in (0xFF, 0x00):
        i -= 1
    return i


def analyze_vectors(d, base, img_end, sram):
    nwords = min(len(d), 0x400) // 4
    words = struct.unpack_from('<%dI' % nwords, d, 0)
    sp, reset = words[0], words[1]
    last_nz = max(i for i, w in enumerate(words) if w)
    n = last_nz + 1

    def plausible(w):
        return bool(w & 1) and base <= w < base + img_end

    default_handler, default_count = collections.Counter(words[1:n]).most_common(1)[0]
    entries = []
    for i in range(1, n):
        w = words[i]
        name = CORE.get(i) if i < 16 else 'IRQ%d_%s' % (i - 16, STM32F401_IRQ.get(i - 16, 'rsvd'))
        entries.append({'index': i, 'offset': i * 4, 'value': w, 'name': name,
                        'plausible': plausible(w), 'is_default': w == default_handler})
    reset_off = (reset & ~1) - base
    return {
        'sp': sp, 'sp_ok': sram[0] < sp <= sram[1] and sp % 8 == 0,
        'reset': reset, 'reset_ok': plausible(reset), 'reset_file_offset': reset_off,
        'reset_first_bytes': d[reset_off:reset_off + 8].hex() if 0 <= reset_off < len(d) else None,
        'entries_total': n, 'table_bytes': n * 4,
        'entries_plausible': sum(1 for e in entries if e['plausible']),
        'entries_zero': sum(1 for e in entries if e['value'] == 0),
        'entries_bad': [e for e in entries if not e['plausible'] and e['value'] != 0],
        'default_handler': default_handler, 'default_handler_count': default_count,
        'populated': [e for e in entries if not e['is_default']],
        'first_nonzero_after_table': next((i for i in range(n * 4, min(len(d), 0x8000)) if d[i]), None),
    }


def block_metrics(b, base, img_end, sram):
    n = len(b)
    c = collections.Counter(b)
    ent = -sum(v / n * math.log2(v / n) for v in c.values())
    printable = sum(v for k, v in c.items() if 0x20 <= k < 0x7F or k in (9, 10, 13)) / n
    hw = struct.unpack_from('<%dH' % (n // 2), b)
    markers = units = wide = 0
    i = 0
    while i < len(hw):
        h = hw[i]
        if (h & 0xF800) in (0xE800, 0xF000, 0xF800) and i + 1 < len(hw):   # 32-bit Thumb-2
            h2 = hw[i + 1]
            if (h & 0xF800) == 0xF000 and (h2 & 0xD000) == 0xD000:          # BL / B.W
                markers += 1
            elif (h & 0xFF00) in (0xE800, 0xE900, 0xEA00, 0xEB00) or (h & 0xF000) == 0xF000 \
                    or (h & 0xFE00) == 0xEC00 or (h & 0xFF00) == 0xEE00:         # ldm/stm/dp/ldr/str/vfp
                markers += 0.8
            wide += 1
            units += 1
            i += 2
            continue
        units += 1
        if (h & 0xFE00) in (0xB400, 0xBC00) or h == 0x4770 or (h & 0xFF00) == 0x4600 \
                or (h & 0xF800) in (0x4800, 0x2000, 0x2800, 0xE000, 0x8000, 0x8800, 0xA000, 0xA800) \
                or ((h & 0xF000) == 0xD000 and (h & 0x0F00) not in (0x0E00, 0x0F00)) \
                or (h & 0xE000) == 0x6000 or (h & 0xF500) == 0xB100 or (h & 0xFF00) in (0xB200, 0xBF00) \
                or (h & 0xF800) == 0x1800:
            markers += 1
        i += 1
    ws = struct.unpack_from('<%dI' % (n // 4), b)
    ptr = sum(1 for w in ws if base <= w < base + img_end or sram[0] <= w < sram[1]) / len(ws)
    return {'ff': c[0xFF] / n, 'zero': c[0] / n, 'entropy': round(ent, 2), 'printable': round(printable, 2),
            'code_score': round(markers / max(units, 1), 2), 'wide_frac': round(wide / max(units, 1), 2),
            'ptr_frac': round(ptr, 2)}


def classify_block(m):
    if m['ff'] == 1.0:
        return 'erased'
    if m['zero'] == 1.0:
        return 'zero'
    if m['ff'] >= 0.25:
        return 'mixed'
    if m['zero'] >= 0.5:
        return 'sparse'
    if m['printable'] >= 0.60:
        return 'ascii'
    if m['ptr_frac'] >= 0.20 and m['code_score'] < 0.55:
        return 'ptr'
    if m['code_score'] >= 0.50:
        return 'code'
    return 'data'


def classify_blocks(d, base=0x08000000, block=BLOCK_DEFAULT, sram=(0x20000000, 0x20010000), vectors_end=0x1E0):
    """Return (classes, metrics) lists, one entry per `block`-byte block."""
    end = image_end(d)
    classes, metrics = [], []
    for off in range(0, len(d), block):
        m = block_metrics(d[off:off + block], base, end, sram)
        cls = classify_block(m)
        if off < vectors_end:
            cls = 'vectors'
        classes.append(cls)
        metrics.append(m)
    return classes, metrics


def byte_runs(d, value, minlen):
    """Maximal runs of a single byte value of length >= minlen: list of (start, end)."""
    runs, i, n = [], 0, len(d)
    while i < n:
        if d[i] == value:
            j = i
            while j < n and d[j] == value:
                j += 1
            if j - i >= minlen:
                runs.append((i, j))
            i = j
        else:
            i += 1
    return runs


def regions(d, classes, block, base):
    """Byte-exact fill runs (0xFF / 0x00 >= 256 B) plus block-granular content regions between them."""
    fills = sorted([(s, e, 'erased') for s, e in byte_runs(d, 0xFF, block)] +
                   [(s, e, 'zero') for s, e in byte_runs(d, 0x00, block)])
    out, cur = [], 0
    for s, e, cls in fills:
        if s > cur:
            out.extend(content_regions(d, classes, block, cur, s))
        out.append({'start': s, 'end': e, 'class': cls})
        cur = e
    if cur < len(d):
        out.extend(content_regions(d, classes, block, cur, len(d)))
    for r in out:
        r['len'] = r['end'] - r['start']
        r['flash_start'] = base + r['start']
        r['flash_end'] = base + r['end']
    return out


def content_regions(d, classes, block, start, end):
    out = []
    b0, b1 = start // block, (end + block - 1) // block
    cur_cls, cur_start = None, start
    for bi in range(b0, b1):
        cls = classes[bi]
        if cls in ('erased', 'zero'):
            cls = 'mixed'  # partial fill block inside a content span
        if cls != cur_cls:
            if cur_cls is not None:
                out.append({'start': cur_start, 'end': max(bi * block, start), 'class': cur_cls})
            cur_cls, cur_start = cls, max(bi * block, start)
    out.append({'start': cur_start, 'end': end, 'class': cur_cls})
    return out


def landmarks(d):
    lm = {}
    for label, pat in [('product_ascii', rb'Keychron V10 Max'), ('build_date', rb'\d{4}-\d{2}-\d{2}-\d{2}:\d{2}:\d{2}'),
                       ('newlib_path', rb'[\x20-\x7e]*newlib/libc/[\x20-\x7e]*\.c'),
                       ('wear_leveling_assert', rb'Invalid sector count[\x20-\x7e]*'),
                       ('product_utf16', 'Keychron V10 Max'.encode('utf-16-le'))]:
        m = re.search(pat, d)
        if m:
            lm[label] = {'offset': m.start(), 'text': m.group(0).decode('utf-16-le' if 'utf16' in label else 'ascii')}
    return lm


def parse_annot(items):
    out = []
    for it in items or []:
        s, e, label = it.split(':', 2)
        out.append({'start': int(s, 0), 'end': int(e, 0), 'label': label})
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('dump')
    ap.add_argument('--out', default='.')
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--block', type=int, default=BLOCK_DEFAULT)
    ap.add_argument('--sram', default='0x20000000:0x20010000', help='SRAM range for SP/pointer checks')
    ap.add_argument('--annotate', action='append', help='start:end:label (file offsets) to mark known regions')
    ap.add_argument('--code-end', type=lambda x: int(x, 0), default=None,
                    help='byte-exact end of .text established by disassembly (recorded next to the block-granular estimate)')
    a = ap.parse_args()

    d = open(a.dump, 'rb').read()
    sram = tuple(int(x, 0) for x in a.sram.split(':'))
    img_end, cont_end = image_end(d), content_end(d)
    vec = analyze_vectors(d, a.base, img_end, sram)
    classes, metrics = classify_blocks(d, a.base, a.block, sram, vectors_end=vec['table_bytes'])
    if a.code_end is not None:  # blocks entirely past the disassembly-verified end of .text cannot be code
        classes = ['data' if (c == 'code' and i * a.block >= a.code_end) else c for i, c in enumerate(classes)]
    regs = regions(d, classes, a.block, a.base)
    annots = parse_annot(a.annotate)
    lm = landmarks(d)
    counts = collections.Counter(classes)
    # code/rodata split estimate: last 'code' block inside the content span before img_end
    code_blocks = [i for i, c in enumerate(classes) if c == 'code']
    last_code_end = (code_blocks[-1] + 1) * a.block if code_blocks else None
    first_nonfill = next((i for i in range(0x200, len(d)) if d[i] not in (0x00, 0xFF)), None)

    res = {
        'file': os.path.abspath(a.dump), 'size': len(d), 'sha256': sha256(d), 'flash_base': a.base,
        'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
        'image_end': img_end, 'content_end': cont_end, 'first_nonfill_after_0x200': first_nonfill,
        'vector_table': vec, 'block_size': a.block, 'block_classes': ''.join(LEGEND[c] for c in classes),
        'block_counts': dict(counts), 'last_code_block_end': last_code_end, 'code_end_from_disassembly': a.code_end,
        'regions': regs, 'annotations': annots, 'landmarks': lm,
        'block_metrics_nonfill': [{'offset': i * a.block, 'class': c, **m} for i, (c, m) in enumerate(zip(classes, metrics))
                                  if c not in ('erased', 'zero')],
    }
    os.makedirs(a.out, exist_ok=True)
    with open(os.path.join(a.out, 'triage.json'), 'w') as f:
        json.dump(res, f, indent=1)
    with open(os.path.join(a.out, 'triage.md'), 'w') as f:
        f.write(render_md(res, d))
    print('wrote', os.path.join(a.out, 'triage.json'), os.path.join(a.out, 'triage.md'))


def render_md(r, d):
    base = r['flash_base']
    v = r['vector_table']
    L = []
    L.append('# Dump triage: %s\n' % os.path.basename(r['file']))
    L.append('Generated %s by tools/dump_triage.py (stdlib heuristics; see script docstring).\n' % r['generated'])
    L.append('| item | value |\n|---|---|')
    L.append('| size | %d B (0x%X) |' % (r['size'], r['size']))
    L.append('| sha256 | `%s` |' % r['sha256'])
    L.append('| flash base | 0x%08X (file offset 0) |' % base)
    L.append('| image end (last non-0xFF byte + 1) | 0x%X (flash 0x%08X); %d B used, %d B erased tail |' %
             (r['image_end'], base + r['image_end'], r['image_end'], r['size'] - r['image_end']))
    L.append('| content end (last non-0xFF/0x00 + 1) | 0x%X |' % r['content_end'])
    L.append('| first non-fill byte after 0x200 | 0x%X |' % (r['first_nonfill_after_0x200'] or -1))
    L.append('| last block classified as code ends at | 0x%X (code/rodata boundary estimate, %d-B granularity) |' %
             (r['last_code_block_end'] or 0, r['block_size']))
    if r.get('code_end_from_disassembly'):
        L.append('| .text end from disassembly (--code-end) | 0x%X (flash 0x%08X): last `bx lr` at 0x%X, zero padding, .rodata from 0x%X |' %
                 (r['code_end_from_disassembly'], base + r['code_end_from_disassembly'], r['code_end_from_disassembly'] - 2, r['code_end_from_disassembly'] + 2))
    L.append('')
    L.append('## Vector table (file 0x0)\n')
    L.append('| item | value | check |\n|---|---|---|')
    L.append('| initial SP (word 0) | 0x%08X | %s (SRAM 0x20000000..0x20010000, 8-aligned) |' % (v['sp'], 'OK' if v['sp_ok'] else 'BAD'))
    L.append('| Reset (word 1) | 0x%08X | %s (odd Thumb address inside image); file 0x%X, first bytes `%s` |' %
             (v['reset'], 'OK' if v['reset_ok'] else 'BAD', v['reset_file_offset'], v['reset_first_bytes']))
    L.append('| entries (through last non-zero word) | %d = 16 core + %d IRQ, table 0x0..0x%X | ChibiOS STM32F4xx cmparams.h: CORTEX_NUM_VECTORS 104 -> 120 entries = 0x1E0 B |' %
             (v['entries_total'], v['entries_total'] - 16, v['table_bytes'] - 1))
    L.append('| plausible handler addresses | %d of %d (zero: %d, bad: %d) | |' %
             (v['entries_plausible'], v['entries_total'] - 1, v['entries_zero'], len(v['entries_bad'])))
    L.append('| default (unhandled) handler | 0x%08X used by %d entries | |' % (v['default_handler'], v['default_handler_count']))
    L.append('| first non-zero byte after table | %s | zero fill expected up to 0x4000 (flash0 sector 0 = 16 KiB) |' %
             ('0x%X' % v['first_nonzero_after_table'] if v['first_nonzero_after_table'] is not None else 'none before 0x8000'))
    L.append('')
    L.append('Populated (non-default) vectors:\n')
    L.append('| idx | file off | name | handler |\n|---|---|---|---|')
    for e in v['populated']:
        L.append('| %d | 0x%03X | %s | 0x%08X |' % (e['index'], e['offset'], e['name'], e['value']))
    L.append('')
    L.append('## 256-byte block map\n')
    L.append('Legend: `V` vectors, `0` zero, `.` erased (0xFF), `C` Thumb code, `D` data, `A` ascii-dense, `P` pointer-dense, `s` sparse (>=50% zero bytes), `m` partly erased. One row = 64 blocks = 16 KiB.\n')
    L.append('```')
    m = r['block_classes']
    for i in range(0, len(m), 64):
        L.append('0x%05X  %s' % (i * r['block_size'], m[i:i + 64]))
    L.append('```')
    L.append('Block counts: ' + ', '.join('%s=%d' % kv for kv in sorted(r['block_counts'].items())) + '\n')
    L.append('## Regions\n')
    L.append('Fill regions are byte-exact; content regions are %d-B granular.\n' % r['block_size'])
    L.append('| file start | file end | flash | len | class | annotation |\n|---|---|---|---|---|---|')
    for g in r['regions']:
        ann = '; '.join('%s (0x%X..0x%X)' % (x['label'], x['start'], x['end']) for x in r['annotations']
                        if x['start'] < g['end'] and x['end'] > g['start'])
        L.append('| 0x%05X | 0x%05X | 0x%08X | %6d | %s | %s |' % (g['start'], g['end'], g['flash_start'], g['len'], g['class'], ann))
    L.append('')
    if r['landmarks']:
        L.append('## Landmarks (string search)\n')
        L.append('| landmark | file off | flash | text |\n|---|---|---|---|')
        for k, x in r['landmarks'].items():
            L.append('| %s | 0x%X | 0x%08X | `%s` |' % (k, x['offset'], base + x['offset'], x['text']))
        L.append('')
    if r['annotations']:
        L.append('## Annotations supplied on the command line\n')
        for x in r['annotations']:
            L.append('- 0x%X..0x%X (flash 0x%08X): %s' % (x['start'], x['end'], base + x['start'], x['label']))
        L.append('')
    return '\n'.join(L) + '\n'


if __name__ == '__main__':
    main()
