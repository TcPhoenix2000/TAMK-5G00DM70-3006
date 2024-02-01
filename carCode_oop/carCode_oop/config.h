#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal.h>
#include <LIDARLite.h>

#include "./lidar.h"
#include "./movement.h"
#include "./lcd.h"
#include "./compass.h"
#include "./joystick.h"
#include "./serialParser.h"

// Pin Definitions
#define Motor_forward 1
#define Motor_return 0
#define Motor_L_dir_pin 7
#define Motor_R_dir_pin 8
#define Motor_L_pwm_pin 9
#define Motor_R_pwm_pin 10
#define Joystick_SW_pin 19
#define CMPS14_address 0x60  // compass

// Communication Settings
#define BAUD_RATE_SERIAL 115200
#define BAUD_RATE_SERIAL2 9600

// joystick button
#define BUTTON_DEBOUNCE_DELAY 50  // 50 milliseconds for debounce
unsigned long lastDebounceTime = 0;

// lidar
LIDARLite myLidarLite;
int initialDistance = 0;     // Initial distance from the LIDAR to the wall
int cumulativeDistance = 0;  // Cumulative distance driven

// to cycle throuh programmes
int program = 0;

// lcd
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// motor pwm
float pwm_R = 0;
float pwm_L = 0;


// uart serial2 for output esp dashboard
bool remoteControl = false;
String paramName = "";
int moveValue = 0;
float turnValue = 0;

#endif // CONFIG_H