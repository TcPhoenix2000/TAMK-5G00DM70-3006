#include "./config.h"

using namespace Lego_car;

movement MyMove;
lidar Mylidar;
serialParser MySerialParser;
joystick Myjoystick;
compass Mycompass;
Lcd MyLcd;

void setup() {
  Serial.begin(115200);
  myLidarLite.begin(0, true);  // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0);    // Change this number to try out alternate configurations
  Wire.begin();
  lcd.begin(20, 4);
  initialDistance = Mylidar.getDistance();  //LIDAR
  Serial.println("initialized");

  attachInterrupt(digitalPinToInterrupt(Joystick_SW_pin), CheckButton, FALLING);
  Serial2.begin(9600);
};

void loop() {
  switch (program) {
    case 0:
      Serial.println("program 0");  // week 1 & 2 exersize 2 part 1
      // Code for program 0 local drive
      remoteControl = false;
      while (analogRead(A9) >= 490 && analogRead(A9) <= 550 && analogRead(A8) >= 460 && analogRead(A8) <= 518) MyMove.stay_put();
      while (analogRead(A9) < 490) MyMove.SetSpeed(100), MyMove.turn_right();
      while (analogRead(A9) > 550) MyMove.SetSpeed(100), MyMove.turn_left();
      while (analogRead(A8) > 518) MyMove.SetSpeed(100), MyMove.go_backwards();
      while (analogRead(A8) < 460) MyMove.SetSpeed(100), MyMove.go_forward();

      break;
    case 1:
      Serial.println("program 1");  // week 1 & 2 exersize 2 part 2
      // Code for program 1 remote control
      remoteControl = true;
      MyMove.stay_put();
      MySerialParser.parseSerialData();
      break;
    case 2:
      Serial.println("program 2");  // week 3 exersize 3 step 2
      // Code for program 2 somthing else
      remoteControl = true;
      MyMove.stay_put();
      MySerialParser.parseSerialData();
      break;
    case 3:
      Serial.println("program 3");  // week 3 exersize 3 step 1
      // program 2 exe
      MyMove.executeMovementSequence(Myjoystick.joystickPotentio());
      break;
    case 4:
      Serial.println("program 4");  // week 3 exersize 2 step 1
      // follow program
      MyMove.maintainDistance(20);
      break;
    case 5:
      Serial.println("program 5");  // week 3 exersize 2 step 2
      // program 2 exe
      MyMove.stay_put();
      MyMove.maintainDistance(Myjoystick.joystickPotentio());
      Serial.println(Myjoystick.joystickPotentio());
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
};

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
};
