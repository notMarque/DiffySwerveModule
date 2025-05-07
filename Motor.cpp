#include "Motor.h"

void Motor::SetParams(int drivePin, int directPin, int fault, int sleep, int motorSlice, PIO pio, int sm, int encoderA, double KP, double KI, double KV){
    drv.setParams(drivePin, directPin, fault, sleep, motorSlice);
    drv.init();
    encoder.init(pio, sm, encoderA);
    this->KI = KI;
    this->KP = KP;
    this->KV = KV;
}


void Motor::setSpeed(int32_t speed){
    desiredSpeed = speed;
    printf("set speed to: %d \n", speed);
}

void Motor::update(bool print){
    encoder.update(false);
    double error = desiredSpeed - encoder.last_speed;
    sumError += error;
    double MotorEffort = 0;
    MotorEffort += (KV * desiredSpeed) / 12; //KV Term
    MotorEffort += KP * error;               //KP Term
    MotorEffort += KI * sumError;            //KI Term
    if(MotorEffort > 1)
    { MotorEffort = 1; } 
    else if(MotorEffort < -1)
    { MotorEffort = -1; } 
    //printf("error: %f       sumError:  %f   MototEffort: %f \n", error, sumError, MotorEffort);
    if(print){
    printf(">error:");
    printf("%f \n", error);
    printf(">desired Speed:");
    printf("%d \n", desiredSpeed);
    printf(">Sum Error:");
    printf("%f \n", sumError);
    printf(">Motor Effort:");
    printf("%f \n", MotorEffort);
    printf(">Speed :");
    printf("%d \n", encoder.last_speed);
    }
    drv.setMotorEffort(MotorEffort);
    
}