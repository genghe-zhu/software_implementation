# Makefile for 'indexer' module
#
# CS50, Summer 2020

PROG = indexer
OBJS = indexer.o 
PROGTEST = indextest
OBJSTEST = indextest.o 
LIBS = ../common/common.a  ../libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
VFLAGS = --leak-check=full --show-leak-kinds=all
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROGTEST): $(OBJSTEST)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

all: $(PROG) $(PROGTEST)

.PHONY: all test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: 
	./$(PROG) ../data index.txt
	./$(PROGTEST) index.txt index.new

valgrind: 
	valgrind $(VFLAGS) ./$(PROG) ../data index.txt
	valgrind $(VFLAGS) ./$(PROGTEST) index.txt index.new


clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

