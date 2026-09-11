#!/bin/sh
# Build and run the EEPROM oracle: the fork's real wear_leveling.c + lib/fnv/hash_64a.c
# compiled with the host cc against mock_backing_store.c.  Writes oracle_cache.hex.
#
#   sh build.sh [FORK_ROOT] [DUMP]
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
FORK=${1:-$(cd "$HERE/../../.." && pwd)}
DUMP=${2:-$HERE/../../dump_a.bin}

WL="$FORK/quantum/wear_leveling"
FNV="$FORK/lib/fnv"

# Same configuration the v10_max build resolves to:
#   info.json eeprom.wear_leveling: backing_size 4096, logical_size 2048
#   wear_leveling_efl_config.h on STM32F4: BACKING_STORE_WRITE_SIZE = 1 << STM32_FLASH_PSIZE = 4
cc -std=gnu11 -O1 -Wall -Wno-unused-function \
   -DWEAR_LEVELING_BACKING_SIZE=4096 \
   -DWEAR_LEVELING_LOGICAL_SIZE=2048 \
   -DBACKING_STORE_WRITE_SIZE=4 \
   -I"$WL" -I"$FNV" \
   "$WL/wear_leveling.c" "$FNV/hash_64a.c" \
   "$HERE/mock_backing_store.c" "$HERE/main.c" \
   -o "$HERE/eeprom_oracle"

echo "built $HERE/eeprom_oracle from:"
echo "  $WL/wear_leveling.c"
echo "  $FNV/hash_64a.c"
"$HERE/eeprom_oracle" "$DUMP" > "$HERE/oracle_cache.hex"
echo "wrote $HERE/oracle_cache.hex ($(wc -c < "$HERE/oracle_cache.hex") chars)"
