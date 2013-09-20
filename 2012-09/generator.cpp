#include <iostream>
using std::cout;
using std::endl;
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using std::vector;
#include "shapeTable.h"

int ppGrid[9][9] =
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

int ppKernel[9][9] =
{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

unsigned long long numBoardsFound = 0;
void FillBoard(int *pPermutation, int num)
{
    for (int col = 0; col < 9; col++)
    {
        ppGrid[pPermutation[col]][col] = num;
    }
}

void PrintBoard()
{
    cout << "===========================" << endl;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << " " << ppGrid[row][col];
        }
        cout << endl;
    }
    cout << "===========================" << endl;
}

vector<int*>*
NarrowList(vector<int*>* pList, int *pShape)
{
    vector<int*>* newList = new vector<int*>;
    for (vector<int*>::iterator it = pList->begin(); it != pList->end(); it++)
    {
        if (((*it)[0] != pShape[0]) &&
            ((*it)[1] != pShape[1]) &&
            ((*it)[2] != pShape[2]) &&
            ((*it)[3] != pShape[3]) &&
            ((*it)[4] != pShape[4]) &&
            ((*it)[5] != pShape[5]) &&
            ((*it)[6] != pShape[6]) &&
            ((*it)[7] != pShape[7]) &&
            ((*it)[8] != pShape[8]))
        {
            newList->push_back(*it);
        }
    }
    return newList;
}

void PrintShape(int *pCurShape)
{
    cout << pCurShape[0]
         << pCurShape[1]
         << pCurShape[2]
         << pCurShape[3]
         << pCurShape[4]
         << pCurShape[5]
         << pCurShape[6]
         << pCurShape[7]
         << pCurShape[8] << endl;
}

bool CountSudoku(vector<int*>* pList, int curNum)
{
    if (((curNum == 8) && (!(pList->size() >= 1))))
    {
        delete pList;
        return false; // this is a dead end. We are done trying
    }
    else if (curNum == 8)
    {
        // cout << "Found a valid permutation. curNum: "
        //      << curNum << " Base case: " << endl;
        int *pCurShape = pList->at(0);
        // PrintShape(pCurShape);
        for (int fillGrid = 0; fillGrid < 9; fillGrid++)
        {
            ppKernel[curNum][fillGrid] = pCurShape[fillGrid];
        }
        numBoardsFound++;
        if (numBoardsFound % 3000000 == 0)
        {
        // if (ppKernel[0][8] != 8)
        // {
            for (int i = 0; i < 9; i++)
            {
                FillBoard(ppKernel[i], i + 1);
            }
            cout << "Found " << numBoardsFound << " boards!" << endl;
            PrintBoard();
            // exit(0);
        }
        delete pList;
        return true;
    }
    else if (!(pList->size() >= 1))
    {
        delete pList;
        return false;
    }
    else
    {
        for (int i = 0; i < pList->size(); i++)
        {
            int *pCurShape = pList->at(i);
            for (int fillGrid = 0; fillGrid < 9; fillGrid++)
            {
                ppKernel[curNum][fillGrid] = pCurShape[fillGrid];
            }
            CountSudoku(NarrowList(pList, pCurShape), curNum + 1);
        }
        delete pList;
        return false;
    }
}

int main (int argc, char **argv)
{
    vector<int*> *pMasterList =
        new vector<int*>(shapeTable, shapeTable + (sizeof(shapeTable) / (sizeof(int) * 9)));

    // // Random search:
    // srand(time(0));
    // int *pCurShape = 0;
    // vector<int*> *pShapeList[9] = {0};
    // pShapeList[0] = pMasterList;
    // int currentPick = 0;
    // for (int curNum = 0; curNum < 9; curNum++)
    // {
    //     if ((pShapeList[curNum]) &&
    //         (pShapeList[curNum]->size() > 0))
    //     {
    //         cout << "List size: " << pShapeList[curNum]->size() << endl;
    //         currentPick = rand() % pShapeList[curNum]->size();
    //         cout << "Current Pick: " << currentPick
    //              << ". Shape: ";
    //         pCurShape = pShapeList[curNum]->at(currentPick);
    //         // pCurShape = pShapeList[curNum]->front();
    //         PrintShape(pCurShape);
    //         FillBoard(pCurShape, curNum + 1);
    //         pShapeList[curNum + 1] = NarrowList(pShapeList[curNum], pCurShape);
    //         cout << "new list size: " << pShapeList[curNum + 1]->size() << endl;
    //     }
    // }

    // Counting:
    CountSudoku(pMasterList, 0);
    PrintBoard();

    // TODO/thoughts on pre-computing board
    // 1. Find all boards that start with the first
    // doesNotHaveInPos(int num = 1..9, int pos = 1..9)

    return 0;
}
// First working run:
// shapeList.size(): 46656
// new list size: 17972
// new list size: 6560
// new list size: 2020
// new list size: 608
// new list size: 244
// new list size: 216
// new list size: 8
// new list size: 1
// ===========================
//  1 7 4 2 9 3 5 8 6
//  2 8 5 1 7 6 3 9 4
//  3 9 6 4 8 5 1 7 2
//  4 1 7 3 2 9 6 5 8
//  5 2 8 6 1 7 4 3 9
//  6 3 9 5 4 8 2 1 7
//  7 4 1 9 3 2 8 6 5
//  8 5 2 7 6 1 9 4 3
//  9 6 3 8 5 4 7 2 1
// ===========================
// This board's reduced description: (numbers sorted smallest to biggest)
// 036147258
// 147036582
// 258360147
// 360258471
// 471582036
// 582471360
// 603714825
// 714825603
// 825603714
// This reduced description describes 9! = 362,880 solved sudoku boards
// How many other reduced descriptions can we find?
// Found a valid permutation. curNum: 8 Base case:
// ===========================
//  0 3 6 1 4 7 2 5 8
//  1 4 7 0 3 6 5 8 2
//  2 5 8 3 6 0 1 4 7
//  3 6 0 2 5 8 4 7 1
//  4 7 1 5 8 2 0 3 6
//  5 8 2 4 7 1 3 6 0
//  6 0 3 7 1 4 8 2 5
//  7 1 4 8 2 5 6 0 3
//  8 2 5 6 0 3 7 1 4
// ===========================
// Found a valid permutation. curNum: 7. i: 0: Found a valid permutation. curNum: 8 Base case:
// ===========================
//  0 3 6 1 4 7 2 5 8
//  1 4 7 0 3 6 5 8 2
//  2 5 8 3 6 0 1 4 7
//  3 6 0 2 5 8 4 7 1
//  4 7 1 5 8 2 0 3 6
//  5 8 2 4 7 1 3 6 0
//  6 0 3 7 1 4 8 2 5
//  7 1 5 8 2 3 6 0 4
//  8 2 4 6 0 5 7 1 3

// +===================================+
// | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
// +===================================+
// | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
// +===================================+
// | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
// +-----------------------------------+
// | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
// +===================================+

// grid 0 starts with col = 0
// grid 1 starts with col = 3
// grid 2 starts with col = 6
// grid 3 starts with col = 0
// grid 4 starts with col = 3
// grid 5 starts with col = 6
// grid 6 starts with col = 0
// grid 7 starts with col = 3
// grid 8 starts with col = 6

// grid 0 starts with row = 0
// grid 1 starts with row = 0
// grid 2 starts with row = 0
// grid 3 starts with row = 3
// grid 4 starts with row = 3
// grid 5 starts with row = 3
// grid 6 starts with row = 6
// grid 7 starts with row = 6
// grid 8 starts with row = 6

// grid's row number is:
//   startNum = (gridNum / 3) * 3          # That's integer division!
//   actualNum = startNum + (cellNum / 3)  # That's integer division!

// grid's col number is:
//   startNum = (gridNum % 3) * 3
//   actualNum = startNum + (cellNum % 3)

// For a test: 2, 5: grid 2, cell 5 should have row, col = 1, 8
// Row:
//   startNum = (2 / 3) * 3 = 0
//   actualNum = 0 + (5 / 3) = 1 # Yay!
// Col:
//   startNum = (2 % 3) * 3 = 6
//   actualNum = 6 + (5 % 3) = 8 # Yay!

// So, to make this one-based:
// grid's row number is:
//   startNum = (((gridNum - 1) / 3) * 3) + 1          # That's integer division!
//   actualNum = startNum + ((cellNum - 1) / 3)        # That's integer division!

// grid's col number is:
//   startNum = (((gridNum - 1) % 3) * 3) + 1
//   actualNum = startNum + ((cellNum - 1) % 3)

// To test: 3, 6: grid 3, cell 6 should have row, col = 2, 9
// Row:
//   startNum = ((2 / 3) * 3) + 1 = 1
//   actualNum = 1 + (5 / 3) = 2
// Col:
//   startNum = 7
//   actualNum = 7 + 2 = 9

