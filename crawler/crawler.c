/* 
 * crawler.c 
 *
 * usage: ./crawler seedURL pageDirectory maxDepth
 * 
 * seedURL: 'internal' directory, to be used as the initial URL
 * pageDirectory: the (existing) directory in which to write downloaded webpages
 * maxDepth: integer in range [0..10] indicating the maximum crawl depth
 *      
 * Jeanmarcos Perez; October 11, 2021
 */

#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "mem.h" 
#include "webpage.h" 
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

void itemdelete_hash(void* item);

int main(const int argc, char* argv[]){
    int depth = 0;
    parseArgs(argc, argv, &argv[1], &argv[2], &depth);
    crawl(argv[1], argv[2], depth);
    exit(0);
}

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){
    if(argc == 4){
        
        if(seedURL != NULL && pageDirectory != NULL && argv[3] != NULL){
            sscanf(argv[3], "%d", maxDepth);

            //normalize and validate URL
            *seedURL = normalizeURL(*seedURL);

            if(!isInternalURL(*seedURL) || !pagedir_init(*pageDirectory) || *maxDepth < 0 || *maxDepth > 10){
                //if any arguments are invalid, print error to stderr and exit non-zero
                mem_free(*seedURL);
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
    const int num_slots = 100;
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
    webpage_t* initial_webpage = webpage_new(seedURL, 0, NULL);
    bag_insert(pages_to_crawl, initial_webpage);

    //while bag is not empty
    webpage_t* current_webpage;
    int doc_ID = 1;
    while((current_webpage = bag_extract(pages_to_crawl)) != NULL){ 
	    //pull a webpage from the bag
	    //fetch the HTML for that webpage, if fetch was successful,
        if(webpage_fetch(current_webpage)){
            //save the webpage to pageDirectory
            pagedir_save(current_webpage, pageDirectory, doc_ID);
            doc_ID++;
		    //if the webpage is not at maxDepth,
            if(webpage_getDepth(current_webpage) < maxDepth){
                //pageScan that HTML
                pageScan(current_webpage, pages_to_crawl, pages_seen);
            }   
        }
        else{
            fprintf(stderr, "unable to fetch HTML\n");
            exit(1);
        }
        //delete that webpage
        webpage_delete(current_webpage);
    }
    //delete the hashtable and bag
    hashtable_delete(pages_seen, NULL);
    bag_delete(pages_to_crawl, webpage_delete);
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
            if(hashtable_insert(pagesSeen, current_url, item)){
                //create a webpage_t for it
                webpage_t* new_webpage = webpage_new(current_url, webpage_getDepth(page) + 1, NULL);
			    //insert the webpage into the bag
                bag_insert(pagesToCrawl, new_webpage);
            }  
            else{
                mem_free(current_url);
            }
        }
        else{
            mem_free(current_url);
        }
    }
}

//delete function for hashtable
void itemdelete_hash(void* item){
    if (item != NULL) {
    mem_free(item);   
  }
}