/* 
 * word.c - CS50 'word' module
 *
 * see word.h for more information.
 *
 * Jeanmarcos Perez; October 22, 2021
 */

#include "ctype.h"

char* normalizeWord(char* word){
    char* letter = word;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter++;
    }
    return word;
}