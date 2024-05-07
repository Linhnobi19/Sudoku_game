#pragma once

#include "Board.h"

// folder for creating some function for solve the game sudoku
bool possible(Board&, int, int, int);
bool solve(Board*, int, int);		// use to solve the board from a position
Board* generateBoard(int);			// use for generate number in sudoku
