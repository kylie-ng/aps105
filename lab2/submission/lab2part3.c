// Part 3 - Coulomb's Law
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare variables
  double q1 = 0.0, q2 = 0.0, r = 0.0, F = 0.0;
  char prefix1, C1, prefix2, C2;
  const double k = 8.9875E9;

  // Prompt user for input
  printf("Enter the value of the two charges separated by a space: ");
  scanf("%lf%c%c %lf%c%c", &q1, &prefix1, &C1, &q2, &prefix2, &C2);
  printf("Enter distance between charges in metres: ");
  scanf("%lf", &r);

  // Convert units to Coulombs
  if (prefix1 == 'n') {
    q1 *= 1E-9;
  } else {
    q1 *= 1E-6;
  }

  if (prefix2 == 'n') {
    q2 *= 1E-9;
  } else {
    q2 *= 1E-6;
  }

  // Calculate F using Coulomb's Law
  F = k * (fabs(q1 * q2) / (pow(r, 2)));

  // Display output
  if (F < 1E-6) {
    printf("The force between charges is %.2lfnN (less than 1uN)\n", F * 1E9);
  } else if (F < 1E-3) {
    printf("The force between charges is %.2lfuN (less than 1mN)\n", F * 1E6);
  } else if (F < 1) {
    printf("The force between charges is %.2lfmN (less than 1N)\n", F * 1E3);
  } else {
    printf("The force between charges is %.2lfN (1N or greater)\n", F);
  }

  return EXIT_SUCCESS;
}