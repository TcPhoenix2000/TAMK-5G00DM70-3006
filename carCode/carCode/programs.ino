/*
  switch that cycles through all the programs
  can be found in programs.ino
*/
void programSwitcher() {
  switch (program) {
    case 0:                         // Code for program 0 local drive
      Serial.println("program 0");  // week 1 & 2 exersize 2 part 1

      remoteControl = false;
      checkRemote();
      while (analogRead(A9) >= 490 && analogRead(A9) <= 550 && analogRead(A8) >= 460 && analogRead(A8) <= 518) stay_put();
      while (analogRead(A9) < 490) SetSpeed(100), turn_right();
      while (analogRead(A9) > 550) SetSpeed(100), turn_left();
      while (analogRead(A8) > 518) SetSpeed(100), go_backwards();
      while (analogRead(A8) < 460) SetSpeed(100), go_forward();

      break;

    case 1:                         // Code for program 1 remote control
      Serial.println("program 1");  // week 1 & 2 exersize 2 part 2
      remoteControl = true;
      checkRemote();
      stay_put();
      parseSerialData();
      break;

    case 2:                         // Step 2: Send the distance value via ESP with a command of your choice
      Serial.println("program 2");  // week 3 exersize 3 step 2

      remoteControl = true;
      checkRemote();
      stay_put();
      parseSerialData();
      break;

    case 3:                         // drive L of potentio value
      Serial.println("program 3");  // week 3 exersize 3 step 1
      // Step 1: Create a program that drives your car to the distance set by
      // potentiometer (value x) and after reaching that value, rotates 90 degrees right
      // (using only one wheel) and then drives the same distance again

      remoteControl = false;
      checkRemote();

      // program 3 exe
      executeMovementSequence(joystickPotentio());
      program = 4;
      break;

    case 4:                         // follow program
      Serial.println("program 4");  // week 3 exersize 2 step 1
      // follow program
      // Create a program that drives your car to a set distance from object/wall
      maintainDistance(20);
      break;

    case 5:                         // Instead of fixed 20 cm distance, the value is read from potentiometer
      Serial.println("program 5");  // week 3 exersize 2 step 2
      // program 5 exe
      // Instead of fixed 20 cm distance, the value is read from potentiometer
      stay_put();
      maintainDistance(joystickPotentio());
      break;

    case 6:                         // calculate M²
      Serial.println("program 6");  // week 4 exersize 1 step 1
      // program 6 exe
      stay_put();
      executeSquareMeter();
      delay(2000);
      program = 7;
      break;
    case 7:                         // drive square
      Serial.println("program 7");  // week 5 exersize 2
      driveSquare();

      // to do
      // count encoderpulses to messure total distance driven !!!
      program = 8;
      break;

    case 8:  //
      // week 7 2-way communication
      //Serial.println("programm 8");
      remoteControl = true;
      // checkRemote();
      stay_put();
      writeSerialData();
      parseSerialData();  // to get ip
                          // Serial.println(IPAddress);

      delay(1000);
      break;


    case 9:  //
      // week 4 exercise 3- Encoder Calibration - BETA
      lcddisp();
      calibrateEncoders();
      delay(10000);
      break;

    case 10:
      //Serial.println("program 10");  // week 10 midpoint

      remoteControl = true;
      // checkRemote();
      stay_put();
      parseSerialData();
      //delay(200);
      //writeSerialData();
      break;
    case 11:
       remoteControl = true;
      // checkRemote();
      stay_put();
      parseSerialData();
      //Serial.println("program 11");  // week 10 midpoint
      uint16_t clear, red, green, blue;
      tcs.getRGBC(&red, &green, &blue, &clear);
      
      tcs.lock();  // turn off LED
      Serial.print("\tR:");
      Serial.print(red %255);
      Serial.print("\tG:");
      Serial.print(green %255);
      Serial.print("\tB:");
      Serial.print(blue %255);
      Serial.println("\t");

      // Figure out some basic hex code for visualization
      uint32_t sum = clear;
      float r, g, b;
      r = red;
      r /= sum;
      g = green;
      g /= sum;
      b = blue;
      b /= sum;
      r *= 256;
      g *= 256;
      b *= 256;
      Serial.print("\t");
      Serial.print((int)r, HEX);
      Serial.print((int)g, HEX);
      Serial.print((int)b, HEX);
      Serial.println();

      break;

    default:  // Reset program to 0
      // Default case, executed when program is neither 0, 1, nor 2
      program = init_program;  // Reset program to init program
      break;
  }
}
