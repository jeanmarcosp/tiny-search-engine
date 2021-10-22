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

#endif // __WORD_H
