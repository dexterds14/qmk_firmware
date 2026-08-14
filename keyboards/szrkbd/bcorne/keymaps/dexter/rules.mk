# The Plum UF2 bootloader expects UF2 family id 0xABCDF401 (matches the stock
# CURRENT.UF2). Override QMK's default STM32F4 family so the produced .uf2 is
# accepted when dragged onto the STM32F4Plum drive.
UF2_FAMILY = 0xABCDF401

ENCODER_MAP_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes

# PIXEL_FRACTAL_OK (rgb_matrix_user.inc): fixed copy of the builtin
# PIXEL_FRACTAL, which never paints the middle matrix column on odd-width
# matrices (this board is 7 cols) and so leaves stale colors on those keys.
RGB_MATRIX_CUSTOM_USER = yes
