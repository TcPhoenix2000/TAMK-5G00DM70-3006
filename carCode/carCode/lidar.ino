void updateCumulativeDistance() { // week 3 exersize 1 part 2
  int currentDistance = getDistance();

  /* not correct yet*/
  int distanceMoved = initialDistance - currentDistance;  // Calculate the change in distance
  cumulativeDistance += distanceMoved;                    // Update the cumulative distance
  initialDistance = currentDistance;                      // Update initial distance for next movement

  lcddisp();  // Update the display
}
int getDistance() {
  int NUM_READINGS = 10;
  int totalDistance = 0;  // Variable to store the sum of all readings
  for (int i = 0; i < NUM_READINGS; i++) {
    totalDistance += myLidarLite.distance();  // Sum each distance reading
    delay(5);                                // Short delay between readings, adjust as needed based on LIDAR specs
  }
  int averageDistance = totalDistance / NUM_READINGS;  // Compute the average
  return averageDistance;                              // Return the average distance
}

double calculateSqMeter() {
  double width = distance[0] + distance[2];
  double height = distance[1] + distance[3];
  double sqMeter = (width * height)/1000;
  return sqMeter;
}