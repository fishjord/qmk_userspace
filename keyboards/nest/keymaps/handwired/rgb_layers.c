// Copyright 2025 Nes Fish (@fishjord)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <quantum/color.h>
#include "layers.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    hsv_t hsv;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            return false;
        case _LOWER:
            hsv =  (hsv_t){HSV_GREEN
	    };
            break;
        default:
            hsv =  (hsv_t){HSV_RED };
            break;
    }
    if (is_caps_word_on()) {
        hsv = (hsv_t){HSV_YELLOW};
    }

    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    rgb_t rgb = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return false;
}
