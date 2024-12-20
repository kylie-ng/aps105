// Part 1 - Debugging

#include <stdio.h>

int main(void) {
  char userSign;
  int sum = 0, userNum = 0;
  printf("Enter sequence of numbers to add: ");

  do {
    scanf("\n%c%d" /*the \n stores the "enter" from the user*/, &userSign,
          &userNum);
    if (userSign == '+') {
      sum += userNum;
      printf("Sum is updated to %d\n", sum);
    } else if (userSign == '-') {
      sum -= userNum;
      printf("Sum is updated to %d\n", sum);
    }
  } while (sum > 0);

  printf("Sum fell below zero.\n");

  return 0;
}