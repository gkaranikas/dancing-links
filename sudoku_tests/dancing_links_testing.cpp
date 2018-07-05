#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

//#include "../sudoku_solver.h"
std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n);


#include "../linked_matrix.h"
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::MNode0;
using linked_matrix_GJK::Column;
using linked_matrix_GJK::DEBUG_display;

#define NUM_TESTS 4

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

void matrix_printer(bool **matrix, int m, int n)
{
    // print original matrix
    std::cout << '\t' << "BOOLEAN MATRIX" << std::endl << std::endl;
    for(int i = 0; i < m; i++) {
        std::cout << '\t';
        for(int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\t' << '\t' << "row " << i << std::endl;
    }
    std::cout << std::endl;
}

void print_solution(std::vector<int>& solution) {
    if(solution.empty()) {
        std::cout << "No solution exists" << std::endl;
        return;
    }
    int s = solution.size();
    std::cout << "Rows:";
    for(int i = 0; i < s; i++) {
        std::cout << '\t' << solution[i];
    }
    std::cout << std::endl;
}

#include <stack>
typedef std::vector<int> S_Stack;

enum RC {_row_, _column_};
struct RC_Item {
    MNode0* node;
    RC type;
};
typedef std::stack<RC_Item> RC_Stack;
typedef std::stack<RC_Stack> H_Stack;

bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history);
Column* choose_column(LMatrix& M);
void update(LMatrix& M, S_Stack& solution, H_Stack& history, MNode0 *r);
void downdate(LMatrix& M, S_Stack& solution, H_Stack& history);

void cont(void) {
    std::cout << std::endl << "continue? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
}

void test_update_downdate()
{
    int m = 4, n = 3;
    bool flat_matrix[4*3] = {
        1,0,0,
        1,1,0,
        1,0,1,
        1,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    matrix_printer(matrix,m,n);
    
    LMatrix M(matrix,m,n);

    cont();
    
    Column* c = choose_column(M);
    assert( c == M.head()->right());
    S_Stack solution;
    H_Stack history;
    MNode0* r = c->down();
    update(M,solution,history,r);
    DEBUG_display(M);
    cont();
    downdate(M,solution,history);
    DEBUG_display(M);
    cont(); 
    r = r->down();
    update(M,solution,history,r);
    DEBUG_display(M);
    cont();
    downdate(M,solution,history);       // seg faults - fixed now
    DEBUG_display(M);
    cont();
    r = r->down();
    update(M,solution,history,r);
    DEBUG_display(M);
    cont();
    downdate(M,solution,history);
    DEBUG_display(M);
    cont();
    r = r->down();
    update(M,solution,history,r);
    DEBUG_display(M);
    cont();
    downdate(M,solution,history);
    DEBUG_display(M);
    cont();
}



void test_0()
{   
    int m = 4, n = 3;
    bool flat_matrix[4*3] = {
        1,0,0,
        1,1,0,
        0,0,1,
        0,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    matrix_printer(matrix,m,n);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    std::cout << std::endl << "Is output correct? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
}

void test_1()
{   
    int m = 4, n = 3;
    bool flat_matrix[4*3] = {
        1,0,0,
        1,1,0,
        1,0,1,
        1,0,1
    };
    bool **matrix = new bool*[m];
    matrix_creator(matrix,m,n,flat_matrix);
    matrix_printer(matrix,m,n);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    std::cout << std::endl << "Is output correct? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
}

bool continue_prompt(void) {
    std::cout << std::endl << "continue? [Y/n]";
    char in;
    std::cin >> in;
    return ( in == 'y' || in == 'Y');
}

void test_2()
{   
do {
    int m = 8, n = 7;
    bool **matrix = new bool*[m];
    srand((int) time(0));
    bool flat_matrix[8*7];
    for(int k = 0; k < m*n; k++) flat_matrix[k] = (bool) (rand() % 2);

    matrix_creator(matrix,m,n,flat_matrix);
    matrix_printer(matrix,m,n);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    std::cout << std::endl << "Is output correct? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
} while(continue_prompt());
}


/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_update_downdate,
&test_0,
&test_1,
&test_2
};

// run all tests
int main() {
    bool TESTS[NUM_TESTS];  // will determine whether a given test is to be run or omitted
    for(int i = 0; i < NUM_TESTS; i++) TESTS[i] = 1;
    TESTS[0] = 0;
    
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}