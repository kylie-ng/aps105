// Part 2 - Arrival Time Calculator

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Prompt user to input current time
  int curHrs = 0, curMins = 0;
  printf("Enter current time: ");
  scanf("%d %d", &curHrs, &curMins);

  // Convert current time to amount of minutes
  int curTimeMins = curHrs * 60 + curMins;

  // Prompt user to input trip time
  double tripHrs = 0;
  printf("Enter trip time: ");
  scanf("%lf", &tripHrs);

  // Convert trip time to amount of minutes
  int tripMins = tripHrs * 60;

  // Calculate total arrival time
  int totalTimeMins = curTimeMins + tripMins;

  // Split total time in minutes in terms of hours and minutes
  int totalHrs = totalTimeMins / 60;
  int totalMins = totalTimeMins % 60;

  // Display output of current time and arrival times
  printf("Current time is %02d:%02d\n", curHrs, curMins);
  if (totalHrs < 24) {
    printf("Arrival Time is same day %02d:%02d\n", totalHrs, totalMins);
  } else {
    printf("Arrival Time is next day %02d:%02d\n", totalHrs - 24, totalMins);
  }

  return EXIT_SUCCESS;
}