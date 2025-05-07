#pragma once
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "STRUCTS/structs.h"
#include <string.h>
#include <stdio.h>

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

class uart_comms { 
public:
#define UART_ID uart1
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 24
#define UART_RX_PIN 25

static uint8_t mvArray[sizeof(BotState)]; //array for receiving data from the OpenMV cam
static uint8_t mvIndex; //for counting bytes

static int chars_rxed;

static BotState botSt;

static void checkUART(void);
static bool handleUART(uint8_t b);
static void on_uart_rx();
static void init_uart_comms();
};