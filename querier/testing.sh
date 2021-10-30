#!/bin/bash
#
# testing.sh
# Author: Jeanmarcos Perez
# Date: October 29, 2021
#
# Description: execute a sequence of commands for querier.c 
# that address both normal and erroneous cases 
# 
# usage: testing.sh pageDirectory indexFilename
#

# no arguments 
./querier

# three arguments 
./querier $1 $2 extraArgument

# passing directory not produced by crawler
./querier ./common $2

# generating random queries from scrape depth 1 using fuzz query
./fuzzquery $2 1 $RANDOM > testquery1
./fuzzquery $2 1 $RANDOM > testquery2
./fuzzquery $2 1 $RANDOM > testquery3
./fuzzquery $2 1 $RANDOM > testquery4
./fuzzquery $2 1 $RANDOM > testquery5


# valid parameters, passing in 1 queries genereated from fuzzquery
./querier $1 $2 < testquery1
./querier $1 $2 < testquery2
./querier $1 $2 < testquery3
./querier $1 $2 < testquery4
./querier $1 $2 < testquery5

# generating queries I know exist in my scrapeIndexTest
echo "many better civitella" > testquery6
echo "religion" > testquery7
echo "king meet soon" > testquery8
echo "young has" > testquery9
echo "window" > testquery10

# valid parameters, passing in queries genereated above
./querier $1 $2 < testquery6
./querier $1 $2 < testquery7
./querier $1 $2 < testquery8
./querier $1 $2 < testquery9
./querier $1 $2 < testquery10
