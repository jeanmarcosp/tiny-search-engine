/* 
 * indextest.c 
 *
 * usage: ./indextest oldIndexFilename newIndexFilename
 * 
 * oldIndexFilename: the name of a file produced by the indexer
 * newIndexFilename: the name of a file into which the index should be written 
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

int main(const int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "invalid command-line arguments, must pass exactly two arguments\n");
        exit(1);
    }
    else{
        index_t* index_result = index_load(argv[1]);
        index_save(index_result, argv[2]);
        index_delete(index_result);
    }
}