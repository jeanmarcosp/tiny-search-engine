/* 
 * crawler.c 
 *
 * Jeanmarcos Perez; October 11, 2021
 */

#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mem.h" 
#include "webpage.h" 
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

void itemdelete_bag(void* item);
void itemdelete_hash(void* key);

int main(const int argc, char* argv[]){
    int temp;
    sscanf(argv[4], "%d", &temp);
    parseArgs(argc, argv, &argv[2], &argv[3], &temp);
    crawl(argv[2], argv[3], temp);
    exit(0);
}

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){
    if(argc == 4){
        if(seedURL != NULL && pageDirectory != NULL && maxDepth != NULL){
            //normalize and validate URL
            normalizeURL(*seedURL);
            if(isInternalURL(*seedURL) && pagedir_init(*pageDirectory) && *maxDepth >= 0 && *maxDepth <= 10){
                //all arguments are valid, exit successfully
                exit(0);
            }
            else{
                //if any arguments are invalid, print error to stderr and exit non-zero
                //add usage line
                fprintf(stderr, "invalid arguments\n");
                exit(1);
            }
        }
        else{
            //if any arguments are null, print error to stderr and exit non-zero
            fprintf(stderr, "invalid arguments\n");
            exit(1);
        }
    }
    else{
        //if command line arguements do not equal 4, print error to stderr and exit non-zero
        fprintf(stderr, "invalid number of arguments\n");
        exit(1);
    }
}

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
    //initialize the hashtable and add the seedURL
    char* item = "";
    const int num_slots = 10;
    hashtable_t* pages_seen = hashtable_new(num_slots);
    if (pages_seen == NULL) {
        fprintf(stderr, "hashtable_new failed for pages_seen\n");
        exit(1);
    }
    hashtable_insert(pages_seen, seedURL, item);

    //initialize the bag and add a webpage representing the seedURL at depth 0
    bag_t* pages_to_crawl = bag_new();
    if (pages_to_crawl == NULL) {
        fprintf(stderr, "bag_new failed for pages_to_crawl\n");
        exit(1);
    }
    webpage_t* initial_webpage = webpage_new(seedURL, 0, pageDirectory);
    bag_insert(pages_to_crawl, initial_webpage);

    //while bag is not empty
    webpage_t* current_webpage;
    int doc_ID = 1;
    while((current_webpage = bag_extract(pages_to_crawl)) != NULL){ 
	    //pull a webpage from the bag
	    //fetch the HTML for that webpage
	    //if fetch was successful,
        if(webpage_fetch(current_webpage)){
            //char* html = mem_malloc(strlen(webpage_getHTML(current_webpage)));
            //html = webpage_getHTML(current_webpage);
            //save the webpage to pageDirectory
            pagedir_save(current_webpage, pageDirectory, doc_ID);
            doc_ID++;
		    //if the webpage is not at maxDepth,
            if(webpage_getDepth(current_webpage) != maxDepth){
                //pageScan that HTML
                pageScan(current_webpage, pages_to_crawl, pages_seen);
            }
            else{
                exit(1);
            }	    
        }
        else{
            exit(1);
        }
        //delete that webpage
        webpage_delete(current_webpage);
    }
    //delete the hashtable and bag
    hashtable_delete(pages_seen, itemdelete_hash);
    bag_delete(pages_to_crawl, itemdelete_bag);
}

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
    //while there is another URL in the page
    char* item = "";
    int position = 0;
    char* current_url;

    while((current_url = webpage_getNextURL(page, &position)) != NULL){
        //if that URL is Internal,
        if(isInternalURL(current_url)){
            //insert the webpage into the hashtable
            //if that succeeded,
            if(hashtable_insert(pagesSeen, current_url, item)){
                //create a webpage_t for it
                webpage_t* new_webpage = webpage_new(current_url, webpage_getDepth(page), NULL);
                webpage_fetch(new_webpage);
			    //insert the webpage into the bag
                bag_insert(pagesToCrawl, new_webpage);
            }  
            else{
                exit(1);
            }
        }
        else{
            exit(1);
        }
	    mem_free(current_url);
    }
	    
}

//delete function for bag
void itemdelete_bag(void* item){
    if (item != NULL) {
    webpage_delete(item);   
  }
}

//delete function for hashtable
void itemdelete_hash(void* key){
    if (key != NULL) {
    mem_free(key);   
  }
}