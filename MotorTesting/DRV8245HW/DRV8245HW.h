#pragma once 
#include <stdio.h>
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <vector>

class DRV8245HW
{ 
    protected:
    uint16_t MOTOR_DRIVE_PIN;
    uint16_t MOTOR_DIRECT_PIN;
    uint16_t FAULT_N;
    uint16_t SLEEP_N;
    uint16_t motorSlice;
    
    public:
    DRV8245HW() {}
    void init(void);
    void setMotorEffort(double);
    void setParams(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
    void initMultiple(std::vector<uint16_t> FaultPins, std::vector<uint16_t> SleepPins);
    
};