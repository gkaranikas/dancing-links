#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include <vector>

namespace sudoku_GJK
{
void Sudoku_Solver(int **grid, int sqrt_of_size);

void Sudoku_Solver_9x9(int **grid);
}

namespace dancing_links_GJK
{
std::vector<int> Exact_Cover_Solver(bool **matrix, int m, int n);
}

#endif