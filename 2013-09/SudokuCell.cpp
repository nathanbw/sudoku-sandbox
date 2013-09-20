#include <iostream>
using std::cout;
using std::endl;
#include <stdlib.h> // For rand()

#include "SudokuCell.h"

SudokuCell::SudokuCell(int index, SudokuCell* prevCell, SudokuCell* zerothCell):
    mIndex(index),
    mpPrevCell(prevCell),
    mpZerothCell(zerothCell)
{
    if (mpZerothCell == 0)
        this->mpZerothCell = this;
    if (mIndex < 81)
    {
        mRow = ((mIndex - 1) / 9) + 1;
        mCol = ((mIndex - 1) % 9) + 1;
        mQuad = ((((mIndex - 1) / 27) + 1) - 1);
        mQuad = mQuad + (((mIndex - 1) / 3) % 3);
        mQuad = mQuad + ((((((mIndex - 1) / 27) + 1) - 1) * 2) + 1);
        mpNextCell = new SudokuCell(mIndex + 1, this, mpZerothCell);
    }
    else
    {
        mRow = 9;
        mCol = 9;
        mQuad = 9;
        mpNextCell = 0;
    }
    clearMe();
}

SudokuCell::~SudokuCell()
{
    if (mpNextCell)
        delete mpNextCell;
}

void SudokuCell::clearMe()
{
    mCurNum = 0;
    for (int i = 0; i < 10; i++)
    {
        mNumsTried[i] = false;
    }
}

bool SudokuCell::solveMe()
{
    while (mCurNum = nextNumber())
    {
        if (!violatesConstraint())
        {
            // We found a number that works so far
            if (mpNextCell)
            {
                if (mpNextCell->solveMe())
                {
                    return true;
                }
            }
            else
            {
                cout << "We found a board" << endl;
                return true; // We found a board!
            }
        }
    }
    clearMe();
    return false; // false == didn't find a complete board
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

    // if (((mIndex - 1) % 9) == 8)
    // {
    //     cout << " " << mQuad << endl;
    // }
    // else
    // {
    //     cout << " " << mQuad;
    // }
    // if (mpNextCell)
    // {
    //     mpNextCell->printBoard();
    // }

    if (((mIndex - 1) % 9) == 8)
    {
        cout << " " << mCurNum << endl;
    }
    else
    {
        cout << " " << mCurNum;
    }
    if (mpNextCell)
    {
        mpNextCell->printBoard();
    }
}

int SudokuCell::nextNumber()
{
    // If there are no numbers left, return 0
    // If there are numbers left, return a random one
    bool anyNumsLeft = false;
    for (int i = 1; i < 10; i++)
    {
        if (!mNumsTried[i])
        {
            anyNumsLeft = true;
        }
    }
    if (anyNumsLeft)
    {
        while (mCurNum = ((rand() % 9) + 1))
        {
            if (!mNumsTried[mCurNum])
            {
                mNumsTried[mCurNum] = true;
                return mCurNum;
            }
        }
    }
    else
    {
        return 0;
    }
}

bool SudokuCell::violatesConstraint()
{
    if (!mpPrevCell)
    {
        return false;
    }
    if (mpPrevCell->checkConstraint(mCurNum, mRow, mCol, mQuad))
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
        (mCurNum == num))
    {
        return true;
    }
    else
    {
        if (mpPrevCell)
        {
            return mpPrevCell->checkConstraint(num, row, col, quad);
        }
        else
            return false;
    }
}
