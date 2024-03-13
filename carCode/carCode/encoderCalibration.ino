void calibrateEncoders() {
  // Reset encoder counts
  encoderRightCount = 0;
  encoderLeftCount = 0;

  // Drive forward measure distance using lidar
  
  driveForwardUntilDistance(20); 

  // Calculate average encoder counts (assuming symmetric movement)
  unsigned long avgPulses = (encoderRightCount + encoderLeftCount) / 2;

  // Calculate distance per pulse (20 cm divided by average pulse count)
  distancePerPulse = 20.0 / avgPulses;

  // Print result to serial monitor
  Serial.print("Distance per pulse: ");
  Serial.print(distancePerPulse, 4);
  Serial.println(" cm");

  // Save result to EEPROM 
  updateFloatInEEPROM(eepromAddress,distancePerPulse);

  // To be decided if testing on different surfaces is necessary
}
void driveForwardUntilDistance(float targetDistance) {
  float initialDistance = getDistance(); 
  float currentDistance = initialDistance;
  float movedDistance = 0;

  // Drive forward
  SetSpeed(100); // Set a suitable speed

  while (movedDistance < targetDistance) {
    currentDistance = getDistance();
    movedDistance = initialDistance - currentDistance;
  }

  // Stop the car
  stay_put();
}

void printDistancePerPulse(){

  
  // Print the currently stored value onto LCD
  
  lcd.setCursor(0, 2);
  lcd.print("Dist/Pulse: ");
  lcd.print(readFloatFromEEPROM(eepromAddress), 4); // 4 decimal places for precision
  lcd.print(" cm");

}

void incrementRightEncoder() {
  encoderRightCount++;
}

void incrementLeftEncoder() {
  encoderLeftCount++;
}

void updateFloatInEEPROM(int address, float value) {
  // Creates a pointer to the float to access its bytes
  byte* valuePtr = (byte*)(void*)&value;

  // Updates each of the 4 bytes of the float in EEPROM
  for (int i = 0; i < 4; i++) {
    EEPROM.update(address + i, valuePtr[i]);
  }
}

float readFloatFromEEPROM(int address) {
  float value;
  // Create a pointer to the result float to access its bytes
  byte* valuePtr = (byte*)(void*)&value;

  // Read each of the 4 bytes of the float from EEPROM
  for (int i = 0; i < 4; i++) {
    valuePtr[i] = EEPROM.read(address + i);
  }

  return value;
}
