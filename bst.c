#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "triprecord.h"
#include "linkedlist.h"

#define NEW_STRUCT 1
#define FIRST_COMPARISON 0
#define NULL_BYTE_CHAR 1
#define SEARCH_PUDATETIME 0
#define SEARCH_PULOCATIONID 1

/*
Node in the BST, puDateTime is the key.
Left is less and right is more.
Linked list for duplicate puDateTime.
Data is stored in a struct
*/
struct bstNode {
    char *puDateTime;
    struct bstNode *left;
    struct bstNode *right;
    struct LinkedList *next;
    struct record *tripRecord;
};

/*
Insert tripRecords into the BST based on puDateTime
Returns a node in the BST
*/
struct bstNode *bstInsert(struct bstNode *parent, struct record *tripRecord){
    //If the parent is empty, create a new node with data and empty pointers
    if(!parent){
        parent = calloc(NEW_STRUCT, sizeof(struct bstNode));
        assert(parent);
        parent->tripRecord = tripRecord;
        parent->puDateTime = malloc((sizeof(char) * strlen(tripRecord->puDateTime)) + NULL_BYTE_CHAR);
        strcpy(parent->puDateTime, tripRecord->puDateTime);
        parent->next = NULL;
        parent->left = NULL;
        parent->right = NULL;
    }

    /* If parent is not empty, and if data is less than data of current parent, 
    do bstInsert on the left pointer(to create new bst and
    put in data with empty pointers left and right) */
    else{
        /*Create return value for comparing the pick up date time strings
        ret < 0: Current node's puDateTime < record being inserted's (go right)
        ret > 0: Current node's puDateTime > record being inserted's (go left)
        ret == 0: Both have the same datetime (insert into linked list)
        */
        int ret;
        ret = strcmp(parent->puDateTime, tripRecord->puDateTime);
        
        if(ret == 0){
            parent->next = linkedListInsert(parent->next, tripRecord);
        }
        else if(ret > 0){
            parent->left = bstInsert(parent->left, tripRecord);
        }
        else if(ret < 0){
            parent->right = bstInsert(parent->right, tripRecord);
        }
    }
    return parent;
}

/*
Search BST for records with the key being searched for
Returns an array of records
Counts number of comparisons
*/
struct record **bstSearch(struct bstNode *parent, int search, char *keys, struct record **results, int *counter, int *noOfResults){
    
    /*If this is the first comparison (new key being searched)
    Free the previous key's results and allocate memory to it
    again to store new results for the new search key*/
    if((*counter) == FIRST_COMPARISON){
        free(results);
        results = calloc(NEW_STRUCT, sizeof(struct record *));
    }
    
    int ret;
    
    /*If search key is pudatetime in stage 1
    compare against pudatetime in the node
    and search through the BST based on the rule
    left is less right is more
    same is linked list*/
    if(search == SEARCH_PUDATETIME){
        ret = strcmp(parent->puDateTime, keys);
        (*counter)++;
        
        if(ret == 0){
            results[0] = parent->tripRecord;
            (*noOfResults)++;
            
            //Check if there are more records with the same key in linked list
            if(parent->next){
                results = linkedListSearch(parent->next, search, keys, results, counter, noOfResults);
            }
            return results;
        }
        //Keep searching left if less and right if more until no more nodes or found a matching pudatetime
        else if(ret > 0 && parent->left){
            results = bstSearch(parent->left, search, keys, results, counter, noOfResults);
        }
        else if(ret < 0 && parent->right){
            results = bstSearch(parent->right, search, keys, results, counter, noOfResults);
        }
        else{
            //If there are no records with the same pudatetime as the search, free the space allocated
            free(results);
            return NULL;
        }
    }
    /*If search key is pulocationid for stage 2
    Compare against pulocationid in the record stored in the node
    Compare with every node for pulocationid*/
    else if(search == SEARCH_PULOCATIONID){
        ret = strcmp(parent->tripRecord->puLocationID, keys);
        (*counter)++;
        
        if(parent->left){
            results = bstSearch(parent->left, search, keys, results, counter, noOfResults);
        }
        
        if(parent->right){
            results = bstSearch(parent->right, search, keys, results, counter, noOfResults);
        }
        
        if(parent->next){
            results = linkedListSearch(parent->next, search, keys, results, counter, noOfResults);
        }
        
        if(ret == 0){
            (*noOfResults)++;
            results = realloc(results, sizeof(struct record *) * (*noOfResults));
            results[*noOfResults-1] = parent->tripRecord;
        }
        return results;
    }
    return results;
}

/*free all the nodes and data in the nodes*/
void freeTree(struct bstNode *parent){
    if(parent->left){
        freeTree(parent->left);
    }
    if(parent->right){
        freeTree(parent->right);
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
        free(parent->puDateTime);
        free(parent);
        parent = NULL;
    }
}