# The Plum UF2 bootloader expects UF2 family id 0xABCDF401 (matches the stock
# CURRENT.UF2). Override QMK's default STM32F4 family so the produced .uf2 is
# accepted when dragged onto the STM32F4Plum drive.
UF2_FAMILY = 0xABCDF401
