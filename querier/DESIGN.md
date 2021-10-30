# CS50 TSE Querier
## Design Spec

According to the [Querier Requirements Spec](REQUIREMENTS.md), the TSE *querier* is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

### User interface

The queriers's interface with the user is on the command-line; it must always have two arguments. It will then prompt the user for a query.

```
querier pageDirectory indexFilename
```

For example, if `scrape1` is a pageDirectory in `../crawler`,

``` bash
$ querier ../crawler/scrape1 ../indexer/scrapeIndexTest
```

### Inputs and outputs

**Input**: the querier reads files from a directory by constructing file pathnames from the `pageDirectory` parameter followed by a numeric document ID (as described in the Requirements).

**Output**: We print the documents that match the user provided query (as described in the Requirements).

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which initializes other modules;
 2. *parseArgs*, parses arguments;
 3. *parseQuery*, which parse query;
 4. *addingToScores* which copies counters over to new counters;
 5. *findingCommonIDS* which finds common DocIds;
 6. *printResults* which prints results;
 7. *findingMatches* which finds number of matches;
 8. *rankingResults* which ranks results based on number of times the query appears in each document;
 9. *printURLS* which prints urls of documents in which query appears;
 10. *prompt* which prints a prompt for an interactive user (when stdin is a "tty", aka teletype, aka keyboard), but not print a prompt when the stdin is not a keyboard.

And some helper modules that provide data structures:

 1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 2. *pagedir*, a module providing functions to validate crawler produced directories;
 3. *word*, a module providing a function to tokenize a word.

### Pseudo code for logic/algorithmic flow

The querier will run as follows:

    parse the command line, validate parameters, initialize other modules
    call parseQuery, with indexFilename and pageDirectory

where *parseQuery:*

      creates a new 'index' object using indexFilename
      prompt user for query, tokenize it
      create a new 'counters' object
      iterate through new counters and add item associated with the first word in the query in index
      for each word in users query
        create new 'counters' object using second word in query
        create a new struct to hold two counters and add first counters and new counters we just made
        iterate through first counters, find common DocIds between it and the new counters
      free index and query
      print results 
      delete first counters object

### Major data structures

The key data structure is the *index*, mapping from *word* to *(docID, #occurrences)* pairs.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID. 

### Testing plan

1. Test `indexer` with various invalid arguments.
	* no arguments
	* three arguments 
	* invalid `pageDirectory` (not a crawler directory)
2. test `querier` using queries generated from fuzzquery
3. test `querier` using queries from personal scrapeIndexTest
4. Run *valgrind* on *querier* to ensure no memory leaks or errors.