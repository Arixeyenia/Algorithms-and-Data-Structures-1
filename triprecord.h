//Record structure with all the fields in each row of the data inserted
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

//Create a record from the input
void createRecord(struct record *tripRecord, char *data, int col);

//Print the records that were found from the search
void printResults(struct record **results, int search, char *keys, int *counter, int *noOfResults, FILE *output);

//Free memory for the record
void freeRecord(struct record *tripRecord);