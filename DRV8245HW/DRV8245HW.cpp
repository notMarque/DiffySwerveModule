
#include "DRV8245HW.h"


void DRV8245HW::setParams(uint16_t _MOTOR_DRIVE_PIN, uint16_t _MOTOR_DIRECT_PIN,uint16_t _FAULT_N, uint16_t _SLEEP_N, uint16_t _motorSlice){
   MOTOR_DRIVE_PIN = _MOTOR_DRIVE_PIN;
   MOTOR_DIRECT_PIN = _MOTOR_DIRECT_PIN;
   FAULT_N = _FAULT_N;
   SLEEP_N = _SLEEP_N;
   motorSlice = _motorSlice;
}

void DRV8245HW::init(){
 
    //Init Motor pins
    gpio_set_function(MOTOR_DRIVE_PIN, GPIO_FUNC_PWM);
    uint driveSlice = pwm_gpio_to_slice_num (MOTOR_DRIVE_PIN); 
    uint driveChannel = pwm_gpio_to_channel (MOTOR_DRIVE_PIN);
    pwm_set_wrap(driveSlice, motorSlice);
    pwm_set_enabled (driveSlice, true);
    pwm_set_chan_level(driveSlice, driveChannel, 3000);
 
    gpio_init(MOTOR_DIRECT_PIN);
    gpio_set_dir(MOTOR_DIRECT_PIN, GPIO_OUT);
 
    //Init Sleep Pin
    gpio_init(SLEEP_N);
    gpio_set_dir(SLEEP_N, GPIO_OUT);
 
    //Init Fault
    gpio_init(FAULT_N);
    gpio_set_dir(FAULT_N, GPIO_IN);
 
    gpio_put(SLEEP_N, true);
 
    // Wait until it recognizes sleep pulse
    while(gpio_get(FAULT_N) == true)
    {
      printf("motors not recognizing wakeup\n");
    } 
    gpio_put(SLEEP_N, false);
    sleep_ms(.008);
    gpio_put(SLEEP_N, true);

    while(!gpio_get(FAULT_N)) {
      printf("motors not responding to second pulse\n");
      gpio_put(SLEEP_N, false);
      sleep_ms(.008);
      gpio_put(SLEEP_N, true);
    }
    setMotorEffort(0);
    printf("Motor wakeup\n");
  }

  void DRV8245HW::setMotorEffort(double effort){
    if(effort == 0)
    {
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, 0);
    } else if(0 < effort && effort <= 1.01){
       gpio_put(MOTOR_DIRECT_PIN, false);
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, effort * motorSlice);
    } else if (-1.01 <= effort){
       gpio_put(MOTOR_DIRECT_PIN, true);
       pwm_set_gpio_level(MOTOR_DRIVE_PIN, (-effort) * motorSlice);
    } else {
       pwm_set_gpio_level(MOTOR_DRIVE_PIN,0);
       printf("WARNING: MOTOR EFFORT OUTSIDE OF BOUNDS");
    }
   }

   void DRV8245HW::initMultiple(std::vector<uint16_t> FaultPins, std::vector<uint16_t> SleepPins){
      //Init Sleep Pins
      for (uint16_t SleepPin : SleepPins) {
         gpio_init(SleepPin);
         gpio_set_dir(SleepPin, GPIO_OUT);
      }
      
      //Init Fault
      for(uint16_t FaultPin : FaultPins){
         gpio_init(FaultPin);
         gpio_set_dir(FaultPin, GPIO_IN);
      }
      
      //send wake up pulse
      for (uint16_t SleepPin : SleepPins) {
      gpio_put(SleepPin, true);
      }

      // Wait until they recognize wake up pulse
      while(gpio_get(SleepPins[0]) == true)
      {
         printf("motors not recognizing wakeup\n");
      } 

      //Send wake up confirm for all 
      for (uint16_t SleepPin : SleepPins) {
      gpio_put(SleepPin, false);
      }
      sleep_ms(.008);
      for (uint16_t SleepPin : SleepPins) {
      gpio_put(SleepPin, true);
      }
      while(!gpio_get(SleepPins[1])) {
         printf("motors not responding to second pulse\n");
      }
   }
 