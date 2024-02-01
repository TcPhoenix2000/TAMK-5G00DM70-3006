#include "./joystick.h"

using namespace Lego_car;

  int joystick::joystickPotentio() {

    int proportion = analogRead(A9);
    int scaledValue = map(proportion, 0, 1024, 2, 20);
    return scaledValue;
  }

