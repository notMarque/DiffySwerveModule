#pragma once 
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"

class Motor{
protected: 
DRV8245HW drv;
Encoder encoder;
int32_t desiredSpeed = 0;
double KV;
double KP;
double KI;
double sumError = 0;
public: 
Motor(){}
void SetParams(int drivePin, 
               int directPin, 
               int fault, 
               int sleep, 
               int motorSlice,
               PIO pio,
               int sm, 
               int encoderA, 
               double KP, 
               double KI, 
               double KV );
void setSpeed(int32_t speed);
void update(bool print);
};