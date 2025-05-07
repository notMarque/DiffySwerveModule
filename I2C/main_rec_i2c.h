#pragma once

#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>
#include <structs.h>

class main_rec_i2c {
public:
    static const uint I2C_BAUDRATE = 100000; // 100 kHz

    // For this example, we run both the master and slave from the same board.
    // You'll need to wire pin GP4 to GP6 (SDA), and pin GP5 to GP7 (SCL).
    static const uint I2C_SLAVE_SDA_PIN = 24;
    static const uint I2C_SLAVE_SCL_PIN = 25;

    static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
    static void setup_slave(uint address);
    static void read_message(BotState&);
    static void save_to_mem(BotState&);
};