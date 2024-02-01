int joystickPotentio() {

  int proportion = analogRead(A9);
  int scaledValue = map(proportion, 0, 1024, 2, 20);
  return scaledValue;
}
