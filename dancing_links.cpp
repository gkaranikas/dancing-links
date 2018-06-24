#include <iostream>
#include "linkedlists.h"

#include "dancing_links.h"

/** 
 *  an implementation of Donald Knuth's Dancing Links algorithm
 *  https://arxiv.org/pdf/cs/0011047.pdf
 *  https://en.wikipedia.org/wiki/Dancing_Links
 */

using myNode = Node<int>;
using Stack = Node<myNode *>;

myNode * convert_matrix(bool **a) {
// a is a pointer to a row of columns of a 0-1 matrix, representing the exact cover problem
    
}

void DLX(myNode *h, myNode *soln, Stack *history) {
    Col *c = choose_col(h);
    if(c == NULL) { return; }  // no columns left.  solution successfully found
    for( myNode *r = c->head(); ; r = r->down() ) {
        update_matrix(h, soln, r);
        DLX(h, soln, history);
        if( h->size == 0) { return; }    // matrix is empty; solution found
        
        
        if(r->down() == c->head() ) {break;}
    }
    // if a column remains in the matrix h (and is therefore unaccounted for by the current solution soln),
    // but no rows remain available, then backtrack
    if( ) {
        backtrack(h, soln, history);
    }
    
    
}


void update_matrix(myNode *h, myNode *soln, myNode *r) {
    soln->add(r);
    for(myNode *j = r; ; j = j->right()) {
        for(myNode *i = j; ; i = i->up()) {
            remove_row(h, i);
            if( i->up() == j ) {break;}
        }
        remove_col(h,j);  // could be NULL ?
        if( j->right() == r ) {break;}
    }
}

void backtrack(myNode *h, myNode *soln, Stack *history) {
    soln->remove(r);
    for(myNode *j = r->left(); ; j = j->left()) {
        add_col(h,j)
        for(myNode *i = j->down(); ; i = i->down()) {
            add_row(h, i);
            if( i->up() == j ) {break;}
        }
        if( j->right() == r ) {break;}
    }
}


void remove_row(myNode *h, myNode *i) {
    for(myNode *k = i; ; k = k->right()) {
        remove_vert(k);
        if( k->right() == i ) {break;}
    }
}

void remove_column(myNode *h, myNode *i) {
    for(myNode *k = i; ; k = k->down()) {
        remove_hor(k);
        if( k->down() == i ) {break;}
    }
}