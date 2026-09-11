# Verification runs (tools/final_compile_compare.py against dump_a.bin)

| rebuild | fork commit | compiler | result |
|---|---|---|---|
| refs/exact8e390f92_dexter_gcc13.elf | 8e390f92a2 (the original's source tree) | xpack GCC 13.2.1 | ALL IDENTICAL: 17 user functions, keymaps[], encoder_map[], tap_dance_actions shape, .bss order, all config-bearing core functions |
| refs/head_dexter_gcc13.elf | wireless_playground HEAD 666862cb | xpack GCC 13.2.1 | user TU + tables identical; 5 core DIFFs from later fork changes: get_mods_for_report (removed), rgb_matrix_mode_eeprom_helper, process_rgb_matrix, raw_hid_receive (now answers Keychron 0xA0 commands), send_nkro_report (adaptive NKRO) |
| refs/head_dexter_gcc15.elf / .bin | wireless_playground HEAD | QMK gcc 15.2.0 | tables byte-identical; code bytes differ by compiler (behavior unchanged). This is the default `qmk compile` output. |

Raw byte identity between the exact-era rebuild and the dump is only ~20% because the differently
built newlib shifts every following address; the masked per-function comparison is the meaningful metric.
