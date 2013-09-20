#include <iostream>
using std::cout;
using std::endl;
#include <stdlib.h>


int ppGrid[9][9] =
{
    {1,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0},
    {0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,1}
};

int pPermutation[9] = {0,3,6,1,4,7,2,5,8};

bool IsBoardCorrect()
{
    int numOnesRow = 0;
    int numOnesCol = 0;
    int numOnesGrid = 0;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (ppGrid[row][col] == 1)
            {
                numOnesRow++;
            }
            if (ppGrid[col][row] == 1)
            {
                numOnesCol++;
            }
            int gridRow = ((row/3)*3)+(col/3);
            int gridCol = ((row%3)*3)+(col%3);
            if (ppGrid[gridRow][gridCol] == 1)
            {
                numOnesGrid++;
            }
        }
        if ((numOnesRow != 1) ||
            (numOnesCol != 1) ||
            (numOnesGrid != 1))
        {
            return false;
        }
        else // we have a shot
        {
            numOnesRow = 0;
            numOnesCol = 0;
            numOnesGrid = 0;
        }
    }
    return true;
}

void FillBoard()
{
    for (int col = 0; col < 9; col++)
    {
        if (pPermutation[col] == 0)
        {
            ppGrid[8][col] = 0;
        }
        else
        {
            ppGrid[pPermutation[col]-1][col] = 0;
        }
        ppGrid[pPermutation[col]][col] = 1;
    }
}

void IncrPermutation()
{
    int index = 8;
    while (index >= 0)
    {
        if (pPermutation[index] == 8)
        {
            pPermutation[index] = 0;
            index = index - 1;
        }
        else
        {
            pPermutation[index] = pPermutation[index] + 1;
            index = -1;
        }
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
int main (int argc, char **argv)
{
    unsigned long numBoardsFound = 0;
    for (unsigned long perm = 0; perm < 387420489; perm++)
    {
        // if ((pPermutation[0] == 8) &&
        //     (pPermutation[1] == 8) &&
        //     (pPermutation[2] == 8) &&
        //     (pPermutation[3] == 8) &&
        //     (pPermutation[4] == 8) &&
        //     (pPermutation[5] == 8) &&
        //     (pPermutation[6] == 8) &&
        //     (pPermutation[7] == 8) &&
        //     (pPermutation[8] == 8))
        // {
        //     cout << "reached wraparound at iteration: " << perm << endl;
        //     cout << "Permutation: " <<
        //         pPermutation[0] <<
        //         pPermutation[1] <<
        //         pPermutation[2] <<
        //         pPermutation[3] <<
        //         pPermutation[4] <<
        //         pPermutation[5] <<
        //         pPermutation[6] <<
        //         pPermutation[7] <<
        //         pPermutation[8] << endl;

        //     PrintBoard();
        //     break;
        // }
        if (IsBoardCorrect())
        {
            numBoardsFound++;
            cout <<
                pPermutation[0] <<
                pPermutation[1] <<
                pPermutation[2] <<
                pPermutation[3] <<
                pPermutation[4] <<
                pPermutation[5] <<
                pPermutation[6] <<
                pPermutation[7] <<
                pPermutation[8] << endl;
            // PrintBoard();
        }
        IncrPermutation();
        FillBoard();
    }
    // Early run shows:
    // Found 46656 total.
    cout << "Found " << numBoardsFound << " total." << endl;
    cout << "One past last permutation: " <<
        pPermutation[0] <<
        pPermutation[1] <<
        pPermutation[2] <<
        pPermutation[3] <<
        pPermutation[4] <<
        pPermutation[5] <<
        pPermutation[6] <<
        pPermutation[7] <<
        pPermutation[8] << endl;
    PrintBoard();
    return 0;
}
