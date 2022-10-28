# Makefile for socket examples
#
# Need common library before running make
#
# CS 50, Summer 2020

PROGS = solverclient creatorserver-fork

FLAGS = #-DDEBUG_FLAG #-DUNIT_TEST  
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$(Co)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
S = ../solver
C = ../creator
Co = ../common
LIBS = $(Co)/common.a

.PHONY: all clean

all: $(PROGS)

########### inclient ##################
solverclient: solverclient.o $(S)/solver.o $(S)/solvecube.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

solverclient.o: 

########### inserver-fork #################
creatorserver-fork: creatorserver-fork.o $(C)/creator.o $(S)/solver.o $(S)/solvecube.o $(C)/cubecreator.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

creatorserver-fork.o: 

# object files deoend on header files
creator.o: $(C)/creator.h
solver.o: $(S)/solver.h
solvecube.o: $(S)/solvecube.h
cubecreator.o: $(C)/cubecreator.h

$(Co)/common.a:
	make -C $(Co)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROGS)
	make -C $(Co) clean
	rm -f core
	rm -f puzzle.txt
