// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "layers.h"

// clang-format off

#define LAYOUT_handwired( \
		k00, k01, k02, k03, k04, k05,                k06, k07, k08, k09, k10, k11, \
	       	k12, k13, k14, k15, k16, k17,                k18, k19, k20, k21, k22, k23, \
		k24, k25, k26, k27, k28, k29,                k30, k31, k32, k33, k34, k35, \
		k36, k37, k38, k39, k40, k41, k42,      k43, k44, k45, k46, k47, k48, k49, \
		          k50, k51, k52, k53, k54,      k55, k56, k57, k58, k59 \
		) \
		 { \
			 {k00, k01, k02, k03, k04, k05}, \
			 {k12, k13, k14, k15, k16, k17}, \
			 {k24, k25, k26, k27, k28, k29}, \
			 {k37, k38, k39, k40, k41, k42}, \
			 {k36, k50, k51, k52, k53, k54}, \
			 \
		         {k11, k10, k09, k08, k07, k06}, \
			 {k23, k22, k21, k20, k19, k18}, \
			 {k35, k34, k33, k32, k31, k30}, \
			 {k48, k47, k46, k45, k44, k43}, \
			 {k49, k59, k58, k57, k56, k55} \
		 }

#define SC_SSPC LSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_handwired(
        QK_GESC,    KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
         KC_TAB,    KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
         KC_GRV,    KC_A,    KC_S,     KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL,    KC_Z,    KC_X,     KC_C,    KC_V,    KC_B, KC_LBRC,     KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
                          KC_RGHT,  KC_LALT,   MO(1),  KC_SPC, KC_LSFT,     KC_RSFT,  KC_ENT,   MO(1), KC_RGUI,   KC_UP
    ),
    [_LOWER] = LAYOUT_handwired(
	_______, RM_TOGG, RM_NEXT, RM_PREV, RM_VALU, RM_VALD,                        RM_SPDU, RM_SPDD, _______, _______, _______, _______,
        _______, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,                        KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______, _______,
         KC_GRV, KC_UNDS, KC_PLUS, KC_MINS,  KC_EQL, _______,                        KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______, 
        _______, _______, _______, _______, _______, _______,  QK_BOOT,      QK_RBT, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,

	                   KC_CAPS, _______, _______, _______,  KC_DEL,      KC_BSPC, _______, _______, _______, QK_BOOT
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
};
#endif
