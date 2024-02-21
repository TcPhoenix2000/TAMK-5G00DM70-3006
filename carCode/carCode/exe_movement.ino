void driveToDistance(int targetDistance) {
  unsigned long startTime = millis();     // Record the start time
  unsigned long twoSecondTimeout = 5000;  // Set the timeout period (2000 milliseconds = 2 seconds)

  int initial = getDistance();
  Serial.print("Initial distance: ");
  Serial.println(initial);

  int targetPosition = initial - targetDistance;  // Calculate the target position
  Serial.print("Target position: ");
  Serial.println(targetPosition);

  // Drive until the target position is reached or until 2 seconds have passed
  while (getDistance() > targetPosition) {
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

void moveDist(int moveValue, int initDist) {
  SetSpeed(100);
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

void maintainDistance(int desiredDistance) {
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

void executeMovementSequence(int number) {
  Serial.println("start sequenz");
  bool executing = true;
  driveToDistance(number);
  delay(100);
  TurnAngle(90, 5);
  delay(400);
  driveToDistance(number);
}

void executeSquareMeter(){ //get dist 4 sides
  distance[0] = getDistance();
  for (int i = 1; i <= 3; i++) {
    delay(500);
    TurnAngle(90, 5);
    stay_put();
    distance[i] = getDistance();
    delay(500);
  }
  TurnAngle(90, 5);
  stay_put();
}

void find_north_turn_north(){
  while(!(getByteAngle() <= 43 || getByteAngle() >= 345)){
    TurnAngle(10,5);
  }
  stay_put();
}

void find_east_turn_east(){
  while(!(getByteAngle() >= 85 && getByteAngle() <= 110)){
    TurnAngle(10,5);
  }
  stay_put();
}

void find_west_turn_west(){
  while(!(getByteAngle() >= 256 && getByteAngle() <= 290)){
    TurnAngle(10,5);
  }
  stay_put();
}

void driveToDistanceFromWall(int targetDistance) {
  SetSpeed(100);
  while (getDistance() > targetDistance + 2) {
    go_forward();
  }
  while (getDistance() < targetDistance + 2) {
    go_backwards();
  }

  stay_put();  // Make sure to stop the motors after exiting the loop
  Serial.println("Drive to distance from wall complete or timeout reached.");
}
