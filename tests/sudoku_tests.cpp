#include "../sudoku_solver.h"

#include <ctime>
#include <cstring>

#define NUM_TESTS 3

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


void run_test_9x9(char *flat_grid_str, char *flat_grid_str_solved)
{
    sudoku_GJK::Sudoku<3> Sdku(flat_grid_str);
    std::cout << "Problem:\n";
    Sdku.display_ASCII();
    std::cout << "Solving . . .\n";
    std::clock_t start = std::clock();
    Sdku.solve();
    std::clock_t end = std::clock();
    std::cout << "Solution:\n";
    Sdku.display_ASCII();
    std::cout << "Elapsed time = " << 1000.0 * (end-start)/CLOCKS_PER_SEC << " ms" << " (CPU time)\n";
    
    sudoku_GJK::Sudoku<3> Sdku_solved(flat_grid_str_solved);
    assert( Sdku == Sdku_solved );

}


void test_0()
{    
    // from the wikipedia sudoku page https://en.wikipedia.org/wiki/Sudoku
    // accessed 27th August 2018
    char puzzle_wkp[82] = 
    "530070000600195000098000060800060003400803001700020006060000280000419005000080079";
   //000000000000000000000000000000000000000000000000000000000000000000000000000000000  ---  81 0's, for alignment
    
    char puzzle_wkp_solved[82] = 
    "534678912672195348198342567859761423426853791713924856961537284287419635345286179";
    
    run_test_9x9(puzzle_wkp,puzzle_wkp_solved);
}


void test_1()
{
    // from http://www.fiendishsudoku.com/ - fiendish puzzle for 6th August 2018
    // 'degree of difficulty' not correlated with brute-force solving time
    char puzzle_f060818[82] = 
    "003050100060000080800090004000206000402000805000501000500060003030000020004070500";
   
    char puzzle_f060818_solved[82] = 
    "943658172165724389827193654758246931412937865396581247571862493639415728284379516";
    
    run_test_9x9(puzzle_f060818,puzzle_f060818_solved);
}

void test_2()
{   
    // a sudoku with only 17 clues (and diagonal symmetry incidentally)
    // from https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
    // accessed 27th August 2018
    char puzzle_17clue[82] = 
    "000000001000000023004005000000100000000030600007000580000067000010004000520000000";
    
    char puzzle_17clue_solved[82] = 
    "672983451951476823384215976468159237295738614137642589843567192719824365526391748";
    
    run_test_9x9(puzzle_17clue,puzzle_17clue_solved);
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/


typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_0,
&test_1,
&test_2
};

// run all tests
int main() {
    bool TESTS[NUM_TESTS];  // will determine whether a given test is to be run or omitted
    for(int i = 0; i < NUM_TESTS; i++) TESTS[i] = 1;
    
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}