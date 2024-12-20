// Part 1 - Law of Sines

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare variables
  double a = 0.0, b = 0.0, c = 0.0, alpha = 0.0, beta = 0.0, gamma = 0.0;
  const double pi = M_PI;
  const double deg_to_rad = pi / 180.0;
  const double rad_to_deg = 180.0 / pi;

  // Prompt user for input
  printf("Enter the length of side A: ");
  scanf("%lf", &a);
  printf("Enter the length of side B: ");
  scanf("%lf", &b);
  printf("Enter the measure of angle alpha in degrees: ");
  scanf("%lf", &alpha);

  // Convert Degrees to Radians
  alpha = alpha * deg_to_rad;

  // Calculating: c, beta (in radians), gamma (in radians)
  beta = asin(b * sin(alpha) / a);
  gamma = pi - (alpha + beta);
  c = (a / sin(alpha) * sin(gamma));

  // Convert Radians to Degrees
  alpha = alpha * rad_to_deg; /*should be the same value as the user input*/
  beta = beta * rad_to_deg;
  gamma = gamma * rad_to_deg;

  // Display output
  printf("\nResults: \n");
  printf("Side A: %.2lf\n", a);
  printf("Side B: %.2lf\n", b);
  printf("Side C: %.2lf\n", c);
  printf("Angle Alpha: %.2lf degrees\n", alpha);
  printf("Angle Beta: %.2lf degrees\n", beta);
  printf("Angle Gamma: %.2lf degrees\n", gamma);

  return EXIT_SUCCESS;
}