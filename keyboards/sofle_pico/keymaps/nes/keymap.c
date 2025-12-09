// Copyright 2025 Nes Fish (@fishjord)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "layers.h"
#include "rgb_layers.h"

/* Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs. */
bool     is_cmd_tab_active = false;
uint16_t cmd_tab_timer     = 0;

/**
 * Keymap.
 * The rotary encoders are programmed manually below because the configurator does not support them yet.
 */

#define SC_SSPC LSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_QWERTY] = LAYOUT(
        QK_GESC,    KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
        KC_TAB,     KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
        KC_LSFT,    KC_A,    KC_S,     KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL,    KC_Z,    KC_X,     KC_C,    KC_V,    KC_B, KC_MUTE,     _______,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RCTL,
                           KC_GRV,  KC_LGUI, KC_LALT,   MO(1), SC_SSPC,     SC_SENT,   MO(1), KC_RALT,  KC_APP,  KC_DEL
    ),
    [_LOWER] = LAYOUT(
	RM_TOGG, RM_NEXT, RM_PREV, RM_VALU, RM_VALD, _______,                        RM_SPDU, RM_SPDD, _______, _______, _______, _______,
        _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,                        KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,
        _______, KC_UNDS, KC_PLUS, KC_MINS,  KC_EQL, _______,                        KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, QK_BOOT,

	                  KC_CAPS, _______, _______, _______,  KC_DEL,      KC_BSPC, _______, _______, _______, _______
    )
};
// clang-format on

/**
 * Rotary Encoder.
 *
 * This can't be programmed through configurator. You must do it here.
 *
 * This uses the amazing "Encoder map" feature which replicates the normal keyswitch layer handling functionality, but with encoders.
 * https://docs.qmk.fm/#/feature_encoders?id=encoder-map
 *
 * Uses a variant of the Super-alt-tab macro to switch between open applications on a mac. (Command-tab)
 * https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
 */
#ifdef ENCODER_MAP_ENABLE

#    define SHIFT_ALT_TAB S(A(KC_TAB))
#    define ALT_TAB A(KC_TAB)
#    define SHIFT_CTRL_TAB S(C(KC_TAB))
#    define CTRL_TAB C(KC_TAB)
#    define LINE_START C(S(KC_LEFT))
#    define LINE_END C(S(KC_RIGHT))

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // clang-format off
                    /* Left Hand */                                  /* Right Hand */
    [_QWERTY] = {
                    ENCODER_CCW_CW(SHIFT_ALT_TAB,   ALT_TAB),        ENCODER_CCW_CW(MS_WHLD,           MS_WHLU)
    },
    [_LOWER] =  {
                    ENCODER_CCW_CW(SHIFT_CTRL_TAB, CTRL_TAB),        ENCODER_CCW_CW(KC_PGDN,           KC_PGUP)
    },
};
// clang-format on
#endif
