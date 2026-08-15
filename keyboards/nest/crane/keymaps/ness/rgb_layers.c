// Copyright 2025 Nes Fish (@fishjord)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "layers.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        if (is_caps_word_on()) {
            rgb_matrix_set_color(i, RGB_YELLOW);
        }

        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _QWERTY:
                break;
            case _LOWER:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            default:
                rgb_matrix_set_color(i, RGB_RED);
                break;
        }
    }
    return false;
}
