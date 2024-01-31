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
    
    moveDist(moveValue , initDist);
  }
  // Check if the received line contains "Turn:"
  if (line.startsWith("Turn:")) {
    turnValue = line.substring(5).toInt();  // Extract the value after "Turn:"

    // Now you can use the turnValue as needed in your program
    Serial.print("Received Turn value: ");
    Serial.println(turnValue);

    int tolerance = 5;  // Adjust the tolerance as neede
    SetSpeed(60);

    TurnAngle(turnValue, tolerance);
    Serial.println("done");
    
  }
}
