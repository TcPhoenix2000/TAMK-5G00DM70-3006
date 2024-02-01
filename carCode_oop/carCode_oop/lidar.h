#ifndef LIDAR_H
#define LIDAR_H

#include <LIDARLite.h>
namespace Lego_car{
  class lidar {
  public:
  
      void updateCumulativeDistance();
      int getDistance();
  
  private:
      int initialDistance;
      int cumulativeDistance;
      LIDARLite myLidarLite;
  };
};

#endif