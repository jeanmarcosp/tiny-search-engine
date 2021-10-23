/* 
 * indexer.c 
 *
 * usage: ./indexer pageDirectory indexFilename
 * 
 * pageDirectory: the pathname of a directory produced by the Crawler
 * indexFilename: the pathname of a file into which the index should be written; 
 *      the indexer creates the file (if needed) and overwrites the file (if it already exists).
 * 
 * Jeanmarcos Perez; October 18, 2021
 */

#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "mem.h" 
#include "webpage.h" 
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"
#include "file.h"
#include "index.h"
#include "word.h"
#include "pagedir.h"


static void parseArgs(const int argc, char* argv[]);
static void indexBuild(const char* pageDirectory, const char* indexFilename);
static void indexPage(webpage_t* webpage, index_t* index, const int docID);

int main(const int argc, char* argv[]){
    parseArgs(argc, argv);
    indexBuild(argv[1], argv[2]);
    return 0;
}

static void parseArgs(const int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "invalid command-line arguments, must pass exactly two arguments\n");
        exit(1);
    }
    if(argv[1] == NULL || argv[2] == NULL){
        fprintf(stderr, "null pageDirectory or indexFilename\n");
        exit(1);
    }
    if(pagedir_validate(argv[1]) == false){
        fprintf(stderr, "not a crawler directory\n");
        exit(1);
    }
}

static void indexBuild(const char* pageDirectory, const char* indexFilename){
    //creates a new 'index' object
    index_t* index = index_new();

    //loops over document ID numbers, counting from 1
    int docID = 1;

    char* pathname = mem_malloc(strlen(pageDirectory) + 10);
    sprintf(pathname, "%s/%d", pageDirectory, docID);
    FILE* fp = fopen(pathname, "r");
    mem_free(pathname);

    while(fp != NULL){
        //loads a webpage from the document file 'pageDirectory/id'
        char* url = file_readLine(fp);
        char* depth_char = file_readLine(fp);
        int depth;
        sscanf(depth_char, "%d", &depth);
        char* html = file_readFile(fp);

        mem_free(depth_char);

        webpage_t* new_webpage = webpage_new(url, depth, html);

        //if successful, 
        if(new_webpage != NULL){
            //passes the webpage and docID to indexPage
            indexPage(new_webpage, index, docID);
            webpage_delete(new_webpage);
        }

        //update pathname
        fclose(fp);
        docID++;
        char* pathname_new = mem_malloc(strlen(pageDirectory) + 10);
        sprintf(pathname_new, "%s/%d", pageDirectory, docID);
        fp = fopen(pathname_new, "r");
        mem_free(pathname_new);
    }  
    //
    //close file, free memory 
    //fclose(fp);
    index_save(index, indexFilename); 
    index_delete(index);
}

static void indexPage(webpage_t* webpage, index_t* index, const int docID){
    //steps through each word of the webpage,
    int pos = 0;
    char* current_word;
    while((current_word = webpage_getNextWord(webpage, &pos)) != NULL){
        //skips trivial words (less than length 3),
        if(strlen(current_word) >= 3){
            //normalizes the word (converts to lower case),
            current_word = normalizeWord(current_word);
            //looks up the word in the index,
            ///adding the word to the index if needed
            //increments the count of occurrences of this word in this docID
            index_add(index, current_word, docID);
        }
        mem_free(current_word);
    }
}