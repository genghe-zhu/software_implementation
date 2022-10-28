
PROG = solver
PROGCUBE = solvecube
OBJS = solver.o
OBJSCUBE = solvecube.o
LIBS = ../common/common.a 


# uncomment the following to turn on verbose memory logging
TESTING = #-DUNIT_TEST #-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
VFLAGS = --leak-check=full --show-leak-kinds=all
CC = gcc
MAKE = make

.PHONY: all test valgrind clean

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

$(PROGCUBE): $(OBJSCUBE)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

all: $(PROGCUBE) $(PROG) 
#all: $(PROG) $(PROGTEST)

# expects a file `test.names` to exist; it can contain any text.

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)


