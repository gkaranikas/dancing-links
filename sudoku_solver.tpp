/*  
    Copyright (C) 2018  Gregory J. Karanikas.

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
 */

#include <iostream> // required for "linked_matrix.h" and for std::cout in Sudoku<>::print_ASCII method
#include "linked_matrix.h"
namespace dancing_links_GJK {
    std::vector<int> Exact_Cover_Solver(linked_matrix_GJK::LMatrix&);
}
#include <cstdlib>   // for std::div


namespace sudoku_GJK
{

template<int sqrt_of_size>
Sudoku<sqrt_of_size>::Sudoku() 
{
    int j = 0;
    grid = new num_t<size>*[size];
    for(int i = 0; i < size; i++) {
        grid[i] = new num_t<size>[size];
    }
}

template<int sqrt_of_size>
Sudoku<sqrt_of_size>::Sudoku(char* flat_grid_str) : Sudoku()
{   
    assert(sqrt_of_size==3);
    int i,j;
    int k = 0;
    while(flat_grid_str[k] != '\0') {
        std::div_t dv = std::div(k,size);
        j = dv.rem;  // column
        i = dv.quot; // row
        grid[i][j] = num_t<size>(flat_grid_str[k] - '0'); // IMPORTANT that size == 9
        assert(0 <= grid[i][j] && grid[i][j] <= 9);     // utilizes num_t's int conversion operator
        k++;
    }
    assert(k==81);
}

template<int sqrt_of_size>
Sudoku<sqrt_of_size>::~Sudoku()
{
    for(int i = 0; i < size; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::logic_solve()
{
    // implement this method
}

template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::solve()
{
    int m = size*size*size;     // # rows of matrix for the exact cover problem formulation
    int n = 4*size*size;        // # columns         ''              ''                  ''
    bool **matrix = new bool*[m];
    for(int i=0; i < m; i++) {
        matrix[i] = new bool[n];
    }
    get_ECP_matrix(matrix);
    linked_matrix_GJK::LMatrix M(matrix,m,n);
    // free memory
    for(int i=0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    std::vector<int> solution = dancing_links_GJK::Exact_Cover_Solver(M);
    // exception handling?
    
    convert_ECP_solution(solution);
    
}

template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::write(Triple<sqrt_of_size> triple)
{
    grid[triple.row-1][triple.column-1] = triple.value;
}

template<int sqrt_of_size>
bool Sudoku<sqrt_of_size>::found(Triple<sqrt_of_size> triple)
{
    return grid[triple.row-1][triple.column-1] == triple.value;
}




/*
 * 
 *            ________row conditions_________column_______square________cell conditions_____
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
template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::get_ECP_matrix(bool** matrix) {
    const int m = size*size*size;
    const int n = 4*size*size;
    
    std::div_t dv;
    enum class Conditions {row=0, column=1, square=2, cell=3} condition_type;
    for(int i = 0; i < m; i++) {
        Triple<sqrt_of_size> triple(i);
        if(!grid[triple.row-1][triple.column-1].is_blank() && !found(triple))
        {
            // incorporate specific sudoku problem data
            for(int j = 0; j < n; j++) matrix[i][j] = 0;
        } else {        // NOTE: if grid[triple.row-1][triple.column-1] == triple.value,
                        // then the solution finding process can perhaps be sped up by removing
                        // the appropriate rows and columns from the matrix and adding them
                        // to the solution
                        // this is a TODO
            for(int j = 0; j < n; j++) {
                dv = std::div(j,size*size);
                condition_type = (Conditions)dv.quot;     // between 0 and 3 inclusive
                dv = std::div(dv.rem,size);
                if(condition_type == Conditions::row) { 
                    num_t<size> row(dv.quot+1), value(dv.rem+1);
                    matrix[i][j] = triple.row == row && triple.value == value;
                } 
                else if(condition_type == Conditions::column) {
                    num_t<size> column = dv.quot+1, value = dv.rem+1;
                    matrix[i][j] = triple.column == column && triple.value == value;
                } 
                else if(condition_type == Conditions::square) {
                    num_t<size> square(dv.quot+1), value(dv.rem+1);
                    matrix[i][j] = triple.is_in_square(square) && triple.value == value;
                } 
                else if(condition_type == Conditions::cell) {
                    num_t<size> row(dv.quot+1), column(dv.rem+1);
                    matrix[i][j] = triple.row == row && triple.column == column;
                }
            }
        }
    }
    
}


template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::convert_ECP_solution(std::vector<int> solution)
{
    int index;
    while(!solution.empty()) {
        index = solution.back();
        solution.pop_back();
        write( Triple<sqrt_of_size>(index) );
    }
}



int pad(int num, int width)
{
    return num;     // do general case
}

template<int sqrt_of_size>
void Sudoku<sqrt_of_size>::display_ASCII() const
{
    const int MAX_WIDTH = 1;   // do general case
    const char *blank = " ";   // in general blank = MAX_WIDTH*" "
    const char *sp = " ";
    const char * hborder = "=========================";
    const char * vborder = "|";
    const char * indent = "\t";
    
    std::cout << indent << hborder << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << indent;
        std::cout << vborder << sp;
        for(int j = 0; j < size; j++) {
            if(!grid[i][j].is_blank())
                std::cout << pad((int)grid[i][j],MAX_WIDTH) << sp;
            else
                std::cout << blank << sp;
            if( (j+1)%sqrt_of_size == 0 ) std::cout << vborder << sp;
        }
        if( (i+1)%sqrt_of_size == 0 )
            std::cout << std::endl << indent << hborder;
        std::cout <<  std::endl;
    }
}





/********************************************************************************************************
 *                                   Triple method implementations
 */

template<int sqrt_of_size> 
int Triple<sqrt_of_size>::to_index() 
{
    return (row-1)*size*size + (column-1)*size + (value-1);
}

template<int sqrt_of_size>
Triple<sqrt_of_size>::Triple(int index) {
    // index = (a-1)*size^2 + (b-1)*size + (c-1)
    // need to find a,b, and c
    std::div_t dv = std::div(index,size);
    value = dv.rem + 1;         // c = index % size + 1, etc
    dv = std::div(dv.quot,size);
    column = dv.rem + 1;
    row = dv.quot + 1;
}

template<int sqrt_of_size>
bool Triple<sqrt_of_size>::is_in_square(num_t<size> square)
{   
    int a = std::div(row-1,sqrt_of_size).quot + 1;
    int b = std::div(column-1,sqrt_of_size).quot;
    num_t<sqrt_of_size*sqrt_of_size> s = a + b*sqrt_of_size;
    return s == square;
}

/********************************************************************************************************/

} // namespace 'sudoku_GJK'