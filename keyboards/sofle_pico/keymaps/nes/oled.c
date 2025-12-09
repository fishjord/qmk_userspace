#include QMK_KEYBOARD_H
#include "layers.h"

// Default timeout for displaying logo on boot.
#ifndef OLED_LOGO_TIMEOUT
// 10 second timeout.
#    define OLED_LOGO_TIMEOUT 10000
#endif

#ifdef OLED_ENABLE

uint16_t startup_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();

    if (is_keyboard_master()) {
        if (is_keyboard_left()) {
            return OLED_ROTATION_0;
        } else {
            return OLED_ROTATION_180;
        }
    } else {
        return OLED_ROTATION_90;
    }
}

void render_rgb_status(void) {
    char *mode_name = strdup(rgb_matrix_get_mode_name(rgb_matrix_get_mode()));
    if (mode_name != NULL) {
        int  len             = strlen(mode_name);
        bool capitalize_next = true;
        for (int i = 0; i < len; i++) {
            if (i == 21 && mode_name[i] == '_') {
                continue; // Skip the underscore if it's the 22nd character
            }
            if (mode_name[i] == '_') {
                mode_name[i]    = ' ';
                capitalize_next = true;
            } else if (capitalize_next) {
                mode_name[i]    = mode_name[i] >= 'a' && mode_name[i] <= 'z' ? mode_name[i] - 'a' + 'A' : mode_name[i];
                capitalize_next = false;
            } else {
                mode_name[i] = mode_name[i] >= 'A' && mode_name[i] <= 'Z' ? mode_name[i] - 'A' + 'a' : mode_name[i];
            }
        }

        // Add line break and spaces if necessary
        if (len < 19) {
            strcat(mode_name, "\n");
            for (int i = 0; i < 21; i++) {
                strcat(mode_name, " ");
            }
        } else {
            // Find the most recent ' ' before the 21st character and replace it with a line break
            int break_pos = -1;
            for (int i = 18; i >= 0; i--) {
                if (mode_name[i] == ' ') {
                    break_pos = i;
                    break;
                }
            }
            if (break_pos >= 0) {
                mode_name[break_pos] = '\n';
                for (int i = 0; i < (21 - (len - break_pos - 1)); i++) {
                    strcat(mode_name, " ");
                }
            } else {
                // No '_' found, just add spaces
                for (int i = 0; i < (21 - len); i++) {
                    strcat(mode_name, " ");
                }
            }
        }

        oled_write_P(PSTR(mode_name), false);
        free(mode_name);
    }
}

static void render_status(void) {
    oled_write_P(PSTR("Sofle Pico\n~~~~~~~~~~\n"), false);

    os_variant_t detected_os = detected_host_os();
    oled_write_P(PSTR("OS: "), false);
    switch (detected_os) {
        case OS_MACOS:
            oled_write_P(PSTR("MacOS"), false);
            break;
        case OS_IOS:
            oled_write_P(PSTR("iOS  "), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("Win  "), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("Linux"), false);
            break;
        case OS_UNSURE:
            oled_write_P(PSTR("Unk  "), false);
            break;
    }

    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\n\nLock: "), false);
    oled_write_P(led_state.caps_lock ? PSTR("C") : PSTR("_"), false);
    oled_write_P(led_state.num_lock ? PSTR("N") : PSTR("_"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR("_"), false);

    oled_write_P(PSTR("\nCaps: "), false);
    if (led_state.caps_lock) {
        oled_write_P(PSTR("lock"), false);
    } else if (is_caps_word_on()) {
        oled_write_P(PSTR("word"), false);
    } else {
        oled_write_P(PSTR("off "), false);
    }

    oled_write_P(PSTR("\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_P(PSTR("Unk  "), false);
            break;
    }

    oled_write_P(PSTR("\n\n"), false);
    render_rgb_status();
}

bool oled_task_user(void) {
            oled_clear();
            render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    if (bootloader) {
        oled_write_P(PSTR("Awaiting New Firmware\n"), false);
    } else {
        oled_write_P(PSTR("Rebooting\n"), false);
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

#endif
