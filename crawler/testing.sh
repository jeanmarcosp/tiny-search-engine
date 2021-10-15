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

# null maxDepth 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 NULL

# negative maxDepth 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 -2

# maxDepth greater than 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 15 

# letters at depth 2
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 2

# letters at depth 5
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters5 5

# letters at depth 10
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters10 10
