// Part 3 - Numerical Integration

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare variables
  int n = 0;

  // Main Do-while loop, as the n-input must not be a negative number and must
  // not be 0 --> !(n <= 0)
  do {
    // Initialize the variables, as the Mn resets each time
    double a = 0.0, b = 0.0, deltaX = 0.0, initialXi = 0.0, Mn = 0.0;

    // Prompt user for input
    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &n);

    // Takes in the n-value above, if n == 0, then it 'breaks' out of the while
    // loop and does the other statements outside of it. In this case, that
    // statement is a statement that prints "Exiting."
    if (n == 0) {
      break;
    }

    // Ensure interval of integration is valid input
    do {
      printf("Please enter the interval of integration (a b): ");
      scanf("%lf %lf", &a, &b);
      if (a > b) {
        printf("Invalid interval!\n\n");
      }
    } while (a > b);

    // For Loop - Integration Calculations
    deltaX = (b - a) / n;  // Placed above For Loop for clearner appearance
    initialXi =
        a +
        (1.0 / 2.0) * deltaX;  // Placed above For Loop for clearner appearance

    for (double Xi = initialXi; Xi <= b; Xi += deltaX) {
      Mn = Mn + deltaX * exp(-pow(Xi, 2.0));
    }

    // Display Output
    printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is: %.5lf\n\n",
           a, b, n, Mn);

  } while (n > 0);

  // From above, if n == 0, then Break, then it exits
  printf("Exiting.\n");

  return EXIT_SUCCESS;
}