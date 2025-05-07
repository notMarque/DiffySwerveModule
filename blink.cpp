#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/pwm.h>
#include "hardware/clocks.h"
#include <string.h>
#include <maini2c.h>
#include <modulei2c.h>
#include <structs.h>
#include <main_rec_i2c.h>


int main() {
    stdio_init_all();

    puts("\nI2C slave example");

    //maini2c hub;
    //modulei2c module;
    main_rec_i2c main_rec;
    //ModuleState state = ModuleState(1, 2, 3, 4, 5);
    //ModuleState returnState = ModuleState();
    BotState botSt = BotState();
    

    //hub.setup_slave();
    //module.setup_slave(0x17);
    //hub.init_master();
    main_rec.setup_slave(0x16);
    //thisi2c.run_master();
    for (int i = 0; i < 30; i++) {
        sleep_ms(100);
        puts("howdy");
    }
    //hub.send_message(state, 0x17);
    //module.save_to_mem(state);
    sleep_ms(100);
    //module.read_message(state);
    //hub.read_message(returnState, 0x17);
    //main_rec.read_message(botSt);

    while (true) {
        //module.read_message(state);
        main_rec.read_message(botSt);
        sleep_ms(100);
    }
    
}
