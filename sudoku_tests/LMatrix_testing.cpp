#include <iostream>
#include <assert.h>

#include "../linked_matrix.h"
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::MNode0;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::join_lr;
using linked_matrix_GJK::join_du;
using linked_matrix_GJK::DEBUG_display;

#define NUM_TESTS 3
const bool TESTS[NUM_TESTS] = {1,1,1};  // will determine whether a given test is to be run or omitted


/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


void test0()
{
    LMatrix M;
    assert(( M.head()->right() == M.head() ));
    assert(( M.head()->left() == M.head() ));
    assert(( M.head()->up() == NULL ));
    assert(( M.head()->down() == NULL ));
    assert(( M.head()->data().row_id == -1 ));
    assert(( M.head()->data().column_id == NULL ));
    assert(( M.is_trivial() ));
    
}

void test1()
{
    bool r0[3] = {1,0,1};
    bool r1[3] = {0,0,0};
    bool r2[3] = {0,1,1};
    bool* mx[3] = {r0,r1,r2};
    
    LMatrix M(mx,3,3);
    DEBUG_display(M);
    std::cout << std::endl << "Is the diagram satisfactory? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
    //  row diagram
    //  >H<>C<>C<>C<    row -1
    //     >N<   >N<    row 0
    //                  row 1
    //        >N<>N<    row 2
    // column diagram
    // 0>H<0            col -1
    //  >C<>N<          col 0
    //  >C<      >N<    col 1
    //  >C<>N<   >N<    col 2
    
    /*
    assert(( M.head()->up() == NULL ));
    assert(( M.head()->down() == NULL ));
    // check column headers
    MNode0 *node;
    MNode0 *prev;
    assert(( static_cast<Column *>(node=M.head()->right())->size() == 1 ));
    assert(( node->data().row_id == -1 && node->data().column_id == node ));
    assert(( static_cast<Column *>(node=node->right())->size() == 1 ));
    assert(( node->data().row_id == -1 && node->data().column_id == node ));
    assert(( static_cast<Column *>(node=node->right())->size() == 2 ));
    assert(( node->data().row_id == -1 && node->data().column_id == node ));
    assert(( node->right() M.head() ))
    

    assert(( M.head()->data().row_id == -1 ))
    assert(( M.head()->data().column_id == NULL ))
    assert(( !M.is_trivial() ));
      */
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