#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "./lcd.h"
namespace Lego_car{
  class movement {
  public:
    void SetSpeed(int Speed);
    int GetSpeed();

    void turn_right();
    void turn_left();
    void go_forward();
    void go_backwards();
    void stay_put();
    void TurnAngle(int turnValue, int tolerance);
    void driveToDistance(int targetDistance);
    void moveDist(int moveValue, int initDist);
    void maintainDistance(int desiredDistance);
    void executeMovementSequence(int number);

  private:
    int pwm_L = 0;
    int pwm_R = 0;
  };
};

#endif