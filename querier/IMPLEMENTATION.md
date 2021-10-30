# CS50 TSE Querier

## Implementation Spec

In this document we reference the Requirements Specification and Design Specification and focus on the implementation-specific decisions. The knowledge unit noted that an implementation spec may include many topics; not all are relevant to the TSE or the Querier. Here we focus on the core subset:

* Data structures
* Control flow: pseudo code for overall flow, and for each of the functions
* Detailed function prototypes and their parameters
* Error handling and recovery
* Testing plan

## Data Structures
We create two structs. One that holds two counters and another that holds a max, a key, a pageDirectory and a counters. We also make use of the Index module and Counters module. 

## Control Flow
The Querier is implemented in one file `querier.c`, with ten functions:

### main
The `main` function simply calls `parseArgs` and `parseQuery`.

### parseArgs
Given arguments from the command line, validate them 
* ensure exactly two arguments are given
* for `pageDirectory`, make sure it is not null and is a valid crawler directory
* for `indexFilename`, make sure it not null
* if any trouble is found, print an error to stderr and exit non-zero.

### parseQuery
Parses query. Pseudocode:

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
        
### addingToScores
Function to copy counters over to new counters. Pseudocode:

     call counters_set on given ctrs, key and count

### findingCommonIDS
Function to find common DocIds. Pseudocode:

     create new struct to hold two counters objects
     if the second counters key is not zero
        calculate score using given count and count of second counters
        set the key of the first counters to the calculated score
     else
        set the key of the first counters to zero

### printResults
Function to print results. Pseudocode:

     iterate through given counters to find matches
     print the number of documents that match the query
     create struct to hot a max of zero, key of o, given pageDirectory and given counters
     iterate through given counters to print urls of matching documents 

### findingMatches
Function to find number of matches. Pseudocode:

     if given count is not zero
        increment number of matches

### rankingResults
Function to rank results based on number of times the query appears in each document. Pseudocode:

     if given count is greater than max passed in rank struct
        set the rank struct max to the given count
        set the rank struct key to the given key

### printURLS
Function to print urls of documents in which query appears. Pseudocode:

     create rank struct to hold initial max and key of zero
     iterate through given counters to rank results
     if rank struct key is not zero
        create and open file using given pageDirectory
        if file is null 
            free pathname and exit non zero
        create pointer to url
        if rank struct max is not zero
            print DocID, count and url
            set key to zero
        
        free url pointer, close file, free pathname

### prompt
Function to print a prompt for an interactive user (when stdin is a "tty", aka teletype, aka keyboard), but not print a prompt when the stdin is not a keyboard. Pseudocode:

     print a prompt iff stdin is a tty (terminal)

## Other modules

### word
We create a re-usable module `word.c` that implements `tokenize`

### pagedir
We add a function `pagedir_validate` to ensure given pageDirectory is a valid crawler directory.

### libcs50
We leverage the modules of libcs50, most notably bag, hashtable, and webpage. See that directory for module interfaces. 

## Function prototypes

### querier
```c
int main(const int argc, char* argv[]);
int fileno(FILE *stream);
static void parseArgs(const int argc, char* argv[]);
static void parseQuery(const char* indexFilename, const char* pageDirectory);
void addingToScores(void* ctrs, const int key, const int count);
void findingCommonIDS(void* ctrs, const int key, const int count);
void printResults(counters_t* ctrs, const char* pageDirectory);
void findingMatches(void* arg, const int key, const int count);
void rankingResults(void* arg, const int key, const int count);
void printURLS(void* arg, const int key, const int count);
static void prompt(void);
```

### word
```c
char* normalizeWord(const char* word);
void tokenize(char* query, char** words, int* pos);
````

### pagedir
```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
```

## Error Handling and Recovery
All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the mem_assert functions, which result in a message printed to stderr and a non-zero exit status. We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the mem_assert functions), e.g., if a function receives bad parameters.

## Testing plan

We write a script testing.sh that invokes the indexer several times, with a variety of command-line arguments.