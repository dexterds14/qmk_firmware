RGBLIGHT_ENABLE = yes
OLED_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
SPLIT_KEYBOARD = yes
CONSOLE_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AUTO_SHIFT_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no
COMMAND_ENABLE = no
KEY_LOCK_ENABLE = no

# LTO works ONLY with the sidestep architecture in place (2026-07): soft
# serial speed 5, rgblight split sync disabled (no RGBLED_SPLIT), slave
# derives RGB from layer state (keymap.c). See config.h for the full story.
# Do NOT retry: CRC-verified RGB sync via user RPC (locks up the slave; AVR
# ISR runs RPC callbacks before payload receive), or READ_WRITE_*_ADJUST
# recalibration (windows don't overlap). Fallback: LTO off + speed 0.
LTO_ENABLE = yes
