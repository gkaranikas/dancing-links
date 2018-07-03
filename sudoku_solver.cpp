#include "sudoku_solver.h"
//#include <math>
#include <cstdlib>


void Sudoku_Solver(int **grid, int size)
{
    int m = size*size*size;
    int n = 4*size*size;
    bool **matrix = new bool*[m];
    for(int i=0; i < m; i++) {
        matrix[i] = new bool[n];
    }
    get_exact_cover_matrix(grid, size, matrix);

    std::vector<int> solution_rows; // need to change Exact_Cover_Solver to return vector - more efficient
    // exception handling
    Exact_Cover_Solver(matrix,m,n,solution_rows);
    
    // for num in solution_rows     // where num = row index
    // int triple[3];
    // num_to_triple(num, triple, size)
    // grid[triple[0]-1][triple[1]-1] = triple[2]
    
    // free memory
    for(int i=0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}



int triple_to_num(int *triple, int size) {
    return (triple[0]-1)*size*size + (triple[1]-1)*size + (triple[2]-1);
}

void num_to_triple(int num, int *triple, int size) {
    // num = (a-1)*size^2 + (b-1)*size + (c-1)
    // need to find a,b, and c
    std::div_t dv = std::div(num,size);
    triple[2] = dv.rem + 1;         // c = num % size + 1, etc
    dv = std::div(dv.quot,size);
    triple[1] = dv.rem + 1;
    triple[0] = dv.quot + 1;
}

/*
 * 
 *            _______row constraints_________column_______square_________grid positions_____
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
bool** exact_cover_matrix(int **grid, int size, bool** matrix) {
    int m = size*size*size;
    int n = 4*size*size;
    
    std::div_t dv;
    int col_type, k;
    for(int i = 0; i < m; i++) {
        num_to_triple(i,triple,size);
        for(int j = 0; j < n; j++) {
            dv = std::div(j,size*size);
            col_type = dv.quot;     // between 0 and 3 inclusive
            k = dv.rem;             // between 0 and size^2-1 inclusive
            dv = std::div(k,size);
            if(col_type == 0) {        // row constraints
                matrix[i][j] = (triple[0] == dv.quot+1 && triple[2] == dv.rem+1) ? 1 : 0;
            } else if(col_type == 1) {   // column constraints
                matrix[i][j] = (triple[1] == dv.quot+1 && triple[2] == dv.rem+1) ? 1 : 0;
            } else if(col_type == 2) {    // square constraints
                int sqrt_size = (int) math.sqrt(size);
                // dv.quot = square index number = a*sqrt_size + b
                std::div_t dv_2 = std::div(dv.quot,sqrt_size);  // quot = a, rem = b
                matrix[i][j] = ( std::div(triple[0]-1,sqrt_size).quot == dv_2.quot
                                && std::div(triple[1]-1,sqrt_size).quot == dv_2.rem
                                && triple[2] == dv.rem+1) ? 1 : 0;
            } else if(col_type == 3) {   // grid point constraints
                matrix[i][j] = (triple[0] == dv.quot+1 && triple[1] == dv.rem+1) ? 1 : 0;
            }
        }
    }
    
    // incorporate specific sudoku problem data
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int value = grid[i][j];
            if( value != 0) {
                int triple[3] = {i+1,j+1,1};
                for(int value_cnt = 1; value_cnt <= 9; value_cnt++) {
                    triple[2] = value_cnt;
                    if(value_cnt != value) {
                        int num = triple_to_num(triple,size);
                        for(int k = 0; k < n; k++) {
                            matrix[num][k] = 0;
                        }
                    }
                }
            }
        }
    } 
    
}

// skip the boolean matrix step altogether
//void sudoku_to_LMatrix(int** grid, LMatrix& M);
