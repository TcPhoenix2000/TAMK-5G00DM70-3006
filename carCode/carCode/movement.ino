int SetSpeed(int Speed){
  pwm_L = Speed;
  pwm_R = Speed;
}

int GetSpeed(){
  return pwm_L,pwm_R;
}
void turn_right() {
  Serial.println("turn right");

  
  pwm_R,pwm_R  =  GetSpeed();
  
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_forward);
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
}

void turn_left() {
  Serial.println("turn left");

  digitalWrite(Motor_L_dir_pin, Motor_return);
  digitalWrite(Motor_R_dir_pin, Motor_forward);

  pwm_R,pwm_R  =  GetSpeed();
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
}

void go_forward() {
  Serial.println("go forward");

  digitalWrite(Motor_R_dir_pin, Motor_forward);
  digitalWrite(Motor_L_dir_pin, Motor_forward);

  //pwm_R = 120; // analogRead(A8) * 0.24926686217
  //pwm_L = 120; // analogRead(A8) * 0.24926686217

  pwm_R,pwm_R  =  GetSpeed();
  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  updateCumulativeDistance();
}

void go_backwards() {
  Serial.println("go back");
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);
  
  pwm_R,pwm_R  =  GetSpeed();

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  updateCumulativeDistance();
}

void stay_put() {
  digitalWrite(Motor_R_dir_pin, Motor_return);
  digitalWrite(Motor_L_dir_pin, Motor_return);

  int pwm_R = 0;
  int pwm_L = 0;

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
  lcddisp();
}

void TurnAngle( int turnValue,int tolerance) {
  int targetAngle = (int)(turnValue + getByteAngle()) % 361;

  while (targetAngle < getByteAngle() - tolerance || targetAngle > getByteAngle() + tolerance) {
    if (targetAngle - getByteAngle() < 0) {
      if (turnValue < 0){turn_left();}
      if (turnValue > 0){turn_right();}
      delay(10);
    }
    if (targetAngle - getByteAngle() > 0) {
      if (turnValue > 0){turn_right();}
      if (turnValue < 0){turn_left();}
      delay(10);
    }
  }
}

void moveDist(int moveValue ,int initDist){
  if (moveValue > 0) {
      Serial.println("move forward");
      while (initDist < getDistance()) {
        go_forward();
      }

    } else if (moveValue < 0) {
      Serial.println("move backwards");
      while (initDist > getDistance()) {
        go_backwards();
      }
    }
}
