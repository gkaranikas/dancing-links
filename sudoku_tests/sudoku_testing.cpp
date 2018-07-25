#include "../sudoku_solver.h"

#include <iostream>
#include <cassert>

#define NUM_TESTS 3

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/

// TEST CASES
//
//
//


void grid_creator(int **grid, int size, int* flat_grid)
{   
    int j = 0;
    for(int i = 0; i < size; i++) {
        grid[i] = new int[size];
        for(; j < (i+1)*size; j++) {
            grid[i][j-i*size] = flat_grid[j];
        }
    }
}

void grid_deletor(int **grid, int size)
{
    for(int i = 0; i < size; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void grid_printer_ascii(int **grid, int size)
{
    // print sudoku grid
    std::cout << '\t' << "SUDOKU GRID" << std::endl << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << '\t';
        for(int j = 0; j < size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void run_test(int *flat_grid, int sqrt_of_size)
{
    int size = sqrt_of_size*sqrt_of_size;
    int **grid = new int*[size];
    grid_creator(grid,size,flat_grid);
    grid_printer_ascii(grid,size);
    sudoku_GJK::Sudoku_Solver(grid,sqrt_of_size);
    grid_printer_ascii(grid,size);
    grid_deletor(grid,size);
}

void test_helper_functions()
{
    
}

void test_0()
{   
    const int sqrt_of_size = 3;
    const int size = 9;
    int flat_grid[size*size] = {
        5,3,0,0,7,0,0,0,0,
        6,0,0,1,9,5,0,0,0,
        0,9,8,0,0,0,0,6,0,
        8,0,0,0,6,0,0,0,3,
        4,0,0,8,0,3,0,0,1,
        7,0,0,0,2,0,0,0,6,
        0,6,0,0,0,0,2,8,0,
        0,0,0,4,1,9,0,0,5,
        0,0,0,0,8,0,0,7,9
    };
    int solved_grid[size*size] = {
        5,3,4,6,7,8,9,1,2,
        6,7,2,1,9,5,3,4,8,
        1,9,8,3,4,2,5,6,7,
        8,5,9,7,6,1,4,2,3,
        4,2,6,8,5,3,7,9,1,
        7,1,3,9,2,4,8,5,6,
        9,6,1,5,3,7,2,8,4,
        2,8,7,4,1,9,6,3,5,
        3,4,5,2,8,6,1,7,9
    };
    run_test(flat_grid,sqrt_of_size);
    // from wikipedia

}

void test_1()
{
    const int sqrt_of_size = 2;
    const int size = 4;
    int flat_grid[size*size] = {
        1,0,4,0,
        0,0,0,0,
        0,2,0,1,
        3,0,0,0
    };
 //   int solved_grid[size*size] = {
 //   };
    run_test(flat_grid,sqrt_of_size);

}

void test_2()
{
    
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_0,
&test_1,
&test_2
};

// run all tests
int main() {
    bool TESTS[NUM_TESTS];  // will determine whether a given test is to be run or omitted
    for(int i = 0; i < NUM_TESTS; i++) TESTS[i] = 1;
    
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}