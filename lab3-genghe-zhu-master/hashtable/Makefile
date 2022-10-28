# Makefile for 'hashtable' module
#
# CS50, Summer 2020

PROG = hashtabletest
OBJS = hashtabletest.o hashtable.o jhash.o ../set/set.o ../lib/readlinep.o ../lib/memory.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../lib/readlinep.h ../set/set.h
hashtable.o: hashtable.h ../set/set.h
jhash.o: jhash.h
readline.o: ../lib/readlinep.h
set.o: ../set/set.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: $(PROG) test.names
	./$(PROG) < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: $(PROG) test.names
	valgrind ./$(PROG) < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

