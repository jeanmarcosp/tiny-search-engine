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
/* 
 *
 *
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* 
 *
 *
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

#endif // __PAGEDIR_H
