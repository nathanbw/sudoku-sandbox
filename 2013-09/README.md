SudokuCell: Represents a single cell in a sudoku grid
=====================================================

The sudoku grid is represented as a doubly-linked list of SudokuCell instances. Each instance "knows":
 - Its current value (the number it is currently holding as a candidate for inclusion in the completed grid)
 - Its row
 - Its column
 - Its quadrant
 - Its "previous" neighbor (previous from a LTR, TTB perspective)
 - Its "next" neighbor (next from a LTR, TTB perspective)

The algorithm used to find a solved sudoku grid is as follows:
(Written from the perspective of a sudoku cell)
```
function solveMe
    while I have a number I haven't tried yet, pick a random number, 1-9
        if that number doesn't violate any constraints against any previous cell
            if I have a nextCell (I'm not the last (rightmost, bottommost) cell)
                if nextCell->solveMe returns true, then this number worked! return true
            else
                return true (I am the last cell, and my number didn't violate any previous cell's constraints)
     end while
     (Now I've tried every number, 1-9, and none worked)
     reset my state
     return false (pass control to previous cell so it can try its next number)
```

To generate a complete board, this algorithm is invoked on the first cell (leftmost, topmost) in the board.

Key Features
------------
You'll note that the constructor is recursive; if you instantiate a single SudokuCell instance, an entire board is created. You interact directly with the first cell, but that cell is essentially your interface to the entire board.

Example Run
-----------
```
$ g++ -o sudoku-gen main.cpp SudokuCell.cpp && ./sudoku-gen
We found a board
 3 9 4 1 6 2 5 7 8
 2 1 5 3 7 8 6 4 9
 6 7 8 9 5 4 2 1 3
 1 5 6 2 9 3 7 8 4
 4 3 9 5 8 7 1 2 6
 7 8 2 4 1 6 9 3 5
 9 4 3 6 2 1 8 5 7
 5 2 7 8 3 9 4 6 1
 8 6 1 7 4 5 3 9 2
```

Pitfalls/TODO/Hopes and Dreams
------------------------------
Currently, we pass the "zerothCell" pointer into to each sudokuCell instance. I think it might be better to add a SudokuBoard class that instantiates the SudokuCell objects, preventing direct manipulation from callers.

The code could be enhanced to check constraint violations in both directions (next cells as well as previous cells.) Also, we could add a flag to each cell denoting whether their current value is a given (immutable.) With these two features, we could solve partially-completed sudoku grids as well as generating solutions from empty grids.

The arithmetic for calculating which quadrant a cell is in could definitely be simplified. I banged this out in one go by trial and error; there certainly is a smaller arithmetic expression that accomplishes the same task.