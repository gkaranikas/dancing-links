#include <iostream>
#include <string>
#include <vector>

#include <stack>
#include "linked_matrix.h"

//#include "sudoku_solver.h"

namespace dancing_links_GJK
{

/** 
 *  an implementation of Donald Knuth's Dancing Links algorithm
 *  https://arxiv.org/pdf/cs/0011047.pdf
 *  https://en.wikipedia.org/wiki/Dancing_Links
 */

typedef linked_matrix_GJK::MNode0 Node;
typedef linked_matrix_GJK::LMatrix LMatrix;
typedef linked_matrix_GJK::Column Column;

typedef std::vector<int> S_Stack;

enum RC {_row_, _column_};
struct RC_Item {
    Node* node;
    RC type;
};
typedef std::stack<RC_Item> RC_Stack;
typedef std::stack<RC_Stack> H_Stack;




/* function declarations */
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history);
Column* choose_column(LMatrix& M);
void update(LMatrix& M, S_Stack& solution, H_Stack& history, Node *r);
void downdate(LMatrix& M, S_Stack& solution, H_Stack& history);


std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n)
{   
    LMatrix M(matrix, m, n);
    H_Stack history;
    std::vector<int> solution;
    solution.reserve(m);
    DLX(M, solution, history);
    solution.shrink_to_fit();
    return solution;
}

// could adjust algorithm to find all solutions
/* 
 * A PSEUDOCODE IMPLEMENTATION OF ALGORITHM X
 * 1. Let c be the column with the most 1's
 * IF   There are no columns:
 *     THEN    [matrix is empty => solution is complete =>] END ALGORITHM
 * ELSEIF   c has no 1's:
 *     THEN    downdate_matrix(); then go back to 1. 
 * 2. FOR each row r with a 1 in column c:
 *      update_matrix()
 *      Go to 1.
 * 
 */
 
 
 
         /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/
            typedef int num_t;       // range understood to be restricted to 1,2,...9 (replace 9 with 'size' in general)
const num_t no_value = 0;

struct Triple {
    num_t row;
    num_t column;
    num_t value;
};
         
    Triple index_to_triple(int index, int size) {
    // index = (a-1)*size^2 + (b-1)*size + (c-1)
    // need to find a,b, and c
    Triple triple;
    std::div_t dv = std::div(index,size);
    triple.value = dv.rem + 1;         // c = index % size + 1, etc
    dv = std::div(dv.quot,size);
    triple.column = dv.rem + 1;
    triple.row = dv.quot + 1;
    return triple;
}
         /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/

 
 
 
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history)
{
    Column *c = choose_column(M);
    // 'M' is empty => solution successfully found
    if( c == NULL ) { 
        return 1;
    }
    for( Node *r = c->down(); r != static_cast<Node*>(c); r = r->down() ) {
        update(M, solution, history, r);
        /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/
    {


int grid_0[9] = {0,0,0,0,0,0,0,0,0};
int grid_1[9] = {0,0,0,0,0,0,0,0,0};
int grid_2[9] = {0,0,0,0,0,0,0,0,0};
int grid_3[9] = {0,0,0,0,0,0,0,0,0};
int grid_4[9] = {0,0,0,0,0,0,0,0,0};
int grid_5[9] = {0,0,0,0,0,0,0,0,0};
int grid_6[9] = {0,0,0,0,0,0,0,0,0};
int grid_7[9] = {0,0,0,0,0,0,0,0,0};
int grid_8[9] = {0,0,0,0,0,0,0,0,0};
int* grid[9] = {grid_0,grid_1,grid_2,grid_3,grid_4,grid_5,grid_6,grid_7,grid_8};

    int size = 9;
    
    int index;
    Triple triple;
    int s = solution.size(),t = 0;
    while(t < s) {
        index = solution[t];
        triple = index_to_triple(index,size);
        grid[triple.row-1][triple.column-1] = triple.value;
        t++;
    }
    
    //std::cout << '\t' << "SUDOKU GRID" << std::endl << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << '\t';
        for(int j = 0; j < size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    }
        /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/
        if( DLX(M, solution, history) ) { 
            return 1;     
        } else {
            downdate(M, solution, history);
            
            
         /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/
    {

int grid_0[9] = {0,0,0,0,0,0,0,0,0};
int grid_1[9] = {0,0,0,0,0,0,0,0,0};
int grid_2[9] = {0,0,0,0,0,0,0,0,0};
int grid_3[9] = {0,0,0,0,0,0,0,0,0};
int grid_4[9] = {0,0,0,0,0,0,0,0,0};
int grid_5[9] = {0,0,0,0,0,0,0,0,0};
int grid_6[9] = {0,0,0,0,0,0,0,0,0};
int grid_7[9] = {0,0,0,0,0,0,0,0,0};
int grid_8[9] = {0,0,0,0,0,0,0,0,0};
int* grid[9] = {grid_0,grid_1,grid_2,grid_3,grid_4,grid_5,grid_6,grid_7,grid_8};


    int size = 9;
    
    int index;
    Triple triple;
    int s = solution.size(),t = 0;
    while(t < s) {
        index = solution[t];
        triple = index_to_triple(index,size);
        grid[triple.row-1][triple.column-1] = triple.value;
        t++;
    }
    
    //std::cout << '\t' << "SUDOKU GRID" << std::endl << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << '\t';
        for(int j = 0; j < size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    }
        /*******************************
         * * * * * * D E B U G * * * * * 
         * *****************************/
            
        }
    }
    // no solution exists
    return 0;
}

/* Given a matrix of linked nodes M, return a pointer to the column with the most nodes
 * If there are no columns, return NULL
 */
Column* choose_column(LMatrix& M)
{
    if( M.is_trivial() ) return NULL;
    
    Column* col = static_cast<Column*>(M.head()->right());
    Column* max_col = col;

    while( col != M.head() )
    {   
        if( col->size() > max_col->size() ) {
            max_col = col;
        }
        col = static_cast<Column*>(col->right());
    }
    return max_col;
}

/*
 * 
 */
void update(LMatrix& M, S_Stack& solution, H_Stack& history, Node *r) 
{
    solution.push_back(r->data().row_id);
    
    RC_Stack temp_stack;
    RC_Item temp_item;

    for(Node * i = r->right(); i != r; i = i->right()) {
        for(Node *j = i->up(); j != i; j = j->up() ) {
            if(j->data().column_id == j) continue;
            M.remove_row(j);
            temp_item.node = j;
            temp_item.type = _row_;
            temp_stack.push(temp_item);
        }
        M.remove_column(i);
        temp_item.node = i;
        temp_item.type = _column_;
        temp_stack.push(temp_item);
    }
    
    for(Node *j = r->up(); j != r; j = j->up() ) {
        if(j->data().column_id == j) continue;
        M.remove_row(j);
        temp_item.node = j;
        temp_item.type = _row_;
        temp_stack.push(temp_item);
    }
    M.remove_column(r);
    temp_item.node = r;
    temp_item.type = _column_;
    temp_stack.push(temp_item);
    
    history.push(temp_stack);
}


/*
 * Undoes the operations of 'update'
 */
void downdate(LMatrix& M, S_Stack& solution, H_Stack& history) 
{
    if( history.empty() ) {
        return;
    }
    solution.pop_back();
    RC_Stack last = history.top();
    RC_Item it;
    while( !last.empty() ) {
        it = last.top();
        if( it.type == _row_ ) {
            M.restore_row(it.node);
        } else if( it.type == _column_ ) {
            M.restore_column(it.node);
        }
        last.pop();
    }
    history.pop();
}


}