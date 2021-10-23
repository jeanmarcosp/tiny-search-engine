# CS50 TSE Indexer

## Implementation Spec

In this document we reference the Requirements Specification and Design Specification and focus on the implementation-specific decisions. The knowledge unit noted that an implementation spec may include many topics; not all are relevant to the TSE or the Indexer. Here we focus on the core subset:

* Data structures
* Control flow: pseudo code for overall flow, and for each of the functions
* Detailed function prototypes and their parameters
* Error handling and recovery
* Testing plan

## Data Structures
We create a data structure called an index, which is mostly a wrapper for a 'hashtable' whose items are 'counters'

## Control Flow
The Indexer is implemented in one file `indexer.c`, with four functions:

### main
The `main` function simply calls `parseArgs` and `indexBuild`, then returns zero.

### parseArgs
Given arguments from the command line, validate them 
* for `pageDirectory`, make sure it is not null and is a valid crawler directory
* for `indexFilename`, make sure it not null
* if any trouble is found, print an error to stderr and exit non-zero.

### indexBuild
Builds an in-memory index from webpage files it finds in the pageDirectory. Pseudocode:

  creates a new 'index' object
  loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
      passes the webpage and docID to indexPage


### indexPage
Scans a webpage document to add its words to the index. Pseudocode:

 steps through each word of the webpage,
   skips trivial words (less than length 3),
   normalizes the word (converts to lower case),
   looks up the word in the index,
     adding the word to the index if needed
   increments the count of occurrences of this word in this docID


## Other modules

### word
We create a re-usable module `word.c` that implements `normalizeWord`

### pagedir
We add a function `pagedir_validate` to ensure given pageDirectory is a valid crawler directory.

### libcs50
We leverage the modules of libcs50, most notably bag, hashtable, and webpage. See that directory for module interfaces. 

## Function prototypes

### indexer
`
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[]);
static void indexBuild(const char* pageDirectory, const char* indexFilename);
static void indexPage(webpage_t* webpage, index_t* index, const int docID);
`

### word
`
char* normalizeWord(const char* word);
`

### pagedir
`
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
`

## Error Handling and Recovery
All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the mem_assert functions, which result in a message printed to stderr and a non-zero exit status. We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the mem_assert functions), e.g., if a function receives bad parameters.

## Testing plan

We write a script testing.sh that invokes the indexer several times, with a variety of command-line arguments.

We test with no arguments, one argument, three arguments, invalid pageDirectory (non-existent path), invalid pageDirectory (not a crawler directory), invalid indexFile (non-existent path), invalid indexFile (read-only directory, invalid indexFile (existing, read-only file)

We also run indexer on a variety of pageDirectories and use indextest as one means of validating the resulting index.