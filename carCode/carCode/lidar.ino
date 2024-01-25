void updateCumulativeDistance() {
  int currentDistance = myLidarLite.distance();
  int distanceMoved = initialDistance - currentDistance;  // Calculate the change in distance
  cumulativeDistance += distanceMoved;                    // Update the cumulative distance
  initialDistance = currentDistance;                      // Update initial distance for next movement

  lcddisp();  // Update the display
}