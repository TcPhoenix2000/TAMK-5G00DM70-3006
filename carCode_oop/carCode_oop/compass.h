#ifndef COMPASS_H
#define COMPASS_H

#include <Wire.h>
namespace Lego_car {
  class compass {
  public:
    float Compass();
    float getByteAngle();
  };
};
#endif