#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/pwm.h>
#include "hardware/clocks.h"
#include <string.h>
#include <maini2c.h>
#include <modulei2c.h>

#define LED_DELAY_MS 500
#define BLUE_LED 21
#define GREEN_LED 22;



int main() {
    stdio_init_all();

    // gpio_init(BLUE_LED);
    // gpio_set_dir(BLUE_LED, GPIO_OUT);

    // gpio_init(GREEN_LED);
    // gpio_set_dir(GREEN_LED, GPIO_OUT);

    puts("\nI2C slave example");

    maini2c hub;
    modulei2c module;

    //hub.setup_slave();
    module.setup_slave();
    hub.init_master();
    //thisi2c.run_master();
    for (int i = 0; i < 50; i++) {
        sleep_ms(100);
        puts("howdy");
    }
    hub.send_message();
    sleep_ms(100);
    module.read_message();

    // while (true) {
    //     thisi2c.run_master();
    //     uint8_t hello = thisi2c.getByte(0);
    //     puts((char *)hello);
    // }

    // while (true) {
    //     gpio_put(BLUE_LED, true);
    //     gpio_put(GREEN_LED, false);

    //     sleep_ms(LED_DELAY_MS);

    //     gpio_put(BLUE_LED, false);
    //     gpio_put(GREEN_LED, true);

    //     sleep_ms(LED_DELAY_MS);
        
    //     uint32_t sys_clk_hz = clock_get_hz(clk_sys);

    //     printf("RP2040 System Clock Frequency: %lu Hz\n", sys_clk_hz);
    //}
}
