Compile-and-compare verification of custom_code/leader.c (leader_start_user / leader_end_user / leader config).
Procedure used (2026-09-10):
  1. cp -R qmk-keychron-ref/keyboards/keychron/v10_max/ansi_encoder/keymaps/ref_feat  .../keymaps/verify_leader_7k2q
  2. replace leader_end_user with custom_code/leader.c bodies, add leader_start_user  -> tools/leader_verify_keymap.c
     append "#define LEADER_PER_KEY_TIMING" / "#define LEADER_TIMEOUT 525" to config.h -> tools/leader_verify_config.h
  3. X=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin
     PATH="$X:$PATH" qmk compile -kb keychron/v10_max/ansi_encoder -km verify_leader_7k2q -j 8 -e TOOLCHAIN="$X/arm-none-eabi-"
     (gcc 13.2.1 20231009, same major/minor/patch as the dump's compiler; also built once with the default gcc 15.2)
  4. outputs kept as refs/ref1011_leader_verify_gcc13.{elf,map,bin}
  5. python3 tools/leader_compile_compare.py <unused> "$X"   -> masks BL/B.W immediates and literal-pool words, compares
     dump bytes vs rebuilt bytes for all 13 leader functions. Result: all 13 masked-identical (sizes incl. literal pools):
       leader_start_user 10, leader_end_user 354, process_leader 74, leader_start 60, leader_end 20,
       leader_sequence_active 12, leader_sequence_add 36, leader_sequence_timed_out 28, leader_task 28,
       leader_reset_timer 16, leader_sequence_is 52, leader_sequence_one_key 20, leader_sequence_two_keys 18.
  6. tools/leader_variants_check.c: standalone gcc13 -Os compile of (A) else-if chain, (B) tap_code() taps,
     (C) tap_code16() chords -- each produces a different instruction stream from the dump (b.n to shared epilogue /
     bl tap_code / movw+bl tap_code16), so those source forms are excluded.
  The scratch keymap dir and its .build artifacts were deleted afterwards.
