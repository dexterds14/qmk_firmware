/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copy of platforms/chibios/boards/common/ld/STM32F401xC_tinyuf2.ld with the
 * tinyuf2 double-tap word relocated for the Plum UF2 bootloader.
 */

f4xx_flash_size = 256k;
f4xx_ram1_size = 64k;
f4xx_ram2_size = 0;
f4xx_ram4_size = 0;
f4xx_ram5_size = 0;

INCLUDE platforms/chibios/boards/common/ld/stm32f4xx_tinyuf2_common.ld

/*
 * The Plum UF2 bootloader checks for the double-tap/reboot magic at
 * 0x2000FC00 (1 KB below the end of RAM), not at the standard tinyuf2
 * location of RAM end - 4. Address extracted from the stock firmware's
 * bootloader_jump literal pool (magic 0xF01669EF written to 0x2000FC00).
 * With the default address QK_BOOT just resets back into the app.
 */
_board_dfu_dbl_tap = 0x2000FC00;
