# Makefile for creator.c
#
# Need common.a libraries before running make
#
# Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams

CC = gcc

# add -DDEBUG_FLAG for log debugging statements
# (and run `make clean; make` whenever you change this)
FLAGS = #-DUNIT_TEST #-DDEBUG_FLAG  

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$(C)
PROG = creator
OBJS = creator.o
PROGCUBE = cubecreator
OBJSCUBE = cubecreator.o
C = ../common
LIBS = $(C)/common.a

.PHONY: clean

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -lm

$(PROGCUBE): $(OBJSCUBE)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -lm

# clean up after our compilation
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f core
