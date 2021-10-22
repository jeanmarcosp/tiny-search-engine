# Makefile for common.a library
#   Builds and compiles all these utility functions into a library.
#
# David Kotz, April 2016, July 2017, April 2019, 2021
# updated by Xia Zhou, July 2016
# updated by Jeanmarcos Perez, October 2021

# object files, and the target library
OBJS = pagedir.o word.o index.o ../libcs50/webpage.h
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I../libcs50
CC = gcc
MAKE = make

$(LIB):	$(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o:	pagedir.h
word.o:		word.h
index.o:	index.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
