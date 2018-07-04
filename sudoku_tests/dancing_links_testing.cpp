#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

//#include "../sudoku_solver.h"
std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n);


#define NUM_TESTS 1

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/

// TEST CASES
//
//
//


void matrix_creator(bool **matrix,int m, int n, bool* flat_matrix)
{   
    int j = 0;
    for(int i = 0; i < m; i++) {
        matrix[i] = new bool[n];
        for(; j < (i+1)*n; j++) {
            matrix[i][j-i*n] = flat_matrix[j];
        }
    }
}

void matrix_deletor(bool **matrix, int m, int n)
{
    for(int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void test()
{   
    int m = 4, n = 3;
    bool flat_matrix[4*3] = {
        1,0,0,
        1,1,0,
        0,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << solution;
    matrix_deletor(matrix,m,n);
}


/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test
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