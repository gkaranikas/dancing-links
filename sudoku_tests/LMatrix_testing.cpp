#include <iostream>
#include <assert.h>

#include "../linked_matrix.h"
using linked_matrix_GJK::MNode0;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::join_lr;
using linked_matrix_GJK::join_du;

#define NUM_TESTS 3
const bool TESTS[NUM_TESTS] = {1,1,1};  // will determine whether a given test is to be run or omitted


/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


void test0()
{

}


void test1()
{

}


void test2()
{

}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {&test0, &test1, &test2};

// run all tests
int main() {
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}