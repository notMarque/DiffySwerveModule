
/**
 * Test file to check upload and PWM function 
 * NOTE: must add  hardware_pwm to target_link_libraries in CMakeLists 
 */

 #include "pico/stdlib.h"
 #include "./DRV8245HW/DRV8245HW.h"
 #define GREEN_LED 22
 #define LED_DELAY_MS 500

 #define LEFT_MOTOR_DRIVE_PIN 14
 #define LEFT_MOTOR_DIRECT_PIN 13
 #define LEFT_SLEEP_N 10
 #define LEFT_FAULT_N 12 
 #define motorSlice 12500


 bool countUp = true;
 double motorOut = 0;
 DRV8245HW leftMotor;
 DRV8245HW rightMotor;

 void loop(void){
   if(countUp){
      motorOut += .000003;
      countUp = motorOut <= 1;
   } else {
      motorOut += -.000003;
      countUp = motorOut <= -1;
   }
   leftMotor.setMotorEffort(.8);
 }

 int main() {
   leftMotor.setParams(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_DIRECT_PIN, LEFT_FAULT_N, LEFT_SLEEP_N, motorSlice);
   leftMotor.init();
   //Init Green LED
   gpio_init(GREEN_LED);
   gpio_set_dir(GREEN_LED, GPIO_OUT);
   gpio_put(GREEN_LED, true);
   //Setting Motor Direction
   while (true) {
      loop();
   }
 }


 