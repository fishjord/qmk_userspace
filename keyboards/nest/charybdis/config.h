// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/* Serial USART Full Duplex for Split Communication */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

/* Handedness via EEPROM */
#define EE_HANDS

/* Split Pointing Device Settings */
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT

/* PMW3360 Chip Select Pin Definitions */
#define POINTING_DEVICE_CS_PIN GP28
#define PMW33XX_CS_PIN GP28
#define PMW33XX_CS_PIN_RIGHT GP28

/* RP2040 Hardware SPI0 Configuration (GP2=SCK, GP3=MOSI, GP4=MISO) */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4
