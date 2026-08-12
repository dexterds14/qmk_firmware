// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

// The BCORNE has a 16 MHz HSE crystal, not the 25 MHz the default
// BLACKPILL_STM32_F401 board config assumes. Derived from the stock
// firmware's RCC_PLLCFGR constant (PLLM=16, PLLN=192, PLLP=4, PLLQ=4,
// PLLSRC=HSE), which only yields the mandatory 48 MHz USB clock with
// a 16 MHz crystal.
#undef STM32_HSECLK
#define STM32_HSECLK 16000000U
