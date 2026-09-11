Compile-and-compare verification of custom_code/config_features.{md,txt} (keymap-level config.h / rules.mk).
Procedure (2026-09-10):
  1. cp -R qmk-keychron-ref/keyboards/keychron/v10_max/ansi_encoder/keymaps/ref_feat  .../keymaps/verify_config_m3k9
     config.h  := exactly the #defines of custom_code/config_features.txt (TAPPING_TERM 175, TAPPING_TERM_PER_KEY,
                  ONESHOT_TAP_TOGGLE 2, LEADER_PER_KEY_TIMING, LEADER_TIMEOUT 525, MK_KINETIC_SPEED, MOUSEKEY_MOVE_DELTA 45,
                  MOUSEKEY_INITIAL_SPEED 30, MOUSEKEY_BASE_SPEED 1500, MOUSEKEY_INTERVAL 40, MOUSEKEY_DELAY 1,
                  MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 64, MOUSEKEY_WHEEL_BASE_MOVEMENTS 32, MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 50,
                  RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP)
     rules.mk  := TAP_DANCE/LEADER/MOUSEKEY = yes; MAGIC/GRAVE_ESC/SPACE_CADET/VIA/LTO/CONSOLE/COMMAND/AUTO_SHIFT/COMBO = no
  2. X=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin
     PATH="$X:$PATH" qmk compile -kb keychron/v10_max/ansi_encoder -km verify_config_m3k9 -j 8 -e TOOLCHAIN="$X/arm-none-eabi-"
     -> compiled clean (gcc 13.2.1 20231009, same release as the dump's compiler). Outputs kept as refs/ref1011_config_verify_gcc13.{elf,map,bin}.
  3. tools/config_compile_compare.py : masks BL/B.W immediates + literal-pool words, compares 41 config-bearing functions
     dump vs rebuild (all masked-identical except rgb_matrix_increase_val_helper, whose dump size in the report (44) is
     just short: it is 48 B and identical), then sweeps all 914 rebuild functions against functions_final.csv.
     tools/config_compile_compare_sweep.py : same sweep tolerating the 2/4-byte trailing pad that functions_final.csv
     sizes include. Result: every non-user, non-newlib function of the rebuild has a masked-identical dump function,
     except wireless_send_nkro (dump 0x0800A33C, 100 B) which has an extra direct wireless_transport.send_nkro(&report->mods)
     call after report_buffer_enqueue = the fork's wireless.c BEFORE commit 0c05eef6cd (2024-06-22). So the dump's source
     tree is fork commit 8e390f92a2 (2024-06-18), one commit before the pinned reference 1011db8c8d; this does not affect
     any config constant (all config-bearing functions are byte-identical after masking).
  4. .data init image and rodata checked directly: mk_interval 0x28, mk_wheel_interval 0x000F, mk_wheel_delay 0x01,
     rgb_matrix_timeout 0xFFFFFFFF, HSV default 00 FF FF -- identical on both sides.
  The scratch keymap dir and its .build artifacts were deleted afterwards.
