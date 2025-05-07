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

// 12 Bytes
struct BotState {
    float u = 0.0f;
    float v = 0.0f;
    float w = 0.0f;

    BotState(void) {}
    BotState(float _u, float _v, float _w) : u(_u), v(_v), w(_w) {}
};

// This is a struct for the geometric position of a swerve module in case you can't tell from the name
// 
struct Cecilia {
    float x = 0.0f;
    float y = 0.0f;

    Cecilia(void) {}

    Cecilia(float _x, float _y) : x(_x), y(_y) {}
};

#endif