#include "pico/stdlib.h"

#define LED_DELAY_MS 500
#define BLUE_LED 21
#define GREEN_LED 22



int main() {
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
    }
}
