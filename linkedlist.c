#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "triprecord.h"

#define MAX_DATETIME_SIZE 20
#define NEW_STRUCT 1
#define SEARCH_PUDATETIME 0
#define SEARCH_PULOCATIONID 1

struct LinkedList{
    struct record *tripRecord;
    struct LinkedList *next;
};

struct LinkedList *linkedListInsert(struct LinkedList *parent, struct record *tripRecord){
    
    //If the parent is empty, create a new node with data and empty pointers
    if(!parent){
        parent = calloc(NEW_STRUCT, sizeof(struct LinkedList));
        
        parent->tripRecord = tripRecord;
        parent->next = NULL;
    }
    /* If parent is not empty, and if data is less than data of current parent, 
    do bstInsert on the left pointer(to create new bst and
    put in data with empty pointers left and right) */
    else{
        parent->next = linkedListInsert(parent->next, tripRecord);
    }
        return parent;
}

struct record **linkedListSearch(struct LinkedList *parent, int search, char *keys, struct record **results, int *counter, int *noOfResults){
    
    if(search == SEARCH_PUDATETIME){
        (*noOfResults)++;
        
        results = realloc(results, sizeof(struct record *) * (*noOfResults));
        results[*noOfResults-1] = parent->tripRecord;
        
        if(parent->next){
            results = linkedListSearch(parent->next, search, keys, results, counter, noOfResults);
        }
    }
    
    else if(search == SEARCH_PULOCATIONID){
        
        if(parent->next){
            results = linkedListSearch(parent->next, search, keys, results, counter, noOfResults);
        }
        
        int ret = strcmp(parent->tripRecord->puLocationID, keys);
        
        (*counter)++;
        
        if(ret == 0){
            (*noOfResults)++;
            results = realloc(results, sizeof(struct record *) * (*noOfResults));
            results[*noOfResults-1] = parent->tripRecord;
        }
    }
    return results;
}

void freeLinkedList(struct LinkedList *parent){
    if(!parent){
        return;
    }
    if(parent->next){
        freeLinkedList(parent->next);
    }
    if(parent->tripRecord){
        freeRecord(parent->tripRecord);
        free(parent->tripRecord);
        parent->tripRecord = NULL;
    }
    if(parent){
        free(parent);
        parent = NULL;
    }
   
}