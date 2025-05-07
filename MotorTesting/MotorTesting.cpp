
#include "pico/stdlib.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
#define GREEN_LED 21
#define BLUE_LED 22 
#define LED_DELAY_MS 500

#define LEFT_MOTOR_DRIVE_PIN 14
#define LEFT_MOTOR_DIRECT_PIN 13
#define LEFT_SLEEP_N 10
#define LEFT_FAULT_N 12 
#define RIGHT_MOTOR_DRIVE_PIN 19
#define RIGHT_MOTOR_DIRECT_PIN 18
#define RIGHT_SLEEP_N 16
#define RIGHT_FAULT_N 17 
#define motorSlice 12500
 #define SPACES "                              "
bool countUp = true;
double motorOut = 0;
DRV8245HW leftMotor;
DRV8245HW rightMotor;

const uint RIGHT_ENCODER_PIN_A = 8;
PIO RIGHT_PIO = pio0;
const uint RIGHT_SM = 0;

const uint LEFT_ENCODER_PIN_A = 6;
PIO LEFT_PIO = pio0;
const uint LEFT_SM = 1;
Encoder leftEncoder;
Encoder rightEncoder;
void loop(void){
   //printf("Looping \n");
   
  if(countUp){
     motorOut += .0001;
     countUp = motorOut <= 1;
  } else {
     motorOut += -.0001;
     countUp = motorOut <= 0;
  }
  leftMotor.setMotorEffort(motorOut);
  rightMotor.setMotorEffort(motorOut);
  printf("%f\n", motorOut); 

   // read the PIO and update the state data
   rightEncoder.update(true);
   leftEncoder.update(true);

   // run at roughly 100Hz
   sleep_ms(10);
}


int main() {
  //Init Green LED
  stdio_init_all();
  rightMotor.setParams(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_DIRECT_PIN, RIGHT_FAULT_N, RIGHT_SLEEP_N, motorSlice);
  rightMotor.init();
  leftMotor.setParams(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_DIRECT_PIN, LEFT_FAULT_N, LEFT_SLEEP_N, motorSlice);
  leftMotor.init(); 
  gpio_init(GREEN_LED);
  gpio_set_dir(GREEN_LED, GPIO_OUT);
  gpio_init(BLUE_LED);
  gpio_set_dir(BLUE_LED, GPIO_OUT);
  gpio_put(GREEN_LED, true);
  gpio_put(BLUE_LED, true);
  leftEncoder.init(LEFT_PIO, LEFT_SM, LEFT_ENCODER_PIN_A);
  rightEncoder.init(RIGHT_PIO, RIGHT_SM, RIGHT_ENCODER_PIN_A); 

  while (true) {
     loop();
  } 
}


