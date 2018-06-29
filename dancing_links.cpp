#include <iostream>
#include <string>

#include <stack>
#include "linked_matrix.h"

#include "dancing_links.h"

/** 
 *  an implementation of Donald Knuth's Dancing Links algorithm
 *  https://arxiv.org/pdf/cs/0011047.pdf
 *  https://en.wikipedia.org/wiki/Dancing_Links
 */

typedef stack<int> S_Stack;

enum RC {_row_, _column_};
struct RC_Item {
    Node* node;
    RC type;
};
typedef stack<RC_Item> RC_Stack;
typedef stack<RC_Stack> H_Stack;

typedef linked_matrix_GJK::MNode0 Node;
typedef linked_matrix_GJK::LMatrix LMatrix;
typedef linked_matrix_GJK::Column Column;


/* function declarations */
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history);
Column* choose_column(LMatrix& M);
void update(LMatrix& M, S_Stack& solution, H_Stack& history, const Node *r);
void downdate(LMatrix& M, S_Stack& solution, H_Stack& history);


void Exact_Cover_Solver(bool **matrix, int m, int n, bool *solution_rows) throw (std::string)
{   
    {
        while(!solution.empty()) {
            solution_rows[solution.pop()] = 1;
        }
    }
    LMatrix M = LMatrix(matrix, m, n);
    S_Stack solution = S_Stack();
    H_Stack history = H_Stack();
    if( DLX(M, solution, history) ) {
        for(int i=0; i < m; i++) solution_rows[i] = 0;
        while(!solution.empty()) {
            solution_rows[solution.pop()] = 1;
        }
        //return solution_rows;
    } else throw "No solution exists";
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
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history)
{
    Column *c = choose_column(M);
    // 'M' is empty => solution successfully found
    if( c == NULL ) { 
        return 1;
    }
    for( Node *r = c->down(); r != static_cast<Node*>(c); r = r->down() ) {
        update_matrix(M, solution, history, r);
        if( DLX(M, solution, history) ) { 
            return 1;     
        } else {
            downdate_matrix(M, solution, history);
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
    
    Node* node = (M.head())->right();
    Column* max_col = static_cast<Column>(node);
    Column* c;
    while( node != M.head() )
    {
        if( (c=static_cast<Column>(node))->size() > max_col->size() ) {
            max_col = c;
        }
        node = node->right();
    }
    return max_col;
}

/*
 * 
 */
void update(LMatrix& M, S_Stack& solution, H_Stack& history, const Node *r) 
{
    solution.push(r->data().row_id);
    
    RC_Stack temp_stack = RC_Stack();
    RC_Item temp_item;
    Node *j = r;
    do {
        Node *i = j;
        do {
            M.remove_row(i);
            temp_item.node = i;
            temp_item.type = _row_;
            temp_stack.push(temp_item);
            i = i->up();
        } while( i != j );
        M.remove_column(j);  // could be NULL ?
        temp_item.node = j;
        temp_item.type = _column_;
        temp_stack.push(temp_item);
        j = j->right();
    } while( j != r);
    
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
    solution.pop();
    RC_Stack last = history.top();
    RC_Item it;
    do {
        it = last.top();
        if( it.type == _row_ ) {
            M.restore_row(it.node);
        } else if( it.type == _column_ ) {
            M.restore_column(it.node);
        }
        last.pop();
    } while( !last.empty() );
    history.pop();
}
