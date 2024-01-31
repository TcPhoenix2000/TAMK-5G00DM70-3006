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
    int initDist = getDistance();
    SetSpeed(100);
    initDist -= moveValue;
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
  // Check if the received line contains "Turn:"
  if (line.startsWith("Turn:")) {
    turnValue = line.substring(5).toInt();  // Extract the value after "Turn:"

    // Now you can use the turnValue as needed in your program
    Serial.print("Received Turn value: ");
    Serial.println(turnValue);


    int targetAngle = (int)(turnValue + getByteAngle()) % 361;
    int tolerance = 5;  // Adjust the tolerance as neede
    SetSpeed(60);

    // debug
    Serial.print("start");
    Serial.println(getByteAngle());
    Serial.print("targe");
    Serial.println(targetAngle);


    if (getByteAngle() != targetAngle) {
      TurnCheck(targetAngle, getByteAngle(), tolerance);
      Serial.println("done");
    }
  }
}

void TurnCheck(int targetAngle, int startAngle, int tolerance) {
  while (targetAngle < getByteAngle() - tolerance || targetAngle > getByteAngle() + tolerance) {
    if (targetAngle - getByteAngle() < 0) {
      turn_left();
      delay(10);
    }
    if (targetAngle - getByteAngle() > 0) {
      turn_right();
      delay(10);
    }
  }

}
