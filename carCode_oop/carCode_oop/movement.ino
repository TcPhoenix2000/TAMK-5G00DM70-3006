#include "./movement.h"

using namespace Lego_car;

void movement::SetSpeed(int Speed) {
  pwm_L = Speed;
  pwm_R = Speed;
}

int movement::GetSpeed() {
  return pwm_L, pwm_R;
}

void movement::turn_right() {
  Serial.println("turn right");


  pwm_R, pwm_R = GetSpeed();

  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_forward);
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  MyLcd.lcddisp();
}

void movement::turn_left() {
  Serial.println("turn left");

  digitalWrite(Motor_L_dir_pin, Motor_return);
  digitalWrite(Motor_R_dir_pin, Motor_forward);

  pwm_R, pwm_R = GetSpeed();
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  MyLcd.lcddisp();
}

void movement::go_forward() {
  Serial.println("go forward");

  digitalWrite(Motor_R_dir_pin, Motor_forward);
  digitalWrite(Motor_L_dir_pin, Motor_forward);

  //pwm_R = 120; // analogRead(A8) * 0.24926686217
  //pwm_L = 120; // analogRead(A8) * 0.24926686217

  pwm_R, pwm_R = GetSpeed();
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  Mylidar.updateCumulativeDistance();
}

void movement::go_backwards() {
  Serial.println("go back");
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);

  pwm_R, pwm_R = GetSpeed();

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  Mylidar.updateCumulativeDistance();
}

void movement::stay_put() {
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);

  int pwm_R = 0;
  int pwm_L = 0;

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  MyLcd.lcddisp();
}

void movement::TurnAngle(int turnValue, int tolerance) {
  int targetAngle = (int)(turnValue + Mycompass.getByteAngle()) % 361;
  SetSpeed(60);

  while (targetAngle < Mycompass.getByteAngle() - tolerance || targetAngle > Mycompass.getByteAngle() + tolerance) {
    if (targetAngle - Mycompass.getByteAngle() < 0) {
      if (turnValue < 0) { turn_left(); }
      if (turnValue > 0) { turn_right(); }
      delay(10);
    }
    if (targetAngle - Mycompass.getByteAngle() > 0) {
      if (turnValue > 0) { turn_right(); }
      if (turnValue < 0) { turn_left(); }
      delay(10);
    }
  }
}

void movement::driveToDistance(int targetDistance) {
  unsigned long startTime = millis();     // Record the start time
  unsigned long twoSecondTimeout = 5000;  // Set the timeout period (2000 milliseconds = 2 seconds)

  int initial = Mylidar.getDistance();
  Serial.print("Initial distance: ");
  Serial.println(initial);

  int targetPosition = initial - targetDistance;  // Calculate the target position
  Serial.print("Target position: ");
  Serial.println(targetPosition);

  // Drive until the target position is reached or until 2 seconds have passed
  while (Mylidar.getDistance() > targetPosition) {
    // Check if 2 seconds have passed
    if (millis() - startTime >= twoSecondTimeout) {
      Serial.println("2-second timeout reached, breaking loop");
      break;
    }

    Serial.println("Driving...");
    SetSpeed(100);
    go_forward();
  }

  stay_put();  // Make sure to stop the motors after exiting the loop
  Serial.println("Drive to distance complete or timeout reached.");
}


void movement::moveDist(int moveValue, int initDist) {
  SetSpeed(100);
  if (moveValue > 0) {
    Serial.println("move forward");
    while (initDist < Mylidar.getDistance()) {
      go_forward();
    }

  } else if (moveValue < 0) {
    Serial.println("move backwards");
    while (initDist > Mylidar.getDistance()) {
      go_backwards();
    }
  }
}

void movement::maintainDistance(int desiredDistance) {
  int currentDistance = myLidarLite.distance();           // Read current distance from LIDAR
  int distanceError = currentDistance - desiredDistance;  // Calculate the difference from the desired distance
  SetSpeed(100);

  // Threshold for distance accuracy, to avoid constant minor adjustments
  int threshold = 2;  // 2cm threshold for error

  if (abs(distanceError) <= threshold) {
    stay_put();  // Stay put if the distance is within the threshold
  } else if (distanceError < 0) {
    go_backwards();  // Move backward if the car is too close to the object
  } else {
    go_forward();  // Move forward if the car is too far from the object
  }
}

void movement::executeMovementSequence(int number) {
  Serial.println("start sequenz");
  bool executing = true;
  driveToDistance(number);
  delay(100);
  TurnAngle(90, 5);
  delay(400);
  driveToDistance(number);
  program = 4;
}
