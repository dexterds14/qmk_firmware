// Oracle: run the fork's real wear_leveling_init() over the dumped backing store and
// print the 2048-byte logical EEPROM the firmware would see, as hex (one line).
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "wear_leveling.h"

void mock_backing_load(const char *path);
void mock_backing_stats(FILE *out);

int main(int argc, char **argv) {
    const char *dump = argc > 1 ? argv[1] : "../../dump_a.bin";
    mock_backing_load(dump);

    wear_leveling_status_t st = wear_leveling_init();
    fprintf(stderr, "wear_leveling_init() -> %d (%s)\n", (int)st,
            st == WEAR_LEVELING_SUCCESS ? "WEAR_LEVELING_SUCCESS" :
            st == WEAR_LEVELING_CONSOLIDATED ? "WEAR_LEVELING_CONSOLIDATED" : "WEAR_LEVELING_FAILED");
    mock_backing_stats(stderr);

    static uint8_t buf[WEAR_LEVELING_LOGICAL_SIZE];
    wear_leveling_status_t rs = wear_leveling_read(0, buf, sizeof(buf));
    fprintf(stderr, "wear_leveling_read(0, buf, %u) -> %d\n", (unsigned)sizeof(buf), (int)rs);

    for (size_t i = 0; i < sizeof(buf); ++i) printf("%02x", buf[i]);
    printf("\n");
    return (st == WEAR_LEVELING_FAILED || rs != WEAR_LEVELING_SUCCESS) ? 1 : 0;
}
