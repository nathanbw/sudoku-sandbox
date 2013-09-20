class SudokuCell
{
 public:
  SudokuCell(int index, SudokuCell* prevCell, SudokuCell* zerothCell);
  ~SudokuCell();
  bool solveMe();
  void clearMe();
  int getCurNum();
  int getIndex();
  void printBoard();
 private:
  int mIndex, mCurNum;
  bool mNumsTried[10];
  SudokuCell *mpNextCell, *mpPrevCell;
  int mRow, mCol, mQuad;

  // Hacky :-(
  SudokuCell* mpZerothCell;

  int nextNumber();
  bool violatesConstraint();
 protected:
  bool checkConstraint(int num, int row, int col, int quad);

};
