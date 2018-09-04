.PHONY: clean tests
#.PHONY: All

HFILES=linked_matrix.h dancing_links.h sudoku_solver.h sudoku_solver.tpp
CPPFILES=linked_matrix.cpp dancing_links.cpp


TESTDIR := ./tests
TESTS_NAMES := MNode_tests.cpp LMatrix_tests.cpp dancing_links_tests.cpp sudoku_tests.cpp
TESTS := $(addprefix $(TESTDIR)/,$(TESTS_NAMES))
TESTS_BIN := $(patsubst %.cpp,%,$(TESTS))

CC=g++
CFLAGS=-c

tests : $(TESTS_BIN)
	$(patsubst %,%;,$(TESTS_BIN))

tests_build : $(TESTS_BIN)

$(TESTDIR)/sudoku_tests : $(TESTDIR)/sudoku_tests.cpp \
			              linked_matrix.cpp dancing_links.cpp \
			              linked_matrix.h dancing_links.h sudoku_solver.h sudoku_solver.tpp
	$(CC) $< linked_matrix.cpp dancing_links.cpp -o $@

$(TESTDIR)/dancing_links_tests : $(TESTDIR)/dancing_links_tests.cpp dancing_links.cpp linked_matrix.cpp \
					             dancing_links.h linked_matrix.h
	$(CC) $< dancing_links.cpp linked_matrix.cpp -o $@

$(TESTDIR)/LMatrix_tests : $(TESTDIR)/LMatrix_tests.cpp linked_matrix.cpp linked_matrix.h
	$(CC) $< linked_matrix.cpp -o $@

$(TESTDIR)/MNode_tests : $(TESTDIR)/MNode_tests.cpp linked_matrix.cpp linked_matrix.h
	$(CC) $< linked_matrix.cpp -o $@

	
dancing_links.o : dancing_links.cpp dancing_links.h linked_matrix.h
	$(CC) $(CFLAGS) $<

linked_matrix.o : linked_matrix.cpp linked_matrix.h
	$(CC) $(CFLAGS) $<

clean :
	rm dancing_links.o linked_matrix.o $(TESTS_BIN)
	
#All:
#	@echo "----------Building project:[ Sudoku - Debug ]----------"
#	@"$(MAKE)" -f  "Sudoku.mk"
#clean:
#	@echo "----------Cleaning project:[ Sudoku - Debug ]----------"
#	@"$(MAKE)" -f  "Sudoku.mk" clean
