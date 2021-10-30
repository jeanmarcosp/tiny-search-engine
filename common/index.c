/* 
 * index.c - CS50 'index' module
 *
 * see index.h for more information.
 *
 * Jeanmarcos Perez; October 21, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "mem.h"
#include "counters.h"

void itemdelete(void* item);
void itemprint(void* fp, const char* key, void* item);
void countersprintfunc(void* arg, const int key, const int count);

/**************** file-local global variables ****************/
/* none */

/**************** global types ****************/
typedef struct index {
    hashtable_t* hashtable;
} index_t;

index_t*
index_new(){
    index_t* new_index = mem_malloc(sizeof(index_t*));

    if(new_index == NULL){
        return NULL;        // error allocating index
    }
    
    int slots = 200;
    new_index->hashtable = hashtable_new(slots);
    return new_index;
}

bool
index_add(index_t* index, const char* word, int docID){
    if(index != NULL && word != NULL && docID > 0){
        void* item = hashtable_find(index->hashtable, word);
        if(item != NULL){  //word found
            counters_add(item, docID);
            return true;
        } 
        else{  //word not found
            counters_t* ctrs = counters_new();
            counters_add(ctrs, docID);
            hashtable_insert(index->hashtable, word, ctrs);
            return true;
        }
    }
    else{
        return false;
    }
}

void
index_save(index_t* index, const char* indexFilename){
    FILE* fp = fopen(indexFilename, "w");
    if(fp == NULL){
        fprintf(stderr, "file is null\n");
        exit(1);
    }
    hashtable_iterate(index->hashtable, fp, itemprint);
    fclose(fp);
}

index_t*
index_load(const char* indexFilename){
    index_t* index = index_new();
    FILE* fp = fopen(indexFilename, "r");

    if(fp == NULL){
        fprintf(stderr, "file is null\n");
        exit(1);
    }

    char* word;
    word = mem_malloc(100);
    int docID = 0;
    int count = 0;
    
    while( fscanf(fp, "%s ", word) == 1){
         while( fscanf(fp, "%d %d ", &docID, &count) == 2){
             index_add(index, word, docID);
             counters_set(hashtable_find(index->hashtable, word), docID, count);
             }
    }
    
    fclose(fp);
    mem_free(word);
    return index;
}

void
index_delete(index_t* index){
    if(index != NULL){
        hashtable_delete(index->hashtable, itemdelete);
        mem_free(index);
    }
}

counters_t*
index_find(index_t* index, const char* key){
    return hashtable_find(index->hashtable, key);
}

void itemdelete(void* item){
    counters_t* ctrs = item;
    if(ctrs != NULL){
        counters_delete(ctrs);
    }
}

void itemprint(void* fp, const char* key, void* item){
    if(fp != NULL){
        fprintf(fp, "%s ", key);
        counters_t* ctrs = item;
        counters_iterate(ctrs, fp, countersprintfunc);
        fprintf(fp, "\n");
    }
}

void countersprintfunc(void* arg, const int key, const int count){
    fprintf(arg, "%d %d ", key, count);
}