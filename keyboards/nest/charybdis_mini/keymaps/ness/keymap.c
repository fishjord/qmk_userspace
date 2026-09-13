// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _NAV_SYM,
    _MEDIA
};

#define WORD_L   LCTL(KC_LEFT)
#define WORD_R   LCTL(KC_RGHT)
#define LINE_STR KC_HOME
#define LINE_END KC_END
#define NAV_SYM  MO(_NAV_SYM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LCTL, KC_LALT, KC_SPC,               KC_ENT,  NAV_SYM
    ),
    [_NAV_SYM] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    LINE_STR,KC_UP,   LINE_END,KC_PGUP, KC_DEL,
        KC_TILD, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EQL,      KC_PLUS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_PIPE,
        KC_LSFT, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, KC_UNDS,     WORD_L,  KC_MINS, KC_ASTR, WORD_R,  KC_AMPR, KC_BSLS,
                          KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS
    ),
    [_MEDIA] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_CAPS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_MPRV, KC_MNXT, KC_MSTP, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS
    )
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (IS_LAYER_ON(_NAV_SYM)) {
        mouse_report.h = mouse_report.x / 4;
        mouse_report.v = -(mouse_report.y / 4);
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
