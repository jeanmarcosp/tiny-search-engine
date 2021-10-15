## Known Bugs

* Does not print error message "invalid arguments" when maxDepth is NULL or a non-integer value, but code still runs 
and does not produce failure message otherwise:
error

`c
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 NULL
`

`c
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters2 n
`