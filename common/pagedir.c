/* 
 * pagedir.c - 'pagedir' module
 *
 * see pagedir.h for more information.
 *
 * Jeanmarcos Perez, October 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "webpage.h"
#include "mem.h"

/**************** pagedir_init() ****************/
/* see pagedir.h for description */
bool 
pagedir_init(const char* pageDirectory){
    //construct the pathname for the .crawler file in that directory
    char* pathname = mem_malloc(strlen(pageDirectory) + 10);
    sprintf(pathname, "%s/.crawler", pageDirectory);
    //open the file for writing; on error, return false.
    FILE* fp = fopen(pathname, "w");
    if(fp != NULL ){
        //close the file and return true.
        fclose(fp);
        mem_free(pathname);
        return true;
    }
    else{
        mem_free(pathname);
        return false;
    }
}

/**************** pagedir_save() ****************/
/* see pagedir.h for description */
void 
pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    //construct the pathname for the page file in pageDirectory
    char* pathname = mem_malloc(strlen(pageDirectory) + 10);
    sprintf(pathname, "%s/%d", pageDirectory, docID);
    //open that file for writing
    FILE* fp = fopen(pathname, "w");
    if(fp != NULL){
        //print the URL, depth, and contents of the webpage
        fprintf(fp, "%s\n", webpage_getURL(page));
        fprintf(fp, "%d\n", webpage_getDepth(page));
        fprintf(fp, "%s\n", webpage_getHTML(page));
        //close the file
        fclose(fp);
        mem_free(pathname);
    }
    else{
        mem_free(pathname);
        fprintf(stderr, "unable to write to file %s\n", pathname);
        exit(1);
    }
}

bool 
pagedir_validate(const char* pageDirectory){
    //construct the pathname for the .crawler file in that directory
    char* pathname = mem_malloc(strlen(pageDirectory) + 10);
    sprintf(pathname, "%s/.crawler", pageDirectory);
    //open the file for writing; on error, return false.
    FILE* fp = fopen(pathname, "r");
    if(fp != NULL ){
        //close the file and return true.
        fclose(fp);
        mem_free(pathname);
        return true;
    }
    else{
        mem_free(pathname);
        return false;
    }
}