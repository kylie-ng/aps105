// Part 3 - Escaping Planet

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare Variables
  double inputCircumference, inputAcceleration, outputRadius, outputMass,
      outputVelocity;
  const double pi = M_PI;
  const double GravitationalConst = 6.6726E-11;

  // Prompt user for input
  printf("Circumference (km) of planet? ");
  scanf("%lf", &inputCircumference);
  printf("Acceleration due to gravity (m/s^2) on planet? ");
  scanf("%lf", &inputAcceleration);

  // Calculations
  outputRadius = inputCircumference / (2.0 * pi);
  outputMass = (inputAcceleration * pow((outputRadius * 1000.0), 2.0)) /
               GravitationalConst / 1E21;
  outputVelocity =
      sqrt(((2 * GravitationalConst * (outputMass * 1E21)) / 1000000000.0) /
           outputRadius);

  // Display output
  printf("\nCalculating the escape velocity...\n");
  printf("Planet radius: %.1lf km\n", outputRadius);
  printf("Planet mass: %.1lf x 10^21 kg\n", outputMass);
  printf("Escape velocity: %.1lf km / s\n", outputVelocity);

  return EXIT_SUCCESS;
}