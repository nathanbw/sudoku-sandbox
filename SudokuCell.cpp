#include <iostream>
using std::cout;
using std::endl;
#include <stdlib.h> // For rand()

#include "SudokuCell.h"

SudokuCell::SudokuCell(int index, SudokuCell* prevCell):
    index(index),
    prevCell(prevCell)
{
    if (index < 81)
    {
        nextCell = new SudokuCell(index + 1, this);
    }
    else
    {
        nextCell = 0;
    }
    clearMe();
}

// TODO Destructor

void SudokuCell::clearMe()
{
    curNum = 0;
    for (int i = 0; i < 10; i++)
    {
        numsTried[i] = false;
    }
}

bool SudokuCell::solveMe()
{
    if (curNum = nextNumber())
    {
    }
    else
    {
        clearMe();
        return false; // false == didn't find a complete board
    }
}

void SudokuCell::printBoard()
{
    if (((index - 1) % 9) == 8)
    {
        cout << " " << curNum << endl;
        cout << "(Rand: " << ((rand() % 9) + 1) << ")";
    }
    else
    {
        cout << " " << curNum;
    }
    if (nextCell)
    {
        nextCell->printBoard();
    }
}

bool SudokuCell::nextNumber()
{
    // If there are no numbers left, return 0
    // If there are numbers left, return a random one
    for (int i = 1; i < 10; i++)
    {
        if (!numsTried[i])
        {
            break;
        }
    }
    for (curNum = (rand() % 10); numsTried[curNum];);
    numsTried[curNum] = true;
    return curNum;
}
