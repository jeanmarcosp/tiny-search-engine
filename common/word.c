/* 
 * word.c - CS50 'word' module
 *
 * see word.h for more information.
 *
 * Jeanmarcos Perez; October 22, 2021
 */

#include "ctype.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../libcs50/file.h"

char* normalizeWord(char* word){
    char* letter = word;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter++;
    }
    return word;
}

void tokenize(char* query, char** words, int* pos){
    words[*pos] = query;
    (*pos)++;

    while(*query != '\0'){
        while(isspace(*query)){
            *query = '\0';

            char* newToken = ++query;

            if(*newToken == ' '){
                break;
            }
            else{
                words[*pos] = newToken;
                (*pos)++;
            }
        }
        query++;
    }
}