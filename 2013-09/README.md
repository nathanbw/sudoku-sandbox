SudokuCell: Represents a single cell in a sudoku grid

The sudoku grid is represented as a doubly-linked list of SudokuCell instances. Each instance "knows"
 - Their current value (the number they are currently holding as a candidate for inclusion in the completed grid)
 - Their row
 - Their column
 - Their quadrant
 - Their "previous" neighbor (previous from a LTR, TTB perspective)
 - Their "next" neighbor (next from a LTR, TTB perspective

The algorithm used to find a solved sudoku grid is as follows:
(Written from the perspective of a sudoku cell; this algorithm is invoked on the first cell (leftmost, topmost) in the board)
```
function solveMe
    while I have a number I haven't tried yet, pick a random number, 1-9
        if that number doesn't violate any constraints against any previous cell
            if I have a nextCell (I'm not the last (rightmost, bottommost) cell)
                if nextCell->solveMe returns true, than this number worked! return true
            else
                return true
     end while
     reset my state
     return false (we tried all numbers, pass control to previous cell to try next number)
```
