#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define NULL_BYTE_CHAR 1
#define SEARCH_PUDATETIME 0
#define SEARCH_PULOCATIONID 1

struct record{
    char *vendorID;
    char *passengerCount;
    char *tripDistance;
    char *rateCodeID;
    char *strAndFwdFlag;
    char *puLocationID;
    char *doLocationID;
    char *paymentType;
    char *fareAmount;
    char *extra;
    char *mtaTax;
    char *tipAmount;
    char *tollsAmount;
    char *improvementSurcharge;
    char *totalAmount;
    char *puDateTime;
    char *doDateTime;
    char *tripDuration;
};

void createRecord(struct record *tripRecord, char *data, int col){
    switch(col){
        case 0:
            tripRecord->vendorID = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->vendorID, data);
            break;
        case 1:
            tripRecord->passengerCount = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->passengerCount, data);
            break;
        case 2:
            tripRecord->tripDistance = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->tripDistance, data);
            break;
        case 3:
            tripRecord->rateCodeID = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->rateCodeID, data);
            break;
        case 4:
            tripRecord->strAndFwdFlag = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->strAndFwdFlag, data);
            break;
        case 5:
            tripRecord->puLocationID = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->puLocationID, data);
            break;
        case 6:
            tripRecord->doLocationID = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->doLocationID, data);
            break;
        case 7:
            tripRecord->paymentType = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->paymentType, data);
            break;
        case 8:
            tripRecord->fareAmount = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->fareAmount, data);
            break;
        case 9:
            tripRecord->extra = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->extra, data);
            break;
        case 10:
            tripRecord->mtaTax = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->mtaTax, data);
            break;
        case 11:
            tripRecord->tipAmount = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->tipAmount, data);
            break;
        case 12:
            tripRecord->tollsAmount = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->tollsAmount, data);
            break;
        case 13:
            tripRecord->improvementSurcharge = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->improvementSurcharge, data);
            break;
        case 14:
            tripRecord->totalAmount = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->totalAmount, data);
            break;
        case 15:
            tripRecord->puDateTime = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->puDateTime, data);
            break;
        case 16:
            tripRecord->doDateTime = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->doDateTime, data);
            break;
        case 17:
            tripRecord->tripDuration = malloc((sizeof(char) * strlen(data)) + NULL_BYTE_CHAR);
            strcpy(tripRecord->tripDuration, data);
            break;
        default:
            printf("Invalid column");
            return;
            break;
    }
}

/*print the results to output file*/
void printResults(struct record **results, int search, char *keys, int *counter, int *noOfResults, FILE *output){
    
    printf("\n%s --> %d\n", keys, *counter);
    
    if(results){
        if(search == SEARCH_PUDATETIME){
            for(int i = 0; i < *noOfResults; i++){
                results[i]->tripDuration[strcspn(results[i]->tripDuration, "\n")] = 0;
                fprintf(output, "%s --> VendorID: %s || passenger_count: %s || trip_distance: %s || "
                        "RatecodeID: %s || store_and_fwd_flag: %s || PULocationID: %s || "
                        "DOLocationID: %s || payment_type: %s || fare_amount: %s || extra: %s || "
                        "mta_tax: %s || tip_amount: %s || tolls_amount: %s || improvement_surcharge: %s || "
                        "total_amount: %s || DOdatetime: %s || trip_duration: %s ||\n", keys,
                        results[i]->vendorID, results[i]->passengerCount, results[i]->tripDistance, 
                        results[i]->rateCodeID, results[i]->strAndFwdFlag, results[i]->puLocationID,
                        results[i]->doLocationID, results[i]->paymentType, results[i]->fareAmount, results[i]->extra,
                        results[i]->mtaTax, results[i]->tipAmount, results[i]->tollsAmount, results[i]->improvementSurcharge,
                        results[i]->totalAmount, results[i]->doDateTime, results[i]->tripDuration);
            }
        }
        else if(search == SEARCH_PULOCATIONID){
            
            for(int i = 0; i < *noOfResults; i++){
                results[i]->tripDuration[strcspn(results[i]->tripDuration, "\n")] = 0;
                fprintf(output, "%s --> %s\n", keys, results[i]->puDateTime);
            }
        }    
    }
    else{
        fprintf(output, "%s --> NOTFOUND\n", keys);
    }
}

void freeRecord(struct record *tripRecord){
    free(tripRecord->vendorID);
    tripRecord->vendorID = NULL;
    
    free(tripRecord->passengerCount);
    tripRecord->passengerCount = NULL;
    
    free(tripRecord->tripDistance);
    tripRecord->tripDistance = NULL;
    
    free(tripRecord->rateCodeID);
    tripRecord->rateCodeID = NULL;
    
    free(tripRecord->strAndFwdFlag);
    tripRecord->strAndFwdFlag = NULL;
    
    free(tripRecord->puLocationID);
    tripRecord->puLocationID = NULL;
    
    free(tripRecord->doLocationID);
    tripRecord->doLocationID = NULL;
    
    free(tripRecord->paymentType);
    tripRecord->paymentType = NULL;
    
    free(tripRecord->fareAmount);
    tripRecord->fareAmount = NULL;
    
    free(tripRecord->extra);
    tripRecord->extra = NULL;
    
    free(tripRecord->mtaTax);
    tripRecord->mtaTax = NULL;
    
    free(tripRecord->tipAmount);
    tripRecord->tipAmount = NULL;
    
    free(tripRecord->tollsAmount);
    tripRecord->tollsAmount = NULL;
    
    free(tripRecord->improvementSurcharge);
    tripRecord->improvementSurcharge = NULL;
    
    free(tripRecord->totalAmount);
    tripRecord->totalAmount = NULL;
    
    free(tripRecord->puDateTime);
    tripRecord->puDateTime = NULL;
    
    free(tripRecord->doDateTime);
    tripRecord->doDateTime = NULL;
    
    free(tripRecord->tripDuration);
    tripRecord->tripDuration = NULL;
}