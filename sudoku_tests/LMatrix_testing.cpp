#include <iostream>
#include <assert.h>
#include <cstdlib>

#include "../linked_matrix.h"
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::MNode0;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::join_lr;
using linked_matrix_GJK::join_du;
using linked_matrix_GJK::DEBUG_display;

#define NUM_TESTS 8

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/
// TEST CASES
// empty matrix
// zero matrix
// ones matrix
// single column/single row matrix
// non-zero matrix with zero rows
// non-zero matrix with trailing zero rows

void test_empty()
{
    LMatrix M;
    assert(( M.head()->right() == M.head() ));
    assert(( M.head()->left() == M.head() ));
    assert(( M.head()->up() == NULL ));
    assert(( M.head()->down() == NULL ));
    assert(( M.head()->data().row_id == -1 ));
    assert(( M.head()->data().column_id == NULL ));
    assert(( M.is_trivial() ));
    
    DEBUG_display(M);
    
}

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

void matrix_tester(bool **matrix,int m,int n)
{
    LMatrix M(matrix,m,n);
    
    // print original matrix
    std::cout << '\t' << "ORIGINAL BOOLEAN MATRIX" << std::endl << std::endl;
    for(int i = 0; i < m; i++) {
        std::cout << '\t';
        for(int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\t' << '\t' << "row " << i << std::endl;
    }
    std::cout << std::endl;
    
    // print diagram of linked matrix
    DEBUG_display(M);
    std::cout << std::endl << "Is the diagram satisfactory? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
}

void test_zeros()
{   
    int m = 4, n = 4;
    bool **matrix = new bool*[m];
    bool matrix_list[4*4] = {
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

void test_ones()
{   
    int m = 4, n = 4;
    bool **matrix = new bool*[m];
    bool matrix_list[4*4] = {
        1,1,1,1,
        1,1,1,1,
        1,1,1,1,
        1,1,1,1
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

void test_single_row()
{   
    int m = 1, n = 5;
    bool **matrix = new bool*[m];
    bool matrix_list[1*5] = {
        1,0,1,0,0
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

void test_single_column()
{   
    int m = 5, n = 1;
    bool **matrix = new bool*[m];
    bool matrix_list[5*1] = {
        0,
        1,
        1,
        0,
        1
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

void test_interior_zero_row()
{
    int m = 3, n = 3;
    bool **matrix = new bool*[m];
    bool matrix_list[3*3] = {
        1,0,1,
        0,0,0,
        0,1,1
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
    // this is what the diagram should look like:
    //  ROW DIAGRAM
    //  >H<>C<>C<>C<        row -1
    //     >N<   >N<        row 0
    //                      row 1
    //        >N<>N<        row 2
}

void test_trailing_zero_row()
{
    int m = 3, n = 3;
    bool **matrix = new bool*[m];
    bool matrix_list[3*3] = {
        1,0,1,
        1,1,1,
        0,0,0
    };
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

void test_random()
{
    int m = 8, n = 7;
    bool **matrix = new bool*[m];
    bool matrix_list[8*7];
    for(int k = 0; k < m*n; k++) matrix_list[k] = (bool) (rand() % 2);
    matrix_creator(matrix,m,n,matrix_list);
    matrix_tester(matrix,m,n);
    matrix_deletor(matrix,m,n);
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_empty, 
&test_zeros, 
&test_ones, 
&test_single_row,
&test_single_column,
&test_interior_zero_row,
&test_trailing_zero_row,
&test_random
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