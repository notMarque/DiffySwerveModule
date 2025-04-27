
#include "DRV8245HW.h"

#define LED_DELAY_MS 500
#define BLUE_LED 21 //2B
#define GREEN_LED 22
#define MOTOR_DRIVE_PIN 14
#define MOTOR_DIRECT_PIN 13
#define SLEEP_N 10
#define FAULT_N 12 
#define motorSlice 12500

void DRV8245HW::init(void){

    //Init Blue LED
    gpio_set_function(BLUE_LED, GPIO_FUNC_PWM);
    uint blueSlice = pwm_gpio_to_slice_num (BLUE_LED); 
    uint blueChannel = pwm_gpio_to_channel (BLUE_LED);
    pwm_set_wrap(blueSlice, motorSlice);
    pwm_set_enabled (blueSlice, true);
 
    //Init Green LED
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
 
    //Init Motor pins
    gpio_set_function(MOTOR_DRIVE_PIN, GPIO_FUNC_PWM);
    uint driveSlice = pwm_gpio_to_slice_num (MOTOR_DRIVE_PIN); 
    uint driveChannel = pwm_gpio_to_channel (MOTOR_DRIVE_PIN);
    pwm_set_wrap(driveSlice, motorSlice);
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
  }

  void DRV8245HW::setMotorEffort(double effort){
    if(effort == 0)
    {
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, 0);
    } else if(0 < effort && effort <= 1){
       gpio_put(MOTOR_DIRECT_PIN, true);
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, effort * motorSlice);
    } else if (-1 <= effort){
       gpio_put(MOTOR_DIRECT_PIN, false);
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, -1 * effort * motorSlice);
    } else {
       pwm_set_gpio_level(MOTOR_DRIVE_PIN,0);
       //TODO: Put warning here once serial works
    }
 }