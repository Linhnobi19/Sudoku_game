#include "Solve.h"
#include <random>
#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <cstdlib>

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
        /*if (col < size - 1)
        {
            if (solve(board, row, col + 1)) return true;
        }
        else {
            if (solve(board, row + 1, 0)) return true;
        }*/
        if (col < size - 1)
        {
            return (solve(board, row, col + 1));
        }
        else {
            return (solve(board, row + 1, 0));
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
            /*if (col < size - 1)
            {
                return (solve(board, row, col + 1));
            }
            else {
                return (solve(board, row + 1, 0));
            }*/
        }
    }

    // if fail --> we set the value to default
    (*board)(row, col) = 0;

    return false;
}

Board* generateBoard(int size)
{
    Board* board = new Board(size);

    //// Tạo một engine ngẫu nhiên
    //std::random_device rd;
    //std::mt19937 gen(rd()); // Sử dụng mersenne_twister_engine

    //// Xác định phạm vi của số ngẫu nhiên
    //std::uniform_int_distribution<> distrib(0, size);


    //for (size_t i = 0; i < size; i++)
    //{
    //    for (size_t j = 0; j < size; j++) {
    //        board(i, j) = distrib(gen);
    //    }
    //}

    vector<vector<int>> arr = {
        {0,6,0,  0,0,7,   0,0,1},
        {0,0,1,  0,8,0,   7,6,2},
        {2,0,0,  0,1,0,   4,0,0},

        {0,9,0,  0,0,8,   0,0,5},
        {0,0,0,  0,0,9,   0,0,0},
        {0,3,0,  5,6,0,   2,0,0},

        {9,0,0,  8,0,0,   5,0,0},
        {0,0,8,  7,4,0,   0,0,0},
        {0,7,0,  0,9,0,   8,0,0}
    };

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++) {
            (*board)(i, j) = arr[i][j];
            if (arr[i][j] != 0)
            {
                board->assignImmutable(i, j, true);
            }
        }
    }

    return board;
}
