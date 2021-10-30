/* 
 * querier.c 
 *
 * usage: ./querier pageDirectory indexFilename
 * 
 * pageDirectory: the pathname of a directory produced by the Crawler
 * indexFilename: the pathname of a file produced by the Indexer  
 * 
 * Jeanmarcos Perez; October 25, 2021
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
#include "counters.h"
#include "file.h"
#include "index.h"
#include "word.h"
#include "pagedir.h"
#include <ctype.h>
#include <unistd.h>

typedef struct twoCtrs{
    counters_t* ctrs1;
    counters_t* ctrs2;
} twoCtrs_t;

typedef struct rank{
    int max;
    int key;
    const char* pageDirectory;
    counters_t* ctrs;

} rank_t;

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

int main(const int argc, char* argv[]){
    parseArgs(argc, argv);
    char* pageDirectory = argv[1];
    char* indexFilename = argv[2];
    parseQuery(indexFilename, pageDirectory);
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
    FILE* fp = fopen(argv[2], "r");
    if(fp  == NULL){
        fprintf(stderr, "file cannot be read");
        exit(1);
    }
    fclose(fp);
}

static void parseQuery(const char* indexFilename, const char* pageDirectory){
    index_t* index = index_load(indexFilename);

    prompt();
    char* query = file_readLine(stdin);
    char* words[(strlen(query)/2) + 1];

    int pos = 0;
    tokenize(query, words, &pos);

    counters_t* scores = counters_new();
    counters_iterate(index_find(index, words[0]), scores, addingToScores);

    for(int i = 1; i < pos; i++){ 
        counters_t* nextCtrs = index_find(index, words[i]);
        twoCtrs_t twoCtrs = {scores, nextCtrs};
        counters_iterate(scores, &twoCtrs, findingCommonIDS);
    }

    index_delete(index);
    mem_free(query);
    printResults(scores, pageDirectory);
    counters_delete(scores);
}

void addingToScores(void* ctrs, const int key, const int count){
    counters_set(ctrs, key, count);
}

void findingCommonIDS(void* ctrs, const int key, const int count){
    twoCtrs_t* twoCtrs = ctrs;
    if(counters_get(twoCtrs->ctrs2, key) != 0){
        int new_score = count + counters_get(twoCtrs->ctrs2, key);
        counters_set(twoCtrs->ctrs1, key, new_score);
    }
    else{
        counters_set(twoCtrs->ctrs1, key, 0);  
    }
}

void printResults(counters_t* ctrs, const char* pageDirectory){
    int matches = 0;
    counters_iterate(ctrs, &matches, findingMatches);
    printf("Matches %d Documents, (ranked): \n", matches);

    rank_t rank = {0, 0, pageDirectory, ctrs};
    counters_iterate(ctrs, &rank, printURLS);
}

void findingMatches(void* arg, const int key, const int count){
    if(count != 0){
        int* matches = arg;
        (*matches)++;
    }
}

void rankingResults(void* arg, const int key, const int count){
    rank_t* rank = arg;
    if(count > rank->max){
        rank->max = count;
        rank->key = key;
    }
}

void printURLS(void* arg, const int key, const int count){
    rank_t* original_rank = arg;
    rank_t rank_struct = {0, 0, NULL, NULL};

    counters_iterate(original_rank->ctrs, &rank_struct, rankingResults);

    if(rank_struct.key != 0){
        char* pathname = mem_malloc(strlen(original_rank->pageDirectory) + 10);
        sprintf(pathname, "%s/%d", original_rank->pageDirectory, rank_struct.key);
        FILE* fp = fopen(pathname, "r");

        if(fp == NULL){
            mem_free(pathname);
            exit(1);
        }

        char* URL = file_readLine(fp);

        if(rank_struct.max != 0){
            printf("%d %d %s\n", rank_struct.key, rank_struct.max, URL);
            counters_set(original_rank->ctrs, rank_struct.key, 0);
        }

        mem_free(URL);
        fclose(fp);
        mem_free(pathname);
    }
}

static void prompt(void){
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
}

