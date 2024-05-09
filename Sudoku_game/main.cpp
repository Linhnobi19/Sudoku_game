#include <iostream>
#include <string>
#include "Board.h"
#include "Solve.h"
#include <math.h>
#include "Game.h"

using namespace std;




int main() {
	/*int size = 9;
	Board* board = new Board(size);
	
	board = generateBoard(size);

	board->printPuzzle();*/
	int size = 9;
	playGame(size);


	return 0;
}