// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* I2C for OLEDs */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define OLED_DISPLAY_64X128
#define OLED_TIMEOUT 30000

#define ENCODER_MAP_KEY_DELAY 10

#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50

#define EE_HANDS
