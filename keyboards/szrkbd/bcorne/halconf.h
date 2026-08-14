// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Enable the ChibiOS serial driver for the USART split transport.
#define HAL_USE_SERIAL TRUE

// PWM (TIM3) drives the WS2812 chain via DMA.
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
