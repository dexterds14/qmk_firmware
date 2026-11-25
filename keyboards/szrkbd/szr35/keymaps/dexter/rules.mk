# UF2_FAMILY for the Plum bootloader is set in the keyboard-level rules.mk.
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes

# PIXEL_FRACTAL_OK (rgb_matrix_user.inc): fixed copy of the builtin
# PIXEL_FRACTAL, which never paints the middle matrix column on odd-width
# matrices (this board is 5 cols) and so leaves stale colors on those keys.
RGB_MATRIX_CUSTOM_USER = yes
