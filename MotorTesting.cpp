
#include "pico/stdlib.h"
#include "Motor.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
#include "Params.h"
#include "UART_COMMS/uart_comms.h"


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
   uart_comms comms;


   

   // OK, all set up.
   // Lets send a basic string out, and then run a loop and wait for RX interrupts
   // The handler will count them, but also reflect the incoming data back with a slight change!
   uart_puts(UART_ID, "\nHello, uart interrupts\n");

   while (1)
         tight_loop_contents();


}





