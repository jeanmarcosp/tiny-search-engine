# Makefile for 'crawler' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Jeanmarcos Perez, October 2021

OBJS = crawler.o 
LIBS = ../libcs50/libcs50-given.a -I../common/common.a


CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

crawler.o: 
../lib/file.o: ../lib/file.h

.PHONY: all clean test valgrind

all: crawler

crawler:	$(OBJS) $(LIBS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o crawler

valgrind:	valgrind.sh
			bash -v valgrind.sh

clean:
	rm -rf *.dSYM  
	rm -f *~ *.o
	rm -f crawler
	rm -f core
