/* 
 * pagedir.h - header file for 'pagedir' module 
 *
 * Jeanmarcos Perez, October 2021
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include "webpage.h"
#include <stdbool.h>

/**************** functions ****************/

/**************** pagedir_init ****************/
/* constructs the pathname for the .crawler file in that directory
 *
 * we return:
 *      false if unable to open file for writing
 *      otherwise, open file, close file and return true
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* constructs the pathname for the page file in pageDirectory
 *
 * we return:
 *      false if unable to open file for writing
 *      otherwise, open file, print URL, depth, and html of webpage, close file and return true
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/**************** pagedir_validate ****************/
/*
 * validates given pageDirectory as crawler directory
 * 
 * we return:
 *      true if valid crawler directory
 *      false otherwise
 */ 
bool pagedir_validate(const char* pageDirectory);

#endif // __PAGEDIR_H
