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
int program = 6;

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
      Serial.println("program 0");  // week 1 & 2 exersize 2 part 1
      // Code for program 0 local drive
      remoteControl = false;
      checkRemote();
      while (analogRead(A9) >= 490 && analogRead(A9) <= 550 && analogRead(A8) >= 460 && analogRead(A8) <= 518) stay_put();
      while (analogRead(A9) < 490) SetSpeed(100), turn_right();
      while (analogRead(A9) > 550) SetSpeed(100), turn_left();
      while (analogRead(A8) > 518) SetSpeed(100), go_backwards();
      while (analogRead(A8) < 460) SetSpeed(100), go_forward();

      break;
    case 1:
      Serial.println("program 1");  // week 1 & 2 exersize 2 part 2
      // Code for program 1 remote control
      remoteControl = true;
      checkRemote();
      stay_put();
      parseSerialData();
      break;
    case 2:
      Serial.println("program 2");  // week 3 exersize 3 step 2
      // Code for program 2 somthing else
      remoteControl = true;
      checkRemote();
      stay_put();
      parseSerialData();
      break;
    case 3:
      Serial.println("program 3");  // week 3 exersize 3 step 1
      remoteControl = false;
      checkRemote();
      // program 2 exe
      executeMovementSequence(joystickPotentio());
      program = 4;
      break;
    case 4:
      Serial.println("program 4");  // week 3 exersize 2 step 1
      // follow program
      maintainDistance(20);
      break;
    case 5:
      Serial.println("program 5");  // week 3 exersize 2 step 2
      // program 2 exe
      stay_put();
      maintainDistance(joystickPotentio());
      Serial.println(joystickPotentio());
      break;
    case 6:
      Serial.println("program 6");  // week 4 exersize 1 step 1
      // program 2 exe
      stay_put();
      executeSquareMeter();
      delay(2000);
      program = 7;
      break;
    case 7:
      Serial.println("program 7");
      stay_put();
      

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
      // Reset the debounce timer
      lastDebounceTime = millis();
    }
  }
}

void checkRemote() {
  if (!remoteControl) {
    Serial.println("remote control activated!");
  } else {
    Serial.println("remote control deactivated!");
  }
}
