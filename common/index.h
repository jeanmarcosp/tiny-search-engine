/* 
 * index.h - header file for CS50 index module
 *
 * Jeanmarcos Perez, October 2021
 */

 #ifndef __INDEX_H
 #define __INDEX_H

 #include <stdio.h>
 #include <stdbool.h>

 /**************** global types ****************/
typedef struct index index_t; 

/**************** functions ****************/

/**************** index_new ****************/
/* Create a new (empty) index
 * 
 * Caller provides:
 *   nothing
 * 
 * We return:
 *   pointer to the new index; NULL if error
 * 
 */
index_t* index_new();

/**************** index_add ****************/
/* Adds an entry to the index, where the key is the word 
 * and the item is a counters
 * 
 * Caller provides:
 *   valid pointer to an index, valid string for key, valid int for docID
 * 
 * We return:
 *   true if successfully added to index
 *      if already in index, increment counter associated with word
 *   false if any parameter is NULL
 * 
 */
bool index_add(index_t* index, const char* word, int docID);

/**************** index_save ****************/
/* saves index output to given file
 * 
 * Caller provides:
 *   valid pointer to an index and file to print to
 * 
 * We return:
 *   nothing
 */ 
void index_save(index_t* index, const char* indexFilename);

/**************** index_load ****************/
/* reads file input and creates index
 * 
 * Caller provides:
 *   valid pointer to readable file
 * 
 * We return:
 *   an index pointer 
 */ 
index_t* index_load(const char* indexFilename);

/**************** index_delete ****************/
/* Delete hashtable, calling a delete function on each item.
 *
 * Caller provides:
 *   valid index pointer
 * 
 * We do:
 *   nothing if index == NULL.
 *   otherwise, call the itemfunc on each item.
 *   free the index itself.
 * 
 */
void index_delete(index_t* index);

#endif // __INDEX_H