#pragma once

//#include <>
class Board
{
public:
	Board(int);
	~Board();

	void printPuzzle();
	void checkPuzzle();		// check if the puzzle is approriate
	void possibleUser(int, int, int);	// use to track number that user typed and change possiblitites
	void clearPuzzle();				// clear puzzle if the user get stuck 
	bool inBounds(int, int);		// chekc if the position is in board
	bool isProblem(int, int);		// check if the current position is valid or not

	// some function for easier acccess and assignValue
	int& operator() (int, int);		// use (x, y) for access
	void assignValue(int, int, int);	// assign value for (x,y)
	void assignImmutable(int, int);		// assign value that cannot change
	bool checkImmutable(int, int);		// checking if the position is immutable or not

	int getSize() const;



private:
	int N;		// size of the board
	int** board;		// 2D array for store value
	bool** immutable;	// for create value that can't change because it's the num generate by compiler
	bool** possiblities;	// tracking the number that user enter. If the number is duplicate
							// will show in red color for user understand
};
