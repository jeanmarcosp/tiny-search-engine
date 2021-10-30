## Functionality
* querier prints the set of documents that contain all the words in the query; you may treat operators ('and', 'or') as regular words.

## Assumptions
* user provided query does not begin with a space character
* user provided query does not have more than one space character between words
* user provided query contains only letters and spaces

## Known Bugs
* only accepts one query at a time, reflected in the way testing.sh is implemented
