void lcddisp() {
  float byteAngle = Compass();

  //lcd
  lcd.clear();
  printCompass();

  if (program == 0) {
    printJoystick();
  } else if (program == 1 || program == 10) {
    printDist();
  } else if (program == 2 || program == 4) {
    printMoveDist();
    printPress();
  } else if (program == 3 || program == 5) {
    printMoveDist();
    printExe();
  } else if (program == 6) {
    printSquareM();
  }
  else if (program == 9) {
    printDistancePerPulse();
  }

  delay(50);
}

void printCompass() {
  float byteAngle = Compass();

  lcd.setCursor(0, 0);
  lcd.print("Direction: ");

  if (byteAngle <= 43 || byteAngle >= 345) lcd.print("N");
  if (byteAngle >= 44 && byteAngle <= 84) lcd.print("NE");
  if (byteAngle >= 85 && byteAngle <= 110) lcd.print("E");
  if (byteAngle >= 111 && byteAngle <= 165) lcd.print("SE");
  if (byteAngle >= 166 && byteAngle <= 210) lcd.print("S");
  if (byteAngle >= 211 && byteAngle <= 255) lcd.print("SW");
  if (byteAngle >= 256 && byteAngle <= 290) lcd.print("W");
  if (byteAngle >= 291 && byteAngle <= 344) lcd.print("NW");
}

void printDist() {  // week 3 exersize 1 part 1
  // Get the LIDAR distance measurement
  lcd.setCursor(0, 1);
  int distance = getDistance();  // Get the distance in cm
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 2);
  lcd.print("Driven: ");
  lcd.print(cumulativeDistance);
  lcd.print(" cm");
}

void printJoystick() {
  // Print the X-position
  lcd.setCursor(0, 1);
  lcd.print("X-position: ");
  lcd.setCursor(0, 1);
  lcd.print("X-position");

  lcd.setCursor(0, 2);
  lcd.print("-100%");

  lcd.setCursor(9, 2);
  lcd.print("0%");

  lcd.setCursor(15, 2);
  lcd.print("+100%");

  int x = (1023 - analogRead(A9)) * (0.019); /* inverted joystick reading; mounted upside-down /*/
  lcd.setCursor(x, 3);
  lcd.print("|");

  // Print the distance
  lcd.setCursor(0, 2);
}

void printMoveDist() {
  // Print the movedist
  lcd.setCursor(0, 1);
  lcd.print("move dist: ");
  lcd.setCursor(11, 1);
  lcd.print(joystickPotentio());
}
void printPress() {
  lcd.setCursor(0, 2);
  lcd.print("press to execute");
}
void printExe() {
  lcd.setCursor(0, 2);
  lcd.print("execute now     ");
}
void printSquareM(){
  lcd.setCursor(0, 2);
  lcd.print("square meters   ");
  lcd.setCursor(16, 2);
  lcd.print(calculateSqMeter());
}
