#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

#include "../linked_matrix.h"
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::MNode0;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::join_lr;
using linked_matrix_GJK::join_du;
using linked_matrix_GJK::DEBUG_display;

#define NUM_TESTS 2

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/
// TEST CASES
//
//
//


// 3 auxiliary test functions to follow

// 'matrix' is an uninitialized array of bool*'s of size m
// 'matrix_list' is an array of bools of size m*n
// Makes 'matrix' a mxn array and fills with the contents of 'matrix_list' interpreted in row-descending order
void matrix_creator(bool **matrix,int m, int n, bool* matrix_list)
{   
    int j = 0;
    for(int i = 0; i < m; i++) {
        matrix[i] = new bool[n];
        for(; j < (i+1)*n; j++) {
            matrix[i][j-i*n] = matrix_list[j];
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

void matrix_printer(LMatrix& M)
{
    DEBUG_display(M);
    std::cout << std::endl << "Is the diagram satisfactory? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
}

void test_row_deletion()
{
    int m = 4, n = 4;
    bool flat_matrix[4*4] = {
        1,0,0,1,
        1,1,0,1,
        0,0,1,1,
        1,1,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    LMatrix M(matrix,m,n);
    DEBUG_display(M);
    
    MNode0 *node = M.head()->right()->right()->right()->down();
    std::cout << std::endl << "Removing row 2" << std::endl << std::endl;
    M.remove_row(node);
    matrix_printer(M);
    
    std::cout << std::endl << "Restoring row 2" << std::endl << std::endl;
    M.restore_row(node);
    matrix_printer(M);
    matrix_deletor(matrix,m,n);
}


void test_column_deletion()
{
    int m = 4, n = 4;
    bool flat_matrix[4*4] = {
        1,0,0,1,
        1,1,0,1,
        0,0,1,1,
        1,1,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    LMatrix M(matrix,m,n);
    DEBUG_display(M);
    
    MNode0 *node = M.head()->right()->right();
    std::cout << std::endl << "Removing column 1" << std::endl << std::endl;
    M.remove_column(node);
    matrix_printer(M);
    
    std::cout << std::endl << "Restoring column 1" << std::endl << std::endl;
    M.restore_column(node);
    matrix_printer(M);
    matrix_deletor(matrix,m,n);
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_row_deletion, 
&test_column_deletion
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