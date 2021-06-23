#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "triprecord.h"
#include "bst.h"

#define INPUT_FILE 1
#define MIN_ARGUMENTS 2
#define GETLINE_ERR_OR_EOF -1
#define RESET_COUNTER 0
#define OUTPUT_FILE 2
#define RESET_NO_OF_RESULTS 0
#define SEARCH_PUDATETIME 0

int main(int argc, char **argv){
        
    //input file
    FILE *in;
    //buffer holds all data in 1 row
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;
    
    //insufficient arguments
    if(argc < MIN_ARGUMENTS){
        printf("Insufficient arguments.\n");
        return 0;
    }
    
    //open input file to insert records into bst
    in = fopen(argv[INPUT_FILE],"r");
    
    //Check if input file can be opened
    if(in == NULL){
        printf("Unable to open input file.\n");
        return 0;
    }
    
    //create rootNode
    struct bstNode *rootNode = NULL;
    char *token;
    
    //Read each line(record) of data into buffer
    while ((read = getline(&buffer, &len, in)) != GETLINE_ERR_OR_EOF){
        int col = 0;
        //token is comma separated value
        token = NULL;
        //Allocate memory to tripRecord and zero out
        struct record *tripRecord = calloc(1, sizeof(struct record));
        assert(tripRecord);
        
        //Separate values in each line of data to be put in struct
        token = strtok(buffer, ",");
        while(token != NULL){
            createRecord(tripRecord, token, col);
            token = strtok(NULL, ",");
            col++;
        }
        
        //Insert into bst
        rootNode = bstInsert(rootNode, tripRecord);   
    }
    
    //Check if output file was indicated
    if(argc!=3){
        printf("No output file indicated.");
        return 0;
    }
    
    //Files for the keys to be searched and output for the results
    FILE *searchKeys = stdin;
    FILE *output;
    
    //search key
    char *keys = NULL;
    
    //Create a null array of records
    struct record **results = NULL;
    
    //Open the output file to write results in
    output = fopen(argv[OUTPUT_FILE], "w");
    if(output == NULL){
        printf("Unable to open output file.\n");
        return 0;
    }
    
    //Read each line of search keys, search in the BST and print results of each search
    while((read = getline(&keys, &len, searchKeys))!= GETLINE_ERR_OR_EOF){
        int counter = RESET_COUNTER;
        int noOfResults = RESET_NO_OF_RESULTS;
        keys[strcspn(keys, "\n")] = 0;
        results = bstSearch(rootNode, SEARCH_PUDATETIME, keys, results, &counter, &noOfResults);
        printResults(results, SEARCH_PUDATETIME, keys, &counter, &noOfResults, output);
    }
    
    //free all data and close all files
    if(buffer){
        free(buffer);
    }
    if(keys){
        free(keys);
    }
    free(results);
    fclose(in);
    fclose(searchKeys);
    fclose(output);
    freeTree(rootNode);
    return 0;
}