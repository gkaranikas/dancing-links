#ifndef DANCING_LINKS_H
#define DANCING_LINKS_H

/** \file dancing_links.h
    \brief Definitions of \ref Exact_Cover_Solver() and \ref DLX().
 */

//! Home of the Exact Cover Problem solver based on the dancing links algorithm.
namespace dancing_links_GJK
{

using linked_matrix_GJK::MNode;
using linked_matrix_GJK::LMatrix;
using linked_matrix_GJK::Column;

typedef std::vector<int> S_Stack;


enum class RC {row, column};
/**
 \brief Holds the data of a row or column removal (of a matrix determined by context).
 
        Whether a row or column was removed is determined by \ref RC_Item#type.
        The field \ref RC_Item#node records the node which was passed to \ref LMatrix#remove_row or \ref LMatrix#remove_column.
 */
struct RC_Item {
    MNode* node;
    RC type;
};

//! Each \ref RC_Stack is to hold the data accumulated by a single call to \ref update().
typedef std::stack<RC_Item> RC_Stack;
/**
    \brief A class used to represent the history of a solution finding process (depth first search).

 */
typedef std::stack<RC_Stack> H_Stack;


/**
 * @brief Solves the exact cover problem for a boolean matrix @p matrix.
 * @param matrix A boolean matrix.
 * @param m The number of rows.
 * @param n The number of columns.
 * @return a solution of the exact cover problem in the form of a vector of row indices.
 * 
 * Converts @p matrix to an \ref LMatrix object and calls \ref DLX().
 * 
*/
std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n);

std::vector<int> Exact_Cover_Solver(LMatrix& M);

/**
 * @brief Recursively solves the exact cover problem using the *dancing links* algorithm of Donald Knuth.
 * @param M The matrix.  It is modified during execution.  If a solution is found, @p M will be the empty matrix
 *            at termination, otherwise it will be unmodified.
 * @param solution At termination, holds the row indices of a solution
 *                  if one exists, otherwise is unmodified.
 * @param history At termination, holds the sequence of row and column deletions
 *                  traversed in finding the solution if one exists, otherwise is unmodified.  See \ref H_Stack.
 * @return 1 if a solution exists, 0 otherwise.
 * 
 * 
 * This procedure implements **Algorithm X**, an obvious backtracking algorithm which can be found on [this wikipedia page](https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X).
 * In pseudocode:
 * 
 *       If the matrix A has no columns, the current partial solution is a valid solution; terminate successfully.
         Otherwise choose a column c (deterministically).
         Choose a row r such that Ar, c = 1 (nondeterministically).
         Include row r in the partial solution.
         For each column j such that Ar, j = 1,
             for each row i such that Ai, j = 1,
                 delete row i from matrix A.
             delete column j from matrix A.
         Repeat this algorithm recursively on the reduced matrix A
 */
bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history);


/**
 * @brief Column selector.
 * @param M a matrix.
 * @return a pointer to the column of @p M with the fewest nodes (ie smallest \ref Column#size() value).  If @p M is empty, return @c NULL.
 */
Column* choose_column(LMatrix& M);


/**
 * @brief Uses @p r to branch into the next step of Algorithm X, deleting the appropriate rows and columns of @p M.
 * @param M a matrix.
 * @param solution The deleted columns are pushed onto the back of this vector.
 * @param history The deleted rows and columns are pushed onto this stack.
 * @param r Indicates the row for the next branch.
 */
void update(LMatrix& M, S_Stack& solution, H_Stack& history, MNode *r);


/**
 * @brief Assumes \ref update() has just been called, and reverses the actions performed by \ref update().
 *
 * It is *very important* that neither @p M, @p solution, nor @p history have been modified since the last call
 * to \ref update().  If this condition is not met the behaviour is undefined.
 * 
 */
void downdate(LMatrix& M, S_Stack& solution, H_Stack& history);
    
    
}

#endif