#include "ctype.h"

char* normalizeWord(char* word){
    char* letter = word;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter++;
    }
    return word;
}