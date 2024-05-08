#pragma once

#include "Board.h"

// folder for creating some function for solve the game sudoku
bool possible(Board&, int, int, int);
bool solve(Board*, int, int);		// use to solve the board from a position
Board* generateBoard(int);			// use for generate number in sudoku


// the instructions for generate a puzzle
/*The first thing that we can realize that we can improve by fill all sub array of puzzle in diagonal
    It means that fill all the square N of the board (a box)
    1. Fill all sub box in diagonal
    2. Fill recursively rest of the non - diagonal matrices
    3. When the matrix is fully filled, remove K elements*/

void fillDiagonal(Board* board);      // function for the first instruction
void removeRandom(Board* board);                    // function for the third instruction
int randomNum(int);                 // for random number
bool possibleInBox(Board* board, int rowStart, int colStart, int val);