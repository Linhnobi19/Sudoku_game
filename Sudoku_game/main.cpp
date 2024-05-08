#include <iostream>
#include <string>
#include "Board.h"
#include "Solve.h"
#include <math.h>

using namespace std;




int main() {
	int size = 9;
	Board* board = new Board(size);
	
	board = generateBoard(size);

	board->printPuzzle();

	return 0;
}