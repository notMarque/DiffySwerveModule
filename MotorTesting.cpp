
#include "pico/stdlib.h"
#include "Motor.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
#include "Params.h"
#include "UART_COMMS/uart_comms.h"
#include <stdio.h>


int main() {
   uart_comms comms;


   comms.init_uart_comms();


   for (int i = 0; i < 100; i++) {
      printf("waiting...");
      sleep_ms(100);
      printf("\twaiting...");
      sleep_ms(100);
   }
   // OK, all set up.
   // Lets send a basic string out, and then run a loop and wait for RX interrupts
   // The handler will count them, but also reflect the incoming data back with a slight change!
   uart_puts(UART_ID, "\nHello, uart interrupts\n");

   while (1)
         tight_loop_contents();
         


}





