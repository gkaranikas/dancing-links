#include <vector>
#include <stack>
#include "linked_matrix.h"
#include "dancing_links.h"
#include "sudoku_solver.h"

//#include "sudoku_solver.h"

namespace dancing_links_GJK
{

/** 
 *  an implementation of Donald Knuth's Dancing Links algorithm
 *  https://arxiv.org/pdf/cs/0011047.pdf
 *  https://en.wikipedia.org/wiki/Dancing_Links
 */




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
 
 
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history)
{
    Column *c = choose_column(M);
    // 'M' is empty => solution successfully found
    if( c == NULL ) { 
        return 1;
    }
    for( Node *r = c->down(); r != static_cast<Node*>(c); r = r->down() ) {
        update(M, solution, history, r);
        if( DLX(M, solution, history) ) { 
            return 1;     
        } else {
            downdate(M, solution, history);            
        }
    }
    // no solution exists
    return 0;
}

/* Given a matrix of linked nodes M, return a pointer to the column with the fewest nodes
 * If there are no columns, return NULL
 */
Column* choose_column(LMatrix& M)
{
    if( M.is_trivial() ) return NULL;
    
    Column* col = static_cast<Column*>(M.head()->right());
    Column* max_col = col;

    while( col != M.head() )
    {   
        if( col->size() < max_col->size() ) {
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
            temp_item.type = RC::row;
            temp_stack.push(temp_item);
        }
        M.remove_column(i);
        temp_item.node = i;
        temp_item.type = RC::column;
        temp_stack.push(temp_item);
    }
    
    for(Node *j = r->up(); j != r; j = j->up() ) {
        if(j->data().column_id == j) continue;
        M.remove_row(j);
        temp_item.node = j;
        temp_item.type = RC::row;
        temp_stack.push(temp_item);
    }
    M.remove_column(r);
    temp_item.node = r;
    temp_item.type = RC::column;
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
        if( it.type == RC::row ) {
            M.restore_row(it.node);
        } else if( it.type == RC::column ) {
            M.restore_column(it.node);
        }
        last.pop();
    }
    history.pop();
}


}