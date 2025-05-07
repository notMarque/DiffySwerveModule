
#include "pico/stdlib.h"
#include "Motor.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
extern "C" {
   #include "./pico_as5600/pico_as5600.h" 
}
#include "Params.h"


bool countUp = true;
double motorOut = 0;
Motor rightMotor;
Motor leftMotor;

as5600_t as5600 = { 0 };
static float value;
double desiredHeading = 0;
double sumHeadingError = 0;
double linearSpeed = 200000;
void loop(void){
   //printf("Looping \n");
   
  if(countUp){
   desiredHeading += 1;
     countUp = desiredHeading <= 270;
  } else {
   desiredHeading += -1;
     countUp = desiredHeading <= 0;
  }
  
  //rightMotor.setSpeed(10000);
  //printf("%f\n", motorOut); 

   // read the PIO and update the state data
   //rightMotor.setSpeed(-(20000 + motorOut));
   //leftMotor.setSpeed(20000 + motorOut);
   
   float heading = (float)as5600_read_angl(&as5600)/(float)AS5600_MAX_ANGLE*360;
   float headingError = heading - desiredHeading;
   
   if(headingError > 180){
      headingError = -(180 - (headingError - 180));
   }

   sumHeadingError += headingError;
   double turnSpeed = headingError * TICKS_PER_SECOND_PER_DEGREE + sumHeadingError * ANGULAR_KI;
   
   if(-.01 < headingError && headingError < .01 )
   {
   sumHeadingError = 0;
   leftMotor.setSpeed(0 + linearSpeed/2);
   rightMotor.setSpeed(0 - linearSpeed/2);
   } else {
   leftMotor.setSpeed(turnSpeed/2 + linearSpeed/2);
   rightMotor.setSpeed(turnSpeed/2 - linearSpeed/2);
   }
   
   leftMotor.update(false);
   rightMotor.update(false);
   printf(">Heading :");
   printf("%f \n", heading);
   printf(">Desired Heading :");
   printf("%f \n", desiredHeading);
   printf(">Heading Error :");
   printf("%f \n", headingError);
   printf(">Turn Speed :");
   printf("%f \n", turnSpeed);
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
   //Init All of The things
   stdio_init_all();
   initLED();
   
   //Motor Initialization 
   
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
   
   //as56000 shit
   // Setup i2c
   gpio_init(AS5600_SDA);
   gpio_set_function(AS5600_SDA, GPIO_FUNC_I2C);
   gpio_pull_up(AS5600_SDA);

   gpio_init(AS5600_SCL);
   gpio_set_function(AS5600_SCL, GPIO_FUNC_I2C);
   gpio_pull_up(AS5600_SCL);
   i2c_init(i2c1, 400 * 1000);

   // Setup as5600
   as5600_init(AS5600_SDA, AS5600_SCL, &as5600);

   as5600_write_zpos(&as5600, 787);

   gpio_put(GREEN_LED, true);
   gpio_put(BLUE_LED, true);
   
   leftMotor.setSpeed(300000);
   leftMotor.update(false);
   rightMotor.setSpeed(000000);
   rightMotor.update(false);

   while (true) {
      loop();
   } 
}





