#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>

void Sudoku_Solver(int **grid, int size);

void Sudoku_Solver_9x9(int **grid);

void Exact_Cover_Solver(bool **matrix, int m, int n, bool *solution_rows) throw (std::string);

#endif