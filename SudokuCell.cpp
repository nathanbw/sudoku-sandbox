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
        mRow = ((index - 1) / 9) + 1;
        mCol = ((index - 1) % 9) + 1;
        mQuad = ((((index - 1) / 27) + 1) - 1);
        mQuad = mQuad + (((index - 1) / 3) % 3);
        mQuad = mQuad + ((((((index - 1) / 27) + 1) - 1) * 2) + 1);
        nextCell = new SudokuCell(index + 1, this);
    }
    else
    {
        mRow = 9;
        mCol = 9;
        mQuad = 9;
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
    cout << "======================" << endl;
    printBoard();
labelmebro:
    if ((curNum = nextNumber()) && (!violatesConstraint(curNum)))
    {
        // We found a number that works so far
        if (nextCell)
        {
            if (nextCell->solveMe())
            {
                return true;
            }
            else
            {
                goto labelmebro;
            }
        }
        else
        {
            return true; // We found a board!
        }
    }
    else
    {
        clearMe();
        return false; // false == didn't find a complete board
    }
}

void SudokuCell::printBoard()
{
    // cout << "(Rand: " << ((rand() % 9) + 1) << ")";

    // for (int i = 0; i < 15; i++)
    //     cout << nextNumber() << endl;
    // cout << "CLEARME" << endl;
    // clearMe();
    // for (int i = 0; i < 15; i++)
    //     cout << nextNumber() << endl;

    // if (((index - 1) % 9) == 8)
    // {
    //     cout << " " << mQuad << endl;
    // }
    // else
    // {
    //     cout << " " << mQuad;
    // }
    // if (nextCell)
    // {
    //     nextCell->printBoard();
    // }

    if (((index - 1) % 9) == 8)
    {
        cout << " " << curNum << endl;
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

int SudokuCell::nextNumber()
{
    // If there are no numbers left, return 0
    // If there are numbers left, return a random one
    bool anyNumsLeft = false;
    for (int i = 1; i < 10; i++)
    {
        if (!numsTried[i])
        {
            anyNumsLeft = true;
        }
    }
    if (anyNumsLeft)
    {
        bool keepLooking = true;
        while (curNum = ((rand() % 9) + 1))
        {
            if (!numsTried[curNum])
            {
                numsTried[curNum] = true;
                return curNum;
            }
        }
    }
    else
    {
        return 0;
    }
}

bool SudokuCell::violatesConstraint(int num)
{
    if (!prevCell)
    {
        return false;
    }
    if (prevCell->checkConstraint(num, mRow, mCol, mQuad))
    {
        return true;
    }
    return false;
}

bool SudokuCell::checkConstraint(int num, int row, int col, int quad)
{
    if (((mRow == row) ||
        (mCol == col) ||
        (mQuad == quad)) &&
        (curNum == num))
    {
        return true;
    }
    else
    {
        if (prevCell)
        {
            return prevCell->checkConstraint(num, row, col, quad);
        }
        else
            return false;
    }
}
