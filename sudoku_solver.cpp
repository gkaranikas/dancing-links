#include "sudoku_solver.h"
//#include <math>
#include <cstdlib>

namespace sudoku_GJK
{

typedef int num_t;       // range understood to be restricted to 1,2,...9 (replace 9 with 'size' in general)
const num_t no_value = 0;

struct Triple {
    num_t row;
    num_t column;
    num_t value;
};

// Helper functions
void get_exact_cover_matrix(num_t **grid, int sqrt_of_size, bool** matrix);
void solution_to_grid(std::vector<int> solution,num_t **grid,int size);
int triple_to_index(Triple triple, int size);
Triple index_to_triple(int index, int size);
bool is_in_square(Triple triple, num_t square, int sqrt_of_size);


// overload with individual data input
void Sudoku_Solver_9x9(num_t **grid)
{
    Sudoku_Solver(grid,3);
}

void Sudoku_Solver(num_t **grid, int sqrt_of_size)
{   
    int size = sqrt_of_size*sqrt_of_size;
    int m = size*size*size;     // # rows of matrix for the exact cover problem formulation
    int n = 4*size*size;        // # columns         ''              ''                  ''
    bool **matrix = new bool*[m];
    for(int i=0; i < m; i++) {
        matrix[i] = new bool[n];
    }
    get_exact_cover_matrix(grid, sqrt_of_size, matrix);

    std::vector<int> solution = dancing_links_GJK::Exact_Cover_Solver(matrix,m,n);
    // exception handling?
    
    solution_to_grid(solution,grid,size);
    
    // free memory
    for(int i=0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


/*
 * 
 *            ________row conditions_________column_______square________point conditions____
 *            |                          |            |            |                       |
 *          j | (r1,1) (r1,2) ... (r9,9) | (c1,1) ... | (s1,1) ... | (1,1) (1,2) ... (9,9) |
 *     i
 *  (1,1,1)       1      0    ...   0        1    ...      1   ...     1     0   ...   0
 *  (1,1,2)       0      1    ...   0        0    ...      0   ...     1     0   ...   0
 *  . . . .
 *  (9,9,8)
 *  (9,9,9)
 * 
 */
void get_exact_cover_matrix(num_t **grid, int sqrt_of_size, bool** matrix) {
    int size = sqrt_of_size*sqrt_of_size;
    int m = size*size*size;
    int n = 4*size*size;
    
    Triple triple;
    std::div_t dv;
    int condition_type;
    for(int i = 0; i < m; i++) {
        triple = index_to_triple(i, size);
        if(grid[triple.row-1][triple.column-1] != no_value && grid[triple.row-1][triple.column-1] != triple.value)
        {
            // incorporate specific sudoku problem data
            for(int j = 0; j < n; j++) matrix[i][j] = 0;
        } else {        // NOTE: if grid[triple.row][triple.column] == triple.value,
                        // then the solution finding process can be sped up by removing
                        // the appropriate rows and columns from the matrix
                        // this is not incorporated yet
            for(int j = 0; j < n; j++) {
                dv = std::div(j,size*size);
                condition_type = dv.quot;     // between 0 and 3 inclusive
                dv = std::div(dv.rem,size);
                if(condition_type == 0) {        // row conditions
                    num_t row = dv.quot+1, value = dv.rem+1;
                    matrix[i][j] = triple.row == row && triple.value == value;
                } 
                else if(condition_type == 1) {   // column conditions
                    num_t column = dv.quot+1, value = dv.rem+1;
                    matrix[i][j] = triple.column == column && triple.value == value;
                } 
                else if(condition_type == 2) {    // square conditions
                    num_t square = dv.quot+1, value = dv.rem+1;
                    matrix[i][j] = is_in_square(triple,square,sqrt_of_size) && triple.value == value;
                } 
                else if(condition_type == 3) {   // point conditions
                    num_t row = dv.quot+1, column = dv.rem+1;
                    matrix[i][j] = triple.row == row && triple.column == column;
                }
            }
        }
    }
 /*   
    // incorporate specific sudoku problem data
    for(num_t row = 1; row <= size; row++) {
        for(num_t column = 1; column <= size; column++) {
            num_t value = grid[i][j];
            if( value != 0) {       // a value of 0 means the grid point is blank (ie unknown value)
                triple.row = row;
                triple.column = column;
                triple.value = 1;
                for(triple.value = 1; triple.value <= size; triple.value++) {
                    if(triple.value != value) {
                        int i = triple_to_index(triple,size);
                        for(int j = 0; j < n; j++) {
                            matrix[i][j] = 0;
                        }
                    }
                }
            }
        }
    } 
*/
    
}
// skip the boolean matrix step altogether
//void sudoku_to_LMatrix(int** grid, LMatrix& M);


void solution_to_grid(std::vector<int> solution,num_t **grid,int size)
{
    int index;
    Triple triple;
    while(!solution.empty()) {
        index = solution.back();
        solution.pop_back();
        triple = index_to_triple(index,size);
        grid[triple.row-1][triple.column-1] = triple.value;
    }
}


/********************************************************************************************************
 *                                      HELPER FUNCTIONS
 */
 
int triple_to_index(Triple triple, int size) {
    return (triple.row-1)*size*size + (triple.column-1)*size + (triple.value-1);
}

Triple index_to_triple(int index, int size) {
    // index = (a-1)*size^2 + (b-1)*size + (c-1)
    // need to find a,b, and c
    Triple triple;
    std::div_t dv = std::div(index,size);
    triple.value = dv.rem + 1;         // c = index % size + 1, etc
    dv = std::div(dv.quot,size);
    triple.column = dv.rem + 1;
    triple.row = dv.quot + 1;
    return triple;
}

/*      Returns 1 iff 'triple' belongs to the square denoted by 'square'
 *      
 *      
 *      square = a + b*sqrt_of_size, where square, a and b are defined in the below example
 *
 *                  EXAMPLE.
 *      sqrt_of_size = 3, size = 9
 * 
 *          a = 1, 2, 3
 *      ___________________
 *      |  1  |  2  |  3  |     b
 *      |_____|_____|_____|     =
 *      |  4  |  5  |  6  |     0,
 *      |_____|_____|_____|     1,
 *      |  7  |  8  |  9  |     2
 *      |_____|_____|_____|
 *
 * 
 *      Which square is the triple (4,6,9) in?
 *      a = 2, b = 1
 *      theSquare = 2 + 3*1 = 5
 */
bool is_in_square(Triple triple, num_t square, int sqrt_of_size)
{   
    int a = std::div(triple.row-1,sqrt_of_size).quot + 1;
    int b = std::div(triple.column-1,sqrt_of_size).quot;
    num_t theSquare = a + b*sqrt_of_size;
    return theSquare == square;
}

/********************************************************************************************************/

}