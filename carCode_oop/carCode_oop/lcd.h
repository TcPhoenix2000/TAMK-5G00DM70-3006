#ifndef LCD_H
#define LCD_H

#include "./compass.h"
#include <LiquidCrystal.h>
namespace Lego_car{
  class Lcd {
  public:
      void lcddisp();
  
  private:
      void printCompass();
      void printDist();
      void printJoystick();
      void printMoveDist();
      void printPress();
      void printExe();
  };
};

#endif