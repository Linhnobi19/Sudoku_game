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
				if (extraSpace)
				{
					cout << setw(2);
				}
				else
				{
					cout << setw(1);
				}
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

bool Board::possibleUser(int, int, int)
{
	return false;
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

bool Board::inBounds(int r, int c)
{
	if ((r < 0) || r >= N || c < 0 || c >= N)
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
