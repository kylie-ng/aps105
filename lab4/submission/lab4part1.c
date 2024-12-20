#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function Headers
double randDouble();
bool inBounds(double x, double y);

// Main Function
int main(void) {
  int iterations = 0, countCircle = 0;
  double pi = 0.0, x = 0.0, y = 0.0;

  // Sets seed to 42 to make it even more random than rand()
  srand(42);

  // Prompts user for input
  printf("Number of monte carlo iterations: ");
  scanf("%d", &iterations);

  for (int count = 0; count < iterations; count++) {
    x = randDouble();
    y = randDouble();
    if (inBounds(x, y)) {
      countCircle++;
    }
  }

  // Calculate pi estimation
  pi = 4.0 * ((double)countCircle / iterations);
  printf("Pi: %.4lf\n", pi);

  return EXIT_SUCCESS;
}

// Double Function
double randDouble() { return (double)rand() / ((double)RAND_MAX); }

// inBounds Function
bool inBounds(double x, double y) { return x * x + y * y <= 1.0; }