// Mock backing store for compiling the fork's real quantum/wear_leveling/wear_leveling.c
// on the host.  Implements the backing_store_* API declared in wear_leveling_internal.h
// (init/unlock/erase/write/lock/read; the *_bulk variants are weak in wear_leveling.c and
// are deliberately NOT overridden so the fork's own code path is exercised).
//
// Semantics copied from platforms/chibios/drivers/wear_leveling/wear_leveling_efl.c:
//   backing_store_write(): flashProgram(~value)     -> we store ~value into the shadow
//   backing_store_read():  value = ~(*loc)          -> we return ~word from the dump slice
// The slice is the raw (non-inverted) flash bytes dump_a.bin[0x4000:0x5000].
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wear_leveling.h"
#include "wear_leveling_internal.h"

static uint8_t  flash_image[WEAR_LEVELING_BACKING_SIZE];  // raw flash bytes (0xFF = erased)
static int      erase_count   = 0;
static int      write_count   = 0;
static int      read_count    = 0;
static uint32_t max_read_addr = 0;

void mock_backing_load(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) { perror(path); exit(2); }
    if (fseek(f, 0x4000, SEEK_SET) != 0) { perror("fseek"); exit(2); }
    size_t n = fread(flash_image, 1, sizeof(flash_image), f);
    fclose(f);
    if (n != sizeof(flash_image)) { fprintf(stderr, "short read: %zu\n", n); exit(2); }
}

void mock_backing_stats(FILE *out) {
    fprintf(out, "mock: reads=%d (max backing addr read 0x%04x), writes=%d, erases=%d\n",
            read_count, max_read_addr, write_count, erase_count);
}

bool backing_store_init(void) { return true; }
bool backing_store_unlock(void) { return true; }
bool backing_store_lock(void) { return true; }

bool backing_store_erase(void) {
    // Would only be reached if wear_leveling decided to consolidate; flag it loudly.
    erase_count++;
    fprintf(stderr, "mock: UNEXPECTED backing_store_erase() -- firmware would consolidate here\n");
    memset(flash_image, 0xFF, sizeof(flash_image));
    return true;
}

bool backing_store_write(uint32_t address, backing_store_int_t value) {
    write_count++;
    fprintf(stderr, "mock: UNEXPECTED backing_store_write(0x%04x, 0x%08x)\n", address, (unsigned)value);
    if (address + sizeof(value) > sizeof(flash_image)) return false;
    value = ~value;  // as wear_leveling_efl.c does before flashProgram()
    memcpy(&flash_image[address], &value, sizeof(value));
    return true;
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    read_count++;
    if (address > max_read_addr) max_read_addr = address;
    if (address + sizeof(*value) > sizeof(flash_image)) return false;
    backing_store_int_t tmp;
    memcpy(&tmp, &flash_image[address], sizeof(tmp));  // little-endian host == little-endian Cortex-M4
    *value = ~tmp;                                       // as wear_leveling_efl.c backing_store_safe_read_from_location()
    return true;
}
