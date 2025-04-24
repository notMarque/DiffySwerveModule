/**
 * Test file to check upload and PWM function 
 * NOTE: must add  hardware_pwm to target_link_libraries in CMakeLists 
 */

 #include "pico/stdlib.h"
 #include "hardware/pwm.h"
 
 #define LED_DELAY_MS 500
 #define BLUE_LED 21 //2B
 #define GREEN_LED 22
 #define MOTOR_DRIVE_PIN 14
 #define MOTOR_DIRECT_PIN 13
 #define SLEEP_N 10
 #define FAULT_N 12 
 
 
 int main() {

    //Init Blue LED
     gpio_set_function(BLUE_LED, GPIO_FUNC_PWM);
     uint blueSlice = pwm_gpio_to_slice_num (BLUE_LED); 
     uint blueChannel = pwm_gpio_to_channel (BLUE_LED);
     pwm_set_wrap(blueSlice, 12500);
     pwm_set_enabled (blueSlice, true);

     //Init Green LED
     gpio_init(GREEN_LED);
     gpio_set_dir(GREEN_LED, GPIO_OUT);

     //Init Motor pins
     gpio_set_function(MOTOR_DRIVE_PIN, GPIO_FUNC_PWM);
     uint driveSlice = pwm_gpio_to_slice_num (MOTOR_DRIVE_PIN); 
     uint driveChannel = pwm_gpio_to_channel (MOTOR_DRIVE_PIN);
     pwm_set_wrap(driveSlice, 12500);
     pwm_set_enabled (driveSlice, true);
     pwm_set_chan_level(driveSlice, driveChannel, 3000);

     
     gpio_init(MOTOR_DIRECT_PIN);
     gpio_set_dir(MOTOR_DIRECT_PIN, GPIO_OUT);

      //Init Sleep Pin
      gpio_init(SLEEP_N);
      gpio_set_dir(SLEEP_N, GPIO_OUT);

      //Init Fault
      gpio_init(FAULT_N);
      gpio_set_dir(FAULT_N, GPIO_IN);
    
      gpio_put(SLEEP_N, true);

     // Wait until it recognizes sleep pulse
     while(gpio_get(FAULT_N) == true)
     {
        pwm_set_gpio_level(BLUE_LED, 0);  
     } 
     gpio_put(SLEEP_N, false);
     sleep_ms(.008);
     gpio_put(SLEEP_N, true);

     pwm_set_gpio_level(BLUE_LED, 12000); 
     
     while(!gpio_get(FAULT_N)) {
        // nada
     }

     gpio_put(GREEN_LED, true);

    //Turning the motor on
     gpio_put(MOTOR_DIRECT_PIN, false);
     while (true) {
         pwm_set_gpio_level(MOTOR_DRIVE_PIN, -12000);
     }
 }
 