// Part 2 - Robot Shooting

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Decalre variables
  double d = 0.0, h = 0.0, y = 0.0, t = 0.0;
  int a = 0;

  // Define Constants
  const double V = 20.0, L = 2.0, G = 9.81, PI = M_PI;

  // Unit conversion factors
  const double deg_to_rad = PI / 180.0;

  // Prompt and Ensure valid user input for the distance
  do {
    printf(
        "Please enter the horizontal distance from the wall between 3 and 30 "
        "m: ");
    scanf("%lf", &d);
  } while (d < 3.0 || d > 30.0);

  // Prompt and Ensure valid user input for the height
  do {
    printf("Please enter the target height between 3 and 6 m: ");
    scanf("%lf", &h);
  } while (h < 3.0 || h > 6.0);

  // Main while loop
  while ((fabs(y - h) > 0.3) && (a < 90)) {
    ++a;
    t = d / (V * cos(a * deg_to_rad));  // calculate the travel time (t)
    y = L + V * sin(a * deg_to_rad) * t -
        (1.0 / 2.0) * G * pow(t, 2.0);  // calculate the vertical height (y)
  }

  // Display output
  printf("The angle should be %.2lf\n",
         (double)a);  // since "a" was an integer, we changed it to a double

  return EXIT_SUCCESS;
}