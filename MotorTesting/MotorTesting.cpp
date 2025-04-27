
#include "pico/stdlib.h"
#include "./DRV8245HW/DRV8245HW.h"
#define GREEN_LED 22
#define BLUE_LED 21 
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

bool countUp = true;
double motorOut = 0;
DRV8245HW leftMotor;
DRV8245HW rightMotor;

void loop(void){
   printf("Looping \n");
  if(countUp){
     motorOut += .000003;
     countUp = motorOut <= 1;
  } else {
     motorOut += -.000003;
     countUp = motorOut <= 0;
  }
  leftMotor.setMotorEffort(.5);
  rightMotor.setMotorEffort(motorOut);
}

int main() {
  //Init Green LED
  stdio_init_all();
  gpio_init(GREEN_LED);
  gpio_set_dir(GREEN_LED, GPIO_OUT);
  gpio_init(BLUE_LED);
  gpio_set_dir(BLUE_LED, GPIO_OUT);
  rightMotor.setParams(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_DIRECT_PIN, RIGHT_FAULT_N, RIGHT_SLEEP_N, motorSlice);
  rightMotor.init();
  leftMotor.setParams(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_DIRECT_PIN, LEFT_FAULT_N, LEFT_SLEEP_N, motorSlice);
  leftMotor.init();
  gpio_put(GREEN_LED, true);

 
  //Setting Motor Direction
  while (true) {
     loop();
  }
}

