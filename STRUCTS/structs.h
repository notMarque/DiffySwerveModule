#ifndef STRUCTS_TEST_H
#define STRUCTS_TEST_H

// 10 bytes
struct ModuleState {
    uint8_t state = 0;
    uint16_t theta = 0;
    int16_t v = 0;
    uint8_t bat = 0;
    uint32_t time = 0;
    

    ModuleState(void) {}
    ModuleState(uint8_t _state, uint16_t _theta, int16_t _v, uint8_t _bat, long _time) : state(_state), theta(_theta), v(_v), bat(_bat), time(_time) {}
};

#endif