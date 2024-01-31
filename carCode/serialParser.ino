void parseSerialData() {
  //serialEvent();
  String line = Serial.readStringUntil('\n');  // Read a line from Serial until newline character

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
      Serial.println("move backwards");
      for (int m = 0; m < moveValue; m++) {
        go_backwards();
      }
    } else if (moveValue < 0) {
      Serial.println("move forward");
      for (int m = 0; m > moveValue; m--) {
        go_forward();
      }
    }
  }
  // Check if the received line contains "Turn:"
  if (line.startsWith("Turn:")) {
    turnValue = line.substring(5).toInt();  // Extract the value after "Turn:"

    // Now you can use the turnValue as needed in your program
    Serial.print("Received Turn value: ");
    Serial.println(turnValue);

    float byteAngle = Compass();
    byteAngle -= 180;
    int wantedAngle = turnValue + byteAngle;

    float targetAngle = turnValue + byteAngle;
    float tolerance = 0.01;  // Adjust the tolerance as neede

    while (abs(wantedAngle - targetAngle) > tolerance) {
      Serial.print("w");
      Serial.println(wantedAngle);
      Serial.print("t");
      Serial.println(targetAngle);
      Serial.print("b");
      Serial.println(byteAngle);
      if (byteAngle > targetAngle){
        Serial.println("turn - right");
      }
      if (byteAngle < targetAngle){
        Serial.println("turn - left");
      }
      if (byteAngle == targetAngle){
        Serial.println("done");
      }
      
      /*
      * keep testing this !!!
      */
      break;
      //stay_put();
    }

    // while (wantedAngle > 180) {
    //   //turn_right();
    // }
    //
    // while (wantedAngle < 180) {
    //   //turn_left();
    // }


  // this works  not dergee angled
  // Turn right loop
    /*if (turnValue > 0) {
      for (int t = 0; t > -turnValue; t--) {
        turn_right();
      }
    }
    else if(turnValue < 0) {
        // Turn left loop
        for (int t = 0; t < turnValue ; t++) {
          turn_left();
        }
      }
    else if(turnValue < 0) {
        // Stay put
        stay_put();
      }
    }
  */
  }
  if (line.startsWith("follow")) {
    Serial.println("Following mode activated");
    followMode = true;  // Set the follow mode flag
  }

if (line.startsWith("stopfollow")) {
    Serial.println("Following mode deactivated");
    followMode = false;  // Disable follow mode
  }
   if (line.startsWith("followjoystick")) {
    Serial.println("Potentiometer following mode activated");
    followModePotent = true;  // Set the follow mode flag
  }

if (line.startsWith("stopfollowjoystick")) {
    Serial.println("Potentiometer following mode deactivated");
    followModePotent = false;  // Disable follow mode
  }
}
