# Makefile for sudoku executable
#
# Need ... before running make
#
# Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams

CC = gcc

# add -DDEBUG_FLAG for log debugging statements
# (and run `make clean; make` whenever you change this)
FLAGS = #-DUNIT_TEST #-DDEBUG_FLAG  

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$(Co)
VFLAGS = --leak-check=full --show-leak-kinds=all
PROG = sudoku
OBJS = sudoku.o $(C)/creator.o $(C)/cubecreator.o $(S)/solver.o $(S)/solvecube.o
S = solver
C = creator
Co = common
LIBS = $(Co)/common.a

.PHONY: valgrind clean test

# Need to comment out -DUNIT_TEST flag for solver and creator before running make
# executable depends on object files
$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(Co)/common.a:
	make -C common

# object files deoend on header files
creator.o: $(C)/creator.h
solver.o: $(S)/solver.h
solvecube.o: $(S)/solvecube.h
cubecreator.o: $(C)/cubecreator.h
	
valgrind: 
	valgrind $(VFLAGS) ./$(PROG) solve

# clean up after our compilation
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f core
	make -C common clean
	rm -f puzzle.txt

test: testing.sh
	bash testing.sh &> testing.out 
