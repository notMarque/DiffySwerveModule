#pragma once
#include "hardware/pwm.h"
#include "pico/stdlib.h"

class DRV8245HW
{ 
    protected:

    public:
    DRV8245HW() {}
    void init(void);
    void setMotorEffort(double effort);
};