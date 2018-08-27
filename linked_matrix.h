#ifndef LINKED_MATRIX_H
#define LINKED_MATRIX_H


/** \file linked_matrix.h
 *  \brief Definition of classes \ref linked_matrix_GJK::LMatrix "LMatrix", 
 \ref linked_matrix_GJK::MNode "MNode", and \ref linked_matrix_GJK::Column "Column".
  * 
  * Requires <tt><iostream></tt>.
 */

/*!    \brief Definition and implementation of \ref LMatrix, \ref MNode, and \ref Column.
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

//! The default matrix node used in this project.
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
 * ![An image of a linked matrix](/C:/Users/GJK/OneDrive/Documents/Projects/Sudoku/images/linked_matrix_image_(Knuth).png)
 * 
 * The data structure consists of a *root* or *head* node (got by calling \ref head() ) which is linked to the
 * *column headers* (objects of type \ref Column ), each of which represents a column of the matrix and whose
 * \ref Column#size() records the number of 1's in that column. Each 1 is represented by an object of type
 * \ref MNode, and each row and column (including the header) is a circular doubly linked list.
 * 
 * For each node, \ref MData#column_id points to the column header, and \ref MData#row_id is the row index.  The
 * values of the row index are determined by the matrix passed as an argument to the constructor - gaps in the
 * row index values of an \ref LMatrix reflect zero rows in the original matrix.  For
 * column headers, \ref MData#row_id = -1.  Also for \ref head(), \ref MData#column_id = @c NULL.  
 * 
 * @see dancing_links.h, \ref dancing_links_GJK::Exact_Cover_Solver
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
    MNode* head() const; //!< \return the head node of the matrix (see the detailed class description).
    bool is_trivial() const; //!< \return 1 if the matrix is empty (ie consists only of a head node), 0 otherwise.
    int number_of_rows() const; //!< \return the number of rows (equivalently, the maximum column size).
    /**
     * @brief Removes the row containing the node @p node.
     * @param node A node of the matrix.
     * 
     * Does not alter any left, right, up or down links belonging to nodes in the row.  If the matrix is empty 
     * or @p node is \ref head() or a column header, no action is taken.
     * 
     * \ref Column#size() values are updated, but \ref row_id values are **not** changed.
     */
    void remove_row(MNode *node);
    /**
     * @brief Undoes the action of \ref remove_row(node).
     * 
     * **Precondition** Neither the row containing @c node, nor the calling object have been altered since the
     * last call to \ref remove_row.
     */
    void restore_row(MNode *node);
    /**
     * @brief Removes the column containing the node @p node.
     * @param node A node of the matrix.
     * 
     * Removes the entire column, including the column header.  Does not alter any left, right, up or down links belonging to nodes in the column.  If @p node is \ref head(),
     * no action is taken.
     */
    void remove_column(MNode *node);
    /**
     * @brief Undoes the action of \ref remove_column(node).
     * 
     * **Precondition** Neither the column containing @c node, nor the calling object have been altered since the
     * last call to \ref remove_column.
     */
    void restore_column(MNode *node);
    ~LMatrix();
    /**
 * @brief Displays the matrix in ascii format, which is useful for debugging.
 * @param out_stream The output stream of the display.
 * 
 * Each line of the display corresponds to a row of the matrix and ends with the row number.  Empty rows are included.
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
         ROW DIAGRAM
         
         >H<>C<>C<>C<    row -1
            >N<   >N<    row 0
                         row 1
               >N<>N<    row 2

 * 
 * Multiple @c assert statements will be made during the process of creating the display.  These
 * will check the structure of the matrix (including the up/down links, which are not displayed).
 * 
 * Following the display of the matrix, the column sizes will be displayed in sequence.  For the above example,

         COLUMN SIZES
         
         >1<>1<>2<
          
will be displayed.  This can be used to check that the \ref Column#size() values are correct.
 */
    void DEBUG_display(std::ostream& out_stream=std::cout);
private:
    MNode *root;
    int row_count;      // 1 plus the index of the last nonzero row index of the ORIGINAL matrix
                        // set in the constructor and not ever modified
                        // only needed for DEBUG_display()
                        // note: if many rows have been deleted from the matrix, this could well be unnecessarily large.
};



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