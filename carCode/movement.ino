
void turn_right() {
  Serial.println("turn right");

  pwm_R = 180;
  pwm_L = 180;
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_forward);
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
  delay(50);
}

void turn_left() {
  Serial.println("turn left");

  digitalWrite(Motor_L_dir_pin, Motor_return);
  digitalWrite(Motor_R_dir_pin, Motor_forward);
  pwm_R = 180;
  pwm_L = 180;
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
  delay(50);
}

void go_forward() {
  //Serial.println("go forward");

  digitalWrite(Motor_R_dir_pin, Motor_forward);
  digitalWrite(Motor_L_dir_pin, Motor_forward);

  analogWrite(Motor_L_pwm_pin, analogRead(A8) * 0.24926686217);
  analogWrite(Motor_R_pwm_pin, analogRead(A8) * 0.24926686217);
  updateCumulativeDistance();
  lcddisp();
  delay(50);
}

void go_backwards() {
  //Serial.println("go back");
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);
  pwm_R = 180;
  pwm_L = 180;

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  updateCumulativeDistance();
  lcddisp();
  delay(50);
}

void stay_put() {
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);
  pwm_R = 0;
  pwm_L = 0;

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
  delay(50);
}

void maintainDistance(int desiredDistance) {
  int currentDistance = myLidarLite.distance(); // Read current distance from LIDAR
  int distanceError = currentDistance - desiredDistance; // Calculate the difference from the desired distance

  // Threshold for distance accuracy, to avoid constant minor adjustments
  int threshold = 2; // 2cm threshold for error

  if (abs(distanceError) <= threshold) {
    stay_put(); // Stay put if the distance is within the threshold
  } 
  else if (distanceError < 0) {
    go_forward(); // Move forward if the car is too far from the object
  } 
  else {
    go_backwards(); // Move backward if the car is too close to the object
  }
}
