# Makefile for 'querier' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Jeanmarcos Perez, October 2021

OBJS = querier.o 
LIBS =  ../common/common.a ../libcs50/libcs50-given.a
ARGS = ../crawler/scrape1 ../indexer/scrapeIndexTest

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test valgrind

all: querier

querier:	$(OBJS) $(LIBS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o querier

test:	testing.sh
		bash -v testing.sh $(ARGS) &> testing.out

valgrind:	valgrind.sh
			bash -v valgrind.sh

clean:
	rm -rf *.dSYM  
	rm -f *~ *.o
	rm -f querier
	rm -f core