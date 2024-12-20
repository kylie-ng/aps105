#include <stdio.h>
#include <stdlib.h>

// FUNCTION HEADERS:
int luckyNumCheck(int num);
int charAt(int self, int num);
int length(int num);

// MAIN FUNCTION:
int main(void) {
  // Initializing vairables
  int inputInt = 0, numLucky = 0;

  printf("Input an integer: ");
  scanf("%d", &inputInt);
  numLucky = numLucky +
             luckyNumCheck(
                 inputInt);  // Number of lucky numbers that appeared thus far

  do {
    // Prompt user for input
    printf("Input an integer (0 to stop): ");
    scanf("%d", &inputInt);

    numLucky = numLucky +
               luckyNumCheck(
                   inputInt);  // Number of lucky numbers that appeared thus far

  } while (inputInt != 0);  // since when the user inputs a 0, the code stops

  printf("You entered %d lucky number(s)!\n", numLucky);
  return EXIT_SUCCESS;
}

// FUNCTIONS:
int luckyNumCheck(int num) {
  // Initializing variables
  int countSeven = 0, self = 1, foundNum = 0;

  for (int i = 0; i < length(num);
       ++i) {  // for every character (digit) of the integer,
    foundNum = charAt(self, num);  // "foundNum" is the extracted digit,
                                   // computed from the charAt function.
    self = self *
           10;  // "self" represents the power of ten that you will divide by
    if (foundNum == 7 || foundNum == -7) {
      ++countSeven;
    }
  }

  // If three sevens, "777", return a 1 or 0, which will be used in Line 22
  // equation of the main function
  if (countSeven == 3) {
    return 1;
  } else {
    return 0;
  }
}

int length(int num) {
  // Initializing variable
  int numLength = 0;
  while (num != 0) {  // while there are integers present,
    num = num / 10;  // divide by 10 to truncate the decimal digit, resulting in
                     // the remaining integer length
    ++numLength;     // counts how many iterations the truncating occurs
  }
  return numLength;  // returns the number of digits of the integer
}

int charAt(int self, int num) {
  num = num / self;  // the variable "self" changes; it is what you multiply by
                     // ten by in Line 39
  return num % 10;   // extracts the last digit of the integer, since it is
                     // basically the remainder
}