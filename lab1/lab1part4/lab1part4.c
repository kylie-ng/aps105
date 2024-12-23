// Part 4 - Debugging

#include <stdio.h>

int main(void) {
  // Declare Variables
  double dailyRate;
  int numDays;
  int freeDays;
  double totalCharge;

  const double HST = 0.13;

  // Get the daily rate
  printf("Enter the daily rate: ");
  scanf("%lf", &dailyRate);

  // Get the number of rental days
  printf("Enter the rental period (in days): ");
  scanf("%d", &numDays);

  // Compute the free days
  freeDays = numDays / 4;
  printf("\nYour total free day(s) in this rental is: %d\n", freeDays);

  // Compute the total charge tax inclusive
  totalCharge = (1 + HST) * (numDays - freeDays) * dailyRate;
  printf("The total charge including taxes is: %.2lf\n", totalCharge);

  return 0;
}