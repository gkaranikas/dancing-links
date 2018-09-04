/*  
    Copyright (C) 2018  Gregory J. Karanikas.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <vector>
#include <cassert>

/** \mainpage
    Contents of README.md
 */

/**
    \file sudoku_solver.h
    \brief Functions for converting sudoku to exact cover problems and solving sudoku.
     * 
     * Requires <tt><cassert></tt>.
     * 
     * The following terminology is helpful in reading the documentation as well as the source code.  A sudoku 
     * is an *n<sup>2</sup>* by *n<sup>2</sup>* grid (where *n<sup>2</sup>* is the **size** of the sudoku), 
     * each **cell** of which holds a **value**.  A cell is specified by **row** and **column** indices, each
     * ranging from *1* to *n<sup>2</sup>*.  A value can be any number from *1* to *n<sup>2</sup>*, or the value
     * *0* which represents a blank cell.  A **triple** consists of a cell plus a value.  A **square** is an
     * *n* by *n* sub-grid (thus a sudoku has *n* squares).
 */

/**
    \brief Contains the Sudoku class.
 */
namespace sudoku_GJK
{


/** \brief Wrapper class for @c int's in the range <tt>0 . . size</tt>
 * 
 * Is used to represent row indices, column indices, and values in a sudoku.
 */
template<int size>
class num_t {
public: 
    num_t(int n=0) : _n(n) { assert(0<=n && n<=size); } //!< Converts @c int to \ref num_t, checking that number is in range
    bool is_blank() const {return _n == 0;}  //!< Whether the object represents a blank/undetermined value (=0)
    operator int() const { return _n; }     //!< Operator for conversion to @c int
    num_t & operator=(const num_t & rhs) { _n = rhs._n; return *this;}
private:
    int _n;
};


/**
 * @brief Represents a sudoku triple.
 */
template<int sqrt_of_size>
struct Triple {
private:
    static const int size = sqrt_of_size*sqrt_of_size;
public:
    num_t<size> row;
    num_t<size> column;
    num_t<size> value;
    Triple(int r, int c, int v) : row(num_t<size>(r)), column(num_t<size>(c)), value(num_t<size>(v)) {};
    int to_index();
    /**
     * @brief Inverse of function \ref to_index(). 
     */
    Triple(int index);
/** \brief  Returns 1 if the triple belongs to @p square
 *      
 * Squares are numbered from left to right and descending. 
 * So @p square = @c s = @c a + @c b &times; @c sqrt_of_size, where @c a and @c b are illustrated
 * in the example below.
 *
 *               EXAMPLE.
 *      sqrt_of_size = 3, size = 9
 * 
 *          a = 1, 2, 3
 *      ___________________
 *      | s=1 | s=2 |  3  |     b
 *      |_____|_____|_____|     =
 *      |  4  |  5  |  6  |     0,
 *      |_____|_____|_____|     1,
 *      |  7  |  8  |  9  |     2
 *      |_____|_____|_____|
 *
 * 
 *      Which square is the triple (4,6,9) in?
 *      a = 2, b = 1
 *      => s = 2 + 3*1 = 5
 * 
 */
    bool is_in_square(num_t<size> square);
};


/**
 * @brief Represents a sudoku puzzle.
 */
template<int sqrt_of_size>
class Sudoku {
public:
    Sudoku();
    //Sudoku(int s, Iterable data);
    /**
     * @brief Only for 9x9 sudokus ( @c sqrt_of_size = 3).
     * @param flat_grid_str A C string representing the sudoku grid in row contiguous format.
     * 
     * \todo add constructor for sizes other than 9 (not necessarily with string input)
     */
    Sudoku(char *flat_grid_str);
    //! \returns the entry at position `(row,col)` in the sudoku grid.
    num_t<sqrt_of_size*sqrt_of_size> get_entry(
                                                num_t<sqrt_of_size*sqrt_of_size> row, 
                                                num_t<sqrt_of_size*sqrt_of_size> col) 
                                    { return grid[row-1][col-1]; }
    //! Writes the data in @p triple to the sudoku grid.
    void write(Triple<sqrt_of_size> triple);      //!< \todo change to array Triple<sqrt_of_size>[]
    bool found(Triple<sqrt_of_size> triple);      //!< \return 1 if @p triple is found, 0 otherwise
    //! Equality of cell values.
    bool operator==(const Sudoku<sqrt_of_size>& other) {
        for(int i=0;i<9;i++) {
            for(int j=0;j<9;j++) {
                if( (int)grid[i][j] != (int)other.grid[i][j]) return false;
            }
        } return true;
    }
    /** \brief Perform logical operations to partially solve a sudoku
     * 
     * \todo Implement this method.
     */
    void logic_solve();
/**
 * @brief Solves the sudoku puzzle
 *
 * Converts the sudoku to an Exact Cover Problem represented by a \ref linked_matrix_GJK::LMatrix
 * and calls \ref dancing_links_GJK::Exact_Cover_Solver(linked_matrix_GJK::LMatrix&).
 */
    void solve();
/**
 \brief Displays the sudoku using ASCII characters.

The format is demonstrated in the following sample output:

```
        =========================
        |       |   5 8 | 1 7   |
        |       |     4 |       |
        | 8   7 | 1     |       |
        =========================
        | 7 5   |     6 | 9 3 1 |
        |       | 9   7 |     5 |
        |   9   |   8 1 | 2     |
        =========================
        | 5 7   |   6   |   9 3 |
        |       |       | 7   8 |
        |     4 | 3 7   | 5     |
        =========================
```

     */
    void display_ASCII() const;
    ~Sudoku();
private:
    static const int size = sqrt_of_size*sqrt_of_size;
    num_t<size> **grid;
    void get_ECP_matrix(bool** matrix);
    void convert_ECP_solution(std::vector<int> solution);
};


} //end namespace 'sudoku_GJK'


#include "sudoku_solver.tpp"

#endif