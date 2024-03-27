#include <Wire.h>
#include <LiquidCrystal.h>
#include <LIDARLite.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <DFRobot_TCS34725.h>


String IPAddress;
#define Motor_forward 1
#define Motor_return 0
#define Motor_L_dir_pin 7
#define Motor_R_dir_pin 8
#define Motor_L_pwm_pin 9
#define Motor_R_pwm_pin 10
#define Joystick_SW_pin 19
#define CMPS14_address 0x60  // compass

// color sensor
#define redpin 3
#define greenpin 5
#define bluepin 6
#define commonAnode true
byte gammatable[256];
DFRobot_TCS34725 tcs = DFRobot_TCS34725(&Wire, TCS34725_ADDRESS,TCS34725_INTEGRATIONTIME_50MS,TCS34725_GAIN_4X);

// EEPROM address to store the calibration data
const int eepromAddress = 0;

// Variable to hold the distance per pulse value
float distancePerPulse = 0.0;

//Encoder pins and count variables
const int encoderRightPin = 24;
const int encoderLeftPin = 23;
volatile unsigned long encoderRightCount = 0;
volatile unsigned long encoderLeftCount = 0;
int turnsTaken = 0;

// lidar
LIDARLite myLidarLite;
int initialDistance = 0;     // Initial distance from the LIDAR to the wall
int cumulativeDistance = 0;  // Cumulative distance driven

// joystick button
#define BUTTON_DEBOUNCE_DELAY 50  // 50 milliseconds for debounce
unsigned long lastDebounceTime = 0;

// to cycle throuh programmes
int init_program = 11;
int program = init_program;

// lcd
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float pwm_R = 0;
float pwm_L = 0;


// uart serial2 for output esp dashboard
bool remoteControl = false;
String paramName = "";
int moveValue = 0;
float turnValue = 0;

// square meters
double distance[4];

//Serial    pin 0  rx and  1 tx used by pc/laptop
//Serial2   pin 17 rx and 16 tx used by esp8266

void setup() {
  Serial.begin(115200);
  myLidarLite.begin(0, true);  // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0);    // Change this number to try out alternate configurations
  Wire.begin();
  lcd.begin(20, 4);
  initialDistance = getDistance();  //LIDAR
  Serial.println("initialized");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;  // halt!
  }
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }


// Initialize encoder pins as inputs
pinMode(encoderRightPin, INPUT);
pinMode(encoderLeftPin, INPUT);

// Attach interrupts for encoder pulse.. to be checked if RISING should be CHANGE if we need to count both rising and falling
attachInterrupt(digitalPinToInterrupt(encoderRightPin), incrementRightEncoder, RISING);
attachInterrupt(digitalPinToInterrupt(encoderLeftPin), incrementLeftEncoder, RISING);

attachInterrupt(digitalPinToInterrupt(Joystick_SW_pin), CheckButton, FALLING);
Serial2.begin(9600);
}

void loop() {
  programSwitcher();

  /*
    * pwm_L = (Ypot);
    * pwm_R = (Xpot);
    */
  pwm_R = 0;
  pwm_L = 0;
}

void CheckButton() {
  // Read the button state
  int buttonState = digitalRead(Joystick_SW_pin);

  // Check if we have passed the debounce delay since the last button change
  if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE_DELAY) {
    if (buttonState == LOW) {  // Assuming pull-up resistor
                               // Button has been pressed
      program++;
      // Reset the debounce timer
      lastDebounceTime = millis();
    }
  }
}

void checkRemote() {
  if (remoteControl) {
    Serial.println("remote control activated!");
  } else {
    Serial.println("remote control deactivated!");
  }
}
