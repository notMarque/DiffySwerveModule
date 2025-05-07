
#include "pico/stdlib.h"
#include "./DRV8245HW/DRV8245HW.h"
#include "./EncoderLib/quadrature_encoder_substep.h"
#include "./dwm_pico_AS5600/dwm_pico_AS5600.h"
#define GREEN_LED 21
#define BLUE_LED 22 
#define LED_DELAY_MS 500

#define LEFT_MOTOR_DRIVE_PIN 14
#define LEFT_MOTOR_DIRECT_PIN 13
#define LEFT_SLEEP_N 10
#define LEFT_FAULT_N 12 
#define RIGHT_MOTOR_DRIVE_PIN 19
#define RIGHT_MOTOR_DIRECT_PIN 18
#define RIGHT_SLEEP_N 16
#define RIGHT_FAULT_N 17 
#define motorSlice 12500

bool countUp = true;
double motorOut = 0;
DRV8245HW leftMotor;
DRV8245HW rightMotor;

const uint RIGHT_ENCODER_PIN_A = 8;
PIO RIGHT_PIO = pio0;
const uint RIGHT_SM = 0;

const uint LEFT_ENCODER_PIN_A = 6;
PIO LEFT_PIO = pio0;
const uint LEFT_SM = 1;
Encoder leftEncoder;
Encoder rightEncoder;
void loop(void){
   //printf("Looping \n");
   
  if(countUp){
     motorOut += .0001;
     countUp = motorOut <= 1;
  } else {
     motorOut += -.0001;
     countUp = motorOut <= 0;
  }
  leftMotor.setMotorEffort(motorOut);
  rightMotor.setMotorEffort(motorOut);
  printf("%f\n", motorOut); 

   // read the PIO and update the state data
   rightEncoder.update(true);
   leftEncoder.update(true);

   // run at roughly 100Hz
   sleep_ms(10);
}

 // Connect SDA to pin 4 and scl to pin 5 on pi pico.
 
 // Print configuration
 void print_conf(as5600_conf_t* as5600_conf)
 {
     const char* outs[] = { "Analog full", "Analog reduced", "Digital PWM" };
     const uint16_t pwmf[] = { 115, 230, 460, 920 };
     const uint8_t sf[] = { 16, 8, 4, 2 };
     const uint8_t fth[] = { 0, 6, 7, 9, 18, 21, 24, 10 };
 
     printf("Power mode : ");
 
     if (as5600_conf->pm == 0)
         printf("NORMAL\n");
     else
         printf("LPM%d\n", as5600_conf->pm);
 
     printf("Hysteresis : %d\n", as5600_conf->hyst);
     printf("Output stage : %s\n", outs[as5600_conf->outs]);
     printf("PWM frequency : %dHZ\n", pwmf[as5600_conf->pwmf]);
     printf("Slow filter : %dx\n", sf[as5600_conf->sf]);
     printf("Fast filter threshold : %dLSB\n", fth[as5600_conf->fth]);
     printf("Watchdog : ");
 
     if (as5600_conf->wd > 0)
         printf("ENABLED\n");
     else
         printf("DISABLED\n");
 }
 
 void print_msg(char* msg)
 {
     printf("---- %s ----" SPACES "\n", msg);
 }
 
 // Read  and print zpos (zero position), mpos (max positon), mang (max angle)
 void print_poss_and_angs(as5600_t* as5600)
 {
     print_msg("AS5600 zpos mpos mang");
     printf("zpos: %d\n", as5600_read_zpos(as5600));
     printf("mpos: %d\n", as5600_read_mpos(as5600));
     printf("mang: %d\n", as5600_read_mang(as5600));
 }
 

int main() {
  //Init Green LED
  stdio_init_all();
  /*
  rightMotor.setParams(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_DIRECT_PIN, RIGHT_FAULT_N, RIGHT_SLEEP_N, motorSlice);
  rightMotor.init();
  leftMotor.setParams(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_DIRECT_PIN, LEFT_FAULT_N, LEFT_SLEEP_N, motorSlice);
  leftMotor.init(); 
  gpio_init(GREEN_LED);
  gpio_set_dir(GREEN_LED, GPIO_OUT);
  gpio_init(BLUE_LED);
  gpio_set_dir(BLUE_LED, GPIO_OUT);
  gpio_put(GREEN_LED, true);
  gpio_put(BLUE_LED, true);
  leftEncoder.init(LEFT_PIO, LEFT_SM, LEFT_ENCODER_PIN_A);
  rightEncoder.init(RIGHT_PIO, RIGHT_SM, RIGHT_ENCODER_PIN_A); 

  while (true) {
     loop();
  } */
  as5600_t as5600 = { 0 };
  static as5600_conf_t as5600_conf;
  static as5600_conf_t as5600_conf_bckp;
  static uint16_t value, reach, zpos, mpos, mang;

  stdio_init_all();
  printf("Switch serial to terminal mode so carriage return is respected!\n");

  // Setup i2c
  i2c_init(i2c_default, 400 * 1000);

  // Setup as5600
  as5600_init(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, &as5600);

  // Read as5600 configuration
  as5600_read_conf(&as5600, &as5600_conf);

  // Print configuration
  print_msg("AS5600 configuration");
  print_conf(&as5600_conf);

  // Read status
  print_msg("AS5600 status");
  printf("Magnet on a scale : %d\n", as5600_status_to_scale(as5600_read_status(&as5600)));

  // Read magnitude
  print_msg("AS5600 magnitude");
  printf("Magnitude : %d\n", as5600_read_magnitude(&as5600));

  // Read AGC
  print_msg("AS5600 automatic gain control");
  printf("AGC : %d\n", as5600_read_agc(&as5600));

  // ZMCO
  print_msg("AS5600 ZMCO");
  printf("ZMCO (Number of setting burns) : %d\n", as5600_read_zmco(&as5600));

  // Write zpos, mpos, mang
  as5600_write_zpos(&as5600, zpos);
  as5600_write_mpos(&as5600, mpos);
  as5600_write_mang(&as5600, mang);
  print_poss_and_angs(&as5600);

  // Display raw angle
  print_msg("AS5600 read raw angle");

  reach = AS5600_MAX_ANGLE / 4; // ~90 degrees

  printf("Reach: %d\n", reach);

  while (value != reach) {
      value = as5600_read_raw_angl(&as5600);

      printf("Current value: %d%s\r", value, SPACES);
      printf("\n");
  }

  // Display raw angle in degrees
  print_msg("AS5600 read raw angle in degrees");

  reach = 270;

  printf("Reach: %d degrees\n", reach);

  while (value != reach) {
      value = as5600_angl_to_degr(as5600_read_raw_angl(&as5600), 0, AS5600_MAX_ANGLE);

      printf("Current value: %d degrees%s\r", value, SPACES);
      printf("\n");
  }

  // Write zpos (zero position)
  zpos = AS5600_MAX_ANGLE / 2 + 1; // ~180 degrees

  as5600_write_zpos(&as5600, zpos);
  print_poss_and_angs(&as5600);

  // Show difference between raw and non-raw zero position value
  print_msg("AS5600 read raw and non-raw angle");

  reach = 0;

  printf("Reach: %d\n", reach);
  printf("Note: for non raw, zpos has changed.\n");

  while (value != reach) {
      value = as5600_read_raw_angl(&as5600);

      printf("Raw value: %d | Non-raw value: %d%s\r", value, as5600_read_angl(&as5600), SPACES);
      printf("\n");
  }

  // Write zpos and mpos
  zpos = 0; // reset
  mpos = AS5600_MAX_ANGLE / 2 + 1; // ~180 degrees

  as5600_write_zpos(&as5600, zpos);
  as5600_write_mpos(&as5600, mpos);
  print_poss_and_angs(&as5600);

  // Show how mpos works
  print_msg("AS5600 display non-raw angle in degrees");
  printf("Note: Resolution does not change with settings.\n");

  reach = 180;

  printf("Reach: %d\n", reach);

  while (value != reach) {
      value = as5600_angl_to_degr(as5600_read_angl(&as5600), 0, mpos);

      printf("Current value: %d degrees | Angle: %d%s\r", value, as5600_read_angl(&as5600), SPACES);
      printf("\n");
  }

  // Show zpos/mpos relation
  zpos = AS5600_MAX_ANGLE / 4; // ~90 degrees
  mpos = AS5600_MAX_ANGLE / 2 + 1; // ~180 degrees

  as5600_write_zpos(&as5600, zpos);
  print_poss_and_angs(&as5600);
  printf("Wrote zpos, note that mpos changed too.\n");
  as5600_write_mpos(&as5600, mpos);
  print_poss_and_angs(&as5600);

  // Show zpos/mpos relation
  print_msg("AS5600 display zpos/mpos relation");

  reach = 0;

  printf("Reach: %d\n", reach);

  while (value != reach) {
      value = as5600_angl_to_degr(as5600_read_angl(&as5600), zpos, mpos);

      printf("Current value: %d degrees | Angle: %d%s\r", value, as5600_read_angl(&as5600), SPACES);
      printf("\n");
  }

  // Write mpos, mang
  mpos = 0; // reset
  mang = AS5600_MAX_ANGLE / 2 + 1; // ~180 degrees

  as5600_write_mpos(&as5600, mpos);
  as5600_write_mang(&as5600, mang);
  print_poss_and_angs(&as5600);

  // Show how mang work
  print_msg("AS5600 display zpos/mang relation");

  reach = 180;

  printf("Reach: %d\n", reach);

  while (value != reach) {
      // Note that zpos was not updated
      value = as5600_angl_to_degr(as5600_read_angl(&as5600), zpos, as5600_mang_to_mpos(zpos, mang));

      printf("Current value: %d degrees | Angle: %d%s\r", value, as5600_read_angl(&as5600), SPACES);
      printf("\n");
  }

  // Clean "settings"
  as5600_write_zpos(&as5600, zpos);
  as5600_write_mpos(&as5600, mpos);
  as5600_write_mang(&as5600, mang);
  print_poss_and_angs(&as5600);
}


