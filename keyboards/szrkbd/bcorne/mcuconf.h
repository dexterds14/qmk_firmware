// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// PLL settings for the 16 MHz HSE crystal (see board.h), mirroring the
// stock firmware exactly: VCO = 16/16*192 = 192 MHz, SYSCLK = 192/4 =
// 48 MHz, USB = 192/4 = 48 MHz. The BLACKPILL_STM32_F401 defaults these
// values for a 25 MHz crystal, which leaves USB clockless on this board.
#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 16
#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 192
#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE 4
#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE 4

// Split serial uses hardware USART1.
#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

// TIM3 PWM drives the WS2812 RGB chain (A7 = TIM3_CH2).
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
