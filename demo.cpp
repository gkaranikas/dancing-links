#include "dancing_links.h"
#include "sudoku_solver.h"
using Sudoku = sudoku_GJK::Sudoku<3>;

#include <ctime>

int main(void) {
    // ************************************
    // ******* DANCING LINKS DEMO *********
    std::cout << "DANCING LINKS DEMO:\n\n";
    // add demo code
    
    // ************************************
    // *********** SUDOKU DEMO ************
    std::cout << "SUDOKU DEMO:\n\n";
    // We represent the sudoku grid data as a C-style string of length 9x9.  Zeroes represent blank spaces.
    // The data represents the following sudoku:
    /*
        =========================
        | 5 3   |   7   |       |
        | 6     | 1 9 5 |       |
        |   9 8 |       |   6   |
        =========================
        | 8     |   6   |     3 |
        | 4     | 8   3 |     1 |
        | 7     |   2   |     6 |
        =========================
        |   6   |       | 2 8   |
        |       | 4 1 9 |     5 |
        |       |   8   |   7 9 |
        =========================
    */
    char data[82] = 
          "530070000600195000098000060800060003400803001700020006060000280000419005000080079"
    // Create an instance of a sudoku puzzle
    Sudoku Sdku(data);
    std::cout << "The puzzle to be solved is:\n";
    // This method displays the sudoku nicely
    Sdku.display_ASCII();
    std::cout << "Solving . . .\n";
    std::clock_t start = std::clock();
    // This method solves the sudoku by converting it
    // to a matrix exact cover problem and using the
    // dancing links solution
    Sdku.solve();
    std::clock_t end = std::clock();
    std::cout << "Solution:\n";
    // Display the solved puzzle
    Sdku.display_ASCII();
    std::cout << "Elapsed time = " << 1000.0 * (end-start)/CLOCKS_PER_SEC << " ms" << " (CPU time)\n";
    
    return 0;  
}
