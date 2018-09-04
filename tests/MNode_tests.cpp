#include <iostream>
#include <assert.h>

#include "../linked_matrix.h"
using linked_matrix_GJK::MNode;
using linked_matrix_GJK::MData;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::join_lr;
using linked_matrix_GJK::join_du;

#define NUM_TESTS 3


/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/

// basic tests of MNode member functions 
void test0()
{
	MNode A(MData(-1));
	assert(A.left() == NULL);
    assert(A.right() == NULL);
    assert(A.up() == NULL);
    assert(A.down() == NULL);
    
    MNode B(MData(-1));
    MNode *C = new MNode(MData());
	A.set_right(&B);
    A.set_left(C);
    A.set_up(&A);
    A.set_down(&A);
    C->set_left(&B);
	assert( &B == A.right() );
    assert( C == A.left() );
    assert( &A == A.up() );
    assert( &A == A.down() );
    assert( C->left() == &B );
    
    delete C;
}

// tests the functions 'join_lr' and 'join_du'
void test1()
{
	MNode *A = new MNode(MData()), *B = new MNode(MData()), *C = new MNode(MData());
    join_lr(A,B);
    join_lr(B,C);
    join_lr(C,A);
    assert( A->right() == B && A->left() == C );
    assert( B->right() == C && B->left() == A );
    assert( C->right() == A && C->left() == B );
    
    MNode *n = A;
    for(int i = 0; i<6; ++i, n = n->right() ) {}
    assert(n == A);
	
//**********************************************

    join_du(A,B);
    join_du(B,C);
    join_du(C,A);
    assert( A->up() == B && A->down() == C );
    assert( B->up() == C && B->down() == A );
    assert( C->up() == A && C->down() == B );
    
    n = A;
    for(int i = 0; i<6; ++i, n = n->up() ) {}
    assert(n == A);
    
    delete A;
    delete B;
    delete C;
}

// creates and manipulates 'Column' objects
void test2()
{
    Column *C = new Column(1);
    assert(C->size() == 1);
    C->set_size(8);
    assert(C->size() == 8);
    
    delete C;
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {&test0, &test1, &test2};

// run all tests
int main() {
    
    bool TESTS[NUM_TESTS] = {1,1,1};  // will determine whether a given test is to be run or omitted
    
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}
