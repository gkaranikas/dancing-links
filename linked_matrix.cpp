#include "linked_matrix.h"

namespace linked_matrix_GJK
{

/*****************************************************************************************************
 * implementation of class LMatrix
 */
    
LMatrix::LMatrix(void) : root(new MNode0())
{   
    // make root->down_link constant somehow
    join_lr(root, root);
}

LMatrix::LMatrix(bool **matrix, int m, int n) : root(new MNode0())
{   
    // create first column
    MNode0 *c = new Column(0);
    join_lr(root,c);
    // create column header objects
    for(int j = 0; j < n; j++) {
        join_lr(c, new Column(0) );
        c = c->right();
    }
    join_lr(c,root);
    
    // initialize m x n array of MNode0 pointers
    MNode0 ***ptr_matrix = new MNode0**[m];
    for(int k = 0; k < m; k++) {
        ptr_matrix[k] = new MNode0*[n];
    }
    
    // create nodes of LMatrix, referenced by pointers in ptr_matrix
    // link the nodes vertically
    MNode0 *tmp;
    c = root->right();
    for( int j = 0; j < n; j++, c = c->right() ) {
        tmp = c;
        for(int i = 0; i < m; i++) {
            if(matrix[i][j]) {
                ptr_matrix[i][j] = new MNode0();
                join_du(ptr_matrix[i][j], tmp);
                tmp = ptr_matrix[i][j];
                (static_cast<Column *>(c))->set_size((static_cast<Column *>(c))->size()+1);
            } 
            else ptr_matrix[i][j] = NULL;
        }
        join_du(c, tmp);
    }
    
    // link the nodes horizontally
    MNode0 * first = NULL;
    for(int i = 0; i < m; i++) {
        tmp = ptr_matrix[i][0];
        for(int j = 1; j < n; j++ ) {
            if(tmp == NULL) {
                tmp = ptr_matrix[i][j];
                first = tmp;
                continue;
            } else if(ptr_matrix[i][j] != NULL) {
                join_lr(tmp, ptr_matrix[i][j]);
                tmp = ptr_matrix[i][j];
            } 
        }
        if(first != NULL) {  // if row i is not empty
            join_lr(tmp, first);
        }
    }
    
    // finished with ptr_matrix, so now delete it
    // note this doesn't delete the nodes of the new LMatrix, just their pointers which 
    // are stored in ptr_matrix
    for(int k = 0; k < m; k++) {
        delete[] ptr_matrix[k];
    }
    delete[] ptr_matrix;
    
}



void LMatrix::remove_row(MNode0 * node)
{
    // make error for header row
    for(MNode0 *k = node; ; k = k->right()) {
        k->up()->set_down(k->down());
        k->down()->set_up(k->up());
        if( k->right() == node ) {break;}  // stop when we're back where we started
    }
}


void LMatrix::restore_row(MNode0 * node)
{
    for(MNode0 *k = node; ; k = k->right()) {
        k->up()->set_down(k);
        k->down()->set_up(k);
        if( k->right() == node ) {break;}  // stop when we're back where we started
    }
}


LMatrix::~LMatrix()
{
    MNode0 *a, *b, *del;
    // a iterates through the column headers horizontally
    // b iterates through each column vertically
    a = root->right();
    while(a != root) {
        b = a->down();
        while(b != a) {
            del = b;
            b = b->down();
            delete del;
        }
        del = a;
        a = a->right();
        delete del;
    }
    delete root;
}


/***
 * Displays the matrix in a convenient visual form
 */
 /*
void LMatrix<T>::display(void)
{
	using std::cout;
	char node_sym = '*', hdash = '-', vdash = '|';
	// form 2d array char
	// fill array with symbols to be printed, by iterating over the nodes and using - & | for links
	// print array
}
*/
/*****************************************************************************************************
 * implementation of MNode operations
 */

template<class T>
void join_lr(MNode<T> *a, MNode<T> *b)
{
    a->set_right(b);
    b->set_left(a);
}

template<class T>
void join_du(MNode<T> *a, MNode<T> *b)
{
    a->set_up(b);
    b->set_down(a);
}


}