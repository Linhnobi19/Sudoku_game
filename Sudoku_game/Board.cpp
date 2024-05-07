#include "Board.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <math.h>

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
			immutable[i][j] = true;

	// matrix to track which values are causing infeasibilitsy
	// these are problem cells that will be
	// highlighted in red during gameplay
	possiblities = new bool* [N];
	for (int i = 0; i < N; i++) {
		possiblities[i] = new bool[N];
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			possiblities[i][j] = false;



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
				if (immutable[row][col] == true) {
					cout << "\033[33m" << board[row][col] << "\033[39m" << ' ';
				}
				else cout << board[row][col] << ' ';
			}
		}
		cout << "|" << endl;
		if ((row + 1) % squareBox == 0)
		{
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

void Board::checkPuzzle()
{
}

void Board::possibleUser(int, int, int)
{
}

void Board::clearPuzzle()
{
}

bool Board::inBounds(int, int)
{
	return false;
}

bool Board::isProblem(int, int)
{
	return false;
}

int& Board::operator()(int x, int y)
{
	// TODO: insert return statement here
	assert(x < N&& y < N);
	return board[x][y];
}

void Board::assignValue(int, int, int)
{
}

void Board::assignImmutable(int, int)
{
}

bool Board::checkImmutable(int, int)
{
	return false;
}

int Board::getSize() const
{
	return 0;
}
