# Makefile for 'indexer' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Jeanmarcos Perez, October 2021

OBJS = indexer.o indextest.o
LIBS =  ../common/common.a ../libcs50/libcs50-given.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test valgrind

all: indexer indextest

indexer:	$(OBJS) $(LIBS)
			$(CC) $(CFLAGS) indexer.o $(LIBS) -o indexer 

indextest:	$(OBJS) $(LIBS)
			$(CC) $(CFLAGS) indextest.o $(LIBS) -o indextest 

test:	testing.sh
		bash -v testing.sh

valgrind:	valgrind.sh
			bash -v valgrind.sh

clean:
	rm -rf *.dSYM  
	rm -f *~ *.o
	rm -f indexer
	rm -f indextest
	rm -f core