#include <stdlib.h> // For rand()
#include <time.h>

#include "SudokuCell.h"

int main()
{
    srand(time(0));
    SudokuCell myCell(1, (SudokuCell*)0, (SudokuCell*)0);
    myCell.solveMe();
    myCell.printBoard();
}
