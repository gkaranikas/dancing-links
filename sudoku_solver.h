#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include <vector>

void Sudoku_Solver(int **grid, int size);

void Sudoku_Solver_9x9(int **grid);

std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n);

#endif