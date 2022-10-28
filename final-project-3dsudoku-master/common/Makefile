# Makefile for common library
#
# Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams

# object files, and the target library
OBJS = common.o memory.o file.o cube.o
LIB = common.a	

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
common.o: common.h
memory.o: memory.h
file.o: file.h
cube.o: cube.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
