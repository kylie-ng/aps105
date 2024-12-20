//
// Author: Kylie Ng
//

#include "reversi.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printBoard(char board[][26], int n) {
  // Print alphabet on First Row
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("%c", 'a' + i);
  }
  printf("\n");
  // Print Board (excluding First Row of alphabet):
  for (int row = 0; row < n; row++) {
    printf("%c ", 'a' + row);  // print a letter of the alphabet at the
                               // beginning of each row
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

bool checkMoveValid(
    char board[][26], int row,
    int col) {  // Checking if move is valid BEFORE board configuration
  if (board[row][col] == 'U') {
    return true;
  } else {
    return false;
  }
}

void printAvailableMoves(char board[][26], int n, char colour) {
  printf("Available moves for %c:\n", colour);
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (checkMoveValid(board, row, col)) {
        bool found = false;  // Initializing the boolean. (I made a boolean so
                             // that it would "break" (without using a break)
                             // --> Once an available move is found, it would
                             // break out of the inner loop)
        for (int deltaRow = -1; deltaRow <= 1 && !found;
             deltaRow++) {  // Rows: Check all 8 directions
          for (int deltaCol = -1; deltaCol <= 1 && !found;
               deltaCol++) {  // Cols: Check all 8 directions
            if (!(deltaRow == 0 &&
                  deltaCol == 0)) {  // Skips current cell (aka. "origin")
              if (checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                        deltaCol)) {
                printf("%c%c\n", 'a' + row, 'a' + col);
                found = true;
              }
            }
          }
        }
      }
    }
  }
}

bool positionInBounds(int n, int row, int col) {
  if ((row >= 0 && row < n) && (col >= 0 && col < n)) {
    return true;
  } else {
    return false;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  char oppColour;
  if (colour == 'W') {
    oppColour = 'B';
  } else {
    oppColour = 'W';
  }

  int newRow = row + deltaRow;
  int newCol = col + deltaCol;

  // Until Hit your colour, return true
  if (!(positionInBounds(n, newRow, newCol)) ||
      board[newRow][newCol] !=
          oppColour) {  // out of bounds or is same color or 'U'
    return false;
  }

  while (positionInBounds(n, newRow, newCol) &&
         board[newRow][newCol] == oppColour) {
    // Move to the next cell in the same direction
    newRow += deltaRow;
    newCol += deltaCol;
  }
  // Once you exit the loop, check more conditions
  if (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == colour) {
    return true;
  }

  return false;
}

void flip(char board[][26], int n, int row, int col, char colour, int deltaRow,
          int deltaCol) {
  int newRow = row + deltaRow;
  int newCol = col + deltaCol;
  while (positionInBounds(n, newRow, newCol) &&
         board[newRow][newCol] != colour && board[newRow][newCol] != 'U') {
    board[newRow][newCol] = colour;
    newRow += deltaRow;
    newCol += deltaCol;
  }
}

/*1PASS 3FAIL void checkValidAndInBounds(char board[][26], int n, char colour,
int row, int col) { int deltaRow, deltaCol; bool flipped = true; for (deltaRow =
-1; deltaRow <= 1 && flipped; deltaRow++) { for (deltaCol = -1; deltaCol <= 1 &&
flipped; deltaCol++) { if ((positionInBounds(n, row, col)) && (board[row][col]
== 'U') &&
          !(deltaRow == 0 && deltaCol == 0) &&
          checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                deltaCol)) {
        board[row][col] = colour;
        flip(board, n, row, col, colour, deltaRow, deltaCol);
      } else {
        flipped = false;
      }
    }
  }
  if (flipped) {
    printf("Valid move.\n");
  } else {
    printf("Invalid move.\n");
  }
}*/

/*3PASS 1FAIL, void checkValidAndInBounds(char board[][26], int n, char colour,
int row, int col) { int deltaRow, deltaCol; if ((positionInBounds(n, row, col))
&& (board[row][col] == 'U')) { for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
      for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
        if (!(deltaRow == 0 && deltaCol == 0) &&
            checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                  deltaCol)) {
          board[row][col] = colour;
          flip(board, n, row, col, colour, deltaRow, deltaCol);
        }
      }
    }
    printf("Valid move.\n");
  } else {
    printf("Invalid move.\n");
  }
}*/

void checkValidAndInBounds(
    char board[][26], int n, char colour, int row,
    int col) {  // Checking if move is valid AFTER board configuration
  int deltaRow, deltaCol;
  bool validMove = false;

  if (positionInBounds(n, row, col) && board[row][col] == 'U') {
    for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
      for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
        if (!(deltaRow == 0 && deltaCol == 0) &&
            checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                  deltaCol)) {
          board[row][col] = colour;
          flip(board, n, row, col, colour, deltaRow, deltaCol);
          validMove = true;  // indicate at least one direction is valid
        }
      }
    }
  }

  if (validMove) {
    printf("Valid move.\n");
  } else {
    printf("Invalid move.\n");
  }
}

int main(void) {
  int n = 0;
  char colour, row, col;
  char board[26][26];
  printf("Enter the board dimension: ");
  scanf("%d", &n);

  // Initialize the board
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      board[row][col] = 'U';
    }
  }
  int center = n / 2;
  board[center - 1][center - 1] = board[center][center] = 'W';  // white tiles
  board[center - 1][center] = board[center][center - 1] = 'B';  // black tiles

  // Print initial board
  printBoard(board, n);

  // Enter board configuration
  printf("Enter board configuration:\n");
  while (!(colour == '!' && row == '!' && col == '!')) {
    scanf(" %c%c%c", &colour, &row, &col);
    int rowIndex =
        row - 'a';  // getting the rowIndex using character arithmetic
    int colIndex =
        col - 'a';  // getting the colIndex using character arithmetic
    board[rowIndex][colIndex] = colour;
  }
  printBoard(board, n);

  // Print available moves
  printAvailableMoves(board, n, 'W');  // passing the color white
  printAvailableMoves(board, n, 'B');  // passing the color black

  // Check Valid or Invalid move
  printf("Enter a move:\n");
  scanf(" %c%c%c", &colour, &row, &col);
  int rowIndex = row - 'a';
  int colIndex = col - 'a';

  // Check valid move and flip tiles respectively
  checkValidAndInBounds(board, n, colour, rowIndex, colIndex);

  // Print final board (after all the flipping) and terminate
  printBoard(board, n);

  return 0;
}