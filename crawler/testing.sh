#!/bin/bash
#
# testing.sh
# Author: Jeanmarcos Perez
# Date: October 14, 2021
#
# Description: execute a sequence of commands for crawler.c that 
# address both normal and erroneous cases 
#

# no arguments
./crawler

# null seedURL 
./crawler NULL letters2 2

# null pageDirectory 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html NULL 2

# null maxDepth, known bug, see README.md 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 NULL

# non-integer maxDepth, known bug, see README.md 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 i

# negative maxDepth 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 -2

# maxDepth greater than 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 15 

# letters at depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 2

# letters at depth 5
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters5 5

# letters at depth 10
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters10 10

# toScrape at depth 0
#./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ scrape0 0

# toScrape at depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ scrape1 1

# wikipedia at depth 0
#./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ wiki0 0

# wikipedia at depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ wiki1 1 

exit 0