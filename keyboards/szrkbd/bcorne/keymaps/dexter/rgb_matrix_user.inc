// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later
//
// PIXEL_FRACTAL_OK: upstream PIXEL_FRACTAL (quantum/rgb_matrix/animations/
// pixel_fractal_anim.h, (C) 2022 @filterpaper) with one fix. Upstream paints
// matrix columns (col, MATRIX_COLS-1-col) for col < MATRIX_COLS/2, which on
// an odd-width matrix (7 cols here) never touches the middle column -- those
// keys hold whatever was last written to them (e.g. the layer indicator's
// color) forever. This copy also paints the middle column, mirroring the
// center-most framebuffer cell. The broken builtin is disabled in
// keyboard.json so RM_NEXT only ever reaches this variant.

RGB_MATRIX_EFFECT(PIXEL_FRACTAL_OK)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_FRACTAL_OK(effect_params_t* params) {
#    if MATRIX_COLS < 2
#        define FRACTAL_MID_COL 1
#    else
#        define FRACTAL_MID_COL (MATRIX_COLS / 2)
#    endif
    static bool     led[MATRIX_ROWS][FRACTAL_MID_COL];
    static uint32_t wait_timer = 0;

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(led, 0, sizeof(led));
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (g_rgb_timer > wait_timer) {
        rgb_t rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            // Light columns outward from center, mirroring each side
            for (uint8_t col = 0; col < FRACTAL_MID_COL; ++col) {
                rgb_t   index_rgb = led[row][col] ? rgb : (rgb_t){0, 0, 0};
                uint8_t l_idx     = g_led_config.matrix_co[row][col];
                uint8_t r_idx     = g_led_config.matrix_co[row][MATRIX_COLS - 1 - col];
                if (l_idx >= led_min && l_idx < led_max && HAS_ANY_FLAGS(g_led_config.flags[l_idx], params->flags)) {
                    rgb_matrix_set_color(l_idx, index_rgb.r, index_rgb.g, index_rgb.b);
                }
                if (r_idx >= led_min && r_idx < led_max && HAS_ANY_FLAGS(g_led_config.flags[r_idx], params->flags)) {
                    rgb_matrix_set_color(r_idx, index_rgb.r, index_rgb.g, index_rgb.b);
                }
            }
#    if (MATRIX_COLS % 2) == 1
            // Odd matrix width: the mirrored loop above skips the true middle
            // column; paint it from the newest (center-most) framebuffer cell
            {
                rgb_t   mid_rgb = led[row][FRACTAL_MID_COL - 1] ? rgb : (rgb_t){0, 0, 0};
                uint8_t m_idx   = g_led_config.matrix_co[row][FRACTAL_MID_COL];
                if (m_idx >= led_min && m_idx < led_max && HAS_ANY_FLAGS(g_led_config.flags[m_idx], params->flags)) {
                    rgb_matrix_set_color(m_idx, mid_rgb.r, mid_rgb.g, mid_rgb.b);
                }
            }
#    endif
        }

        // Advance state and reset timer only on the final LED range iteration
        if (!rgb_matrix_check_finished_leds(led_max)) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                memmove(led[row], led[row] + 1, (FRACTAL_MID_COL - 1) * sizeof(bool));
                led[row][FRACTAL_MID_COL - 1] = !(random8() & 3);
            }
            wait_timer = g_rgb_timer + 3000 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
#    undef FRACTAL_MID_COL
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
