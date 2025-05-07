#include "pico/stdlib.h"
#include <stdio.h>
#include "lib/pico_as5600/pico_as5600.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"


#define SPACES "                              "
#define AS5600_SDA 2
#define AS5600_SCL 3

// Connect SDA to pin 2 and scl to pin 3 on rp2040.


void print_msg(char* msg)
{
    printf("---- %s ----" SPACES "\n", msg);
}

// Read  and print zpos (zero position), mpos (max positon), mang (max angle)
void print_poss_and_angs(as5600_t* as5600)
{
    print_msg("AS5600 zpos mpos mang");
    printf("zpos: %d\n", as5600_read_zpos(as5600));
    printf("mpos: %d\n", as5600_read_mpos(as5600));
    printf("mang: %d\n", as5600_read_mang(as5600));
}

int main()
{
    as5600_t as5600 = { 0 };
    static float value;

    stdio_init_all();
    printf("Switch serial to terminal mode so carriage return is respected!\n");

    // Setup i2c
    gpio_init(AS5600_SDA);
    gpio_set_function(AS5600_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(AS5600_SDA);

    gpio_init(AS5600_SCL);
    gpio_set_function(AS5600_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(AS5600_SCL);

    i2c_init(i2c1, 400 * 1000);

    // Setup as5600
    as5600_init(AS5600_SDA, AS5600_SCL, &as5600);


    // Display raw angle
    print_msg("AS5600 read raw angle");

    as5600_write_zpos(&as5600, 787);

    while (true) {
        value = (float)as5600_read_angl(&as5600)/(float)AS5600_MAX_ANGLE*360;

        printf("Current value: %f%s\r", value, SPACES);
    }
}