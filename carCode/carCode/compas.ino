float Compass() {
  // compass
  Wire.beginTransmission(CMPS14_address);
  Wire.write(1);
  Wire.endTransmission(false);
  Wire.requestFrom(CMPS14_address, 1, true);
  byte raw = Wire.read();
  float byteAngle = (raw * 1.41176470588); /* from raw to 0-360 angle /*/
  return byteAngle;
}

/*value between 0 and 360*/
float getByteAngle(){
  return Compass();
}

void find_north(){

  while(!(byteAngle <= 43 || byteAngle >= 345)){
    turnAngle();
  }
}