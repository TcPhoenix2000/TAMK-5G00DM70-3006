#include <Wire.h>
#include <LiquidCrystal.h>
#include <LIDARLite.h>

#define Motor_forward 0
#define Motor_return 1
#define Motor_L_dir_pin 7
#define Motor_R_dir_pin 8
#define Motor_L_pwm_pin 9
#define Motor_R_pwm_pin 10
#define Joystick_SW_pin 19
#define CMPS14_address 0x60 // compass

// lidar
LIDARLite myLidarLite;
int initialDistance = 0;     // Initial distance from the LIDAR to the wall
int cumulativeDistance = 0;  // Cumulative distance driven

// joystick button
#define BUTTON_DEBOUNCE_DELAY 50  // 50 milliseconds for debounce
unsigned long lastDebounceTime = 0;

// lcd
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float pwm_R = 0;
float pwm_L = 0;


// uart serial2 for output esp dashboard
bool remoteControl = true;
String paramName = "";
int moveValue = 0;
int turnValue = 0;


void setup() {
  Serial.begin(115200);
  myLidarLite.begin(0, true);  // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0);    // Change this number to try out alternate configurations
  Wire.begin();
  lcd.begin(20, 4);
  initialDistance = myLidarLite.distance();  //LIDAR
  Serial.println("initialized");

  attachInterrupt(digitalPinToInterrupt(Joystick_SW_pin), CheckButton, FALLING);

  Serial2.begin(9600);
}

void loop() {

  if (!remoteControl) {
    while (analogRead(A9) >= 490 && analogRead(A9) <= 550 && analogRead(A8) >= 460 && analogRead(A8) <= 518) stay_put();
    while (analogRead(A9) < 490) turn_left();

    while (analogRead(A9) > 550) turn_right();
    while (analogRead(A8) > 518) go_forward();
    while (analogRead(A8) < 460) go_backwards();

  } else {
    stay_put();
    parseSerialData();
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

      if (!remoteControl) {
        Serial.println("remote control activated!");
      } else {
        Serial.println("remote control deactivated!");
      }
      // do something with general esp8266
      remoteControl = !remoteControl;
      // Reset the debounce timer
      lastDebounceTime = millis();
    }
  }
}
