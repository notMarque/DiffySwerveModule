#pragma once

#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>

class maini2c {
public:
    static const uint I2C_SLAVE_ADDRESS = 0x17;
    static const uint I2C_BAUDRATE = 100000; // 100 kHz

    // For this example, we run both the master and slave from the same board.
    // You'll need to wire pin GP4 to GP6 (SDA), and pin GP5 to GP7 (SCL).
    static const uint I2C_SLAVE_SDA_PIN = 4;
    static const uint I2C_SLAVE_SCL_PIN = 5;
    static const uint I2C_MASTER_SDA_PIN = 6;
    static const uint I2C_MASTER_SCL_PIN = 7;


    static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
    static void setup_slave();
    static void run_master();

    uint8_t getByte(uint8_t address); 
};