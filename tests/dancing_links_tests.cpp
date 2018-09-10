#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "../linked_matrix.h"
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::MNode;
using linked_matrix_GJK::Column;

#include <vector>
#include <stack>
#include "../dancing_links.h"
using dancing_links_GJK::choose_column;
using dancing_links_GJK::update;
using dancing_links_GJK::downdate;
using dancing_links_GJK::DLX;

using dancing_links_GJK::Exact_Cover_Solver;

#define NUM_TESTS 7

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
    
    Column* c = static_cast<Column*>(M.head()->right());
    dancing_links_GJK::S_Stack solution;
    dancing_links_GJK::H_Stack history;
    MNode* r = c->down();
    update(M,solution,history,r);
    M.DEBUG_display();
    cont();
    downdate(M,solution,history);
    M.DEBUG_display();
    cont(); 
    r = r->down();
    update(M,solution,history,r);
    M.DEBUG_display();
    cont();
    downdate(M,solution,history);       // seg faults - fixed now
    M.DEBUG_display();
    cont();
    r = r->down();
    update(M,solution,history,r);
    M.DEBUG_display();
    cont();
    downdate(M,solution,history);
    M.DEBUG_display();
    cont();
    r = r->down();
    update(M,solution,history,r);
    M.DEBUG_display();
    cont();
    downdate(M,solution,history);
    M.DEBUG_display();
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
    matrix_deletor(matrix,m,n);
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
    matrix_deletor(matrix,m,n);
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
    matrix_deletor(matrix,m,n);
    std::cout << std::endl << "Is output correct? [Y/n]";
    char in;
    std::cin >> in;
    assert( in == 'y' || in == 'Y');
} while(continue_prompt());
}


void test_big_random_matrix()
{
    do {
    int m = 729, n = 4*81;
    bool **matrix = new bool*[m];
    srand((int) time(0));
    bool flat_matrix[m*n];
    for(int k = 0; k < m*n; k++) flat_matrix[k] = (bool) (rand() % 4 != 0);

    matrix_creator(matrix,m,n,flat_matrix);
    //matrix_printer(matrix,m,n);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    matrix_deletor(matrix,m,n);
} while(continue_prompt());
}


void test_big_soluble_matrix()
{
    do {
    int m = 729, n = 4*81;
    bool **matrix = new bool*[m];
    srand((int) time(0));
    bool flat_matrix[m*n];
    int k = 0;
    for(; k < 4*81*400; k++) flat_matrix[k] = (bool) (rand() % 4 != 0);
    for(; k < 4*81*400 + 4*81; k++) flat_matrix[k] = 1;        // this row is the (a) solution
    for(; k < m*n; k++) flat_matrix[k] = (bool) (rand() % 4 != 0);

    matrix_creator(matrix,m,n,flat_matrix);
    //matrix_printer(matrix,m,n);
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    matrix_deletor(matrix,m,n);
    } while(continue_prompt());
}

void test_sparse_matrix()
{
    do {
        int m = 729, n = 4*81;
        bool **matrix = new bool*[m];
        srand((int) time(0));
        for(int i = 0; i < m; i++) {
            matrix[i] = new bool[n];
            for(int j = 0; j < n; j++) {
            matrix[i][j] = 0;
            }
            matrix[i][(rand() % 81)] = 1;
            matrix[i][81 + (rand() % 81)] = 1;
            matrix[i][2*81 + (rand() % 81)] = 1;
            matrix[i][3*81 + (rand() % 81)] = 1;
        }

    //matrix_printer(matrix,m,n);
    LMatrix M(matrix,m,n);
//    std::ofstream ofs(".\\lmatrix.txt",std::ofstream::app);
//    M.DEBUG_display(ofs);
//    ofs.close();
    std::vector<int> solution = Exact_Cover_Solver(matrix,m,n);
    std::cout << std::endl << '\t' << "SOLUTION" << std::endl << std::endl;
    print_solution(solution);
    matrix_deletor(matrix,m,n);
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
&test_2,
&test_big_random_matrix,
&test_big_soluble_matrix,
&test_sparse_matrix
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
