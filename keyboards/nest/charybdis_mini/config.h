// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* Swap TX and RX pins if keyboard is master half. Only available on some MCU's. This _is_ available on the RP2040 */
#define SERIAL_USART_PIN_SWAP

/* I2C for OLEDs */
#define I2C1_SDA_PIN GP3
#define I2C1_SCL_PIN GP2

// Cirque Pinnacle trackpad configuration
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_ROTATION_270
#define POINTING_DEVICE_RIGHT
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define CIRQUE_PINNACLE_CURVED_OVERLAY

#define EE_HANDS
