#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function Headers (Part 1)
void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);

// Function Headers (Part 2)
void search(const int Size, char puzzle[][Size], const int wordSize,
            char* word);
bool check1D(const int Size, char puzzle[][Size], const int wordSize,
             char* word, int rowLoc, int colLoc, int dir);
bool inBounds(int row, int col, const int Size);

// Main Function
int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);

  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");

  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }

  free(word);
  word = NULL;
  return 0;
}

// Part 2 - Searching for a Word
const char* dirName[] = {"south-east", "south",      "south-west",
                         "west",       "north-west", "north",
                         "north-east", "east"};  // south-east, then clockwise

void search(const int Size, char puzzle[][Size], const int wordSize,
            char* word) {
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      for (int dir = 0; dir < 8; dir++) {
        if (check1D(Size, puzzle, wordSize, word, row, col, dir)) {
          printf(
              "%s can be found at row , col = (%d, %d) in the %s direction.\n",
              word, row + 1, col + 1,
              dirName[dir]);  // (row + 1) and (col + 1) because the index of
                              // row was 0 and index of col was 0
        }
      }
    }
  }
}

// Part 1 - Input Word Puzzle and Word
char* readWord(int* wordSize) {
  printf("How many characters are there in the word?\n");
  scanf("%d", wordSize);  // don't need to put "&" since wordSize is a POINTER
                          // to an integer

  // "Dynamically allocate an array using malloc with size entered by the user"
  char* word = (char*)malloc((*wordSize + 1) * sizeof(char));

  printf("What is the word that you are looking for?\n");
  scanf("%s", word);

  return word;
}

// Part 1 - Input Word Puzzle and Word
void readWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("Please enter the word puzzle:\n");
  char letter;  // created a variable called "letter" that stores each
                // character. it changes
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      scanf(" %c", &letter);  // ignores whitespace before the entered character
      puzzle[row][col] = letter;
    }
  }
}

// Part 2 - Searching for a Word
bool check1D(const int Size, char puzzle[][Size], const int wordSize,
             char* word, int rowLoc /*current row index*/,
             int colLoc /*current col index*/,
             int dir) /*function prototype (suggested)*/ {
  int rowOffset[] = {1, 1, 1, 0, -1, -1, -1, 0};
  int colOffset[] = {1, 0, -1, -1, -1, 0, 1, 1};

  int newRowIndex =
      rowLoc + (wordSize - 1 /*"-1" bcz 0-base index*/) * rowOffset[dir];
  int newColIndex =
      colLoc + (wordSize - 1 /*"-1" bcz 0-base index*/) * colOffset[dir];

  // Check if the new position is within bounds
  if (!inBounds(newRowIndex, newColIndex, Size)) {
    return false;
  }

  // Check if the word matches in the specified direction
  for (int i = 0; i < wordSize; i++) {
    int currentRow = rowLoc + i * rowOffset[dir];
    int currentCol = colLoc + i * colOffset[dir];

    // Compare the puzzle letter with the corresponding word letter
    if (puzzle[currentRow][currentCol] != word[i]) {
      return false;
    }
  }

  return true;
}

bool inBounds(int row, int col, const int Size) {
  return ((row >= 0 && row < Size) && (col >= 0 && col < Size));
}

// Part 1 - Input Word Puzzle and Word
void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("The word puzzle entered is\n");
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      printf("%c ", puzzle[row][col]);
    }
    printf("\n");
  }
}

// Part 1 - Input Word Puzzle and Word
void printWord(char* word, const int wordSize) {
  for (int i = 0; i < wordSize; i++) {
    printf("%c ", word[i]);
  }
}