#include <stdlib.h>
#include <climits>
#include <time.h>

#include "SudokuCell.h"

int main(int argc, const char* argv[])
{
    srand(time(0));
    unsigned long numBoards = 1;
    if (argc == 2)
    {
        numBoards = strtol(argv[1], 0, 10);
        if ((numBoards == 0) ||
            (numBoards == ULONG_MAX))
        {
            numBoards = 1;
        }
    }
    SudokuCell *myCell = 0;
    for (unsigned long board = 0; board < numBoards; board++)
    {
        myCell = new SudokuCell(1, (SudokuCell*)0, (SudokuCell*)0);
        if (myCell)
        {
            myCell->solveMe();
            myCell->printBoard();
            delete myCell;
            myCell = 0;
        }
        else
        {
            return -1;
        }
    }
}
