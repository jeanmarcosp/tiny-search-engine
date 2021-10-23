#!/bin/bash
#
# testing.sh
# Author: Jeanmarcos Perez
# Date: October 22, 2021
#
# Description: execute a sequence of commands for index.c and indextest.c 
# that address both normal and erroneous cases 
# 
# usage: ./indexer pageDirectory indexFilename
#

# no arguments 
./indexer

# one arguments 
./indexer ../crawler/scrape1

# three arguments 
./indexer ../crawler/scrape1 indexFilename extraArgument

# invalid pageDirectory (non-existent path)
./indexer ../crawler/scrape100 indexFilename

# invalid pageDirectory (not a crawler directory) 
./indexer ../common indexFilename

# invalid indexFile (read-only directory)
./indexer ../crawler/scrape1 ../readOnlyDir

# invalid indexFile (existing, read-only file)
./indexer ../crawler/scrape1 ../readOnlyDir/readOnlyFile.txt

# valid arguments; scrape depth 1
./indexer ../crawler/scrape1 scrapeIndex

# valid arguments for indextest; scrape depth 1
./indextest scrapeIndex scrapeIndexTest

# comparing output for scrape1
~/cs50-dev/shared/tse/indexcmp scrapeIndex scrapeIndexTest

# valid arguments; letters depth 2
./indexer ../crawler/letters2 lettersIndex

# valid arguments for indextest; letters depth 2
./indextest lettersIndex lettersIndexTest

# comparing output for letters2
~/cs50-dev/shared/tse/indexcmp lettersIndex lettersIndexTest


