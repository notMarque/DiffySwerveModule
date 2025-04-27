
/**
 * Test file to check upload and PWM function 
 * NOTE: must add  hardware_pwm to target_link_libraries in CMakeLists 
 */

 #include "pico/stdlib.h"
 #include <DRV8245HW.h>
 

 bool countUp = true;
 double motorOut = 0;

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


 