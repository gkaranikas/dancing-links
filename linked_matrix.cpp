#include <iostream>   // for 'DEBUG_display()'
#include "linked_matrix.h"
#include <cassert>    // for 'DEBUG_display()'

using std::endl;

namespace linked_matrix_GJK
{

/*****************************************************************************************************
 * implementation of class LMatrix
 */
    
LMatrix::LMatrix(void) : root( new MNode( MData() ) )
{   
    // make root->down_link constant somehow
    join_lr(root, root);
    row_count = 0;
}

LMatrix::LMatrix(bool **matrix, int m, int n) : root( new MNode( MData() ) )
{   
    if( m == 0 || n == 0 ) {
        row_count = 0;
        return;
    }
    // create first column
    MNode *c = new Column(0);
    //c->data().column_id = static_cast<Column*>(c);        // point column object to itself
    join_lr(root,c);
    // create column header objects
    for(int j = 1; j < n; j++) {
        join_lr(c, new Column(0) );
        c = c->right();
        //c->data().column_id = static_cast<Column*>(c);
    }
    join_lr(c,root);
    
    // initialize m x n array of MNode pointers
    MNode ***ptr_matrix = new MNode**[m];
    for(int k = 0; k < m; k++) {
        ptr_matrix[k] = new MNode*[n];
    }
    
    // create nodes of LMatrix, referenced by pointers in ptr_matrix
    // also link the nodes vertically
    MNode *tmp;
    c = root->right();
    // j = column of matrix, i = row of matrix
    for( int j = 0; j < n; j++, c = c->right() ) {
        tmp = c;
        for(int i = 0; i < m; i++) {
            if(matrix[i][j]) {
                ptr_matrix[i][j] = new MNode(MData(i,static_cast<Column*>(c)));
                join_du(ptr_matrix[i][j], tmp);
                tmp = ptr_matrix[i][j];
                (static_cast<Column *>(c))->add_to_size(1);
            } 
            else ptr_matrix[i][j] = NULL;
        }
        join_du(c, tmp);
    }
    
    // ignore zero rows at the bottom of the matrix
    int i;
    bool zero_row;
    for(i=m-1; i >= 0; i--) {
        zero_row = 1;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j]) {
                zero_row = 0;
                break;
            }
        }
        if(!zero_row) break;
    }
    
    // 'i' is now the index of the last non-zero row, or -1 if there are no non-zero rows
    row_count = i + 1;

    
    // link the nodes horizontally
    MNode * first, *prev;
    // i = row, j = column
    for(; i >= 0; i--) {
        first = NULL;
        for(int j = 0; j < n; j++ ) {
            // find first non-zero matrix entry in row i,
            // and make 'first' point to the corresponding node
            if(ptr_matrix[i][j] != NULL) {
                if( first == NULL) {
                    first = ptr_matrix[i][j];
                } else {
                    join_lr(prev, ptr_matrix[i][j]);
                }
                prev = ptr_matrix[i][j];
            }
        }
        if(first != NULL) {  // if row i is not a zero row
            join_lr(prev, first);
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

MNode* LMatrix::head() const
{
    return root;
}

bool LMatrix::is_trivial() const
{
    return root->right() == root && root->left() == root;
}

int LMatrix::number_of_rows() const
{
    int num = 0;
    for(MNode *node = root->right(); node != root; node = node->right() ) {
        if(static_cast<Column*>(node)->size() > num) num = static_cast<Column*>(node)->size();
    }
    return num;
}


void LMatrix::remove_row(MNode * node)
{   
    if(node == NULL || node == root || node->data().column_id == node ) return;
    MNode *k = node;
    do {
        join_du( k->down(), k->up() ); 
        k->data().column_id->add_to_size(-1);
        k = k->right();
    } while( k != node ); // stop when we're back where we started
}



void LMatrix::restore_row(MNode * node)
{
    MNode *k = node;
    do {
        k->up()->set_down(k);  // connect row back
        k->down()->set_up(k);  // into the matrix
        k->data().column_id->add_to_size(1);
        k = k->left();
    } while( k != node );
}




void LMatrix::remove_column(MNode * node)
{   
    if(node == NULL || node == root ) return;
    MNode *k = node;
    do {
        join_lr( k->left(), k->right() ); 
        k = k->up();
    } while( k != node ); // stop when we're back where we started
}


void LMatrix::restore_column(MNode * node)
{
    MNode *k = node;
    do {
        k->right()->set_left(k);
        k->left()->set_right(k);
        k = k->down();
    } while( k != node );
}


LMatrix::~LMatrix()
{
    MNode *a, *b, *del;
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



void LMatrix::DEBUG_display(std::ostream& ofs)
{   
    const char l = '>';
    const char d = '<';
    const char r = '<';
    const char u = '>';
    const char H = 'H';
    const char C = 'C';
    const char N = 'N';
    const char ind = '\t';
    const char sp = ' ';
    ofs << ind << "ROW DIAGRAM" << endl << endl;
    
    ofs << ind;
    ofs << l << H << r;

    MNode *node = root->right();
    assert( node->left() == root );
    while( node != root ) {
        assert( node->data().row_id == -1 );
        assert( node->right() != NULL );
        assert( node == node->right()->left() );
        ofs << l << C << r;
        node = node->right();
    }
    ofs << ind << ind << "row " << -1 << endl;
    
    int rownum = 0;
    MNode *colhead;
    MNode *prev, *first;
    while(rownum < row_count ) {
        ofs << ind << sp << sp << sp;
        colhead = root->right();
        prev = NULL;
        while(colhead != root) {
            node = colhead->down();
            while(node != colhead && node->data().row_id != rownum) {
                assert(node != NULL);
                assert(node->down() != NULL);
                assert(node->down()->up() == node);
                assert(node->data().column_id == colhead);
                node = node->down();
            }
            if(node == colhead) {
                ofs << sp << sp << sp;
            } else if(node->data().row_id == rownum) {
                if(prev != NULL) {
                    assert(prev->right() == node);
                    assert(node->left() == prev);
                } else {
                    first = node;
                }
                ofs << l << N << r;
                prev = node;
            }
            colhead = colhead->right();
        }
        if(prev != NULL) {
            assert(prev->right() == first);
            assert(first->left() == prev);
        }
        ofs << ind << ind << "row " << rownum << endl;
        rownum++;
    }
    
    ofs << endl << endl;
    ofs << ind << "COLUMN SIZES" << endl << endl;
    ofs << ind;
    node =root->right();
    while(node != root) {
        ofs << l << static_cast<Column*>(node)->size() << r;
        node = node->right();
    }
    ofs << endl;
}


/*****************************************************************************************************
 * implementation of MNode_t operations
 */

template<class T>
void join_lr(MNode_t<T> *a, MNode_t<T> *b)
{   
    a->set_right(b);
    b->set_left(a);
}

template<class T>
void join_du(MNode_t<T> *a, MNode_t<T> *b)
{
    a->set_up(b);
    b->set_down(a);
}


}