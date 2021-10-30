/* 
 * word.h - header file for CS50 word module
 *
 * Jeanmarcos Perez, October 2021
 */

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>

/**************** functions ****************/

/**************** normalizeWord  ****************/
/*
 * normalize given word by making it all lowercase
 *
 * Caller provides:
 *    word to be normalized
 *
 * We return:
 *    normalized word
 */
char* normalizeWord(const char* word);

/**************** tokenize  ****************/
/*
 * turn given string of words into individual 
 * tokenized words
 *
 * Caller provides:
 *   valid pointer to query string
 *   valid array of pointers to strings
 * 
 * We return:
 *   integer representing number of tokens
 * 
 * Note:
 *   the array passed into the function
 *   will be modified
 * 
 */
void tokenize(char* query, char** words, int* pos);


#endif // __WORD_H
