// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ------------------------------------------------------------------
 * Split handedness (reverse-engineered from stock Vial firmware)
 * SPLIT_HAND_PIN = C1, read as input; C1 LOW = left, C1 HIGH = right.
 * QMK default is "high = left", so invert it.
 * ------------------------------------------------------------------ */
#define SPLIT_HAND_PIN_LOW_IS_LEFT

/* ------------------------------------------------------------------
 * Split transport: hardware USART1, full-duplex.
 * TX = A9 (USART1_TX, AF7), RX = A10 (USART1_RX, AF7).
 * Two data lines crossed in the C-to-C interconnect cable.
 * ------------------------------------------------------------------ */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10

/* Master half is detected by USB presence. */
#define SPLIT_USB_DETECT

/* ------------------------------------------------------------------
 * WS2812 per-key RGB on A7 = TIM3_CH2 (AF2), driven by PWM + DMA.
 * TIM3_UP requests map to DMA1 stream 2, channel 5 on STM32F401.
 * ------------------------------------------------------------------ */
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 5
