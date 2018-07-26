#ifndef LINKED_MATRIX_H
#define LINKED_MATRIX_H

#include <iostream>

/*!
 * @file linked_matrix.h
 * 
 * Definition of \ref LMatrix, \ref MNode, and \ref Column classes.
 *
 */

/**
 * 
 */
namespace linked_matrix_GJK
{

template<class T>
class MNode_t;

class Column;

//! Identifies location of a node within a matrix
class MData
{
public:
    MData(int r=-1, Column *c=NULL) : row_id(r), column_id(c) {}
    int row_id;  //!< A number identifying the row
    Column *column_id; //!< A pointer to the column header
};

typedef MNode_t<MData> MNode;


/**
 * \brief Implementation of a matrix as a linked data structure.
 * 
 * An efficient implementation of a boolean matrix, used in a solution of the Exact Cover Problem.
 * This implementation only stores non-zero entries, and is especially suitable for sparse matrices.
 * Moreover, rows and columns are represented as circular doubly linked lists, so as to be naturally
 * amenable to the so-called ``Dancing Links'' algorithm of D. Knuth. 
 * 
 * The following is a helpful illustration of the LMatrix data structure taken from [this article](https://arxiv.org/pdf/cs/0011047.pdf) by Knuth.
 * ![An image of a linked matrix](/C:/Users/GJK/OneDrive/Documents/Projects/Sudoku/linked_matrix_image_(Knuth).png)
 * 
 * @see dancing_links.h, \ref Exact_Cover_Solver
 */
class LMatrix
{
public:
    LMatrix(); //!< Creates an empty matrix.
    /**
     * @brief Converts a standard boolean matrix to \ref LMatrix form.
     * @param matrix A boolean matrix.
     * @param m The number of rows in @p matrix.
     * @param n The number of columns in @p matrix.
     */
    LMatrix(bool **matrix, int m, int n);
    MNode* head() const; //!< \return the head node of the matrix (see the top-level class description).
    bool is_trivial() const; //!< \return 1 if the matrix is empty (ie consists only of a head node), 0 otherwise.
    int num_rows() const;
    /**
     * @brief Removes the row containing @p node.
     * @param node A node which is not a column header.
     * 
     * Does not alter any links belonging to elements in the row.
     */
    void remove_row(MNode *node);
    void restore_row(MNode *node);
    void remove_column(MNode *node);
    void restore_column(MNode *node);
    ~LMatrix();
private:
    MNode *root;
    int row_count;
};

/**
 * @brief Displays a matrix in ascii format, which is useful for debugging.
 * @param M The matrix to be displayed.
 * @param out_stream The output stream of the display.
 * 
 * Each line of the display corresponds to a row of @p M and ends with the row number.  Empty rows are included.
 * The head <tt>M.head()</tt> is represented by the symbol `H', column headers by the symbol `C', and all
 * other nodes (ie non-zero matrix entries) by `N'.  Left and right links are represented by the symbols 
 * `<' and `>' respectively, 
 * and each row is understood to wrap into a circular list.
 * 
 * As an example, the matrix
 * 
        1 0 1
        0 0 0
        0 1 1
 * 
 * when converted to type LMatrix, will be displayed as
 * 
         >H<>C<>C<>C<    row -1
            >N<   >N<    row 0
                         row 1
               >N<>N<    row 2

 * 
 * Multiple @c assert statements will be made during the process of creating the display.  These
 * will check the structure of the matrix @p M (including the up/down links, which are not displayed).
 */
void DEBUG_display(LMatrix& M, std::ostream& out_stream=std::cout);

/**
 * \brief A node containing data of variable type @c T and four links to other nodes - left, right, up and down.
 *
 */
template<class T>
class MNode_t
{
public:
    MNode_t(const T& theData, MNode_t<T> *theRight = NULL, MNode_t<T> *theLeft = NULL,
          MNode_t<T> *theUp = NULL, MNode_t<T> *theDown = NULL) 
          : _data(theData), right_link(theRight), left_link(theLeft), up_link(theUp), down_link(theDown) {}
    void set_data(const T& theData) {_data = theData;} //!< Sets the node's data to @p theData.
    T& data() const {return const_cast<T&>(_data);} //!< \return the data object. 
    // don't know why I have to cast the argument, but compiler otherwise complains
    MNode_t<T> * right() const {return right_link;} //!< \return the right link.
    MNode_t<T> * left() const {return left_link;} //!< \return the left link.
    MNode_t<T> * up() const {return up_link;} //!< \return the up link.
    MNode_t<T> * down() const {return down_link;} //!< \return the down link.
    void set_right(MNode_t<T> *node) {right_link = node;} //!< Points the right link to @c node.
    void set_left(MNode_t<T> *node) {left_link = node;} //!< Points the left link to @c node.
    void set_up(MNode_t<T> *node) {up_link = node;} //!< Points the up link to @c node.
    void set_down(MNode_t<T> *node) {down_link = node;} //!< Points the down link to @c node.
private:
    T _data;
    MNode_t<T> *right_link;
    MNode_t<T> *left_link;
    MNode_t<T> *up_link;
    MNode_t<T> *down_link;
};


/*!
 * \brief A type of \ref MNode which acts as a header for a column
 *
 * The \ref MData#row_id is set to -1 and \ref MData#column_id points to the object itself.
 * \ref Column objects also store the size of their column, which can be accessed via member functions.
 */
class Column : public MNode
{
public:
    Column(int theSize=0) 
        : MNode(MData(-1,this)), _size(theSize) {}
    int size() const {return _size;} //!< returns the number of nodes in the column.
    void set_size(int N) {_size = N;} //!< sets the number of nodes in the column to @p N.
    void add_to_size(int N) {_size += N;} //!< Adds @p N to the number of nodes in the column.
private:
    int _size;
};


/**
 * @brief Joins two nodes together horizontally.
 * 
 * Sets the right link of @p a to @p b and the left link of @p b to @p a.
 * Assumes neither @p a nor @p b point to @c NULL.
 */
template<class T>
void join_lr(MNode_t<T> *a, MNode_t<T> *b);

/**
 * @brief Joins two nodes together vertically.
 * 
 * Sets the up link of @p a to @p b and the down link of @p b to @p a.
 * Assumes neither @p a nor @p b point to @c NULL.
 */
template<class T>
void join_du(MNode_t<T> *a, MNode_t<T> *b);


} // end namespace 'linked_matrix_GJK'
#endif