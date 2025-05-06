#pragma once
#include "quadrature_encoder_substep.pio.h"
#include "quadrature_encoder_substep.c"

class Encoder
{
protected: 
substep_state_t state;
uint last_position = 0;
int last_speed = 0;
uint last_raw_step = 0;


public: 
Encoder() {}
void init(PIO pio, int sm, int PIN_A ) {
    pio_add_program(pio, &quadrature_encoder_substep_program); 
    substep_set_calibration_data(&state, 64, 128, 192); 
    substep_init_state(pio, sm, PIN_A, &state); 
}
void update(bool print){
    substep_update(&state);
    if (last_position != state.position || last_speed != state.speed || last_raw_step != state.raw_step) {
    // print out the result
    printf("pos: %-10d  speed: %-10d  raw_steps: %-10d\n", state.position, state.speed, state.raw_step);
    last_position = state.position;
    last_speed = state.speed;
    last_raw_step = state.raw_step;
 }}


};