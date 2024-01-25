void parseSerialData() {
  //serialEvent();
  String line = Serial2.readStringUntil('\n');  // Read a line from Serial until newline character

  // Check if the received line contains "Param name:"
  if (line.startsWith("Param name:")) {
    paramName = line.substring(12);  // Extract and trim the parameter name

    // Now you can use paramName as needed in your program
    if (paramName.startsWith("dist")) {
      Serial.println("Received parameter: dist");
      // Perform actions for "dist"

    } else if (paramName.startsWith("dire")) {
      Serial.println("Received parameter: dire");
      // Perform actions for "dire"

    } else {
      Serial.println(paramName);
      Serial.println("Unknown parameter received");
    }
  }
  // Check if the received line contains "Move:"
  if (line.startsWith("Move:")) {
    moveValue = line.substring(5).toInt();  // Extract the value after "Move:"

    // Now you can use the moveValue as needed in your program
    Serial.print("Received Move value: ");
    Serial.println(moveValue);
    if (moveValue > 0) {
      Serial.println("move forward");
      for (int m = 0; m < moveValue; m++) {
        go_forward();
      }

    } else if (moveValue < 0) {
      Serial.println("move backwards");
      for (int m = 0; m > moveValue; m--) {
        go_backwards();
      }
    }
  }
  // Check if the received line contains "Turn:"
  if (line.startsWith("Turn:")) {
    turnValue = line.substring(5).toInt();  // Extract the value after "Turn:"

    // Now you can use the turnValue as needed in your program
    Serial.print("Received Turn value: ");
    Serial.println(turnValue);

    int wantedAngle = turnValue + getByteAngle();

    float targetAngle = turnValue + getByteAngle();
    float tolerance = 5.0;  // Adjust the tolerance as neede

    Serial.print("w");
    Serial.println(wantedAngle);
    Serial.print("t");
    Serial.println(targetAngle);
    Serial.print("b");
    Serial.println(getByteAngle());

    if (getByteAngle() != targetAngle) {
      TurnCheck(targetAngle, wantedAngle, tolerance);
      Serial.println("done");
    }
  }
}
void TurnCheck(int targetAngle, int wantedAngle, int tolerance) {
  while (abs(getByteAngle() - wantedAngle) > tolerance) {
    while (getByteAngle() < wantedAngle) {
      delay(10);
      turn_right();
    }
    while (getByteAngle() > wantedAngle) {
      delay(10);
      turn_left();
      
    }
  }
}
