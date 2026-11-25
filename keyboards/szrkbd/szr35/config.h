// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5

/* Stock firmware clocks the WS2812 chain at 80 kHz (PWM period 300 ticks @ 24 MHz)
 * with the usual high times, not the default 800 kHz. Mirror it. */
#define WS2812_PWM_FREQUENCY 80000

/* Emulated EEPROM lives in flash sector 3 (0x0800C000, 16 KB), where the stock
 * firmware keeps it. Sectors 0-1 hold the Plum UF2 bootloader; never let the
 * wear-leveling driver default into them. */
#define WEAR_LEVELING_EFL_FIRST_SECTOR 3
