class SudokuCell
{
 public:
  SudokuCell(int index, SudokuCell* prevCell);
  bool solveMe();
  void clearMe();
  int getCurNum();
  int getIndex();
  void printBoard();
 private:
  int index, curNum;
  bool numsTried[10];
  SudokuCell *nextCell, *prevCell;

  bool nextNumber();
};
