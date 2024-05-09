#include "Board.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include "Solve.h"

using namespace std;


Board::Board(int s)
	: N(s)
{
	

	// Declare 3 array 2D
	board = new int* [N];
	for (int i = 0; i < N; i++) {
		board[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j] = 0;

	//matrix to track immutables
	immutable = new bool* [N];
	for (int i = 0; i < N; i++) {
		immutable[i] = new bool[N];
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			immutable[i][j] = false;

	// matrix to track which values are causing infeasibilitsy
	// these are problem cells that will be
	// highlighted in red during gameplay
	possiblities = new bool* [N];
	for (int i = 0; i < N; i++) {
		possiblities[i] = new bool[N];
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			possiblities[i][j] = true;



}

Board::~Board()
{
	// delete the board
	for (size_t i = 0; i < N; i++)
	{
		delete[] board[i];
	}
	for (size_t i = 0; i < N; i++)
	{
		delete[] immutable[i];
	}
	for (size_t i = 0; i < N; i++)
	{
		delete[] possiblities[i];
	}
	delete[] board;
	delete[] immutable;
	delete[] possiblities;
}

void Board::printPuzzle() 
{
	bool extraSpace = N > 9;
	int squareBox = sqrt(N);

	// print the upper bound 
	cout << "\t\t\t\t";
	for (size_t i = 0; i < N; i++)
	{
		cout << "+---";
		// extra line means that the number will need more space
		// 1 - 9 need a space 
		// 11 -- 99 need 2 space
		if (extraSpace)
		{
			cout << "-";
		}
	}
	cout << "+" << endl;	// end corner

	// print number
	
	for (size_t row = 0; row < N; row++)
	{
		cout << "\t\t\t\t";
		for (size_t col = 0; col < N; col++) {

			if ((col) % squareBox == 0)
			{
				cout << "| ";
			}
			else
			{
				cout << "  ";
			}

			// if number is 0 --> print .
			if (board[row][col] == 0)
			{
				cout << ". ";
				if (extraSpace)
				{
					cout << ' ';
				}
			}

			// if the number is immutable --> print yellow
			else
			{
				if (extraSpace) cout << setw(2);
				else cout << setw(1);
				if (immutable[row][col] == true) {
					cout << "\033[33m" << board[row][col] << "\033[39m" << ' ';
				}
				else if (possiblities[row][col] == false)
				{
					cout << "\033[31m" << board[row][col] << "\033[39m" << ' ';
				}
				else cout << board[row][col] << ' ';
			}
		}
		cout << "|" << endl;
		if ((row + 1) % squareBox == 0)
		{
			cout << "\t\t\t\t";
			for (size_t i = 0; i < N; i++) {
				cout << "+---";
				if (extraSpace)
				{
					cout << "-";
				}
			}
			cout << "+" << endl;
		}
	}
}

bool Board::checkPuzzle()
{
	// check every position
	for (size_t row = 0; row < N; row++)
	{
		for (size_t col = 0; col < N; col++) {
			int val = (*this)(row, col);


			// set to 0 because possible function loop through all possible position that inlcude this position
			(*this)(row, col) = 0;
			if (!possible(*this, row, col, val))
			{
				(*this)(row, col) = val;	// return value
				return false;
			}
			(*this)(row, col) = val;
		}
	}

	bool check = true;
}

// function is simmilar to function possible in solve header file
// But it change the possible square to help change the color
// use to warn user that enter wrong number
bool Board::possibleUser(int row, int col, int val)
{
	int boxSize = sqrt(N);

	if (row > N || row < 0)
	{
		cout << "\n\t\t\t--> You can't play off the game board";
		return false;
	}
	if (col > N || col < 0)
	{
		cout << "\n\t\t\t--> You can't play off the game board";
		return false;
	}

	bool isPossible = true;
	// check every ele in row
	for (size_t i = 0; i < N; i++)
	{
		/*if (i == col)
		{
			continue;
		}*/
		if ((*this)(row, i) == val) {
			possiblities[row][i] = false;
			cout << "duplicate in row with (" << row + 1 << ", " << i + 1 << ")" << " value is " << (*this)(row, i) << endl;
			isPossible = false;
		}
		else
		{
			possiblities[row][i] = true;
		}
	}

	// check every ele in col
	for (size_t i = 0; i < N; i++)
	{
		/*if (i == row)
		{
			continue;
		}*/
		if ((*this)(i, col) == val) {
			possiblities[i][col] = false;
			cout << "duplicate in col with (" << i + 1 << ", " << col + 1 << ")" << (*this)(i, col) << endl;
			isPossible = false;
		}
		else
		{
			possiblities[row][i] = true;
		}
	}

	// check every ele in box
	int boxRow = row - (row % boxSize);
	int boxCol = col - (col % boxSize);

	for (size_t i = boxRow; i < boxSize + boxRow; i++)
	{
		for (size_t j = boxCol; j < boxCol + boxSize; j++) {
			/*cout << board(i, j) << ' ';*/
			if ((*this)(i, j) == val)
			{
				/*if (i == row && j == col)
				{
					continue;
				}*/
				possiblities[i][j] = false;
				cout << "duplicate in box with (" << i + 1 << ", " << j + 1 << ")" << " value is " << (*this)(i, j) << endl;
				isPossible = false;
			}
			else
			{
				possiblities[i][j] = true;
			}
		}
		//cout << endl;
	}


	return isPossible;
}

void Board::clearPuzzle()
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < 0; j++) {
			if (checkImmutable(i, j) == false)
			{
				(*this)(i, j) = 0;
			}
		}
	}
}

bool Board::inBounds(int val)
{
	if ((val < 0) || val >= N)
	{
		return false;
	}
	return true;
}

bool Board::isProblem(int r, int c)
{
	return possiblities[r][c];
}

int& Board::operator()(int x, int y)
{
	// TODO: insert return statement here
	assert(x < N&& y < N);
	return board[x][y];
}

void Board::assignValue(int r, int c, int val)
{
	(*this)(r, c) = val;
}

void Board::assignImmutable(int r, int c, bool val)
{
	immutable[r][c] = val;
}

bool Board::checkImmutable(int r, int c)
{
	return immutable[r][c];
}

int Board::getSize() const
{
	return N;
}
