# Makefile for 'querier' module
#
# Genghe Zhu
# CS50, Summer 2020

PROG = querier
OBJS = querier.o 
#PROGTEST = fuzzquery
#OBJSTEST = fuzzquery.o
LIBS = ../common/common.a  ../libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
VFLAGS = --leak-check=full --show-leak-kinds=all
CC = gcc
MAKE = make

.PHONY: all test valgrind clean

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

#$(PROGTEST): $(OBJSTEST)
	#$(CC) $(CFLAGS) $^ $(LIBS) -o $@

all: $(PROG) 
#all: $(PROG) $(PROGTEST)


# expects a file `test.names` to exist; it can contain any text.
test: 
	./$(PROG) ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-6

valgrind: 
	valgrind $(VFLAGS) ./$(PROG) ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-6 


clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

