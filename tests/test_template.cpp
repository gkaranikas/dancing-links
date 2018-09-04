/* 
 *  A basic template for unit tests.
 * 
 */
 
#include <iostream>
#include <cassert>
#include <ctime>
// ******** INCLUDE HEADER FILES TO BE TESTED ***********


#define NUM_TESTS 3    // ********** TOTAL NUMBER OF TESTS DEFINED BELOW ****************


/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/

// ******** DEFINE ALL TESTS HERE *************



void test_0()
{
    
}

void test_1()
{
    
}

void test_2()
{
    
}

/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/





typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
&test_0,
&test_1,
&test_2
// ********** INCLUDE ALL TESTS HERE *************
};


int main() {
    bool TESTS[NUM_TESTS];  // will determine whether a given test is to be run or omitted
                            // for example, do "TEST[1] = 0" if you want to skip over 'test_1()'
    for(int i = 0; i < NUM_TESTS; i++) TESTS[i] = 1;

    // Run the chosen tests
	for(int i = 0; i < NUM_TESTS; i++) {
		if(TESTS[i]) {
			tests[i]();
            std::cout << "Test " << i << " passed!" << std::endl;
		}
	}
	return 0;
}