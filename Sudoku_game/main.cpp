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

	cout << "\n\nAfter solve:" << endl;
	if (solve(board, 0,0))
	{
		cout << "Puzzle was solved" << endl;
		board->printPuzzle();
	}
	else
	{
		cout << "Couldn't solve this problem" << endl;
	}


	return 0;
}