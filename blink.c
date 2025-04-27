
/**
 * Test file to check upload and PWM function 
 * NOTE: must add  hardware_pwm to target_link_libraries in CMakeLists 
 */

 #include "pico/stdlib.h"
 #include <DRV8245HW.h>
 
 #define LED_DELAY_MS 500
 #define BLUE_LED 21 //2B
 #define GREEN_LED 22
 #define MOTOR_DRIVE_PIN 14
 #define MOTOR_DIRECT_PIN 13
 #define SLEEP_N 10
 #define FAULT_N 12 
 
 bool countUp = true;
 double motorOut = 0;
 int motorSlice = 12500;


 void loop(void){
   if(countUp){
      motorOut += .000003;
      countUp = motorOut <= 1;
   } else {
      motorOut += -.000003;
      countUp = motorOut <= -1;
   }
   setMotorEffort(.1);
 }

 int main() {
   init();
   //Setting Motor Direction
   while (true) {
      loop();
   }
 }


 