// Part 2 - That Thermostat!

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare Variables
  double inputFahrenheit, outputCelsius, DifferenceCelcius,
      outputDegreesFrom22Celcius;

  // Prompt user for input
  printf("Enter the thermostat temperature: ");
  scanf("%lf", &inputFahrenheit);

  // Convert Fahrenheit to Celsius
  outputCelsius = (inputFahrenheit - 32) * (5.0 / 9.0);

  // Display Output
  printf("The temperature in Celsius is: %.1lf\n\n", outputCelsius);

  // Calculate Difference in Celcius
  DifferenceCelcius = outputCelsius - 22;

  // Converting Difference in Celsius back to Fahrenheit
  outputDegreesFrom22Celcius = DifferenceCelcius * (9.0 / 5.0);

  // Display Output
  printf(
      "You are %.1lf degrees Fahrenheit away from a nice 22 degrees Celsius.\n",
      outputDegreesFrom22Celcius);

  return EXIT_SUCCESS;
}