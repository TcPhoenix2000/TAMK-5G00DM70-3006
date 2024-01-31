#include <Wire.h>
#include <LiquidCrystal.h>
#include <LIDARLite.h>

#define Motor_forward 1
#define Motor_return 0
#define Motor_L_dir_pin 7
#define Motor_R_dir_pin 8
#define Motor_L_pwm_pin 9
#define Motor_R_pwm_pin 10
#define Joystick_SW_pin 19
#define CMPS14_address 0x60  // compass

// lidar
LIDARLite myLidarLite;
int initialDistance = 0;     // Initial distance from the LIDAR to the wall
int cumulativeDistance = 0;  // Cumulative distance driven

// joystick button
#define BUTTON_DEBOUNCE_DELAY 50  // 50 milliseconds for debounce
unsigned long lastDebounceTime = 0;

// to cycle throuh programmes
int program = 1;

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


void setup() {
  Serial.begin(115200);
  myLidarLite.begin(0, true);  // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0);    // Change this number to try out alternate configurations
  Wire.begin();
  lcd.begin(20, 4);
  initialDistance = getDistance();  //LIDAR
  Serial.println("initialized");

  attachInterrupt(digitalPinToInterrupt(Joystick_SW_pin), CheckButton, FALLING);
  Serial2.begin(9600);
}

void loop() {
  switch (program) {
    case 0:
      // Code for program 0 local drive
      remoteControl = false;
      while (analogRead(A9) >= 490 && analogRead(A9) <= 550 && analogRead(A8) >= 460 && analogRead(A8) <= 518) stay_put();
      while (analogRead(A9) < 490) SetSpeed(100), turn_left();
      while (analogRead(A9) > 550) SetSpeed(100), turn_right();
      while (analogRead(A8) > 518) SetSpeed(100), go_forward();
      while (analogRead(A8) < 460) SetSpeed(100), go_backwards();

      break;
    case 1:
      // Code for program 1 remote control
      remoteControl = true;
      stay_put();
      parseSerialData();
      break;
    case 2:
      // Code for program 2 somthing else
      remoteControl = false;

      break;
    default:
      // Default case, executed when program is neither 0, 1, nor 2
      program = 0;  // Reset program to 0
      break;
  }

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
      if (!remoteControl) {
        Serial.println("remote control activated!");
      } else {
        Serial.println("remote control deactivated!");
      }
      // Reset the debounce timer
      lastDebounceTime = millis();
    }
  }
}
