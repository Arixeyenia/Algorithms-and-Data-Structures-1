//Node in linked list
struct LinkedList;

//Insert record into linked list, returns the ndoe
struct LinkedList *linkedListInsert(struct LinkedList *parent, struct record *tripRecord);

//Search in linked list for the specific search key
struct record **linkedListSearch(struct LinkedList *parent, int search, char *keys, struct record **results, int *counter, int *noOfResults);

//free memory in linked list
void freeLinkedList(struct LinkedList *parent);