
#include "pico/stdlib.h"
#include "Motor.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
#include "Params.h"


bool countUp = true;
double motorOut = 0;
Motor rightMotor;
Motor leftMotor;

void loop(void){
   //printf("Looping \n");
   
  if(countUp){
     motorOut += 250;
     countUp = motorOut <= 20000;
  } else {
     motorOut += -250;
     countUp = motorOut <= 0;
  }
  
  //rightMotor.setSpeed(10000);
  //printf("%f\n", motorOut); 

   // read the PIO and update the state data
   //rightMotor.setSpeed(-(20000 + motorOut));
   //leftMotor.setSpeed(20000 + motorOut);
   leftMotor.update(true);
   //rightMotor.update(true);

   // run at roughly 100Hz
   sleep_ms(MOTOR_LOOP_MS);
}

void initLED(void){
  gpio_init(GREEN_LED);
  gpio_set_dir(GREEN_LED, GPIO_OUT);
  gpio_init(BLUE_LED);
  gpio_set_dir(BLUE_LED, GPIO_OUT);
}


int main() {
  //Init Green LED
  stdio_init_all();
  initLED();
  leftMotor.SetParams(
      LEFT_MOTOR_DRIVE_PIN,  
      LEFT_MOTOR_DIRECT_PIN, 
      LEFT_FAULT_N,  
      LEFT_SLEEP_N,  
      MOTORSLICE, 
      LEFT_PIO, 
      LEFT_SM, 
      LEFT_ENCODER_PIN_A, 
      LEFT_KP, 
      LEFT_KI, 
      LEFT_KV
 );

 rightMotor.SetParams(
   RIGHT_MOTOR_DRIVE_PIN,  
   RIGHT_MOTOR_DIRECT_PIN, 
   RIGHT_FAULT_N,  
   RIGHT_SLEEP_N,  
   MOTORSLICE, 
   RIGHT_PIO, 
   RIGHT_SM, 
   RIGHT_ENCODER_PIN_A, 
   RIGHT_KP, 
   RIGHT_KI, 
   RIGHT_KV
); 

  gpio_put(GREEN_LED, true);
  gpio_put(BLUE_LED, true);
  
  leftMotor.setSpeed(300000);
  leftMotor.update(false);
  //rightMotor.setSpeed(300000);
  //rightMotor.update(false);

  while (true) {
     loop();
  } 
}





