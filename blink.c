/**
 * Test file to check upload and PWM function 
 * NOTE: must add  hardware_pwm to target_link_libraries in CMakeLists 
 */

 #include "pico/stdlib.h"
 #include "hardware/pwm.h"
 
 #define LED_DELAY_MS 500
 #define BLUE_LED 21 //2B
 #define GREEN_LED 22
 
 
 
 int main() {
     gpio_set_function(BLUE_LED, GPIO_FUNC_PWM);
     uint slice = pwm_gpio_to_slice_num (BLUE_LED); 
     uint channel = pwm_gpio_to_channel (BLUE_LED);
     pwm_set_wrap(slice, 12500);
     pwm_set_enabled (slice, true);
 
     pwm_set_chan_level(slice, channel, 3000);
 
     gpio_init(GREEN_LED);
     gpio_set_dir(GREEN_LED, GPIO_OUT);
 
     while (true) {
         pwm_set_gpio_level(BLUE_LED, 12000);
         gpio_put(GREEN_LED, false);
 
         sleep_ms(LED_DELAY_MS);
 
         pwm_set_gpio_level(BLUE_LED, 3000);
         gpio_put(GREEN_LED, true);
 
         sleep_ms(LED_DELAY_MS);
     }
 }
 