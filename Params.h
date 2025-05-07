#pragma once 
#include "pico/stdlib.h"


#define GREEN_LED 21
#define BLUE_LED 22 
#define LED_DELAY_MS 500


#define MOTORSLICE 12500
#define LEFT_KV .000028
#define RIGHT_KV -.000028
#define MOTOR_LOOP_MS 10

#define LEFT_MOTOR_DRIVE_PIN 14
#define LEFT_MOTOR_DIRECT_PIN 13
#define LEFT_SLEEP_N 10
#define LEFT_FAULT_N 12 
#define LEFT_KP 0.000001
#define LEFT_KI 0.00000005

#define RIGHT_MOTOR_DRIVE_PIN 19
#define RIGHT_MOTOR_DIRECT_PIN 18
#define RIGHT_SLEEP_N 16
#define RIGHT_FAULT_N 17 
#define RIGHT_KP -0.000001
#define RIGHT_KI -0.00000005

const uint LEFT_ENCODER_PIN_A = 8;
PIO LEFT_PIO = pio0;
const uint LEFT_SM = 0;

const uint RIGHT_ENCODER_PIN_A = 6;
PIO RIGHT_PIO = pio0;
const uint RIGHT_SM = 1;