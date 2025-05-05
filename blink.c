#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include "hardware/clocks.h"

#define LED_DELAY_MS 500
#define BLUE_LED 21
#define GREEN_LED 22



int main() {
    stdio_init_all();

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    while (true) {
        gpio_put(BLUE_LED, true);
        gpio_put(GREEN_LED, false);

        sleep_ms(LED_DELAY_MS);

        gpio_put(BLUE_LED, false);
        gpio_put(GREEN_LED, true);

        sleep_ms(LED_DELAY_MS);
        
        uint32_t sys_clk_hz = clock_get_hz(clk_sys);

        printf("RP2040 System Clock Frequency: %lu Hz\n", sys_clk_hz);
    }
}
