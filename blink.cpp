#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/pwm.h>
#include "hardware/clocks.h"
#include <string.h>
#include <maini2c.h>
#include <modulei2c.h>
#include <structs.h>


int main() {
    stdio_init_all();

    puts("\nI2C slave example");

    maini2c hub;
    modulei2c module;
    ModuleState state = ModuleState(1, 2, 3, 4, 5);
    ModuleState returnState = ModuleState();


    //hub.setup_slave();
    module.setup_slave();
    hub.init_master();
    //thisi2c.run_master();
    for (int i = 0; i < 30; i++) {
        sleep_ms(100);
        puts("howdy");
    }
    hub.send_message(state);
    module.save_to_mem(state);
    sleep_ms(100);
    module.read_message(state);
    hub.read_message(returnState);

    
}
