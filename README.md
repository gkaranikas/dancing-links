# Dancing Links and Sudoku

This project includes a C++ implementation of Donald Knuth's [Dancing Links](https://en.wikipedia.org/wiki/Dancing_Links) algorithm for the [exact cover problem](https://en.wikipedia.org/wiki/Exact_cover_problem), as well as a sudoku solver based upon it.

## Background
The **exact cover problem** can be stated as follows.  Given a rectangular boolean matrix, delete rows to get a submatrix with exactly one 1 in each column.  It is known to be NP-complete, and the fastest known solutions use backtracking/trial-and-error methods.  The **Dancing Links** algorithm is no exception; however, by representing the columns and rows of the matrix by circular doubly linked lists, great savings are made in the common scenario of a sparse matrix.  See the above wikipedia link for more information.

Among the problems which can be reduced to an exact cover problem is **Sudoku**.  Taking a blank 9 by 9 Sudoku grid, a boolean matrix is constructed as follows.  The matrix M will have 729 rows, each corresponding to a possible entry (i.e. 81 cells, 9 values).  The constraints are encoded in the columns.  They are of four kinds, each adding 81 columns to M:
1. **cell constraints** require each cell to be filled with a single value.  The column of M has a 1 in each row corresponding to some specific cell (9 in total per cell).
2. **row constraints** prevent rows of the sudoku from having duplicates.  The column (of M) has a 1 in each row (of M) corresponding to some specific sudoku row and value.
3. **column constraints** prevent columns of the sudoku from having duplicates.  The column has a 1 in each row corresponding to some specific sudoku column and value.
4. **square/box constraints** prevent squares of the sudoku from having duplicates.  The column has a 1 in each row corresponding to some specific sudoku square and value.

Thus, a solution to the exact cover problem for M corresponds to a legally filled sudoku grid.  Given a _partially filled_ Sudoku grid instead of a blank one, we construct M as above but delete rows which correspond to wrong entries (e.g. if the grid has a 1 in cell (2, 3), then we delete the rows of M corresponding to the values 2, 3, . . . & 9 in the cell (2, 3)).

## Usage
To build the object files, run 
```sh
> make objects
```
The file [demo.cpp](../blob/master/demo.cpp) illustrates how to use the library.
### Documentation
Doxygen markup is embedded in the header files.  To build the documentation open a terminal in the project home directory and type
```sh
> doxygen
```
You can then browse the full html documentation from the newly created file `./html/index.html`.
### Headers
If you only need to use the Sudoku class, just add `#include "sudoku_solver.h"`.

If you need the exact cover problem solver for boolean matrices, add the following:
```cpp
#include <iostream>    // only for the DEBUG_display() method
#include "linked_matrix.h"
#include <vector>
#include <stack>
#include "dancing_links.h"
```
Of course, you will also need to link with the object files.

## License
See `LICENSE` for details.

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
