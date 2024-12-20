//
// Author: Kylie Ng
//

#include "lab8part1.h"

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
    printf("%c ", 'a' + row);
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
        bool found = false;
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
  return (row >= 0 && row < n) && (col >= 0 && col < n);
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

bool checkLegalDirections(char board[][26], int n, int row, int col,
                          char colour) {
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (!(deltaRow == 0 && deltaCol == 0) &&
          checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                deltaCol)) {
        return true;
      }
    }
  }
  return false;
}

int checkValidBoard(char board[][26], int n, char colour) {
  int count = 0;  // count number of valid moves in whole board
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (checkMoveValid(board, row, col) &&
          checkLegalDirections(board, n, row, col, colour)) {
        count++;
      }
    }
  }
  return count;
}

int countFlip(char board[][26], int n, int row, int col, char colour,
              int deltaRow, int deltaCol, bool toFlip) {
  int newRow = row + deltaRow;
  int newCol = col + deltaCol;
  int countFlipped = 0;
  while (positionInBounds(n, newRow, newCol) &&
         board[newRow][newCol] != colour && board[newRow][newCol] != 'U') {
    if (toFlip) {
      board[newRow][newCol] = colour;  // flips the tile
    }
    countFlipped++;  // count number of tiles to flip regardless
    newRow += deltaRow;
    newCol += deltaCol;
  }
  return countFlipped;
}

int countFlipForPosition(char board[][26], int n, char colour, int row, int col,
                         bool toFlip) {
  int score = 0;
  if (positionInBounds(n, row, col) && board[row][col] == 'U') {
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
      for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
        if (!(deltaRow == 0 && deltaCol == 0) &&
            checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                  deltaCol)) {
          score +=
              countFlip(board, n, row, col, colour, deltaRow, deltaCol, toFlip);
        }
      }
    }
  }
  if (toFlip) {
    board[row][col] = colour;  // flips the current tile
  }
  return score;
}

int checkScore(char board[][26], int n,
               char colour) {  // copied and pasted from ComputerMove function
  int maxScore = 0;
  // Find move that flips max number of opponent tiles
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (countFlipForPosition(board, n, colour, row, col, false) != 0) {
        int score = countFlipForPosition(board, n, colour, row, col, false);
        if (score > maxScore) {
          maxScore = score;  // update score
        }
      }
    }
  }
  return maxScore;
}

bool gameOver(char board[][26], int n) {
  bool boardFull = true;
  bool blackValidMove = false;
  bool whiteValidMove = false;

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {  // check full
        boardFull = false;
      }
    }
  }

  if (checkScore(board, n, 'B') != 0) {
    blackValidMove = true;
  }

  if (checkScore(board, n, 'W') != 0) {
    whiteValidMove = true;
  }

  if (boardFull || (!blackValidMove &&
                    !whiteValidMove)) {  // if game is really over, return true
    return true;
  }

  return false;
}

void computerMove(char board[][26], int n, char colour) {
  int bestRow = -1, bestCol = -1, maxScore = 0;
  // Find move that flips max number of opponent tiles
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (countFlipForPosition(board, n, colour, row, col, false) !=
          0) {  // "if the score is 0, don't need to flip."
                // toFlipForPosition already accounts for when the score is
                // 0, and no need to call checkLegalInDirection and
                // moveValid
        int score = countFlipForPosition(board, n, colour, row, col, false);
        if (score > maxScore) {
          maxScore = score;  // update score
          bestRow = row;     // update best row
          bestCol = col;     // update best column
        }
      }
    }
  }

  // Make the best move
  if (maxScore != 0) {  // best move not found (double dipping: no valid move)
    countFlipForPosition(board, n, colour, bestRow, bestCol,
                         true);  // true meaning should flip, since bool
    printf("Computer places %c at %c%c.\n", colour, bestRow + 'a',
           bestCol + 'a');
    // Print current board
    printBoard(board, n);
  } else {
    printf("%c player has no valid move.\n", colour);
  }
}

void userMove(char board[][26], int n, int row, int col, char colour) {
  // Translate user input by placing it on the board
  board[row][col] = colour;
  // Check and flip tiles
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                deltaCol)) {
        countFlip(board, n, row, col, colour, deltaRow, deltaCol, true);
      }
    }
  }
  // Print current board
  printBoard(board, n);
}

char winnerPlayer(char board[][26], int n) {
  int blackCount = 0;
  int whiteCount = 0;

  // Count the number of black and white tiles on the board
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'B') {
        blackCount++;
      } else if (board[row][col] == 'W') {
        whiteCount++;
      }
    }
  }

  // Compare the counts to determine the winner
  if (blackCount > whiteCount) {
    return 'B';
  } else if (whiteCount > blackCount) {
    return 'W';
  } /*else {
    return 'D';
  }*/
}

int main(void) {
  int n = 0;
  char turn = 'B', computer;
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

  // Ask user what the Computer Color should be
  printf("Computer plays (B/W): ");
  scanf(" %c", &computer);

  // Print initial board
  printBoard(board, n);

  // Main Game While Loop
  while (!gameOver(board, n)) {
    if (turn == computer) {
      computerMove(board, n, computer);
    } else {
      char row, col;
      if (checkValidBoard(board, n, turn) == 0) {
        printf("%c player has no valid move.\n", turn);
      } else {
        printf("Enter move for colour %c (RowCol): ", turn);
        scanf(" %c%c", &row, &col);
        int rowIndex = row - 'a';
        int colIndex = col - 'a';
        if (checkLegalDirections(
                board, n, rowIndex, colIndex,
                turn)) {  // dif func from check legal in dir in one dir
          userMove(board, n, rowIndex, colIndex, turn);
        } else {
          printf("Invalid move.\n");
          break;
        }
      }
    }
    // Switch turn
    if (turn == 'B') {
      turn = 'W';
    } else {
      turn = 'B';
    };
  }

  // Print final outcome
  char winner = winnerPlayer(board, n);
  if (winner == 'B') {
    printf("B player wins.\n");
  } else if (winner == 'W') {
    printf("W player wins.\n");
  } else {
    printf("Draw!\n");
  }

  return 0;
}
