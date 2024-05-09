#include "Solve.h"
#include <random>
#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>


using namespace std;

bool possible(Board& board, int row, int col, int val)
{
    int size = board.getSize();
    int boxSize = sqrt(size);

    assert(row < size);
    assert(col < size);
    

    // check every ele in row
    for (size_t i = 0; i < size; i++)
    {
        if (board(i, col) == val) return false;
    }
    
    // check every ele in col
    for (size_t i = 0; i < size; i++)
    {
        if (board(row, i) == val) return false;
    }

    // check every ele in box
    int boxRow = row - (row % boxSize);
    int boxCol = col - (col % boxSize);

    for (size_t i = boxRow; i < boxSize + boxRow; i++)
    {
        for (size_t j = boxCol; j < boxCol + boxSize; j++) {
            /*cout << board(i, j) << ' ';*/
            if (board(i, j) == val) 
            {
                return false;
            }
        }
        //cout << endl;
    }

    return true;
}

// solve the puzzle by backtracking
bool solve(Board* board, int row, int col)
{
    int size = board->getSize();

    assert(size == pow(sqrt(size), 2));       // check again just use N that can square
    // condition to end this function is check to the position exceed the range
    if (row == size)
    {
        return true;
    }
    
    // if the position already has value --> try next position
    if ((*board)(row, col) != 0)
    {
        // try the next col if the col still not reach the bound
        if (col < size - 1)
        {
            if (solve(board, row, col + 1)) return true;
        }
        else {
            if (solve(board, row + 1, 0)) return true;
        }

        return false;
    }
    
    // if the position still not have value --> try each value at this position until complete
    for (size_t i = 1; i <= size; i++)
    {
        
        // check if it possible --> set value --> go to the next position
        if (possible(*board, row, col, i))
        {
            // set value for this position
            (*board)(row, col) = i;
            if (col == size - 1) {
                if (solve(board, row + 1, 0)) return true;
            }
            else {
                if (solve(board, row, col + 1)) return true;
            }
        }
    }

    // if fail --> we set the value to default
    (*board)(row, col) = 0;

    return false;
}

Board* generateBoard(int size)
{
    Board* board = new Board(size);

    fillDiagonal(board);

    solve(board, 0, 0);

    removeRandom(board);

    /*vector<vector<int>> arr = {
        {0,6,0,  0,0,7,   0,0,1},
        {0,0,1,  0,8,0,   7,6,2},
        {2,0,0,  0,1,0,   4,0,0},

        {0,9,0,  0,0,8,   0,0,5},
        {0,0,0,  0,0,9,   0,0,0},
        {0,3,0,  5,6,0,   2,0,0},

        {9,0,0,  8,0,0,   5,0,0},
        {0,0,8,  7,4,0,   0,0,0},
        {0,7,0,  0,9,0,   8,0,0}
    };*/

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++) {
            if ((*board)(i, j) != 0)
            {
                board->assignImmutable(i, j, true);
            }
        }
    }



    return board;
}

void fillDiagonal(Board* board)
{
    int gap = sqrt(board->getSize());

    // loop through each box in diagoonal
    for (size_t i = 0; i < board->getSize(); i = i + gap)
    {
        // fill the box
        for (size_t row = 0; row < gap; row++)
        {
            for (size_t col = 0; col < gap; col++) {
                int randNum = 0;
                if ((*board)(i + row, i + col) != 0)
                {
                    continue;
                }
                do
                {
                    randNum = randomNum(board->getSize()) ;
                } while (!possibleInBox(board, i, i, randNum));
                (*board)(i + row, i + col) = randNum;
                //cout << (*board)(i + row, i + col) << endl;
            }
        }
    }
    //board->printPuzzle();
}

void removeRandom(Board* board)
{
    int size = board->getSize();
    // define the number want to remove around 2 / 3
    int removeMax = size * size * 3 / 4;
    int removeMin = size * size * 2 / 3;
    int removeNum = 0;
    do
    {
        removeNum = randomNum(size * size);
    } while (removeNum > removeMax || removeNum < removeMin);

    //cout << "Clear " << removeNum << endl;
    // try to delete
    while (removeNum > 0)
    {
        // random row, col
        // number is sum --> find row, col
        int sum = randomNum(size * size) - 1;
        int r = sum / size;
        int c = sum % size;

        if ((*board)(r, c) != 0)
        {
            (*board)(r, c) = 0;
            removeNum--;
        }
    }
}

int randomNum(int N)
{
    /*srand(time(0));
    return (int)floor((float)(rand() / (double)RAND_MAX * N + 1));*/

    // Tạo một engine ngẫu nhiên
    std::random_device rd;
    std::mt19937 gen(rd()); // Sử dụng mersenne_twister_engine

    // Xác định phạm vi của số ngẫu nhiên
    std::uniform_int_distribution<> distrib(1, N);

    return distrib(gen);

}

bool possibleInBox(Board* board, int rowStart, int colStart, int val)
{
    int numLoop = sqrt(board->getSize());


    for (size_t i = rowStart; i < rowStart + numLoop; i++)
    {
        for (size_t j = colStart; j < colStart + numLoop; j++)
        {
            //if (row == i && col == j) continue;
            int compare = (*board)(i, j);
            if (compare == val)
            {
                return false;
            }

        }
    }
    return true;
}

